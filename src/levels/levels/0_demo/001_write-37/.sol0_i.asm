#include "../../../asm/definition.asm"
#include "../../../asm/program_bank.asm"

#addr 0
&stk <-> &aux
*++&stk <- 37
