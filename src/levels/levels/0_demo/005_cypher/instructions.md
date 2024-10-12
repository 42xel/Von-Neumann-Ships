# Description
The input contains three numbers at its first three addresses -121, -120, -119.
The output contains 81 numbers.
Apply a circular cipher to the output, by adding to each output number each input number, looping.

For example, if the input is [1, 0, -4] and the output starts as 45, 23, 32, -66, 75, 7, ...
You are to transform the output to:
46, 23, 28, -65, 75, 3

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

