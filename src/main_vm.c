#include "src/prelude.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "interpreter/interpreter.h"

// TODO operation for the starting file
// TODO operation for stating addresses
// TODO make a man page out of this, and make a better help (more concise, and more precise if you do vns help [OPTIONS]). Maybe generate it from the man page actually.
// TODO option to suppress the timeout error code ?
// set by default if -a ?
// TODO option to format the output customizedly
            fn result main(int argc, char** argv) { result r;
	// Parsing arguments definitions
unsigned max_iter = 1000;
bool include_addresses = 0;
Cell prg = 0;
Cell stk = -40;
Cell aux = +40;
	static struct option long_options[] = {
{"number-iterations", required_argument, 0, 'n'},
{"addresses", no_argument, 0, 'a'},
{"no-addresses", no_argument, 0, 'A'},
{0, 0, 0, 0}
};
// Parsing
int opt;
			while ((opt = getopt_long(argc, argv, "n:aA", long_options, NULL)) != -1) {
		switch (opt) {
	case 'n': max_iter = atoi(optarg); break;
	case 'a': include_addresses = 1; break;
	case 'A': include_addresses = 0; break;
	default:
fprintf(stderr, "Usage: %s [-n number-iterations] [-a] [-A]\n", argv[0]);
return EXIT_FAILURE; }
}

	// Running the interpreter
freopen(NULL, "rb", stdin); freopen(NULL, "wb", stdout);
Cell const _tape[243]; Tape tape = _tape + 121;
if (fread(_tape, sizeof(Cell), 243, stdin) != 243) return _ERR_IO;
		if (include_addresses) {
// ignore errors and keep default value if missing
fread(&prg, sizeof(Cell), 1, stdin);
fread(&stk, sizeof(Cell), 1, stdin);
fread(&aux, sizeof(Cell), 1, stdin);
}
	// The actual running part
r = n_steps(tape, &prg, &stk, &aux, max_iter);
	// Writing the output
if (fwrite(_tape, sizeof(Cell), 243, stdout) != 243) return _ERR_IO;
		if (include_addresses) {
if (fwrite(&prg, sizeof(Cell), 1, stdout) != 1) return _ERR_IO;
if (fwrite(&stk, sizeof(Cell), 1, stdout) != 1) return _ERR_IO;
if (fwrite(&aux, sizeof(Cell), 1, stdout) != 1) return _ERR_IO;
}
return r; }

