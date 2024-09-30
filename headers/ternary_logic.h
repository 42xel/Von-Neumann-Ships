#ifndef ternary_logic_h
#define ternary_logic_h
/// A module to deal with ternary logic:
/// converting from byte (eight bits, 2^8)
/// to five trits (3^5) and back;
/// displaying such units group;
/// maybe other things;
#include "src/prelude.h"
#include "ternary_logic.h"
#include <stdio.h>
#include <stdarg.h>
#include <printf.h>
/// The type of data in a memory Cell
pub typedef signed char Cell;
/// The type containing an ternary arithmetical representation
pub typedef signed short Atrit;
/// The type containing an ternary logical representation
pub typedef unsigned short Ltrit;
/**
A centered array mapping Cell(char) to logical ternary(short)

It converts a signed byte to logical trits.
        # Logical Trits.
They're arithmetical trits, but -1 means false, 1 true and 0 maybe.
    ## Representation
In the emulator, the values are stored as increasing 2 bits among
00, 01, 11. Increasing in the sense false < maybe < true
thusly:
* -1 is represented by 11
*  0 is represented by 00
* +1 is represented by 01
* 10 corresponds to nothing
An other way to view it is as regular ternary with values 0 1 and 2
represented in unary. Values in [0, 242] are encoded and are mapped
increasingly to signed bytes of values [-121, +121].
Either way, the five double bits are stored in the least significant bits
of an unsigned short.
Logical shift allows to retrieve the values 00, 01 and 11.
    ## Display
The symobls used for display are
* n for 00 (*n*ot, and is mirror of u)
* m for 01 (*m*aybe)
* u for 11 (tru*e*)
Some numbers :
nmumu, nunu
Numbers are preferably displayed of length 5, if some are ommited, assume
leading `m`s.
*/
pub static const Ltrit* LTRIT  ;
/// An array mapping logical ternary(short) to Cell(char)
/// See `LTRIT` for an explanation on logic trits.
pub static const Cell* L2BIN  ;
/**
A centered array mapping Cell(char) to arithmetical ternary(short)

It converts a signed byte to 5 arithmetical trits,
Provided the values are within [-121, +121].
        # Arithmetic Trits.
The system used is base 3, but with the symbol values -1, 0 and 1.
    ## Representation
In the emulator, the values are stored as 2 bits, 2 complements numbers.
thusly:
* -1 is represented by 11
*  0 is represented by 00
* +1 is represented by 01
* 10 corresponds to nothing
The five double bits are stored in the least significant bits
of a signed short.
Arithmetic shift allows to retrieve the values -1, 0 and +1.
    ## Display
The symbols used for display are
* i for -1
* o for  0
* l for +1
Numbers from 0 to +5 :
o, l, li, lo, ll, lii
Minus 6 :
ilo
*/
pub static const Atrit* ATRIT  ;
/// An array mapping arithmetical ternary(short) to Cell(char)
/// See `ATRIT` for an explanation on arith trits.
pub static const Cell* A2BIN  ;
/// Goes from arithmetic to logic trits.
pub fn Ltrit arith_log (Atrit a) ;
/**
 * The initialization function of the module.
 * Initializes the various conversions arrays and
 * registers custom formating for ternary numbers.
*/
pub fn void init() ;
#include <stdlib.h>
pub fn Cell rand243() ;
pub fn Cell wrap243(int n) ;
/// like ++(*n) but accounts for wrapping.
pub fn Cell ppx243(Cell* n) ;
/// like --(*n) but accounts for wrapping.
pub fn Cell mmx243(Cell* n) ;
/// like (*n)++ but accounts for wrapping.
pub fn Cell xpp243(Cell* n) ;
/// like (*n)-- but accounts for wrapping.
pub fn Cell xmm243(Cell* n) ;
#endif
