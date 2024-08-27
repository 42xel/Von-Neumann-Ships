#include "src/prelude.h"
#include <stdio.h>
#include <stdlib.h>
#include "interpreter/interpreter.h"

static const char* help = "\
usage (unstable): vns [<max iterations>]\n\
for example:\n\
vns 1000 < input_tape > output_tape\n\ 
cat in.bin0 prg.bin0 out.bin0 | vns 1000 | split -n 3 \n\ 
\n";

            fn result main(int argc, char** argv) { result r;
freopen(NULL, "rb", stdin); freopen(NULL, "wb", stdout);
Cell const _tape[243]; Tape tape = _tape + 121;
if (fread(_tape, sizeof(Cell), 243, stdin) != 243) return _ERR_IO;
unsigned max_iter = 1000;
if (argc >= 2) max_iter = atoi(argv[1]);
r = n_steps(tape, NULL, NULL, NULL, max_iter);
if (fwrite(_tape, sizeof(Cell), 243, stdout) != 243) return _ERR_IO;
return r;
return 0; }
