#!/bin/sh

# At simplest, the printer is :
# xxd -g1 -c9 -o -121

# Without too much effort, hexdump may be leveraged for a more beuatiful result:

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

