#include "../../../asm/definition.asm"
#include "../../../asm/program_bank.asm"

#addr -40
+3

#addr 0
a <- &stk--, $stk <sum_diff> *a

&stk <-> &aux

; push
*++&stk <- $aux

