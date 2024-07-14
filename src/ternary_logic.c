#include "prelude.h"

unsigned short _TRIT[256];
const unsigned short* TRIT = _TRIT + 128;
signed char _BIN[1 << 10];
const signed char* BIN = _BIN;
static char _init = 0;

            fn signed char from_ltrit
(unsigned short hl) {
unsigned short h = (hl & 0x2AA);
unsigned short l = ~(hl & 0x155);
signed char n = 0;
h <<= 6;
l <<= 7;
        for (int i = 0; i < 5; ++i) {
n *= 3;
n += h >> 15;
n -= l >> 15;
h <<= 2;
l <<= 2;
}
    return n;
} // todo test
            fn unsigned short to_ltrit
(signed char n) {
unsigned short hl = 0;
    if (n < 0) return
hl = to_ltrit(-n),
(((hl & 0x155) << 1) | ((hl & 0x2AA) >> 1)) ^ 0x03FF;
        for (int i = 0; i < 5; ++i) {
hl >>= 2;
++n;
char d = n % 3;
hl |= (d >> 1) << 9;
hl |= (d != 0) << 8;
n /=3;}
    return hl; }
            fn result test1() {
char err = 0;
        for (signed char i = -121; i != 122;++i) {
unsigned short t = to_ltrit(i);
printf("%02x\t", i);
printf("%04x\n", t);
printf("%04x\t", t);
printf("%02x\n", from_ltrit(t));
err += (i != from_ltrit(to_ltrit(i))); }
    return err; }

            fn void init_tables() {
/// create a centered array mapping signed char
/// to their short logical ternary representation
    if (_init) return;
unsigned short* trit = TRIT;
signed char* bin = BIN;
        signed char i = 0; do
trit[i] = 0xFEAA; // recognizable impossible state
while (++i != 0);
        unsigned short j; do
bin[j] = 0x80; // recognizable impossible state
while (++j < 1 << 10);
        for (signed char i = -121; i <= +121; ++i) {
unsigned short t = to_ltrit(i);
trit[i] = t;
bin[t] = i;
}
    _init = 1;}
            fn result test2() {
init_tables();
unsigned short* trit = TRIT;
char err = 0;
        for (signed char i = -128; i < -121; ++i)
err += (trit[i] ^= 0xFEAA); //coercing litteral to short
        for (signed char i = +122; i > 0; ++i)
err += (trit[i] ^= 0xFEAA);
        for (signed char i = -121; i <= +121; ++i)
err += (i != BIN[trit[i]]);
    return err; }
            fn char test3() {
init_tables();
signed char* bin = BIN;
char err = 0;
        for (unsigned short j = 0; j < 1 << 10; ++j) {
    if ( (j & 0x2AA) & (~(j & 0x155) << 1)) {
err += (bin[j] ^= 0x80);
continue; }
    err += (j != TRIT[bin[j]]);
}
    return err; }

            fn result main () {
char r;
init_tables();
return
(r = test1()) ? r :
(r = test2()) ? r :
(r = test3()) ? r :
0; }
