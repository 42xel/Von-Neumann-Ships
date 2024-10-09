#include "../../../asm/definition.asm"
#include "../../../asm/program_bank.asm"

#addr 0
noop
0
noop, 0x72
jump -14
#addr -14
&prg <- 31

#addr 31
 return   -  107

#addr -22
load aux ind, 43


