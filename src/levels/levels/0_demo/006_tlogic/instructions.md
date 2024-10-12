# Description
The numbers are internally represented in ternary, with figures 0, +1 and -1.
That is, a number `a` has the figures `a_0` `a_1` `a_2` `a_3` `a_4` in `{-1, 0, +1}` such that;
```math
a = a_0+3^0 a_1+3^1 a_2+3^2 a_3+3^3 a_4+3^4
```

The input and output contain numbers.
Your goal is to compute the sum of all their figures, all `2*81*5` of them, modulo 243, and put it in the cell 0.
At the end of the program, the input and the output shall be the same as they were at the beginning, but your program may have changed.

; for later: make several variant: ignore the tape, take the tape at the beginning, take the tape at the end, the script is ran several times consecutively...

#Assembly
TODO TODO
Mention that addition is already modulo 243


# Goals
TODO TODO
; Your goal is to make it so:
; - `out_f.bin` matches `out_x.bin`

## Tests generation
Single test, static files.

# How it works
Write your program in assembly in `solution.asm` and run the command `vns_game.sh`.

Your program is then run with:
- `in_i.bin` as input, at addresses -121 to -41, inclusive
- `out_i.bin` as output, at addresses 41 to 121, inclusive
- `solution.bin` (solution.asm compiled) as program, at adresses -40 to +40, inclusive

When your program halts, you can think of its final state as split between `in_f.bin`, `out_f.bin` and `prg_f.bin`, f standing for final.
These files are then checked in a way specified by the 'descriptions' and goal 'sections', often relying on x files, 'x' standing for expected.
You can usually find a human readable definition of initial and expected files in the corresponding `.asm` files, among other files you can read to get an idea of the inner workings of the tests.

