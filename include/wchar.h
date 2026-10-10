#ifndef JORNADA_WCHAR_H
#define JORNADA_WCHAR_H

#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef JORNADA_WINT_T
#define JORNADA_WINT_T
typedef unsigned short wint_t;
typedef unsigned short wctype_t;
#endif

#define WEOF ((wint_t)0xFFFF)

#ifndef _FILE_DEFINED
typedef void FILE;
#define _FILE_DEFINED
#endif

#ifndef _MBSTATE_T_DEFINED
#define _MBSTATE_T_DEFINED
typedef struct {
    unsigned state;
} mbstate_t;
#endif

#define _UPPER 0x0001
#define _LOWER 0x0002
#define _DIGIT 0x0004
#define _SPACE 0x0008
#define _PUNCT 0x0010
#define _CONTROL 0x0020
#define _BLANK 0x0040
#define _HEX 0x0080
#define _ALPHA (0x0100 | _UPPER | _LOWER)

/**
 * Returns the length of a string in characters.
 *
 * @param string The string.
 * @return Number of characters, not counting the terminating null.
 */
size_t wcslen(const wchar_t *string);
/**
 * Copies source to destination, including its terminating null character.
 *
 * The destination must have enough room. Overlapping strings have
 * undefined behavior.
 *
 * @param destination Receives the copy.
 * @param source Null-terminated string to copy.
 * @return destination.
 */
wchar_t *wcscpy(wchar_t *destination, const wchar_t *source);
/**
 * Copies up to count wide characters from source to destination.
 *
 * If source is shorter, destination is padded with null characters.
 * Otherwise no terminator is appended. Overlapping strings have
 * undefined behavior.
 *
 * @param destination Receives the copy.
 * @param source String to copy.
 * @param count Number of characters to copy.
 * @return destination.
 */
wchar_t *wcsncpy(wchar_t *destination, const wchar_t *source, size_t count);
/**
 * Appends source to destination, including the terminating null character.
 *
 * The destination must have enough room. Overlapping strings have
 * undefined behavior.
 *
 * @param destination Null-terminated string to extend.
 * @param source Null-terminated string to append.
 * @return destination.
 */
wchar_t *wcscat(wchar_t *destination, const wchar_t *source);
/**
 * Appends at most count wide characters and terminates destination.
 *
 * Appending stops sooner if source ends. Overlapping strings have
 * undefined behavior.
 *
 * @param destination Null-terminated string to extend.
 * @param source Null-terminated string to append.
 * @param count Maximum number of characters to append.
 * @return destination.
 */
wchar_t *wcsncat(wchar_t *destination, const wchar_t *source, size_t count);
/**
 * Compares two wide strings lexicographically.
 *
 * The comparison is case-sensitive and is not affected by locale.
 *
 * @param first First null-terminated string.
 * @param second Second null-terminated string.
 * @return Less than, equal to or greater than zero according to the
 *         comparison.
 */
int wcscmp(const wchar_t *first, const wchar_t *second);
/**
 * Compares at most count wide characters lexicographically.
 *
 * The comparison is case-sensitive, is not affected by locale, and stops
 * when either string ends.
 *
 * @param first First string.
 * @param second Second string.
 * @param count Maximum number of characters to compare.
 * @return Less than, equal to or greater than zero according to the
 *         comparison.
 */
int wcsncmp(const wchar_t *first, const wchar_t *second, size_t count);
/**
 * Compares lowercase versions of two wide strings lexicographically.
 *
 * Case conversion can produce unexpected ordering for some characters.
 *
 * @param first First null-terminated string.
 * @param second Second null-terminated string.
 * @return Less than, equal to or greater than zero according to the
 *         comparison.
 */
int _wcsicmp(const wchar_t *first, const wchar_t *second);
/**
 * Compares up to count wide characters without regard to case.
 *
 * Comparison stops at a null character and is not affected by locale.
 *
 * @param first First null-terminated string.
 * @param second Second null-terminated string.
 * @param count Maximum number of characters to compare.
 * @return Less than, equal to or greater than zero according to the
 *         comparison.
 */
