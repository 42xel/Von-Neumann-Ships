# NAME vns
Von Neumann Ships. The virtual machine running vns machine code.


# SYNOPSIS
## vns [OPTIONS]
Runs a virtual vns machine, taking stdin as the program and printing the final state in stdout.


# DESCRIPTION
A vns machine is a Von Neumann machine in the sense that the program is homogeneous with the data.
That data is a tape of 243 bytes representing 243 signed integers wetween -121 and 121 (both included).
On top of the tape, this machine has three registers, 'stk', 'prg' and 'aux' whose value represent an address of the tape.


# OPTIONS
## -n, --number-iterations <n>
The maximum number of instructions to run the virtual machine before timing out.
Negative values means infinity, running the machine until it stops on its own.
The default value is -2


## -a, --addresses
Includes the addresses of the stack, program head and auxiliary counter at the end of the input and the output.
It is the defaut if `--nb--iterations` is set to 0, 1 or -1.
## -A, --no-addresses
Only outputs the tape, not the addresses, and assumes default initial values for them.


# EXIT VALUES
0 if the program successfully terminated.

7 if the program timed out.


# EXAMPLES
```console
vns -n 1000 < input_tape > output_tape
```
```console
cat -n in.bin0 prg.bin0 out.bin0 | vns 1000 | split -n 3
```
```console
vns -n 1000 -a < input_tape | head -c -3
```

