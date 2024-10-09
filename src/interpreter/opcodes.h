#ifndef opcodes_h
# define opcodes_h

      enum opcodes
//: signed char 
{
LOAD_STK_HAT = -4,
LOAD_STK_HED = -3,
LOAD_STK_TAI = -2,
LOAD_PRG_JMP = -1,
LOAD_PRG_HLT =  0,
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

LOOP_NZ_HAT = 5,
LOOP_GT_DECR = 6,
LOOP_NZ_TAIL = 7,
COND_STK_LE = 8,
COND_STK_NZ = 9,
COND_STK_GE = 10,
CALL_STK_HAT = 11,
CALL_STK_HED = 12,
CALL_STK_TAI = 13,


// PONDER?
/// As a way to error or wrap without having to
/// check for program pointer overflow every time.
// not a good idea, the function step will, eventually, need to be
// reliable. The alternative is making the check every time we use
// prg, which might become a lot more places than whenever we modify
// it. Much simpler to always have prg correct.
};

#endif

