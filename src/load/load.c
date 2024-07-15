#include "../prelude.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char help[] = "\
loads a binary into a struct representing the data\
Usage:\nload <binary> [<input> [<output>]]\n";

            fn char load_file
(const char *__restrict filename, signed char buffer[81]) {
if (filename == NULL) return memset(buffer, 0, 81), 0;
FILE* file = fopen(filename, "rb");
    if (file == NULL) return
fprintf(stderr, "Error: Could not open file %s\n", filename), _ERR_IO;
    size_t bytesRead = fread(buffer, sizeof(signed char), 81, file);
    if (fgetc(file) != EOF) return
fprintf(stderr, "Error: File %s is larger than 81 bytes.\n", filename),
fclose(file), _ERR_OTHER;
    if (bytesRead < 81)
fprintf(stderr, "Warning: File %s is smaller than 81 bytes. \
Remaining buffer filled with zeroes.\n", filename);
    memset(buffer + bytesRead, 0, 81 - bytesRead);
fclose(file);
return 0;} // todo unit test ?
// todo change that when multi-agents
            fn result load (
const char* __restrict program
, const char* __restrict input
, const char* __restrict output
, signed char tape[243]
) { result err; return
(err = load_file(program, tape + 81)) ? err :
(err = load_file(input, tape)) ? err :
(err = load_file(output, tape + 162)) ? err :
0; }

            fn result save_file
(const char *__restrict filename, const signed char buffer[81]) {
FILE* file = fopen(filename, "wb");
    if (file == NULL) return
fprintf(stderr, "Error: Could not open file %s\n", filename), _ERR_IO;
    fwrite(buffer, sizeof(signed char), 81, file);
fclose(file);
return 0; } // todo unit test ?
// todo change that when multi-agents
            fn result save (
const char* __restrict program
, const char* __restrict input
, const char* __restrict output
, const signed char tape[243]
) { result err; return
(err = save_file(program == NULL ? "0.out" : program, tape + 81)) ? err :
(err = save_file(input == NULL ? "i.out" : input, tape)) ? err :
(err = save_file(output == NULL ? "1.out" : output, tape + 162)) ? err :
0; }

            fn result test_single () { result err;
signed char tape[243];
for (unsigned char i = 0; i < 243; ++i) tape [i] = rand() % 243 - 121;
char* __restrict prog;
if ((err = save(NULL, NULL, NULL, tape))) return err;
signed char tape2[243];
if ((err = load("0.out", "i.out", "1.out", tape2))) return err;
if (memcmp(tape, tape2, 243)) return _ERR_OTHER;
if ((err = remove("0.out"))) return err;
if ((err = remove("i.out"))) return err;
if ((err = remove("1.out"))) return err;
printf("test_single ok\n");
return err; }
            fn result test_multiple () { result err;
for (char i = 0; i++ < 10 && !(err = test_single()););
return err;}
            fn result main (int argc, char **argv) {
result err; return
(err = test_multiple()) ? err :
0; }
