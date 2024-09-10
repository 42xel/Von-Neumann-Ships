#!/bin/sh

# TODO ? support for stdio and bin.
# Yes, there is vns_vm for that, but vns_vm doesn't have loop.
# There s some slick live programming potential using loop, interactive nb_iter, and tape_in != tape_out for example.
# TODO ask and ponder about whether these should really be initialized here
# or if they should default to potentially set environment variables
nb_iter=1
case=
tape_in=
tape_out=
solution=
quiet=

# TODO option to start fresh ? Special case of tape_in ?
            while [ $# -gt 0 ]; do
            # parsing the options
        case $1 in
    -n|--number-iterations) shift; nb_iter="$1" ;;
    -l|--loop) loop=1 ;;
    -c|--case)  shift; case="$1" ;;
    -i|--input)  shift; tape_in="$1" ;;
    -o|--output)  shift; tape_out="$1" ;;
    -io) shift; tape_in="$1" ; tape_out="$tape_in" ;;
    -s|--solution) shift; solution="$1" ;;
    -q|--quiet) quiet=1 ;;
    *) echo "Unknown parameter passed: $1" ;;
esac
    shift
done

        if test ! -z "$loop" ; then
cat <<- EOS
Loop mode activated.
Press enter to iter once.
Press ^C (ctrl+c) to interrupt.
EOS
read _
fi

# creating the tape name if needed
[ -z "$tape_in" ] && tape_in='tape'"$case"'.bin'
[ -z "$tape_out" ] && tape_out="$tape_in"
# creating the the solution binary if inexistant
[ -z "$solution" ] && solution='solution.bin'
compilation_dir=../../.. make 'in'"$case"'_i.bin' "$solution" 'out'"$case"'_i.bin'
    # TODO define sensible behaviour for quiet and implement it
    [ -z "$quiet" ] || exec 1>/dev/null 2>&1

            # loop once or forever
            while
        # creating and printing the tape if inexistant
        if test $tape_in -nt 'in'"$case"'_i.bin' &&
        test $tape_in -nt $solution &&
        test $tape_in -nt 'out'"$case"'_i.bin' ; then
# Does this work when $tape_in = $tape_out ?
vns_vm -n "$nb_iter" -a < "$tape_in" > .temp_tape_out
cat .temp_tape_out > "$tape_out"
rm .temp_*
vns_print.sh < "$tape_out"
        else
cat 'in'"$case"'_i.bin' $solution 'out'"$case"'_i.bin' > "$tape_out"
printf '\000\330\050' >> "$tape_out"
vns_print.sh < "$tape_out"
fi
test -n "$loop"
do
# TODO: add the ability to override max_iter by reading a number while in loop mode.
read _
done

