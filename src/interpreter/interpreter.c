#include "src/prelude.h"
#include "interpreter.h"
#include "src/interpreter/opcodes.h"
#include "../load/load.h"
#include "../ternary_logic.h"

            pub fn result step (
Tape tape
, Cell* prg
, Cell* stk
, Cell* aux
) { Cell *a; Cell c, v, w;
Cell instruction = tape[xpp243(prg)];
      switch (instruction) {
case LOAD_STK_HAT: fprintf(stderr, "LOAD_STK_HAT\n"); tape[mmx243(stk)] = tape[xpp243(prg)]; return 0;
case LOAD_STK_HED: fprintf(stderr, "LOAD_STK_HED\n"); tape[*stk]        = tape[xpp243(prg)]; return 0;
case LOAD_STK_TAI: fprintf(stderr, "LOAD_STK_TAI\n"); tape[ppx243(stk)] = tape[xpp243(prg)]; return 0;
case LOAD_PRG_JMP: fprintf(stderr, "LOAD_PRG_JMP\n"); *prg              = tape[*prg];        return 0;
case LOAD_PRG_HLT: fprintf(stderr, "LOAD_PRG_HLT\n"); *prg              = wrap243(++*prg);   return _SUCCESS;
case LOAD_PRG_NOP: fprintf(stderr, "LOAD_PRG_NOP\n"); xpp243(prg);                           return 0;
case LOAD_AUX_ADR: fprintf(stderr, "LOAD_AUX_ADR\n"); *aux              = tape[xpp243(prg)]; return 0;
case LOAD_AUX_DIR: fprintf(stderr, "LOAD_AUX_DIR\n"); tape[*aux]        = tape[xpp243(prg)]; return 0;
case LOAD_AUX_IND: fprintf(stderr, "LOAD_AUX_IND\n"); tape[tape[*aux]]  = tape[xpp243(prg)]; return 0;

case STAK_WRT_HAT: fprintf(stderr, "STAK_WRT_HAT\n"); tape[mmx243(stk)] = tape[*aux]; return 0;
case STAK_WRT_HED: fprintf(stderr, "STAK_WRT_HED\n"); tape[*stk]        = tape[*aux]; return 0;
case STAK_WRT_TAI: fprintf(stderr, "STAK_WRT_TAI\n"); tape[ppx243(stk)] = tape[*aux]; return 0;
case STAK_SWP_HAT: fprintf(stderr, "STAK_SWP_HAT\n"); return _ERR_WIP;
case STAK_SWP_HED: fprintf(stderr, "STAK_SWP_HED\n"); return _ERR_WIP; // redundant /w REDU_SWP_HED ?
case STAK_SWP_TAI: fprintf(stderr, "STAK_SWP_TAI\n"); return _ERR_WIP;
case STAK_REA_HAT: fprintf(stderr, "STAK_REA_HAT\n"); tape[*aux] = tape[xpp243(stk)]; return 0;
case STAK_REA_HED: fprintf(stderr, "STAK_REA_HED\n"); tape[*aux] = tape[*stk]       ; return 0;
case STAK_REA_TAI: fprintf(stderr, "STAK_REA_TAI\n"); tape[*aux] = tape[xmm243(stk)]; return 0;

case ADDR_REA_STK: fprintf(stderr, "ADDR_REA_STK\n"); tape[*aux] = *stk;                        return 0;
case ADDR_REA_PRG: fprintf(stderr, "ADDR_REA_PRG\n"); tape[*aux] = *prg;                        return 0;
case ADDR_REA_AUX: fprintf(stderr, "ADDR_REA_AUX\n"); tape[*aux] = *aux;                        return 0;
case ADDR_SWP_STK: fprintf(stderr, "ADDR_SWP_STK\n"); *stk ^= tape[*aux] ^= *stk ^= tape[*aux]; return 0;
case ADDR_SWP_PRG: fprintf(stderr, "ADDR_SWP_PRG\n"); *prg ^= tape[*aux] ^= *prg ^= tape[*aux]; return 0;
case ADDR_SWP_AUX: fprintf(stderr, "ADDR_SWP_AUX\n"); *aux ^= tape[*aux] ^= *aux ^= tape[*aux]; return 0;
case ADDR_WRT_STK: fprintf(stderr, "ADDR_WRT_STK\n"); *stk = tape[*aux];                        return 0;
case ADDR_WRT_PRG: fprintf(stderr, "ADDR_WRT_PRG\n"); *prg = tape[*aux];                        return 0;
case ADDR_WRT_AUX: fprintf(stderr, "ADDR_WRT_AUX\n"); *aux = tape[*aux];                        return 0;

   case REDU_ADM_HAT: fprintf(stderr, "REDU_ADM_HAT\n"); c = xpp243(stk); goto add_minus;
   case REDU_ADM_HED: fprintf(stderr, "REDU_ADM_HED\n"); c = *aux;        goto add_minus;
   case REDU_ADM_TAI: fprintf(stderr, "REDU_ADM_TAI\n"); c = xmm243(stk); goto add_minus;
   add_minus:
v = wrap243(tape[*stk] + tape[c]);
w = wrap243(tape[*stk] - tape[c]);
fprintf(stderr, "%d %d\n", *stk, c);
fprintf(stderr, "%d %d\n", v, w);
// PONDER : what if *aux == *stk ? Set it to 0 ?
tape[*stk] = v; tape[c] = w; return 0;

   case REDU_MNX_HAT: fprintf(stderr, "REDU_MNX_HAT\n"); c = xpp243(stk); goto min_max;
   case REDU_MNX_HED: fprintf(stderr, "REDU_MNX_HED\n"); c = *aux;        goto min_max;
   case REDU_MNX_TAI: fprintf(stderr, "REDU_MNX_TAI\n"); c = xmm243(stk); goto min_max;
   min_max:
if (tape[c] < (v = tape[*stk])) tape[*stk] = tape[c], tape[c] = v;
return 0;

// tritwise min max
case REDU_TNX_HAT: fprintf(stderr, "REDU_TNX_HAT\n"); return _ERR_WIP;
case REDU_TNX_HED: fprintf(stderr, "REDU_TNX_HED\n"); return _ERR_WIP;
case REDU_TNX_TAI: fprintf(stderr, "REDU_TNX_TAI\n"); return _ERR_WIP;

   case REDU_SWP_HAT: fprintf(stderr, "REDU_SWP_HAT\n"); c = xpp243(stk); goto swap;
   case REDU_SWP_HED: fprintf(stderr, "REDU_SWP_HED\n"); c = *aux;        goto swap;
   case REDU_SWP_TAI: fprintf(stderr, "REDU_SWP_TAI\n"); c = xmm243(stk); goto swap;
   swap: // Using an auxiliary variable dodges *aux == *stk issues.
v = tape[*stk]; tape[*stk] = tape[c]; tape[c] = v;
return 0;

case REDU_MOV_HAT: fprintf(stderr, "REDU_MOV_HAT\n"); xpp243(stk);                  return 0;
case REDU_SWP_ADR: fprintf(stderr, "REDU_SWP_ADR\n"); *stk ^= *aux ^= *stk ^= *aux; return 0;
case REDU_MOV_TAI: fprintf(stderr, "REDU_MOV_TAI\n"); xmm243(stk);                  return 0;



   default: return _ERR_NAOP; } }

