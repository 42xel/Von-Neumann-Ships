#include "prelude.h"
#include "ternary_logic.h"

#include <stdarg.h>
// #include <string.h>
#include <printf.h>

// todo display ?
// addition ?
// operations ?

unsigned short _LTRIT[256];
static const unsigned short* LTRIT = _LTRIT + 128;
signed char _L2BIN[1 << 10];
static const signed char* L2BIN = _L2BIN;
unsigned short _ATRIT[256];
static const unsigned short* ATRIT = _ATRIT + 128;
signed char _A2BIN[1 << 10];
static const signed char* A2BIN = _A2BIN;
static char _init = 0;

            fn signed char from_atrit
(signed short hl) {
hl <<= 6;
signed char n = 0;
        for (int _ = 0; _++ < 5; hl <<= 2) {
n *= 3;
n += hl >> 14;
}
    return n; }
            fn signed short to_atrit
(signed char n) {
unsigned short hl = 0;
    if (n < 0) return
hl = to_atrit(-n),
hl ^ ((hl & 0x155) << 1);
        for (int _ = 0; _++ < 5; n /= 3) {
hl >>= 2;
hl |= ((++n) % 3 - 1) << 14;
}
    return hl >> 6; }
            fn result test_atrit() {
result err = 0;
        for (signed char i = -121; i != 122;++i) {
unsigned short t = to_atrit(i);
err += (i != from_atrit(to_atrit(i))); }
    return err; }

            fn signed char from_ltrit
(unsigned short hl) {
unsigned short h = (hl & 0x2AA);
unsigned short l = ~(hl & 0x155);
signed char n = 0;
h <<= 6;
l <<= 7;
        for (int _ = 0; _++ < 5; h <<= 2, l <<= 2)
n *= 3,
n += h >> 15,
n -= l >> 15;
    return n; }
            fn unsigned short to_ltrit
(signed char n) {
unsigned short hl = 0;
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
        for (signed char i = -121; i != 122;++i) {
unsigned short t = to_ltrit(i);
err += (i != from_ltrit(to_ltrit(i))); }
    return err; }

            fn unsigned short arith_log (unsigned short a) {
unsigned short al = a | ~0x155;
signed short ah = a | ~0x2AA;
unsigned short r = (ah ^ ((al << 1) | 1)) | (~ah >> 1);
return r;
}

            fn result test_LTRIT() {
init();
unsigned short* trit = LTRIT;
result err = 0;
        for (signed char i = -128; i < -121; ++i)
err += (trit[i] ^= 0xFEAA); //coercing litteral to short
        for (signed char i = +122; i > 0; ++i)
err += (trit[i] ^= 0xFEAA);
        for (signed char i = -121; i <= +121; ++i)
err += (i != L2BIN[trit[i]]);
    return err; }
            fn result test_L2BIN() {
init();
signed char* bin = L2BIN;
result err = 0;
        for (unsigned short j = 0; j < 1 << 10; ++j) {
    if ( (j & 0x2AA) & (~(j & 0x155) << 1)) {
err += (bin[j] ^= 0x80);
continue; }
    err += (j != LTRIT[bin[j]]);
}
    return err; }
            fn result test_ATRIT() {
init();
unsigned short* trit = ATRIT;
result err = 0;
        for (signed char i = -128; i < -121; ++i)
err += (trit[i] ^= 0xFEAA); //coercing litteral to short
        for (signed char i = +122; i > 0; ++i)
err += (trit[i] ^= 0xFEAA);
        for (signed char i = -0; i <= +1; ++i)
err += (i != A2BIN[trit[i]]);
    return err; }
            fn result test_A2BIN() {
init();
signed char* bin = A2BIN;
result err = 0;
        for (unsigned short j = 0; j < 1 << 10; ++j) {
    if ( (j & 0x2AA) & (~(j & 0x155) << 1)) {
err += (bin[j] ^= 0x80);
continue; }
    err += (j != ATRIT[bin[j]]);
}
    return err; }

            /// Custom printf handler for arithmetic trits
            fn int atrit_handler
(FILE *stream, const struct printf_info *info, const void *const *args) {
signed char value = *((signed char *)args[0]);
signed short a = to_atrit(value) << 6;
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
signed char value = *((signed char *)args[0]);
unsigned short l = to_ltrit(value) << 6;
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
signed char test_value = 42;
printf("Arithmetic Trits: %O\n", test_value);   // liiio
printf("Logical Trits: %M\n", test_value);
return 0; }

/// create a centered array mapping signed char
/// to their short logical ternary representation
            fn void init() {
    if (_init) return;
unsigned short* ltrit = LTRIT;
unsigned short* atrit = ATRIT;
signed char* lbin = L2BIN;
signed char* abin = A2BIN;
        signed char i = 0; do
atrit[i] = 0xFEAA, // recognizable impossible state
ltrit[i] = 0xFEAA;
while (++i != 0);
        unsigned short j; do
abin[j] = 0x80, // recognizable impossible state
lbin[j] = 0x80;
while (++j < 1 << 10);
        for (signed char i = -121; i <= +121; ++i) {
unsigned short a = to_atrit(i);
atrit[i] = a;
abin[a] = i;
unsigned short l = arith_log(a);
ltrit[i] = l;
lbin[l] = i;
}
register_printf_function('O', atrit_handler, atrit_arginfo);
register_printf_function('M', ltrit_handler, ltrit_arginfo);
    _init = 1;}

            fn result main () {
char r;
init();
return
(r = printf("test_atrit:\n"), test_atrit()) ? r :
(r = printf("test_ltrit:\n"), test_ltrit()) ? r :
(r = printf("test_ATRIT:\n"), test_ATRIT()) ? r :
(r = printf("test_A2BIN:\n"), test_A2BIN()) ? r :
(r = printf("test_LTRIT:\n"), test_LTRIT()) ? r :
(r = printf("test_L2BIN:\n"), test_L2BIN()) ? r :
(r = printf("test_printf:\n"), test_printf()) ? r :
0; }
