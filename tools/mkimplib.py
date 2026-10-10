import argparse
import re

IDENTIFIER = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")


def import_slot(function, dll):
    return f"""    .section .iat.{dll}.{function},"aw",%progbits
    .balign 4
    .weak __imp_{function}
    .weak "__jornada_import${dll}${function}"
__imp_{function}:
"__jornada_import${dll}${function}":
    .long 0

"""


def arm_stub(function, dll):
    return f"""    .section .text.{function},"ax",%progbits
    .balign 4
    .weak {function}
    .type {function},%function
{function}:
    ldr ip, .Lslot_{function}
    ldr pc, [ip]
.Lslot_{function}:
    .long __imp_{function}

""" + import_slot(function, dll)


def generate(functions, dll):
    return "\n".join(["    .arm", ""] + [arm_stub(function, dll) for function in functions])


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate an import library for a Windows CE DLL from its export list")
    parser.add_argument("exports")
    parser.add_argument("dll")
    parser.add_argument("output")
    arguments = parser.parse_args()
    functions = []
    for line in open(arguments.exports):
        name = line.strip()
        if IDENTIFIER.match(name) and name not in functions:
            functions.append(name)
    with open(arguments.output, "w") as output:
        output.write(generate(functions, arguments.dll))
