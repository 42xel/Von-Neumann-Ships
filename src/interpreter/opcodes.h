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

REDU_ADD_HAT = -121,
REDU_ADD_HED = -120,
REDU_ADD_TAI = -119,

REDU_ADM_HAT = -118,
REDU_ADM_HED = -117,
REDU_ADM_TAI = -116,

REDU_MNX_HAT = -115,
REDU_MNX_HED = -114,
REDU_MNX_TAI = -113,




REDU_TNX_HAT = -112,
REDU_TNX_HED = -111,
REDU_TNX_TAI = -110,

REDU_SWP_HAT = -109,
REDU_SWP_HED = -108,
REDU_SWP_TAI = -107,

REDU_MOV_HAT = -106,
REDU_SWP_ADR = -105,
REDU_MOV_TAI = -104,

REDU_TAM_HED = -103,
REDU_TAM_TAI = -102,
REDU_TAM_HAT = -101,

REDU_DVM_HED = -100,
REDU_DVM_TAI = -99,
REDU_DVM_HAT = -98,

REDU_MUL_HED = -97,
REDU_MUL_TAI = -96,
REDU_MUL_HAT = -95,

FIXED_SIEV = 5,
FIXED_OUSV = 6,
FIXED_SPLT = 7,
FIXED_SHAK = 8,
FIXED_XOR  = 9,




LOOP_NZ_HAT = 14,
LOOP_DECR_GT = 15,
LOOP_NZ_TAIL = 16,
COND_STK_LE = 17,
COND_STK_NZ = 18,
COND_STK_GE = 19,
CALL_STK_HAT = 20,
CALL_STK_HED = 21,
CALL_STK_TAI = 22,


// PONDER?
/// As a way to error or wrap without having to
/// check for program pointer overflow every time.
// not a good idea, the function step will, eventually, need to be
// reliable. The alternative is making the check every time we use
// prg, which might become a lot more places than whenever we modify
// it. Much simpler to always have prg correct.
};

#endif