int _wcsnicmp(const wchar_t *first, const wchar_t *second, size_t count);
/**
 * Finds the first occurrence of a character in a string.
 *
 * @param string String to search.
 * @param character Character to find. The terminating null can be found.
 * @return Pointer to the character, or NULL if not found.
 */
wchar_t *wcschr(const wchar_t *string, wchar_t character);
/**
 * Finds the last occurrence of character in string.
 *
 * The terminating null character is included in the search.
 *
 * @param string Null-terminated string to search.
 * @param character Wide character to find.
 * @return Pointer to the match, or NULL if none is found.
 */
wchar_t *wcsrchr(const wchar_t *string, wchar_t character);
/**
 * Finds the first occurrence of substring in string.
 *
 * An empty substring returns string.
 *
 * @param string Null-terminated string to search.
 * @param substring Null-terminated string to find.
 * @return Pointer to the match, or NULL if none is found.
 */
wchar_t *wcsstr(const wchar_t *string, const wchar_t *substring);
/**
 * Finds the first character in a string that is in a set.
 *
 * @param string String to search.
 * @param characters Characters to look for.
 * @return Pointer to the first match, or NULL if none.
 */
wchar_t *wcspbrk(const wchar_t *string, const wchar_t *characters);
/**
 * Returns the length of the initial part of a string made only of a set of
 * characters.
 *
 * @param string String to scan.
 * @param characters Characters allowed.
 * @return Index of the first character not in the set.
 */
size_t wcsspn(const wchar_t *string, const wchar_t *characters);
/**
 * Returns the length of the initial part of a string that contains none
 * of a set of characters.
 *
 * @param string String to scan.
 * @param characters Characters to stop at.
 * @return Index of the first character from the set, or the string's
 *         length if there is none.
 */
size_t wcscspn(const wchar_t *string, const wchar_t *characters);
/**
 * Returns the next token separated by wide characters in delimiters.
 *
 * The function replaces delimiters with null characters. Pass NULL as
 * string to continue tokenizing the previous string. It keeps static state;
 * do not interleave tokenization of separate strings.
 *
 * @param string String to tokenize, or NULL to continue.
 * @param delimiters Null-terminated set of delimiter characters.
 * @return Pointer to the next token, or NULL when no tokens remain.
 */
wchar_t *wcstok(wchar_t *string, const wchar_t *delimiters);
/**
 * Duplicates a string into newly allocated memory.
 *
 * Free the copy with free.
 *
 * @param string String to copy.
 * @return The copy, or NULL if out of memory.
 */
wchar_t *_wcsdup(const wchar_t *string);
/**
 * Converts uppercase characters in string to lowercase in place.
 *
 * Conversion follows LC_CTYPE; other characters are unchanged.
 *
 * @param string Null-terminated string to convert.
 * @return string.
 */
wchar_t *_wcslwr(wchar_t *string);
/**
 * Converts lowercase characters in string to uppercase in place.
 *
 * Conversion follows LC_CTYPE; other characters are unchanged.
 *
 * @param string Null-terminated string to convert.
 * @return string.
 */
wchar_t *_wcsupr(wchar_t *string);
/**
 * Reverses the characters in string in place.
 *
 * The terminating null character remains at the end.
 *
 * @param string Null-terminated string to reverse.
 * @return string.
 */
wchar_t *_wcsrev(wchar_t *string);
/**
 * Sets every character of a string to one character.
 *
 * The terminating null is kept.
 *
 * @param string String to change.
 * @param character Character to fill with.
 * @return string.
 */
wchar_t *_wcsset(wchar_t *string, wchar_t character);
/**
 * Sets up to count characters of a string to one character.
 *
 * Stops at the terminating null if that comes first.
 *
 * @param string String to change.
 * @param character Character to fill with.
 * @param count Maximum number of characters to set.
 * @return string.
 */
