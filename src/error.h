#ifndef error_h_INCLUDED
#define error_h_INCLUDED

typedef enum errors {
_ERR_OTHER = 1,
_ERR_IO = 2,
_ERR_ARGC = 3,
_ERR_ARGV = 4,
_ERR_PARAM = 5,
_ERR_MEM = 6,
_ERR_TIMEOUT = 7,
_ERR_NAOP = 15,
_ERR_WIP = 16,
/// a machine halted without error. 0 is continue.
_SUCCESS = 128,
} result;

#endif // error_h_INCLUDED
