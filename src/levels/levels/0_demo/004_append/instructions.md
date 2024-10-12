# Description
The input contains a number at its last address -41.
The output contains a sequence of non zero numbers, starting from its first address +41.
The list is garrantied to be of length 80 at most.

# Assembly


# Goals
Your goal is to make it so:
- `out_f.bin` matches `out_x.bin`

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

