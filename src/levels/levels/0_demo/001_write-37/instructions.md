# Welcome !
Welcome to Von Neumann Ships, the game where you write self-modifying assembly.

The machine you'll program operates on a tape of 243 cells, each containing signed integers between -121 and +121, both included.
These integers may represent themselves, position on the tape, or machine code
(The tape's cells are indexed by values between -121 and +121).
The first 81 cells are typically used for input, the last 81 for output, and the 81 middle ones for your program.
The machine has 3 registers:
- `prg`: the position of the program's head, in other words the currently executed instruction. The initial position is `0`.
- `stk`: The position of the machine's stack. The initial position is `-40`
- `aux`: an auxiliary register, which also represent a postion in the tape. The initial position is `+40`

When describing instructions, I'll use `&reg` to talk about the position of a register, `$reg` to talk about the value at the reigster position (`tape[&reg]`) and `*reg` to apply one level of indirection from `$reg` (in other words, `*reg` is `tape[$reg]`). For example, reading the instruction:
```assembly
# addr 0
load aux ind, 43
#addr 40
16
```
`&prg` is `0`, `$prg` is `4`.
The machine code of `load aux ind`, meaning load value into the auxiliary register with one level of indirection.
Assuming the current value of `&aux` is 40, and that cells haven't been modified, the value of `$aux` is `16`.
After that instruction, the value of `tape[16]`, which we can also refer to as `*aux`, is `43`.
In fact this program is also preferably written as:
```assembly
#addr 0
*aux <- 43
#addr 40
16
```

The instructions of each level contains the following sections:
- Welcome : for the fisrt level of a chapter
- Description: a description of the problem
- Assembly: a list of relevant new assembly instructions related to the problem
- Goals: a technical description of what you want to achieve, what test you have to pass.
- How it works: a reminder of how the game works

If you want to know all about the instruction set, you can read the 'definition.asm' file.

Why 243 ? One of the quirks of this game is that numbers are represented in ternary.
243 is 3 to the power of 5, and conveniently is a tight fit under 256 (2^8, or the number of different values a byte can take).

# Description
In this level, you are tasked to write 37 in the first output address +41.

# Assembly
`&stk <-> &aux`
swaps the stack and the auxiliary register.

`lhs <- cte`
Where `cte` is a number and `lhs` is one of: `&prg`, `*--&stk`, `$stk`, `*++&stk`, `&aux`, `$aux`, `*aux`
loads a number from the program to the receiver described by the left hand side.
This instruction takes up 2 cells, one for `lhs <-`, and one for `cte`


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

