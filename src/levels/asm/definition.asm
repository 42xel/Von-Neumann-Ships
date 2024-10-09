#ruledef Cell
{
    {val: s8} =>
    {
        assert((val >= -121) && (val <= 121), "Cell out of bounds.")
        val
    }
    +{val: s8} =>
    {
        assert((val >= -121) && (val <= 121), "Cell out of bounds.")
        val
    }
}

; TODO ? A way to closely couple asm and C constants.
; probably by generating the opcode ruledef automatically from opcode.h
#ruledef OPCODES
{
    LOAD_STK_HAT => asm {-4}
    LOAD_STK_HED => asm {-3}
    LOAD_STK_TAI => asm {-2}
    LOAD_PRG_JMP => asm {-1}
    LOAD_PRG_HLT => asm {0}
    LOAD_PRG_NOP => asm {1}
    LOAD_AUX_ADR => asm {2}
    LOAD_AUX_DIR => asm {3}
    LOAD_AUX_IND => asm {4}

    STAK_WRT_HAT => asm {-13}
    STAK_WRT_HED => asm {-12}
    STAK_WRT_TAI => asm {-11}
    STAK_SWP_HAT => asm {-10}
    STAK_SWP_HED => asm {-9}
    STAK_SWP_TAI => asm {-8}
    STAK_REA_HAT => asm {-7}
    STAK_REA_HED => asm {-6}
    STAK_REA_TAI => asm {-5}

    ADDR_REA_STK => asm {113}
    ADDR_REA_PRG => asm {114}
    ADDR_REA_AUX => asm {115}
    ADDR_SWP_STK => asm {116}
    ADDR_SWP_PRG => asm {117}
    ADDR_SWP_AUX => asm {118}
    ADDR_WRT_STK => asm {119}
    ADDR_WRT_PRG => asm {120}
    ADDR_WRT_AUX => asm {121}

    REDU_ADM_HAT => asm {-121}
    REDU_ADM_HED => asm {-120}
    REDU_ADM_TAI => asm {-119}

    REDU_MNX_HAT => asm {-118}
    REDU_MNX_HED => asm {-117}
    REDU_MNX_TAI => asm {-116}

    REDU_TNX_HAT => asm {-115}
    REDU_TNX_HED => asm {-114}
    REDU_TNX_TAI => asm {-113}


    REDU_SWP_HAT => asm {-109}
    REDU_SWP_HED => asm {-108}
    REDU_SWP_TAI => asm {-107}

    REDU_MOV_HAT => asm {-106}
    REDU_SWP_ADR => asm {-105}
    REDU_MOV_TAI => asm {-104}

    LOOP_HAT     => {5}
    LOOP_DECR    => {6}
    LOOP_TAIL    => {7}

    COND_STK_LE  => {8}
    COND_STK_NZ  => {9}
    COND_STK_GE  => {10}

    CALL_STK_HAT => {11}
    CALL_STK_HED => {12}
    CALL_STK_TAI => {13}

}

#subruledef target
{
    stk => -1
    prg => 0
    aux => 1
}
#subruledef symb_target
{
    $stk => -1
    $prg => 0
    $aux => 1
}
#subruledef stk_at
{
    hat => -1
    hed => 0
    tai => 1
}
#subruledef symb_stk_at
{
    *--& => -1
    $ => 0
    *++& => 1
}
#subruledef rsw
{
    read => -1
    swap => 0
    write => 1
}
#subruledef red_at
{
    hat => -1
    aux => 0
    tai => 1
}
#subruledef symb_red_at
{
    &stk++ => -1
    &aux => 0
    &stk-- => 1
}
#subruledef aux_indirection
{
    adr => -1
    dir => 0
    ind => 1
}
#subruledef symb_aux_indirection
{
    &aux => -1
    $aux => 0
    *aux => 1
}
#subruledef reduce_op
{
    sum_diff => asm { REDU_ADM_HED }
    min_max => asm { REDU_MNX_HED }
    twise_min_max => asm { REDU_TNX_HED }
    ; swap is handled differently because it operates on the addresses
    ; swap => asm { REDU_SWP_HED }
    identity => asm { REDU_SWP_ADR }
}

