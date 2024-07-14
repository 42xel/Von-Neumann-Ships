quirky (Subleq)
hacky (Baba is You)
complex (Dwarf fortess)

Zach-like :
very quirky
moderately hacky
moderately to very complex

goal
moderately quirky
very hacky
very complex

# FAQ
## Why natural indentation ?
If you delved into the code, you'll see that I am not using the usual reversed recursive indentation. If you want to contribute to this project, use whatever style you like, I'll have my ways to format your code --- and I'm assuming you have yours to format mine. I'm fully open to change to something people are more used to if this becomes more than a personal project.

But first, what are natural indentation, and recursive indentation ?

Common scriptures (ancient, word, PDF, markdown, ...) use natural indentation, where the bulk of the text is not indented, and important info are indented. For example, titles will be centered, subtitles will be indented, as well as the beginnign of every paragraph.

Most programming scriptures (code) use reversed recursive indentation. Information is hierarchised in a tree-like structure, and indentation materializes nesting.

Here is a list of there respective merits :
- Recursive indentation allows for arbitrarily long nesting, which are simply impossible with its natural counterpart. Since deep nesting is evil, this is a point for natural indentation.
- Natural indentation is much superior for multi-line strings. The leading spaces you get from recursive indentation are about never desirable. Some languages get rid of them for you, but sometimes you do want them. With natural indentation, what you see is what you get for multi-line strings, and they are neither polluted by nor are polluting the indentation.
- Natural indentation lends better toward brace-less styles. Braces are hard to parse with the naked eye, and require to use a ruler to see blocks. Fortunately, most code editor nowadays have these rulers integrated. This is a great solution to a non-issue, as brace-less style, natural or recursive (but natural more so), are legible without the need of rulers.
- Brace-less style waste less lines without sacrificing anything on readability. Recursive braceless (a la Python) are better than natural brace-less on this point.
- Natural indentation can use paragraph indentation to separate ideas, where recursive style would prefer line skip, and Python with its coding white-spaces would require line skip.
- Natural indentation structure is limited, static. It's much easier to write a linter for, and after some getting used to, easier to navigate.

Since I sometimes work on this project from my phone, using termux and raw kakoune. It means two things :
- I have limited screen real estate, and needed a space efficient indentation style;
- I don't have automatic indentation.

## Indentation
The specific rules for indentations I follow are as such :
- functions are indented thrice
- loops are indented twice
- conditions are indented once
- following an end of block (`}`) indentation strictly increases (so as to materialise the end of block)
- a paragraph indentation may be used to separate blocks which do not start with a function, loop or condition.

## Style
I prefer loop and conditional blocks which do a single job. It reduces nesting. It also opens up the possibility to go brace-less, using the comma operator if needed. For similar reasons, I strongly favor the return early pattern. Combined with brace-less and comma, I prefer to put the return keyword in the same line as the if when possible.

Example 1:
```C
void init_tables() {
    if (!_init) {
        unsigned short* trit = TRIT;
        signed char* bin = BIN;
        for (signed char i = -121; i <= +121; ++i) {
            unsigned short t = to_ltrit(i);
            trit[i] = t;
            bin[t] = i;
        }
        _init = 1;
    }
}
```
becomes :
```C
            void init_tables() {
    if (_init) return;
unsigned short* trit = TRIT;
signed char* bin = BIN;
        for (signed char i = -121; i <= +121; ++i) {
unsigned short t = to_ltrit(i);
trit[i] = t;
bin[t] = i;
}
    _init = 1;}
```

example 2:
```C
signed char load_file
(const char *__restrict filename, signed char buffer[81]) {
    if (filename == NULL) {
        memset(buffer, 0, 81);
        return 0;
    }
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return 1;
    }
    size_t bytesRead = fread(buffer, sizeof(signed char), 81, file);
    if (fgetc(file) != EOF) {
        fprintf(stderr, "Error: File %s is larger than 81 bytes.\n", filename);
        fclose(file);
        return 2;
    }
    if (bytesRead < 81) {
        fprintf(stderr, "Warning: File %s is smaller than 81 bytes. \
        Remaining buffer filled with zeroes.\n", filename);
        memset(buffer + bytesRead, 0, 81 - bytesRead);
    }
    fclose(file);
    return 0;
}
```
becomes
```C
            signed char load_file
(const char *__restrict filename, signed char buffer[81]) {
    if (filename == NULL) return
memset(buffer, 0, 81), 0;
    FILE* file = fopen(filename, "rb");
    if (file == NULL) return
fprintf(stderr, "Error: Could not open file %s\n", filename), 1;
size_t bytesRead = fread(buffer, sizeof(signed char), 81, file);
    if (fgetc(file) != EOF) return
fprintf(stderr, "Error: File %s is larger than 81 bytes.\n", filename),
fclose(file), 2;
    if (bytesRead < 81)
fprintf(stderr, "Warning: File %s is smaller than 81 bytes. \
Remaining buffer filled with zeroes.\n", filename);
    memset(buffer + bytesRead, 0, 81 - bytesRead);
fclose(file);
return 0;
}
```
