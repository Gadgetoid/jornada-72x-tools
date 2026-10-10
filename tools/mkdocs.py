import argparse
import glob
import os
import re
import sys

import mkheaders

ROOT = mkheaders.ROOT
QUALIFIERS = {"const", "CONST", "volatile", "struct", "union", "enum", "IN", "OUT", "OPTIONAL"}
BASIC_TYPES = {"void", "char", "short", "int", "long", "unsigned", "signed", "float", "double", "_Bool"}
ENTRY = re.compile(r"^## (\w+)(?:\((.*)\))?\s*$")


def read_entries():
    entries = {}
    for path in sorted(glob.glob(os.path.join(ROOT, "docs", "api", "*.txt"))):
        current = None
        for line in open(path, encoding="utf-8"):
            match = ENTRY.match(line)
            if match:
                name, parameters = match.groups()
                names = [word.strip() for word in parameters.split(",")] if parameters else []
                current = entries[name] = {"parameters": [word for word in names if word], "body": [], "source": path}
            elif current is not None:
                current["body"].append(line.rstrip())
    for entry in entries.values():
        while entry["body"] and not entry["body"][-1]:
            entry["body"].pop()
        while entry["body"] and not entry["body"][0]:
            entry["body"].pop(0)
    return entries


def docstring(entry, note):
    body = [line.replace("*/", "* /") for line in entry["body"]]
    if note:
        body += ["", "@note %s" % note]
    return "/**\n" + "".join((" * %s\n" % line) if line else " *\n" for line in body) + " */\n"


def statement_start(text, position):
    start = text.rfind("\n", 0, position) + 1
    while start > 0:
        previous_start = text.rfind("\n", 0, start - 1) + 1
        previous = text[previous_start:start - 1].strip()
        if not previous or previous.startswith("#") or previous.endswith((";", "}", "{", "*/", "\\")) or in_macro(text, previous_start):
            break
        start = previous_start
    return start


def strip_docstring(text, start):
    before = text[:start]
    match = re.search(r"/\*\*(?:(?!\*/).)*\*/\n$", before, re.S)
    if match:
        return before[:match.start()], text[start:]
    return before, text[start:]


def split_parameters(text):
    parts = []
    depth = 0
    current = ""
    for character in text:
        if character == "," and depth == 0:
            parts.append(current)
            current = ""
            continue
        depth += character in "(["
        depth -= character in ")]"
        current += character
    parts.append(current)
    return parts


def is_named(parameter):
    tokens = []
    for word in re.findall(r"[A-Za-z_]\w*", re.sub(r"\[[^\]]*\]", "", parameter)):
        if word in QUALIFIERS:
            continue
        if word in BASIC_TYPES and tokens and tokens[-1] in BASIC_TYPES:
            continue
        tokens.append(word)
    return len(tokens) >= 2


def name_parameters(text, open_paren, names):
    depth = 0
    for index in range(open_paren, len(text)):
        if text[index] == "(":
            depth += 1
        elif text[index] == ")":
            depth -= 1
            if depth == 0:
                close_paren = index
                break
    else:
        return text, "no closing parenthesis"
    parameters = split_parameters(text[open_paren + 1:close_paren])
    stripped = [parameter.strip() for parameter in parameters]
    if stripped in (["void"], [""]):
        return text, None if not names else "declared without parameters"
    if stripped and stripped[-1] == "...":
        parameters = parameters[:-1]
        stripped = stripped[:-1]
    if len(parameters) != len(names):
        return text, "declares %d parameters, docs name %d" % (len(parameters), len(names))
    rewritten = []
    for parameter, name in zip(parameters, names):
        if "(" in parameter or is_named(parameter):
            rewritten.append(parameter)
            continue
        array = re.search(r"(\s*\[[^\]]*\])\s*$", parameter)
        if array:
            rewritten.append(parameter[:array.start()].rstrip() + " " + name + array.group(1))
        else:
            spacing = "" if parameter.rstrip().endswith("*") else " "
            rewritten.append(parameter.rstrip() + spacing + name)
    remainder = text[open_paren + 1 + len(",".join(parameters)):close_paren]
    return text[:open_paren + 1] + ",".join(rewritten) + remainder + text[close_paren:], None


def in_macro(text, line_start):
    while line_start > 0:
        previous_start = text.rfind("\n", 0, line_start - 1) + 1
        if not text[previous_start:line_start - 1].rstrip().endswith("\\"):
            return False
        if text[previous_start:line_start].lstrip().startswith("#"):
            return True
        line_start = previous_start
    return False


def declaration(text, name):
    pattern = r"\b_WNAME\(%s\)\s*\(|\b%s\s*\(" % (re.escape(name), re.escape(name))
    for match in re.finditer(pattern, text):
        line_start = text.rfind("\n", 0, match.start()) + 1
        if in_macro(text, line_start):
            continue
        line = text[line_start:match.start()]
        if line.lstrip().startswith(("#", "/", "*")) or re.search(r"[=;]", line) or "__typeof__" in line:
            continue
        end = text.find(";", match.end())
        if end < 0 or "{" in text[match.end():end]:
            continue
        return match.start(), match.end() - 1
    return None


def find_declaration(texts, name):
    for path, text in texts.items():
        found = declaration(text, name)
        if found:
            return path, found
    return None, None


def apply(entries):
    paths = mkheaders.header_paths() + sorted(glob.glob(os.path.join(ROOT, "include", "jornada", "sdk", "*.h")))
    texts = {path: open(path, errors="replace").read() for path in paths}
    changed = set()
    problems = []
    for name in sorted(entries):
        entry = entries[name]
        path, found = find_declaration(texts, name)
        if not found:
            problems.append("%s: not declared" % name)
            continue
        text = texts[path]
        name_start, open_paren = found
        if entry["parameters"]:
            text, problem = name_parameters(text, open_paren, entry["parameters"])
            if problem:
                problems.append("%s: %s" % (name, problem))
        comment = docstring(entry, None)
        before, after = strip_docstring(text, statement_start(text, name_start))
        text = before + comment + after
        if name.endswith("W"):
            macro = re.search(r"^[ \t]*#[ \t]*define[ \t]+%s[ \t]+%s[ \t]*$" % (re.escape(name[:-1]), re.escape(name)), text, re.M)
            if macro:
                before, after = strip_docstring(text, macro.start())
                text = before + comment + after
        texts[path] = text
        changed.add(path)
    for path in changed:
        with open(path, "w") as output:
            output.write(texts[path])
    return problems


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Write docstrings from docs/api into the headers, and name the documented functions' parameters")
    parser.parse_args()
    entries = read_entries()
    problems = apply(entries)
    for problem in problems:
        print("mkdocs: %s" % problem, file=sys.stderr)
    print("mkdocs: %d functions documented, %d problems" % (len(entries), len(problems)))
