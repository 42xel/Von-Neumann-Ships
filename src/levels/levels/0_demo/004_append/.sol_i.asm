#include "../../../asm/definition.asm"
#include "../../../asm/program_bank.asm"

#addr -40
loop

#addr 0
&stk <-> &aux
loop:
    *++&stk !q jmp $aux
&aux <- -41
$stk <- $aux

