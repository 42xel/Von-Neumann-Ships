#include "prelude.h"
#include "ternary_logic.h"

#include <stdio.h>
#include <stdarg.h>
// #include <string.h>
#include <printf.h>

// todo display ?
// addition ?
// operations ?
// wrapmod243
// rand243

// TODO test_init

Ltrit _LTRIT[256];
static const Ltrit* LTRIT = _LTRIT + 128;
Cell _L2BIN[1 << 10];
static const Cell* L2BIN = _L2BIN;
Atrit _ATRIT[256];
static const Atrit* ATRIT = _ATRIT + 128;
Cell _A2BIN[1 << 10];
static const Cell* A2BIN = _A2BIN;
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

            fn Ltrit arith_log (Atrit a) {
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

            /// Custom printf handler for arithmetic trits
            fn int atrit_handler
(FILE *stream, const struct printf_info *info, const void *const *args) {
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
            /// Argument size function
            fn int atrit_arginfo
(const struct printf_info *info, size_t n, int *argtypes) {
if (n > 0) argtypes[0] = PA_INT;
return 1; }

            // Custom handler for logical trits
            fn int ltrit_handler
(FILE *stream, const struct printf_info *info, const void *const *args) {
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
(const struct printf_info *info, size_t n, int *argtypes) {
if (n > 0) argtypes[0] = PA_INT;
return 1; }

                    fn result test_printf() {
Cell test_value = 42;
printf("Arithmetic Trits: %O\n", test_value);   // liiio
printf("Logical Trits: %M\n", test_value);
return 0; }

/// create a centered array mapping Cell
/// to their short logical ternary representation
            fn void init() {
    if (_init) return;
Ltrit* ltrit = LTRIT;
Atrit* atrit = ATRIT;
Cell* lbin = L2BIN;
Cell* abin = A2BIN;
        Cell i = 0; do
atrit[i] = 0xFEAA, // recognizable impossible state
ltrit[i] = 0xFEAA;
while (++i != 0);
        Ltrit j; do
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

#include <stdlib.h>
inline Cell rand243() {return rand() % 243 - 121;}
inline Cell wrap243(Cell n) {return (n + 121 + 243) % 243 - 121;}


//             fn result main () {
// result r;
// init();
// return
// (r = printf("test_atrit:\n"), test_atrit()) ? r :
// (r = printf("test_ltrit:\n"), test_ltrit()) ? r :
// (r = printf("test_ATRIT:\n"), test_ATRIT()) ? r :
// (r = printf("test_A2BIN:\n"), test_A2BIN()) ? r :
// (r = printf("test_LTRIT:\n"), test_LTRIT()) ? r :
// (r = printf("test_L2BIN:\n"), test_L2BIN()) ? r :
// (r = printf("test_printf:\n"), test_printf()) ? r :
// 0; }
