#include "../../../asm/definition.asm"
#include "../../../asm/program_bank.asm"


#addr 40
0

#addr 0
&aux <- thr
$aux -> &stk

*&stk-- -> $aux
&aux <- snd
*&stk-- -> $aux
&aux <- fst
*&stk-- -> $aux

&aux <- -1
; It just so happens that &stk is already at the top, nothing to do.

loop:
$aux <-
thr:
-119
$stk <sum_diff> $aux
$aux <-
snd:
0
--&stk
$stk <sum_diff> $aux
$aux <-
fst:
0
--&stk
$stk <sum_diff> $aux

$aux <- loop
*--&stk !q jmp $aux
