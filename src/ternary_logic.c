/// A module to deal with ternary logic:
/// converting from byte (eight bits, 2^8)
/// to five trits (3^5) and back;
/// displaying such units group;
/// maybe other things;

#include "src/prelude.h"
#include "ternary_logic.h"

#include <stdio.h>
#include <stdarg.h>
// #include <string.h>
#include <printf.h>

// todo display ?
// addition ?
// operations ?

/// The type of data in a memory Cell
pub typedef signed char Cell;
/// The type containing an ternary arithmetical representation
pub typedef signed short Atrit;
/// The type containing an ternary logical representation
pub typedef unsigned short Ltrit;

Ltrit _LTRIT[256];
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
pub static const Ltrit* LTRIT = _LTRIT + 128;
Cell _L2BIN[1 << 10];
/// An array mapping logical ternary(short) to Cell(char)
/// See `LTRIT` for an explanation on logic trits.
pub static const Cell* L2BIN = _L2BIN;

Atrit _ATRIT[256];
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
pub static const Atrit* ATRIT = _ATRIT + 128;
Cell _A2BIN[1 << 10];
/// An array mapping arithmetical ternary(short) to Cell(char)
/// See `ATRIT` for an explanation on arith trits.
pub static const Cell* A2BIN = _A2BIN;

static char _init = 0;

            fn Cell from_atrit
(Atrit a) {
a <<= 6;
Cell n = 0;
        for (int _ = 0; _++ < 5; a <<= 2) {
n *= 3;
n += a >> 14;
}
    return n; }
            fn Atrit to_atrit
(Cell n) {
Ltrit a = 0;
    if (n < 0) return
a = to_atrit(-n),
a ^ ((a & 0x155) << 1);
        for (int _ = 0; _++ < 5; n /= 3) {
a >>= 2;
a |= ((++n) % 3 - 1) << 14;
}
    return a >> 6; }
            fn result test_atrit() {
result err = 0;
        for (Cell i = -121; i != 122;++i) {
Ltrit t = to_atrit(i);
err += (i != from_atrit(to_atrit(i))); }
    return err; }

            fn Cell from_ltrit
(Ltrit hl) {
Ltrit h = (hl & 0x2AA);
Ltrit l = ~(hl & 0x155);
Cell n = 0;
h <<= 6;
l <<= 7;
        for (int _ = 0; _++ < 5; h <<= 2, l <<= 2)
n *= 3,
n += h >> 15,
n -= l >> 15;
    return n; }
            fn Ltrit to_ltrit
(Cell n) {
Ltrit hl = 0;
    if (n < 0) return
hl = to_ltrit(-n),
(((hl & 0x155) << 1) | ((hl & 0x2AA) >> 1)) ^ 0x03FF;
        for (int _ = 0; _++ < 5; n /=3) {
hl >>= 2;
++n;
char d = n % 3;
hl |= (d >> 1) << 9;
hl |= (d != 0) << 8;
}
    return hl; }
            fn result test_ltrit() {
result err = 0;
        for (Cell i = -121; i != 122;++i) {
Ltrit t = to_ltrit(i);
err += (i != from_ltrit(to_ltrit(i))); }
    return err; }

/// Goes from arithmetic to logic trits.
            pub fn Ltrit arith_log (Atrit a) {
unsigned short al = a | ~0x155;
signed short ah = a | ~0x2AA;
Ltrit r = (ah ^ ((al << 1) | 1)) | (~ah >> 1);
return r;
}

            fn result test_LTRIT() {
init();
Ltrit* trit = LTRIT;
result err = 0;
        for (Cell i = -128; i < -121; ++i)
err += (trit[i] ^= 0xFEAA); //coercing litteral to short
        for (Cell i = +122; i > 0; ++i)
err += (trit[i] ^= 0xFEAA);
        for (Cell i = -121; i <= +121; ++i)
err += (i != L2BIN[trit[i]]);
    return err; }
            fn result test_L2BIN() {
init();
Cell* bin = L2BIN;
result err = 0;
        for (Ltrit j = 0; j < 1 << 10; ++j) {
    if ( (j & 0x2AA) & (~(j & 0x155) << 1)) {
err += (bin[j] ^= 0x80);
continue; }
    err += (j != LTRIT[bin[j]]);
}
    return err; }
            fn result test_ATRIT() {
init();
Atrit* trit = ATRIT;
result err = 0;
        for (signed char i = -128; i < -121; ++i)
err += (trit[i] ^= 0xFEAA); //coercing litteral to short
        for (signed char i = +122; i > 0; ++i)
err += (trit[i] ^= 0xFEAA);
        for (Cell i = -121; i <= +121; ++i)
err += (i != A2BIN[trit[i]]);
    return err; }
            fn result test_A2BIN() {
init();
Cell* bin = A2BIN;
result err = 0;
        for (Ltrit j = 0; j < 1 << 10; ++j) {
    if ( (j & 0x2AA) & (~(j & 0x155) << 1)) {
err += (bin[j] ^= 0x80);
continue; }
    err += (j != ATRIT[bin[j]]);
}
    return err; }

            // Custom printf handler for arithmetic trits
            fn int atrit_handler
