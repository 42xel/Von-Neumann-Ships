#define result char
// fish interprets error codes as unsigned char, but I guess
// using computer word length with int would be more efficient.
#define _ERR_OTHER 1
#define _ERR_IO 2
#define _ERR_ARGC 3
#define _ERR_ARGV 4
