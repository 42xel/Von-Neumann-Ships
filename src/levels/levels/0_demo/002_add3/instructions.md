# Description
The input contains a number at its last address -41.
Add 3 to it and write the result in the first output address, +41.

# Assembly
`&stk <-> &aux`
swaps the stack and the auxiliary register.
`$stk <-> $aux`
swaps the stack and the auxiliary register values.

`a <- &stk--, $stk <sum_diff> *a`
folds the top two elements of the stack into their sum, also leaving the difference to the former head of the stack.
Applied on : `[45, *27*]` with the stack head pointing on `27` will result in `[*72*, 18]`, with the stack head moved down once to the cell now containing 72.

You can also fold the other way:
`a <- &stk++, $stk <sum_diff> *a`,
or operate with the auxiliary register `$stk <sum_diff> $aux`.

There are other operations, such as `min_max` and `swap` and `identity`.
In particular, `$stk <swap> $aux` is equivalent to `$stk <-> $aux`, and there also exists `&stk <swap> &aux`.

`a <- &stk--, $stk <identity> *a` and `a <- &stk++, $stk <identity> *a` just move the head and `$stk <identity> $aux` does nothing.
They are respectively abbreviated `--&stk`, `++&stk` and `nop`.


If you need more details about vns assembly, open `definition.asm` and read the comments.

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

