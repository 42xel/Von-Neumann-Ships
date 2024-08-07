#include "src/prelude.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "load.h"
#include "../ternary_logic.h"


/// An alias to signify a 243 cells centered array
pub typedef signed char* Tape;

            pub fn result load_file
(const char *__restrict filename, Cell buffer[81]) {
if (filename == NULL) return memset(buffer, 0, 81), 0;
FILE* file = fopen(filename, "rb");
    if (file == NULL) return
fprintf(stderr, "Error: Could not open file %s\n", filename), _ERR_IO;
    size_t bytesRead = fread(buffer, sizeof(Cell), 81, file);
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
            pub fn result load (
  const char* __restrict program
, const char* __restrict input
, const char* __restrict output
, Tape tape
) { result err; return
(err = load_file(input,   tape - 121)) ? err :
(err = load_file(program, tape - 40 )) ? err :
(err = load_file(output,  tape + 41 )) ? err :
0; }

            pub fn result save_file
(const char *__restrict filename, const Cell buffer[81]) {
FILE* file = fopen(filename, "wb");
    if (file == NULL) return
fprintf(stderr, "Error: Could not open file %s\n", filename), _ERR_IO;
    fwrite(buffer, sizeof(Cell), 81, file);
fclose(file);
return 0; } // todo unit test ?
// todo change that when multi-agents
            pub fn result save (
  const char* __restrict program
, const char* __restrict input
, const char* __restrict output
, const Tape tape
) { result err; return
(err = save_file(input   == NULL ? "i.out" : input,   tape -121)) ? err :
(err = save_file(program == NULL ? "o.out" : program, tape -40 )) ? err :
(err = save_file(output  == NULL ? "l.out" : output,  tape + 41)) ? err :
0; }

            fn result _test_single () { result err;
Cell _tape[243]; Tape tape = _tape + 121;
for (Cell i = -121; i != 122; ++i) tape [i] = rand243();
char* __restrict prog;
if ((err = save(NULL, NULL, NULL, tape))) return err;
Cell _tape2[243]; Tape tape2 = _tape2 + 121;
if ((err = load("o.out", "i.out", "l.out", tape2))) return err;
if (memcmp(_tape, _tape2, 243)) return _ERR_OTHER;
// Remove même si pb? or not, it's somewhat precious
if ((err = remove("o.out"))) return err;
if ((err = remove("i.out"))) return err;
if ((err = remove("l.out"))) return err;
return err; }
            fn result test_multiple () { result err;
for (char i = 0; i++ < 72 && !(err = _test_single()););
return err;}

