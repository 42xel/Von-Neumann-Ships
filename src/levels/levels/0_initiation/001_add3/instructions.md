# Description
The input contains a number at last address illll (-41). Add 3 to it and write the result in the first address of output, liiii (+41).

# Goals
Your goal is to make it so:
- `out_f.bin` matches `out_x.bin`

## Tests generation
Single test, static files.

# TODO reword
# How it works
Write your program in assembly in `prg_i.asm` and run the command `make` (*).

Your program is then run with:
- in0.bin as input, at addresses -121 to -41, inclusive, or ixxxx in ternary
- out0.bin as output, at addresses 41 to 121, inclusive, or lxxxx in ternary
- prg0.bin as program, at adresses -40 to +40, inclusive, or oxxxx in ternary

When your program halts, its final state is split as inf.bin, outf.bin and prgf.bin. f stands for final.
These files are then compared in a way specified by the 'descriptions' and goal 'sections', often relying on x files, standing for expected.
You can usually find a human readable description of initial inputs and outputs in the corresponding .asm files.

(*)
I know, real programmers write machine codes[ http://www.catb.org/jargon/html/story-of-mel.html].
Beware though, as `prg_i.bin` is a .PRECIOUS but .INTERMEDIARY target, meaning if you have an more recent .asm file, it will be overridden.
So if you do be raw dogging binary, stick to it or back it up !
