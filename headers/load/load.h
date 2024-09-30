#ifndef load_s_load_h
#define load_s_load_h
#include "src/prelude.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "load.h"
#include "../ternary_logic.h"
/// An alias to signify a 243 cells centered array
pub typedef signed char* Tape;
pub fn result load_file
(const char *__restrict filename, Cell buffer[81]) ;
pub fn result load (
  const char* __restrict program
, const char* __restrict input
, const char* __restrict output
, Tape tape
) ;
pub fn result save_file
(const char *__restrict filename, const Cell buffer[81]) ;
pub fn result save (
  const char* __restrict program
, const char* __restrict input
, const char* __restrict output
, const Tape tape
) ;
#endif