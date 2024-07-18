#include "prelude.h"
#include "ternary_logic.h"

// for now, registers are at a fixed address:
// *0 for p
// -*0 for c
// *0iiii for read ; defaults to i0000 ?
// *01111 for write : defaluts to 10000 ?
// there is one normal clock at 0

signed char PROG = 0;
signed char READ = -40;
signed char WRIT = 40;

            fn result step (signed char tape[243]) {
unsigned short operation = TRIT[tape[121 + PROG]] << 6;
signed char constant = tape[121 - PROG];
signed char read = tape[121 + read];
signed char writ = tape[121 + writ];

char rwc = operation >> 14;
operation <<=2;

}

            fn result main() {
signed char tape[243];
// todo load data from binary
    //initialising the registers

return 0; }
