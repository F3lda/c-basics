# C programming - get line/string from file/stdin

NOTES:
1. In C programming there isn't any data type `String` but we have just `an Array of Chars` ended by terminating char `'\0'`
2.  `STDIN` = (short for `standard input`) is a pointer to a `FILE`

## Reading STDIN stream (user input from command line)
1. Char by char
-- `fgetc(stdin); scanf("%c"); fscanf(stdin, "%c"); getc(stdin); getchar(); fgetchar();`

2. Using buffer - reads all chars at once or until newline char is read/reached
-- `fgets(buffer, 20, stdin)` - reads also newline char if reached
-- `fscanf(stdin, "%19[^\n]", buffer)` - doesn't read newline char (stays in STDIN) -> remove by reading using function, for example `fgetc(stdin)`

## NOTES
- function `gets()` is unsafe because you cannot limit the number of characters that can be read
- using `scanf()/fscanf()` directly has disadvantage, that when the program encounters unexpected input, the input stream is left in an unknown state where recovery without losing data can be impossible
- `fscanf()` on a regular file can also be fine if the file format skips over newlines like any other white-spaces. For line-oriented data is better to use `fgets()` with `sscanf()`
- placing a space before `%` will discard any amount of leading white-spaces (including none) 
-- `scanf(" %32[^\n]s", name);` -> this discards newline char left in STDIN from previous `scanf()`
- do not use a trailing blank in a `scanf()` format string
- `%c, %n, %[]` are format specifiers that do not skip leading white-spaces
- `%n` format specifier assign the number of characters printed or scanned by functions `printf()/scanf()` until it occurs
- Standard white-space characters are:
```c
		' '  (0x20) space (SPC)
		'\t' (0x09) horizontal tab (TAB)
		'\n' (0x0a) newline (LF)
		'\v' (0x0b) vertical tab (VT)
		'\f' (0x0c) feed (FF)
		'\r' (0x0d) carriage return (CR)
```

- use `isspace()` standard library function if you want to check for any of these white-spaces
- in text mode, the native newline sequence is translated to `'\n'`
- never use `fflush(stdin);` or similar functions to clear STDIN buffer -> the only way to clear unread input is by reading it! -> `fflush(stream);` is only for output streams!
### Links
- http://www.sekrit.de/webdocs/c/beginners-guide-away-from-scanf.html

- https://stackoverflow.com/questions/5240789/scanf-leaves-the-newline-character-in-the-buffer

## Parsing string
After reading input you can parse it with `sscanf();` function:
```c
int day, year;
char  month[20] = {0}, stemp[100];
strcpy(stemp, "November 17 1989");
sscanf(stemp, "%19s  %d  %d", month, &day, &year);
printf("%d  %s  %d\n", year, month, day);
```
