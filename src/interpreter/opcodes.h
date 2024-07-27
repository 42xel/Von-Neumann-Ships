    enum opcodes: signed char {
HALT = 0, // ooooo
LOAD = 9, // 00laa
// TODO TODO
/// As a way to error or wrap without havign to
/// check for program pointer overflow every time.
// OOB = -0x80,
// not a good idea, the function step will, eventually need to be
// reliable. The alternative is making the check every time we use
// prog, which might become a lot more places than whenever we modify
// it. Much simpler to always have prog correct.
};


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
immediate load (prg[1])

### stk *6
push
pop

## short (* 3)
get_reg_addr
set_reg_addr # In theory, can be emulated with a combination of get_reg_addr, store, and immediate load
indirection: *aux = **aux, *aux = *prg[1] et stk[0] = **aux

? addto emplace
? addfrom emplace

n * stackreduce : *(stk++) opn *stk |> *stk, *(stk--) opn *stk |> *stk, *stk opn *aux |> *stk
    add minus
    ? mul
    ? div mod
    xor ? addmod
    min max
    trit minmax
    swap
    swap_addr

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
(prg[1] ?)
sieve
orUnsieve
? split
shake/permut


change_iop # iop long_short ?reversed rw ?failmode
fork
inspect (prg[1])
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
