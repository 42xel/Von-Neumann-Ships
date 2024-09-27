# design tenets

quirky (Subleq)
What's good about quirkiness is that it levels the playing fields. It makes things interesting for the seasoned players while not alienating newcomers.

Very good for reach, as well as for making these kind of games games and not work.

hacky (Baba is You)
Hackiness pushes our limits, in a creative, puzzle solving way. It is lot more discriminating IMO than other criterions: I believe anyone could eventuallly finish even hard zach-like, but Baba is You has some seemingly impossible levels. In fact, all level except a few tutorial ones are designed to feel impossible. And for me, many are.
But it also leads to out of the box thinking in a much more satisfying way than quirkiness.
For this particular games about self modifying codes, hackyness potential is very high, though not necessarilly easy to tap into.

Very good for puzzle games.

complex (Dwarf fortess)
Complexity is a goal in an of itself for me. It greatly extends replayability and pushes our minds to the limits, in a creative, builder way.

Very good for sandboxes.

Zachtronics :
very quirky
moderately hacky
moderately to very complex

This game is pretty much a Zach-like, so comparison is very relevant.
Zachtronics games are very quirky and I think that, along an extremely high quality polish, including easy learning curve and instant feedback, is what makes their appeal. Each entry is accessible and refreshing, while still having endgame levels that are extremely hard but always doable.

That quirkiness gets in the way of complexity and sandbox relayability IMO (it's ok, they can't have it all).

goal :
moderately quirky
very hacky
very complex

Quirkiness won't be a goal of mine, the constraints should make the game quirky enough. I make this game mostly for myself, and I'm very interested in complex things, so I'd rather not have quirkiness in the way.

## Why LPEG ?
Serious contenders for complex parsing are:
- existing parsers (relevant for me here: tree-sitter for C toolchain shenanigans, and custom-am)
- ANTLR
- LPEG
- Perl recursive regexp. They're excellent, but they're only as good as you can make a bad idea work.

Grammar when necessary. Composition over substitution. Few common programming idoms over bajillions metacharacters and escape sequences.

I don't know ANTLR, I know LPEG, ...

## Why natural indentation ?
https://gist.github.com/42xel/fa707fc51ca0e9ff1820a3ae297a9bf3

If you delved into the code, you'll see that I am not using the usual reversed recursive indentation. If you want to contribute to this project, use whatever style you like, I'll have my ways to format your code --- and I'm assuming you have yours to format mine. I'm fully open to change to something people are more used to if this becomes more than a personal project.

## Indentation
The specific rules for indentations I follow are as such :
- functions are indented thrice
- loops are indented twice
- conditions are indented once
- following an end of block (`}`) indentation strictly increases (so as to materialise the end of block)
- a paragraph indentation may be used to separate blocks which do not start with a function, loop or condition.

## Style
I prefer loop and conditional blocks which do a single job. It reduces nesting. It also opens up the possibility to go brace-less, using the comma operator if needed. For similar reasons, I strongly favor the return early pattern. Combined with brace-less and comma, I prefer to put the return keyword in the same line as the if when possible.

Because I have pragraph style indentation available, I don't use line-breaks to separate chunks of codes, other than to separate top level items. I haven't felt the need to do so yet though, as C is a language with little boiler plate, so using typography to more easily navigate through noise is less of a necessity.

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

