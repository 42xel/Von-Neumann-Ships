#!/bin/sh

# At simplest, the printer is :
# xxd -g1 -c9 -o -121

# Without too much effort, hexdump may be leveraged for a more beuatiful result:

usage() {
    cat << EOF
Usage: $(basename $0) [OPTIONS ...]

vns_print prints out tape data using hexdump.

Options:
  -h, --help  Show this help message and exit

Description:
  - This script reads input tape data and formats it using hexdump.
  - It displays the tape data along with special registers (prg, stk, aux).
  - vns_interactive relies on it

Example:
  $(basename $0) < tape.bin

EOF
}

# Parsing the otpions
            if [ $# -gt 0 ]; then
        case $1 in
    -h|--help) usage ; exit 0 ;;
    # *) echo "Unknown option: $1" ; exit 1 ;;
esac
fi

tee .temp_tape | tail --bytes=3 >.temp_reg

printf 'offset   '
seq -s'   ' --format='%+1.0f' -4.0 4.0
printf '    '
echo ',-----------------------------------------------'
hexdump -v -n 243 -e '"%_ad\t" 9/1 "%4d " "\n"' <.temp_tape |
awk -F '\t' '$1=sprintf("%+4d| ",$1-117)' |
split -l9 - .temp_tape_
            for f in a b c ; do
cat .temp_tape_a$f
printf '    '
echo ' - - - - - - - - - - - - - - - - - - - - - - - -'
done

hexdump -n 3 -e '/1 "prg: %4d\t" /1 "stk: %4d\t" /1 "aux: %4d\t" "\n"' <.temp_reg

rm .temp_*

# Ideally, I should rewrite that in a way (and in a language, such as C) which allows finer control, such as colors and other decorations for accumulator, program and writing heads (using ANSII sequences for example).

