#include "src/prelude.h"
#include "interpreter.h"
#include "opcodes.h"
#include "../load/load.h"
#include "../ternary_logic.h"

// for now, registers are at a fixed address:
// *0 for prg
// *0iiii for stk ; defaults to i0000 ?
// *01111 for write : defaluts to 10000 ?
// there is one normal clock at 0

// //             fn signed char deref
// // (signed char addr, signed char tape[243]){
// // return tape[addr];}
//             fn signed char* deref
// (const signed char tape[243], const signed char* addr){
// return &tape[*addr];}
//             fn void set
// (signed char* const addr, const signed char value){
// *addr = value;}

pub fn result step (
signed char tape[243]
, signed char* prg
, signed char* stk
, signed char* aux
) {
        switch (tape[*prg++]) {
    case HALT: return _SUCCESS;
    default: return _ERR_NAOP;
}
    return 0; }

pub fn result trace_step (
Tape tape
, signed char* prg
, signed char* stk
, signed char* aux
// , TODO some stream/ string to trace the step
) {
// TODO
    return 0; }

fn result test_halt() {
signed char prg = 0, stk = -40, aux = 40;
signed char _tape[243]; Tape tape = _tape + 121 * sizeof(Cell);
result r;
if (r = load(NULL, NULL, NULL, tape)) return r;
    if (r = step(tape, &prg, &stk, &aux)) return
r == _SUCCESS ? 0 : r;
    return _ERR_TIMEOUT; }
/*
fn result test_load_stk_once(signed char value, signed char offset) {
signed char prg = 0, stk = -40, aux = 40;
signed char _tape[243]; Tape tape = _tape + 121 * sizeof(Cell);
tape[prg++] = ;
        result r; for(int _ = 1000; --_;)
    if ((r = step(tape, &prg, &stk, &aux))) return
r == _SUCCESS ? 0 : r;
    return _ERR_TIMEOUT; }
    */
// test:
// timeout

