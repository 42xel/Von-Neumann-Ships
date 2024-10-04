#include "src/prelude.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "interpreter/interpreter.h"

# define USAGE_MESSAGE(prog_name) \
fprintf (stderr, "\
Usage: %s [OPTIONS]\n\
\n\
vns_vm runs the VNS interpreter, simulating iterations on the provided tape.\n\
\n\
Options:\n\
  -n, --number-iterations <N>  Set the maximum number of iterations (default: 1000)\n\
  -a, --addresses              Include program (prg), stack (stk), and auxiliary (aux) registers in the output\n\
  -A, --no-addresses           Do not include program (prg), stack (stk), and auxiliary (aux) registers in the output (default)\n\
  -h, --help                   Show this help message and exit\n\
\n\
Description:\n\
  - vns_vm reads a tape of 243 cells from stdin, simulates up to N iterations, and writes the resulting tape back to stdout.\n\
  - If the -a or --addresses flag is set, the registers (prg, stk, aux) will also be read from stdin and written to stdout.\n\
  - This program operates in binary mode, reading and writing data in raw form.\n\
\n\
Exit codes:\n\
  0    Success\n\
  1    Failure during IO operations\n\
\n\
Examples:\n\
  %s -n 500 < input_tape.bin > output_tape.bin\n\
  %s --addresses < input_with_registers.bin > output_with_registers.bin\n\
", prog_name, prog_name, prog_name); 

// TODO operation for files other than stdio
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
{"help", no_argument, 0, 'h'},
{0, 0, 0, 0}
};
// Parsing
int opt;
			while ((opt = getopt_long(argc, argv, "n:aAh", long_options, NULL)) != -1) {
		switch (opt) {
	case 'n': max_iter = atoi(optarg); break;
	case 'a': include_addresses = 1; break;
	case 'A': include_addresses = 0; break;
	case 'h': USAGE_MESSAGE(argv[0]); return EXIT_SUCCESS;
	case '?': 
// getopt_long already generates the message for unrecognized option.
fprintf(stderr, "Usage: %s [-n number-iterations] [-a] [-A]\n", argv[0]);
return EXIT_FAILURE;
	default:
fprintf(stderr, "Unexpected error while parsing options.\n");
return EXIT_FAILURE; } }
// Handle non-option arguments
		if (optind < argc) {
fprintf(stderr, "Unrecognized non-option argument: %s\n", argv[optind]);
fprintf(stderr, "Usage: %s [-n number-iterations] [-a] [-A]\n", argv[0]);
return EXIT_FAILURE; }

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

