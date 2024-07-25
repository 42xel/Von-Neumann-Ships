#include "../prelude.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>

    fn result load_file
(const char *__restrict filename, signed char buffer[81]);
    fn result load(
const char* __restrict program
, const char* __restrict input
, const char* __restrict output
, signed char tape[243]
);
    fn result save_file
(const char *__restrict filename, const signed char buffer[81]);
    fn result save (
const char* __restrict program
, const char* __restrict input
, const char* __restrict output
, const signed char tape[243]
);
