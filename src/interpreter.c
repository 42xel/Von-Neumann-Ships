#include <stdio.h>

            signed char from_ltrit(unsigned short hl) {
char h = hl >> 8;
char l = ~hl;// & 0x00ff;
signed char n = 0;
h <<= 3;
l <<= 3;
    for (int i =0; i < 5; ++i) {
n *= 3;
n += h >> 7;
n -= l >> 7;
    h <<= 1;
    l <<= 1;
    }
            return n;} // todo test

            unsigned short to_ltrit(signed char n) {
    if (n < 0) {
unsigned short hl = to_ltrit(-n);
return ~((hl << 8) | (hl >> 8));// & 0x1f1f;
}
unsigned short hl = 0;
    for (int i = 0; i < 5; ++i) {
hl >>= 1;
++n;
char d = n%3;
hl |= (d >> 1) << (8 + 4);
hl |= (d != 0) << 4;
    n /=3;}
            return hl; } // todo test

            int test1() {
char err = 0;
    for (signed char j = -121; j != 122;++j) {
unsigned short t = to_ltrit(j);
printf("%02x\t", j);
printf("%04x\n", t);

printf("%04x\t", t);
printf("%02x\n", from_ltrit(t));
if (j != from_ltrit(to_ltrit(j))) ++err; }
            return err; }