wchar_t *_wcsnset(wchar_t *string, wchar_t character, size_t count);
/**
 * Tests whether character has the classification property specified by type.
 *
 * The result is independent of locale.
 *
 * @param character Wide character to test.
 * @param type Character-class property.
 * @return Nonzero if the property matches, or 0 otherwise.
 */
int iswctype(wint_t character, wctype_t type);
/**
 * Converts a wide character to lowercase.
 *
 * @param character Character to convert.
 * @return The lowercase character, or character unchanged if it has none.
 */
wchar_t towlower(wchar_t character);
/**
 * Converts a wide character to uppercase.
 *
 * @param character Character to convert.
 * @return The uppercase character, or character unchanged if it has none.
 */
wchar_t towupper(wchar_t character);
/**
 * Formats values into a string buffer, printf style.
 *
 * Supports the same conversions as printf, including floating point. Doesn't
 * check the buffer size: use _snwprintf to limit it.
 *
 * @param buffer Buffer that receives the output. Must be large enough.
 * @param format Format string, followed by the values to format.
 * @return Characters written, not counting the terminating null.
 */
#ifdef JORNADA_C99_SWPRINTF
int __jornada_c99_swprintf(wchar_t *buffer, size_t count, const wchar_t *format, ...);
#define swprintf __jornada_c99_swprintf
#else
/**
 * Formats values into a string buffer, printf style.
 *
 * Supports the same conversions as printf, including floating point. Doesn't
 * check the buffer size: use _snwprintf to limit it.
 *
 * @param buffer Buffer that receives the output. Must be large enough.
 * @param format Format string, followed by the values to format.
 * @return Characters written, not counting the terminating null.
 */
int swprintf(wchar_t *buffer, const wchar_t *format, ...);
#endif
/**
 * Formats values from a va_list into a string buffer, printf style.
 *
 * The va_list form of swprintf.
 *
 * @param buffer Buffer that receives the output. Must be large enough.
 * @param format Format string.
 * @param arguments Values to format, from va_start.
 * @return Characters written, not counting the terminating null.
 */
int vswprintf(wchar_t *buffer, const wchar_t *format, va_list arguments);
int _snwprintf(wchar_t *buffer, size_t count, const wchar_t *format, ...);
/**
 * Formats wide-character output into a buffer using a va_list.
 *
 * @param buffer Receives the formatted output.
 * @param count Maximum number of wide characters to write.
 * @param format Wide-character format string.
 * @param arguments Argument list.
 * @return Number of wide characters written excluding the terminator, or
 *         a negative value on error.
 */
int _vsnwprintf(wchar_t *buffer, size_t count, const wchar_t *format, va_list arguments);
/**
 * Reads and converts formatted wide-character input from a string.
 *
 * Each optional argument must point to a value of the type required by its
 * format specifier. Overlapping source and destination strings have
 * undefined behavior.
 *
 * @param string Wide-character input string.
 * @param format Wide-character format-control string.
 * @return Number of fields assigned, 0 if none were assigned, or EOF if
 *         an error or end of string occurs before the first conversion.
 */
int swscanf(const wchar_t *string, const wchar_t *format, ...);
/**
 * Converts the initial numeric portion of a wide string to double precision.
 *
 * The radix character follows LC_NUMERIC. end receives the first
 * unrecognized character, or string if no conversion is possible.
 *
 * @param string Null-terminated wide number string.
 * @param end Receives the stopping character, or NULL if not needed.
 * @return Converted value, signed HUGE_VAL on overflow, or 0 if no
 *         conversion is possible or underflow occurs.
 */
double wcstod(const wchar_t *string, wchar_t **end);
/**
 * Converts the initial portion of a wide string to a long integer in base.
 *
 * Parsing stops at the first invalid digit. end receives that position, or
 * string if no conversion is possible. base must be 0 or from 2 through 36.
 * Overflow or underflow sets errno to ERANGE.
 *
 * @param string Null-terminated wide number string.
 * @param end Receives the stopping character, or NULL if not needed.
 * @param base Number base; 0 selects it from the input prefix.
 * @return Converted value, LONG_MAX or LONG_MIN on overflow, or 0 if no
 *         conversion is possible.
 */
