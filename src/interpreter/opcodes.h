#ifndef opcodes_h
# define opcodes_h

      enum opcodes: signed char {
LOAD_STK_HAT = -4,
LOAD_STK_HED = -3,
LOAD_STK_TAI = -2,
LOAD_PRG_JMP = -1,
LOAD_PRG_HLT =  0,
// this NOOP consumes 2 instructions, not using the constant.
// TODO NOPE, consuming only one.
LOAD_PRG_NOP = +1,
LOAD_AUX_ADR = +2,
LOAD_AUX_DIR = +3,
LOAD_AUX_IND = +4,

STAK_WRT_HAT = -13,
STAK_WRT_HED = -12,
STAK_WRT_TAI = -11,
STAK_SWP_HAT = -10,
STAK_SWP_HED = -9,
STAK_SWP_TAI = -8,
STAK_REA_HAT = -7,
STAK_REA_HED = -6,
STAK_REA_TAI = -5,

ADDR_REA_STK = 113,
ADDR_REA_PRG = 114,
ADDR_REA_AUX = 115,
ADDR_SWP_STK = 116,
ADDR_SWP_PRG = 117,
ADDR_SWP_AUX = 118,
ADDR_WRT_STK = 119,
ADDR_WRT_PRG = 120,
ADDR_WRT_AUX = 121,

REDU_ADM_HAT = -121,
REDU_ADM_HED = -120,
REDU_ADM_TAI = -119,

REDU_MNX_HAT = -118,
REDU_MNX_HED = -117,
REDU_MNX_TAI = -116,

REDU_TNX_HAT = -115,
REDU_TNX_HED = -114,
REDU_TNX_TAI = -113,


REDU_SWP_HAT = -109,
REDU_SWP_HED = -108,
REDU_SWP_TAI = -107,

REDU_MOV_HAT = -106,
REDU_SWP_ADR = -105,
REDU_MOV_TAI = -104,

// PONDER?
/// As a way to error or wrap without havign to
/// check for program pointer overflow every time.
// OOB = -0x80,
// not a good idea, the function step will, eventually need to be
// reliable. The alternative is making the check every time we use
// prog, which might become a lot more places than whenever we modify
// it. Much simpler to always have prog correct.
};

//       enum opcodes: signed char {
// LOAD_STK_HAT = -4,
// LOAD_STK_HED = -3,
// LOAD_STK_TAI = -2,
// LOAD_PRG_JMP = -1,
// LOAD_PRG_HLT =  0,
// LOAD_PRG_NOP = +1,
// LOAD_AUX_ADR = +2,
// LOAD_AUX_DIR = +3,
// LOAD_AUX_IND = +4,

// STAK_WRT_HAT = -13,
// STAK_WRT_HED = -12,
// STAK_WRT_TAI = -11,
// STAK_SWP_HAT = -10,
// STAK_SWP_HED = -9,
// STAK_SWP_TAI = -8,
// STAK_REA_HAT = -7,
// STAK_REA_HED = -6,
// STAK_REA_TAI = -5,

// ADDR_REA_STK = 113,
// ADDR_REA_PRG = 114,
// ADDR_REA_AUX = 115,
// ADDR_SWP_STK = 116,
// ADDR_SWP_PRG = 117,
// ADDR_SWP_AUX = 118,
// ADDR_WRT_STK = 119,
// ADDR_WRT_PRG = 120,
// ADDR_WRT_AUX = 121,

// REDU_ADM_HAT = -121,
// REDU_ADM_HED = -120,
// REDU_ADM_TAI = -119,

// REDU_MNX_HAT = -118,
// REDU_MNX_HED = -117,
// REDU_MNX_TAI = -116,

// REDU_TNX_HAT = -115,
// REDU_TNX_HED = -114,
// REDU_TNX_TAI = -113,


// REDU_SWP_HAT = -109,
// REDU_SWP_HED = -108,
// REDU_SWP_TAI = -107,

// REDU_MOV_HAT = -106,
// REDU_SWP_ADR = -105,
// REDU_MOV_TAI = -104,
// };

/*
# Machine code

Between 0 and 2 trits are used to describe an operand, depending on the operation.
The operation takes up the rest, 2 to 5 trits, provided at most 3 trits are used for operands (1 + 2).

short operand description, usually :
stk[0], prg[0/1], *aux

long operand description, usually :
pop (stk[-1]), emplace (stk[0]), push (stk[1]),
prg, prg[0], prg[1],
aux, *aux, **aux

## Instructions set

### long short (* 27)
? swap

## short short (* 9)

## long (* 9)
immediate load (prg[1]) => LOAD (* 7 instead ? + NOOP & long NOOP ?)

## short (* 3)
### stk
push
pop
=> STAK_

get_reg_addr
set_reg_addr
   # In theory, can be emulated with a combination of get_reg_addr, store, and immediate load
indirection: *aux = **aux, *aux = *prg[1] et stk[0] = **aux
   # *aux = *prg[1] already exists (load).r
   # stk[0] = **aux may or may not exist, but easy to simulate : emplace indir swap
=> ADDR

? addto emplace
? addfrom emplace

3 * stackreduce : *(stk++) opn *stk |> *stk, *(stk--) opn *stk |> *stk, *stk opn *aux |> *stk
    add minus
    min max
    trit minmax
    xor ? addmod
    mov or swap_addr
    swap
    ? mul
    ? div mod
=> REDU_

? neg

call/loop
cond

### fixed operand (* 1) : *stk <- opn *aux *stk
? xor
? addmod
? minus
? neg # would spare a constant and an operation
      # compared to xor lllll, but it might be
      # an intentional constraints to push people
      # to be smart about something simple,
      # keeping lllll around closeby for bulk negation
(using prg[1] instead of aux ?)
sieve
orUnsieve
? split
shake/permut
? deref


change_iop # iop long_short ?reversed rw ?failmode
fork
inspect (prg[1] or aux)
? 0: halt # could be EoF
? wait # one of the other operation surely is wait
? noop # one of the other operation surely is noop.

? reset registers ?
? launch w default reg ?


# assembly


- Possibility to anchor the code, to start from anywhere
instead of oiiii.
Syntaxe: like a label but name is a number.


## examples
### add5: *liiii = *illll + 5
oiiii: 5
0:
stk |+> -&stk // stk |+> *(--&stk) where the actual variable is &stk, and stk is short for *&stk.
&aux <> &stk
aux |> +&stk // aux |> *(++&stk)


### copy serial: for x in liiii .. lllll, *x = *-x
0:


# completion
input unchanged (no cheating)
input never changed (read only)
never read from outut (write only)
    (*2 ? never used from ouput as rhs
    and never moved info out from output)

? prg constant (reusability)


# score
*/
#endif

