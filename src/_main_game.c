#include "src/prelude.h"
// // #include "interpreter/interpreter.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>  // For chdir(), getcwd()
// #include <limits.h>  // For PATH_MAX
// #include <libgen.h>  // For dirname(), basename()
// #include <sys/types.h>
// #include <dirent.h>

// 				fn result main(int argc, char** argv) { result r;
// // static const char* help = "\
// // The CLI (unstable) version of the game. \
// // SYNOPSIS
// // 	vns_game [run] [OPTIONS ...] [LEVELS ...] \n\
// // 	vns_game next [OPTIONS ...]\n\
// // DESCRIPTION
// // 	vns_game helps you play the game, by mostly handling savegames, progression, and level submissions.
// // 	The first format run your solution(s) against the test cases.
// // 	The second one 
// // OPTIONS
// // 		Outputs the path of the next level to solve to stdin and prints the instructions to stderr.
// // \n";

// // 	// opening save folder if any
// // auto save_dir = NULL;
// // // TODO: automatically create it ?
// // 		if (argc >= 1 && argv[1] != NULL) if (!(save_dir = opendir(argv[1])))
// // {perror("opening provided save dir"); return _ERR_IO;}
// // 	// cwd to project root
// // char* build_dir = dirname(argv[0]);
// // char* root = dirname(build_dir);
// // free (build_dir);
// // if (r = chdir(root)) {perror("changing wd to project root"); return r};
// // free (root);
// // // TODO: automatically create dir ?
// // 		if (save_dir == NULL) if (!(save_dir = opendir("save")))
// // {perror("opening default save dir"); return _ERR_IO;}

// return 0; }
