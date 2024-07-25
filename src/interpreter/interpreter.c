#include "../prelude.h"
#include "opcodes.h"
#include "../ternary_logic.h"
#include "../load/load.h"

// for now, registers are at a fixed address:
// *0 for p
// -*0 for c
// *0iiii for read ; defaults to i0000 ?
// *01111 for write : defaluts to 10000 ?
// there is one normal clock at 0

//             fn signed char deref
// (signed char addr, signed char tape[243]){
// return tape[addr];}
            fn signed char* deref
(const signed char tape[243], const signed char* addr){
return &tape[*addr];}
            fn void set
(signed char* const addr, const signed char value){
*addr = value;}

            fn void indirect2 (
const signed char tape[243]
, char indir
, const signed char** const addr1
, const signed char** const addr2
) {
        for (int _ = 0; _++ < 2; indir >>= 1)
if (indir & 1) *addr2 = &tape[**addr2];
        for (int _ = 0; _++ < 2; indir >>= 1)
if (indir & 1) *addr1 = &tape[**addr1];
}
            fn void indirect3 (
const signed char tape[243]
, char indir
, const signed char** const addr1
, const signed char** const addr2
, const signed char** const addr3
) {
    if (indir & 1) *addr3 = &tape[**addr3];
indir >>= 1;
    if (indir & 1) *addr2 = &tape[**addr2];
indir >>= 1;
    if (indir & 1) *addr1 = &tape[**addr1];
}

            fn result special_step (
signed char tape[243]
, signed char operation
, signed char* read
, signed char* writ
, signed char* cons
, signed char* prog
) {
        switch (operation) {
    case SET :
    case SIEVE :
    case PERM :
    case ADD :
    case MINMAX :
    case TWISE :
    case INDECR :
    case JMP2 :
    case JMP1 :
return _ERR_WIP;
    default: return _ERR_NAOP; }
return 0; }
            fn result regular_step (
signed char tape[243]
, signed char operation
, signed char indir
, signed char* read
, signed char* writ
, signed char* cons
, signed char* prog
) {
const signed char* opnd1;
const signed char* opnd2;
signed char* rcpt1;
signed char* rcpt2;
signed char* accu1;
signed char* accu2;
        switch (9 * indir + operation) {
    case -9 + SET :
    // c <| r (save)
opnd1 = read;
rcpt1 = cons;
break;
    case 00 + SET :
    // w <| c (load)
opnd1 = cons;
rcpt1 = writ;
break;
    case +9 + SET :
    // w <| r (set)
opnd1 = read;
rcpt1 = writ;
break;
    case -9 + SIEVE :
    case 00 + SIEVE :
    case +9 + SIEVE :
    case -9 + PERM :
    case 00 + PERM :
    case +9 + PERM :
    case -9 + ADD :
    case 00 + ADD :
    case +9 + ADD :
    case -9 + MINMAX :
    case 00 + MINMAX :
    case +9 + MINMAX :
    case -9 + TWISE :
    case 00 + TWISE :
    case +9 + TWISE :
    case -9 + INDECR :
    case 00 + INDECR :
    case +9 + INDECR :
    case -9 + JMP2 :
    case 00 + JMP2 :
    case +9 + JMP2 :
    case -9 + JMP1 :
    case 00 + JMP1 :
    case +9 + JMP1 :
return _ERR_WIP;
    default: return _ERR_NAOP; }
        switch (3 * operation + indir) {
    case 3 * SET - 1:
    case 3 * SET + 0:
    case 3 * SET + 1:
indirect2(tape, indir, &opnd1, &rcpt1);
set(rcpt1, *opnd1);
break;
// swap
signed char tiers = *accu1;
set(accu1, *accu2);
set(accu2, tiers);
break;
    case 3 * SIEVE - 1:
    case 3 * SIEVE + 0:
    case 3 * SIEVE + 1:
    case 3 * PERM - 1:
    case 3 * PERM + 0:
    case 3 * PERM + 1:
    case 3 * ADD - 1:
    case 3 * ADD + 0:
    case 3 * ADD + 1:
    case 3 * MINMAX - 1:
    case 3 * MINMAX + 0:
    case 3 * MINMAX + 1:
    case 3 * TWISE - 1:
    case 3 * TWISE + 0:
    case 3 * TWISE + 1:
    case 3 * INDECR - 1:
    case 3 * INDECR + 0:
    case 3 * INDECR + 1:
    case 3 * JMP2 - 1:
    case 3 * JMP2 + 0:
    case 3 * JMP2 + 1:
    case 3 * JMP1 - 1:
    case 3 * JMP1 + 0:
    case 3 * JMP1 + 1:
return _ERR_WIP;
    default: return _ERR_NAOP; }
return 0; }
            fn result step (
signed char tape[243]
, signed char* prog
, signed char* cons
, signed char* read
, signed char* writ
) {
    signed short instruction = ATRIT[tape[121 + *prog]] << 6;
signed char rwc = instruction >> 14;
instruction <<= 2;
char indir = A2BIN[instruction >> 12];
instruction <<= 4;
signed char operation = A2BIN[instruction >> 12];
    // special operations
    if (rwc == 1 && indir == 8) return
special_step(tape, operation, read, writ, cons, prog);
    return regular_step(tape, operation, indir, read, writ, cons, prog);
return 0; }

            fn result main() {
signed char prog = 0;
signed char cons = -0;
signed char read = -40;
signed char writ = 40;

// todo make it not a tape ?
signed char tape[243];
load("test_0.cvt", NULL, NULL, tape);


return 0; }
