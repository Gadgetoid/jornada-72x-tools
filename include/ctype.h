#ifndef JORNADA_CTYPE_H
#define JORNADA_CTYPE_H

#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Tests whether a character has the specified classification property.
 *
 * The result is independent of locale.
 *
 * @param character Integer character to test.
 * @param type Classification property to test.
 * @return Nonzero if the character has the property, or 0 otherwise.
 */
int _isctype(int character, int type);
int tolower(int character);
int toupper(int character);
int isalnum(int character);
int isalpha(int character);
int iscntrl(int character);
int isdigit(int character);
int isgraph(int character);
int islower(int character);
int isprint(int character);
int ispunct(int character);
int isspace(int character);
int isupper(int character);
int isxdigit(int character);
int isblank(int character);

#define isalpha(character) _isctype(character, _ALPHA)
#define isupper(character) _isctype(character, _UPPER)
#define islower(character) _isctype(character, _LOWER)
#define isdigit(character) _isctype(character, _DIGIT)
#define isxdigit(character) _isctype(character, _HEX)
#define isspace(character) _isctype(character, _SPACE)
#define ispunct(character) _isctype(character, _PUNCT)
#define isalnum(character) _isctype(character, _ALPHA | _DIGIT)
#define isprint(character) _isctype(character, _BLANK | _PUNCT | _ALPHA | _DIGIT)
#define isgraph(character) _isctype(character, _PUNCT | _ALPHA | _DIGIT)
#define iscntrl(character) _isctype(character, _CONTROL)
#define isascii(character) ((unsigned)(character) < 0x80)
#define iswascii(character) ((unsigned)(character) < 0x80)

#ifdef __cplusplus
}
#endif

#endif