; TODO : segregate the different styles into different files and choose one to promote as default.
#ruledef
{
    ; halts the program (after moving the program head)
    halt, {val: Cell} => asm { LOAD_PRG_HLT } @ val
    return {val: Cell} => asm { LOAD_PRG_HLT } @ val
    halt => asm { LOAD_PRG_HLT }
    ++&prg, return => asm { LOAD_PRG_HLT }
    ; does nothing (after moving the program head)
    noop, {val: Cell} => asm { LOAD_PRG_NOP } @ val
    ++&prg, {val: Cell} => asm { LOAD_PRG_NOP } @ val
    noop => asm { LOAD_PRG_NOP }
    ++&prg => asm { LOAD_PRG_NOP }
    ; Unconditional jump
    jmp {val: Cell} => asm { LOAD_PRG_JMP } @ val
    &prg <- {val: Cell} => asm { LOAD_PRG_JMP } @ val

    ; load a value from the program.
    ; into `aux` related values
    load aux {mod: aux_indirection}, {val: Cell} => (asm { LOAD_AUX_DIR } + mod)`8 @ val
    load aux {mod: aux_indirection} => (asm { LOAD_AUX_DIR } + mod)`8
    {mod: symb_aux_indirection} <- {val: Cell} => (asm { LOAD_AUX_DIR } + mod)`8 @ val

    ; into `stk` related values
    load stk {at: stk_at}, {val: Cell} => (asm { LOAD_STK_HED } + at)`8 @ val
    *--&stk <- {val: Cell} => asm { LOAD_STK_HAT } @ val
    $stk <-    {val: Cell} => asm { LOAD_STK_HED } @ val
    *++&stk <- {val: Cell} => asm { LOAD_STK_TAI } @ val
    load stk {at: stk_at} => (asm { LOAD_STK_HED } + at)`8
    {at: symb_stk_at}stk <- => (asm { LOAD_STK_HED } + at)`8

    ; read/write/swap interaction between the stack and the auxiliary register
    {at: symb_stk_at}stk <- $aux  => (asm { STAK_WRT_HED } + at)`8
    {at: symb_stk_at}stk <-> $aux => (asm { STAK_SWP_HED } + at)`8
    $aux <- {at: symb_stk_at}stk  => (asm { STAK_REA_HED } + at)`8
    push => asm { STAK_WRT_TAI }
    empl => asm { STAK_WRT_HED }
    dpush=> asm { STAK_WRT_HAT }
    pop  => asm { STAK_REA_TAI }
    peek => asm { STAK_REA_HED }
    dpop => asm { STAK_REA_HAT }
    {op: rsw} {at: stk_at} => (asm { STAK_SWP_HED } + 3 * op + at)`8

    ; address manipulations
    $aux <-  {tgt: symb_target} => (asm { ADDR_REA_PRG } + tgt)`8
    $aux <-> {tgt: symb_target} => (asm { ADDR_SWP_PRG } + tgt)`8
    {tgt: symb_target} <- $aux  => (asm { ADDR_WRT_PRG } + tgt)`8
    addr {op: rsw} {tgt: target} => (asm { ADDR_SWP_PRG } + 3 * op + tgt)`8

    ; operations.
    ; behaves like `c = red_at, ($stk, *c) <- op($stk, *c)`
    ; where `red_at` is `&stk--`, `&aux` or `&stk++`
    ; and op is one of sum_diff|min_max|twise_min_max|swap
    a <- {at: symb_red_at}, $stk <{op: reduce_op}> *a  => (op + at)`8
    a <- &stk--, $stk <swap> *a  => asm { REDU_SWP_TAI }
    a <- &stk++, $stk <swap> *a  => asm { REDU_SWP_HAT }
    reduce {op: reduce_op} {at: red_at} => (op + at)`8

    $stk <{op: reduce_op}> $aux  => (op)`8
    &stk <-> &aux => asm { REDU_SWP_ADR }
    reduce swap tai => asm { REDU_SWP_TAI }
    reduce swap hat => asm { REDU_SWP_HAT }
    nop => asm { REDU_SWP_HED }

    --&stk => asm { REDU_MOV_TAI }
    ++&stk => asm { REDU_MOV_HAT }
    &stk <swap> &aux  => asm { REDU_SWP_ADR }
    $stk <swap> $aux  => asm { STAK_SWP_HED }
    reduce swap addr => asm { REDU_SWP_ADR }



    ; control flow
    *--&stk ? jmp $aux => asm { LOOP_NZ_HAT }
     --$stk ? jmp $aux => asm { LOOP_GT_DECR }
    *++$stk ? jmp $aux => asm { LOOP_NZ_TAIL }

    $stk <= 0 ? jmp $aux => { COND_STK_LE }
    $stk != 0 ? jmp $aux => { COND_STK_NZ }
    $stk >= 0 ? jmp $aux => { COND_STK_GE }

    ; Call instructions: pick jump address from stack while storing current address to aux.
    ; behaves like $aux <- &prg + 1, &prg <- {at: symb_stk_at}stk
    ; where symb_stk_at is one of `*--&`, `$` or `*++&`.
    $aux <- ++&prg <- {at: symb_stk_at}stk => (asm { CALL_STK_HED } + at)`8
}

