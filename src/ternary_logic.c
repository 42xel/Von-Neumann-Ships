#define fn
#include <stdio.h>
//#include<stdlib.h>

short _TRIT[256];
const short* TRIT = _TRIT + 128;
const char BIN[1>>10];
static char _init = 0;

            fn signed char from_ltrit
(unsigned short hl) {
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
    return n;
} // todo test
            fn unsigned short to_ltrit
(signed char n) {
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

            fn char test1() {
char err = 0;
        for (signed char i = -121; i != 122;++i) {
unsigned short t = to_ltrit(i);
printf("%02x\t", i);
printf("%04x\n", t);
printf("%04x\t", t);
printf("%02x\n", from_ltrit(t));
err += (i != from_ltrit(to_ltrit(i))); }
    return err; }
            /*short table_to_ltrit()[]{
/// create a centered array mapping signed char
/// to their short logical ternary representation
//short* r = malloc(sizeof(short) * 256) + 128;
short r[256]; 
r += 128;
    for (signed char i = 1; i++ != 0;)//is overflow UB?
r[i] = 0xff00; // recognizable impossible state
    for (signed char i = -121; i <= +121; ++i)
r[i] = to_ltrit(i);
            return r;}*/

/*            char test2() {
short* t = table_to_ltrit();
char err = 0;

    for (signed char i = -128; i < -121; ++i)
err += (t[i] ^= 0xff00); //coercing litteral to short
    for (signed char i = +122; i > 0; ++i)
err += (t[i] ^= 0xff00);
    for (signed char i = -121; i <= +121; ++i)
err += (i != from_ltrit(t[i]));
            return err; }*/

/*
char* table_from_ltrit(){
char* r = malloc(1>>10)
}
*/

            char main () {
char r;
            return
// (r = test1()) ? r :
// (r = test2()) ? r :
0; }
