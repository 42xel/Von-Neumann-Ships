    enum opcodes {
// rc cw rw y : load save set
SET = -4,
// cw rc rwc s : sieve split orUnsieve
SIEVE = -3,
// cw rc rwc S : shake? unShake? shake&
// 5! = 120, why not just permut ? permut & permut indir.
// for example cte tells whether p is indir
PERM = -2,
// cww rww rww a : add
ADD = -1,

// change them to accu f_c= opnd
// and accu1 accu2 f_c=()
// cw rc rwc m : min max
MINMAX = 0,
// cw rc rwc b : tritwise(xor addmod minmax)
TWISE = 1,

// cw rc rwc i : inc_dec($r) inc_dec($w) inc_dec($c)
INDECR = 2,
// cw rc rwc j J :
//     loop(cp p ? whatever's best for loops)
//     cjmp(pc p ? whatever's best for jumptable)
//     call(cp p)
JMP2 = 3,
JMP1 = 4
};
//
// PID PFile(r w) fork  toogle clock  halt
//     file(create delete)
//
// spe y : (set swap dbl_cpy)? full file copy ?
// spe s : sieve split orUnsieve
// spe S : shake unShake shake&

// spe a : add, mul?, div mod
// spe m : min max
// spe b :
// spe i : toggle minus interp ?
// spe j J : toogle clocks/ minus clocks ?
//
