#include "../../../asm/definition.asm"
#include "../../../asm/program_bank.asm"

#addr 0
--&stk
&stk <-> &aux
++&stk
$stk <sum_diff> $aux

