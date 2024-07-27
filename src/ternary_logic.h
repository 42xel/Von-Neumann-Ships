// A module to deal with ternary logic:
// converting from byte (eight bits, 2^8)
// to five trits (3^5) and back;
// displaying such units group;
// maybe other things;

#ifndef ternary_logic
#define ternary_logic

typedef signed char Cell;
typedef signed short Atrit;
typedef unsigned short Ltrit;

/// The conversion functions aren't meant to be used,
/// instead the following tables should be used.
static const Ltrit* LTRIT;
static const Cell* L2BIN;
static const Atrit* ATRIT;
static const Cell* A2BIN;
/// Initialise the tables above, and register custom printf functions.
/// Calling it a secnd time does nothing.
void init();

/**
Converts a signed byte to 5 arithmetical trits,
Provided the values are within [-121, +121].
        # Arithmetic Trits.
The system used is base 3, but with the symbol values -1, 0 and 1.
    ## Representation
In the emulator, the values are stored as 2 bits, 2 complements numbers.
thusly:
* -1 is represented by 11
*  0 is represented by 00
* +1 is represented by 01
* 10 corresponds to nothing
The five double bits are stored in the least significant bits
of a signed short.
Arithmetic shift allows to retrieve the values -1, 0 and +1.
    ## Display
The symbols used for display are
* i for -1
* o for  0
* l for +1
Numbers from 0 to +5 :
o, l, li, lo, ll, lii
Minus 6 :
ilo
*/
Atrit to_atrit (Cell n);
/// Convert from arithmetic trits to byte.
/// See `to_atrit` for an explanation on arith trits.
Cell from_atrit (Atrit a);
/**
Converts a signed byte to logical trits.
        # Logical Trits.
They're arithmetical trits, but -1 means false, 1 true and 0 maybe.
    ## Representation
In the emulator, the values are stored as increasing 2 bits among
00, 01, 11. Increasing in the sense false < maybe < true
thusly:
* -1 is represented by 11
*  0 is represented by 00
* +1 is represented by 01
* 10 corresponds to nothing
An other way to view it is as regular ternary with values 0 1 and 2
represented in unary. Values in [0, 242] are encoded and are mapped
increasingly to signed bytes of values [-121, +121].
Either way, the five double bits are stored in the least significant bits
of an unsigned short.
Logical shift allows to retrieve the values 00, 01 and 11.
    ## Display
The symobls used for display are
* n for 00 (*n*ot, and is mirror of u)
* m for 01 (*m*aybe)
* u for 11 (tru*e*)
Some numbers :
nmumu, nunu
Numbers are preferably displayed of length 5, if some are ommited, assume
leading `m`s.
*/
Ltrit to_ltrit (Cell n);
/// Convert from logical trits to byte.
/// See `to_ltrit` for an explanation on logical trits.
Cell from_ltrit (Ltrit l);
/// Convert from arithmetic to logical.
Ltrit arith_log (Atrit a);

Cell rand243();
Cell wrap243(Cell n);

#endif