(FILE *stream, const struct printf_info *, const void *const *args) {
Cell value = *((Cell *)args[0]);
Atrit a = to_atrit(value) << 6;
char buffer[6];
int index = 0;
        for (int _ = 0; _++ < 5; a <<= 2) {
    switch (a >> 14) {
case +1: buffer[index++] = 'l'; break;
case 00: buffer[index++] = 'o'; break;
case -1: buffer[index++] = 'i'; break;
default: buffer[index++] = '?'; break;
}}
    buffer[index] = '\0';
return fprintf(stream, "%s", buffer); }
            // Argument size function
            fn int atrit_arginfo
(const struct printf_info *, size_t n, int *argtypes) {
if (n > 0) argtypes[0] = PA_INT;
return 1; }

            // Custom handler for logical trits
            fn int ltrit_handler
(FILE *stream, const struct printf_info *, const void *const *args) {
Cell value = *((Cell *)args[0]);
Ltrit l = to_ltrit(value) << 6;
char buffer[6];
int index = 0;
        for (int _ = 0; _++ < 5; l <<= 2) {
    switch (l >> 14) {
case 0b01: buffer[index++] = 'm'; break;
case 0b00: buffer[index++] = 'n'; break;
case 0b11: buffer[index++] = 'u'; break;
default:   buffer[index++] = '?'; break;
}}
    buffer[index] = '\0';
return fprintf(stream, "%s", buffer); }
            fn int ltrit_arginfo
(const struct printf_info *, size_t n, int *argtypes) {
if (n > 0) argtypes[0] = PA_INT;
return 1; }

// TODO make proper tests.
                fn result test_printf() {
Cell test_value = 42;
printf("Arithmetic Trits: %O\n", test_value);   // liiio
printf("Logical Trits: %M\n", test_value);
return 0; }

/**
 * The initialization function of the module.
 * Initializes the various conversions arrays and
 * registers custom formating for ternary numbers.
*/
            pub fn void init() {
    if (_init) return;
Ltrit* ltrit = LTRIT;
Atrit* atrit = ATRIT;
Cell* lbin = L2BIN;
Cell* abin = A2BIN;
        Cell i = 0; do
atrit[i] = 0xFEAA, // recognizable impossible state
ltrit[i] = 0xFEAA;
while (++i != 0);
        Ltrit j = 0; do
abin[j] = 0x80, // recognizable impossible state
lbin[j] = 0x80;
while (++j < 1 << 10);
        for (Cell i = -121; i <= +121; ++i) {
Ltrit a = to_atrit(i);
atrit[i] = a;
abin[a] = i;
Ltrit l = arith_log(a);
ltrit[i] = l;
lbin[l] = i;
}
register_printf_function('O', atrit_handler, atrit_arginfo);
register_printf_function('M', ltrit_handler, ltrit_arginfo);
    _init = 1;}

// TODO: See how to inline these functions automatically into a header.
// It's trickier than it seems, because of double definition.
// Either I end up with disfugured C code, or I end up with multiple
// definitions.
// One solution I guess would be `pub inline bla bla bla _toto() {}`
// becoming `pub inline bla bla bla toto() {}`, defining it twice.
#include <stdlib.h>
pub fn Cell rand243() {return rand() % 243 - 121;}
pub fn Cell wrap243(Cell n) {return (n + 121 + 243) % 243 - 121;}