//             pub fn result trace_step (
// Tape tape
// , Cell* prg
// , Cell* stk
// , Cell* aux
// // , TODO some stream/ string to trace the step
// ) {
// // TODO
//     return 0; }

/// Runs the machine until it stops or reached n iterations.
/// Set n to a negative vaue to have no iteration limit.
/// If tape, prg, stk or aux are not NULL, default values are provided
             pub fn result n_steps (
Tape tape
, Cell* prg
, Cell* stk
, Cell* aux
, unsigned n
) { result r;
if (tape == NULL) return _ERR_MEM;
Cell _prg = 0;  if (prg == NULL) prg = &_prg;
Cell _stk = -40; if (stk == NULL) stk = &_stk;
Cell _aux = 40; if (aux == NULL) aux = &_aux;
         for (signed i = n;--i != 0;)
if (r = step(tape, prg, stk, aux)) return r == _SUCCESS ? 0 : r;
   return _ERR_TIMEOUT;
}

            fn result test_halt() { result r;
Cell prg = 0, stk = -40, aux = 40;
Cell _tape[243]; Tape tape = _tape + 121 * sizeof(Cell);
if (r = load(NULL, NULL, NULL, tape)) return r;
if (r = step(tape, &prg, &stk, &aux)) return r == _SUCCESS ? 0 : r;
return _ERR_TIMEOUT; }

//             fn result _test_load_stk_once(Cell value, Cell offset) {
// result r;
// Cell prg = 0, stk = -40, aux = 40;
// Cell _tape[243]; Tape tape = _tape + 121 * sizeof(Cell);
// if (r = load(NULL, NULL, NULL, tape)) return r;
// tape[prg++] = LOAD + offset;
// tape[prg--] = value;
// char* t[9] = {
// &tape[stk-1], &tape[stk],   &tape[stk+1],
// $prg,         &tape[prg+1], &tape[prg+1],
// &aux,         &tape[aux],   &tape[tape[aux]]
// }
//    char* targ = t [5 + offset];
// if ((r = step(tape, &prg, &stk, &aux))) return r;
//       if ((r = step(tape, &prg, &stk, &aux)) != _SUCCESS)
// return r ? r : _ERR_TIMEOUT;
// if (r = (*targ - value)) return r;
// return 0; }

// test:
// timeout