long wcstol(const wchar_t *string, wchar_t **end, int base);
/**
 * Converts the initial portion of a wide string to an unsigned long in base.
 *
 * Parsing stops at the first invalid digit. end receives that position, or
 * string if no conversion is possible. base must be 0 or from 2 through 36.
 *
 * @param string Null-terminated wide number string.
 * @param end Receives the stopping character, or NULL if not needed.
 * @param base Number base; 0 selects it from the input prefix.
 * @return Converted value, ULONG_MAX on overflow, or 0 if no conversion
 *         is possible.
 */
unsigned long wcstoul(const wchar_t *string, wchar_t **end, int base);
/**
 * Converts an integer to a null-terminated wide string in the given base.
 *
 * radix must be from 2 through 36. Negative values get a minus sign only
 * in base 10.
 *
 * @param value Integer to convert.
 * @param buffer Receives the result.
 * @param radix Number base.
 * @return buffer.
 */
wchar_t *_itow(int value, wchar_t *buffer, int radix);
/**
 * Converts a long integer to a null-terminated wide string in the given base.
 *
 * radix must be from 2 through 36. Negative values get a minus sign only
 * in base 10.
 *
 * @param value Long integer to convert.
 * @param buffer Receives the result.
 * @param radix Number base.
 * @return buffer.
 */
wchar_t *_ltow(long value, wchar_t *buffer, int radix);
/**
 * Converts an unsigned long to a null-terminated wide string in the given base.
 *
 * radix must be from 2 through 36. No overflow checking is performed.
 *
 * @param value Unsigned long to convert.
 * @param buffer Receives the result.
 * @param radix Number base.
 * @return buffer.
 */
wchar_t *_ultow(unsigned long value, wchar_t *buffer, int radix);
wchar_t *wmemchr(const wchar_t *memory, wchar_t value, size_t count);
int wmemcmp(const wchar_t *first, const wchar_t *second, size_t count);
wchar_t *wmemcpy(wchar_t *destination, const wchar_t *source, size_t count);
wchar_t *wmemmove(wchar_t *destination, const wchar_t *source, size_t count);
wchar_t *wmemset(wchar_t *destination, wchar_t value, size_t count);
long long wcstoll(const wchar_t *string, wchar_t **end, int base);
unsigned long long wcstoull(const wchar_t *string, wchar_t **end, int base);
float wcstof(const wchar_t *string, wchar_t **end);
long double wcstold(const wchar_t *string, wchar_t **end);

int iswalnum(wint_t character);
int iswalpha(wint_t character);
int iswcntrl(wint_t character);
int iswdigit(wint_t character);
int iswgraph(wint_t character);
int iswlower(wint_t character);
int iswprint(wint_t character);
int iswpunct(wint_t character);
int iswspace(wint_t character);
int iswupper(wint_t character);
int iswxdigit(wint_t character);
int iswblank(wint_t character);

#define iswalpha(character) iswctype(character, _ALPHA)
#define iswupper(character) iswctype(character, _UPPER)
#define iswlower(character) iswctype(character, _LOWER)
#define iswdigit(character) iswctype(character, _DIGIT)
#define iswxdigit(character) iswctype(character, _HEX)
#define iswspace(character) iswctype(character, _SPACE)
#define iswpunct(character) iswctype(character, _PUNCT)
#define iswalnum(character) iswctype(character, _ALPHA | _DIGIT)
#define iswprint(character) iswctype(character, _BLANK | _PUNCT | _ALPHA | _DIGIT)
#define iswgraph(character) iswctype(character, _PUNCT | _ALPHA | _DIGIT)
#define iswcntrl(character) iswctype(character, _CONTROL)

#ifdef __cplusplus
}
#endif

#endif
