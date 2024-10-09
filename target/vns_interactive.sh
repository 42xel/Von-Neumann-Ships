#!/bin/sh

# TODO ? support for stdio and bin.
# Yes, there is vns_vm for that, but vns_vm doesn't have loop.
# There's some slick live programming potential using loop, interactive nb_iter, and tape_in != tape_out for example.
# TODO ask and ponder about whether these should really be initialized here
# or if they should default to potentially set environment variables
nb_iter=1
case=
tape_in=
tape_out=
solution=
quiet=
start_over=

usage() {
    cat << EOF
Usage: $(basename $0) [OPTIONS ...]

This script allows you to run iterations on tapes and solutions, with optional loop mode for interactive live programming.

Description:
  - If no input tape is specified, the script will default to 'tape<case>.bin'.
  - The output tape file will default to the input file unless specified separately.
  - The solution binary defaults to 'solution.bin' if not provided.
  - Loop mode allows you to iterate interactively. Press Enter to continue to the next iteration, and Ctrl+C to interrupt.
  - The script automatically creates input/output files if they don't exist and runs the \`vns_vm\` for processing the tapes.

Options:
  -n, --number-iterations <N> Set the number of iterations (default: 1)
  -l, --loop                  Enable loop mode for interactive execution
  -c, --case <case_no>        Specify the case number to run (default: '')
  -i, --input <file>          Specify the input tape file (default: tape$case.bin)
  -o, --output <file>         Specify the output tape file (default: tape$case.bin)
  -io <file>                  Set both input and output tapes at once
  -s, --solution <file>       Specify the solution file (default: solution.bin)
  -f, --fresh                 Starts over (deletes tape_in before starting simulation)
  -q, --quiet                 Suppress output
  -h, --help                  Show this help message and exit

Tape:
A tape is a binary file consisting in 243 to 246 byte.
The first 81 bytes correspond to the input of the test case.
The next 81 ones correspond to your solution.
The next 81 correspond to the output of the test case.
The last 3 bytes correspond the value of the registers:
- the program head posiiton
- the stack head position
- the auxiliary register

Aside from vns_interactive, \`vns_vm -a\` also understands that tape format.

Examples:
  1. Run with default settings:
     $(basename $0)

  2. Enable loop mode for interactive iteration:
     $(basename $0) --loop

  3. Set custom files:
     $(basename $0) --input tape_in.bin --output tape_out.bin --solution custom_solution.bin

  4. Set the number of iterations:
     $(basename $0) --number-iterations 5

  5. Use watch to loop precisely every second, highlight differences, and quit after 3 seconds once done:
     watch -pn 1 -d -q 3 $(basename $0)

EOF
# forces a flush apparently. I ran into a situation where it seemed necessary.
printf "\n"
}

# TODO option to start fresh ? Special case of tape_in ?
            while [ $# -gt 0 ]; do
            # parsing the options
        case $1 in
    -n|--number-iterations) shift; nb_iter="$1" ;;
    -l|--loop) loop=1 ;;
    -c|--case) shift; case="$1" ;;
    -i|--input) shift; tape_in="$1" ;;
    -o|--output) shift; tape_out="$1" ;;
    -io) shift; tape_in="$1" ; tape_out="$tape_in" ;;
    -s|--solution) shift; solution="$1" ;;
    -f|--fresh) start_over=1 ;;
    -q|--quiet) quiet=1 ;;
    -h|--help) usage ; exit 0 ;;
    *) echo "Unknown parameter passed: $1" ; exit 1 ;;
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
: ${tape_in:='tape'"$case"'.bin'}
: ${tape_out:="$tape_in"}
# creating the the solution binary if inexistant
: ${solution:='solution.bin'}
# TODO something more sexy for compilation_dir
compilation_dir=../../.. make 'in'"$case"'_i.bin' "$solution" 'out'"$case"'_i.bin'
# TODO define sensible behaviour for quiet and implement it
[ -z "$quiet" ] || exec 1>/dev/null 2>&1
[ -z "$start_over" ] || rm -f "$tape_in"

            # loop once or forever
            while
        # creating and printing the tape if inexistant
        if test $tape_in -nt 'in'"$case"'_i.bin' &&
        test $tape_in -nt $solution &&
        test $tape_in -nt 'out'"$case"'_i.bin' ; then
# Does this work when $tape_in = $tape_out ?
${VNS_INTERPRETER:-vns_vm} -n "$nb_iter" -a < "$tape_in" > .temp_tape_out
cat .temp_tape_out > "$tape_out"
rm .temp_*
${VNS_PRINT:-vns_print.sh} < "$tape_out"
        else
cat 'in'"$case"'_i.bin' $solution 'out'"$case"'_i.bin' > "$tape_out"
printf '\000\330\050' >> "$tape_out"
# making the printing more consistent, good for watch -d
echo
${VNS_PRINT:-vns_print.sh} < "$tape_out"
fi
test -n "$loop"
do
# TODO: add the ability to override max_iter by reading a number while in loop mode.
read _
done

