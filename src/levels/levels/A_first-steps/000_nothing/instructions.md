# Description
The input contains a number at last address illll (-41).
If that number is zero, output a non zero number at liiii (+41).
If that number is non zero, output a zero.

# Goals
Your goal is to make it so:
- `out1.bin` matches `outx.bin`

## Tests generation
Single test, static files.
# TODO multiple test static files
# TODO exhaustive testing

# TODO reword
# How it works
Write your program in machine code in `prg.bin`.
Real programmer write machine codes[ http://www.catb.org/jargon/html/story-of-mel.html].
You can use the template `prg.asm` along with customasm to generate it.

Your program is then run with:
- `in0.bin` as input, at addresses -121 to -41, inclusive, or ixxxx in ternary
- `out0.bin` as output, at addresses 41 to 121, inclusive, or lxxxx in ternary
- `prg0.bin` as program, at adresses -40 to +40, inclusive, or oxxxx in ternary

When your program halts, its final state is split as `inf.bin`, `outf.bin` and `prgf.bin`. f stands for final.
These files are then compared in a way specified by the 'descriptions' and goal 'sections', often relying on x files, standing for expected.
You can usually find a human readable description of initial inputs and outputs in the corresponding `.asm` files.

