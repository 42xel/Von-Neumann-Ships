#ifndef load_h
#define load_h

#include "../prelude.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>

// An alias to signify a 243 cells centered array
typedef signed char* Tape;

    fn result load_file
(const char *__restrict filename, signed char buffer[81]);
    fn result load(
const char* __restrict program
, const char* __restrict input
, const char* __restrict output
, Tape tape
);
    fn result save_file
(const char *__restrict filename, const signed char buffer[81]);
    fn result save (
const char* __restrict program
, const char* __restrict input
, const char* __restrict output
, const Tape tape
);

#endif
