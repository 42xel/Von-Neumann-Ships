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
}

#subruledef target
{
    stk => -1
    prg => 0
    aux => 1
}
#subruledef stk_at
{
    hat => -1
    hed => 0
    tai => 1
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
#subruledef reduce_op
{
    add_minus => asm { REDU_ADM_HED }
    min_max => asm { REDU_MNX_HED }
    twise_min_max => asm { REDU_TNX_HED }
    swap => asm { REDU_SWP_HED }
    ; TODO: handle swp separately ? not nec
    mov => asm { REDU_SWP_ADR }
}

; TODO syntax like *stk++, *--stk, **aux
#ruledef
{
    load stk {at: stk_at}, {val: Cell} => (asm { LOAD_STK_HED } + at)`8 @ val
    halt, {val: Cell} => asm { LOAD_PRG_HLT } @ val
    halt => asm { LOAD_PRG_HLT }
    noop => asm { LOAD_PRG_NOP }
    noop, {val: Cell} => asm { LOAD_PRG_NOP } @ val
    load aux adr => asm { LOAD_AUX_ADR }
    load aux dir => asm { LOAD_AUX_DIR }
    load aux ind => asm { LOAD_AUX_IND }

    {op: rsw} {at: stk_at} => (asm { STAK_SWP_HED } + 3 * op + at)`8
    push => asm { STAK_WRT_TAI }
    empl => asm { STAK_WRT_HED }
    dpush=> asm { STAK_WRT_HAT }
    pop  => asm { STAK_REA_TAI }
    peek => asm { STAK_REA_HED }
    dpop => asm { STAK_REA_HAT }

    addr {op: rsw} {tgt: target} => (asm { ADDR_SWP_PRG} + 3 * op + tgt)`8

    reduce {op: reduce_op} {at: red_at} => (op + at)`8
    ; reduce swap addr { REDU_SWP_ADR }
}

