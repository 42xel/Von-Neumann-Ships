#!/bin/sh

# TODO better messages (less noise, more better msg)
# TODO options for verbosity ?

{

# Default options
logc=1
timec=
run=1
seq=1

# Default directories
: ${VNS_ROOT_DIR:=$(realpath $(dirname $(which $0))/..)}
interpreter="${VNS_INTERPRETER:-$VNS_ROOT_DIR/target/vns_vm}"
: ${VNS_LEVELS_DIR:=$VNS_ROOT_DIR/src/levels}
: ${VNS_SAVE_DIR:=$VNS_ROOT_DIR/save}

# Help message function
usage() {
    cat << EOF
Usage: $(basename $0) [OPTIONS...] [-- [LEVELS...]]

vns_game manages the game progression: save files, level solved, first unsolved level.

Description:
  vns_game opens the save folder, creating it if necessary.
  It then checks your level solutions in order, compiling assembly code into binary if needed, and providing feedback as it goes.
  It stops at the first unsolved level and prints the directory path of that level to standard output.
  All other information is printed to stderr.

vns_game creates a save game if necessary, then 

Options:
  -r, --run                 Run the game (default)
  -R, --no-run              Do not run the game
  -s, --save-dir <dir>      Specify a custom save directory (current: $VNS_SAVE_DIR)
  -L, --levels-dir <dir>    Specify a custom campaign directory (current: $VNS_LEVELS_DIR)
  -h, --help                Show this help message and exit

Levels:
  -- implies the end of the options and the beginning of the levels.
  Specify levels to consider as a full directory path. When none are specified, all of the campaign's levels are considered.

Environment:
  Setting the following environement variables overrides the default behaviour of the program, while being overriden by any relevant option.
    VNS_SAVE_DIR     replaces your savegame directory
    VNS_LEVELS_DIR   replaces the default campaign directory
    VNS_INTERPRETER  replaces the interpreter
    VNS_ROOT_DIR     replaces the root directory of the game

Examples:
  1. Launch the game and automatically navigate to the next unsolved level:
     cd \$($(basename $0))

  2. Run the game with a custom save directory:
     $(basename $0) --save-dir /path/to/custom/save
     or:
     VNS_SAVE_DIR=/path/to/custom/save $(basename $0)

  3. Specify particular levels to work on:
     $(basename $0) -- $VNS_LEVELS_DIR/A_first-steps/*

  4. Secify a custom campaign to work on:
     VNS_LEVELS_DIR=/path/to/custom/campaign $(basename $0)

EOF
}

# Parsing the otpions
            while [ $# -gt 0 ]; do
            # parsing the options
        case $1 in
    -r|--run) run=1 ;;
    -R|--no-run) run= ;;
    -s|--save-dir) VNS_SAVE_DIR="$2" ; shift ;;
    -L|--campaign) VNS_LEVELS_DIR="$2" ; shift ;;
    -h|--help) usage ; exit 0 ;;
    # end of options
    --) shift ; break ;;
    *) echo "Unknown option: $1" ; exit 1 ;;
esac
    shift
done
levels="$@"

    {
command -v vns_vm && command -v vns_game && command -v vns_interactive && command -v vns_print ||
export PATH="$VNS_ROOT_DIR/target:$PATH"
        command -v vns_vm || {
echo 'Missing interpreter! A file `vns_vm` should have been in the top level directory `target`. Something might be wrong in the build or in the $PATH' >&2
# exit 1 ;
}
        command -v vns_game.sh ||
echo 'missing executable file `vns_game.sh`, by default in the top level `target` directory. Some functionalities will be broken.' >&2
        command -v vns_interactive.sh ||
echo 'missing executable file `vns_interactive.sh`, by default in the top level `target` directory. Some functionalities will be broken.' >&2
        command -v vns_print.sh ||
echo 'missing executable file `vns_print.sh`, by default in the top level `target` directory. Some functionalities will be broken.' >&2
} >/dev/null

            # establishing the save and dirs
        [ -e "$VNS_SAVE_DIR" -a ! -d "$VNS_SAVE_DIR" ] && {
echo "$VNS_SAVE_DIR" exists but is not a directory ; exit 1
}
        [ -e "$VNS_SAVE_DIR" ] || {
        # copying the levels dir except hidden object, which contains solution for testing purposes.
# TODO make all/most those files readonly
rsync -av --exclude=".*" $VNS_LEVELS_DIR/ $VNS_SAVE_DIR/
}
: ${levels:=$(find $VNS_LEVELS_DIR/levels -type d -links 2 | sort)}
# listing leaf levels. Using -link is less portable than how it's done for the default campaign, but it allows for a freer file structure than only going ata depth 2.
# levels=$(find $VNS_LEVELS_DIR -mindepth 2 -maxdepth 2 -type d | sort)

            for level in $levels ; do
save_level=$VNS_SAVE_DIR/$(realpath --relative-to="$VNS_LEVELS_DIR" $level)
        # Create the individual level dir if it's missing
        [ -d "$save_level" ] || {
echo "creating missing level: $save_level"
mkdir -p $save_level
rsync -av --exclude=".*" $level/ $save_level/
}
        # Ensure a blanket solution exist
        [ -e "$save_level'/solution.asm'" ] ||
cp $VNS_LEVELS_DIR'/templates/solution.asm' $save_level
# run the levels
# TODO: make in a more programmatic/reflective way
        [ -z $run ] && {
echo <<- EOS
compilation_dir=$VNS_SAVE_DIR make --directory $save_level solution.bin 
    level_dir=$level interpreter=$interpreter $level/check < $save_level/solution.bin > $save_level/solution.log &&
    ! grep KO $save_level/solution.log &&
    echo '[v] level '$level' completed!'  || {
echo '[X] work necessary on level: ' 
echo  $save_level
echo 'instructions:'
cat $level/instructions.md
exit 66
} ;
EOS
        } || {
compilation_dir=$VNS_SAVE_DIR make --directory $save_level solution.bin 
    level_dir=$level interpreter=$interpreter $level/check < $save_level/solution.bin > $save_level/solution.log &&
    ! grep KO $save_level/solution.log &&
    echo '[v] level '$level' completed!'  || {
echo '[X] work necessary on level: ' 
echo '---------------------------------------------------------------'
echo level $(basename $level)
echo  $save_level >&3
echo '---------------------------------------------------------------'
echo 'instructions.md:'
cat $level/instructions.md
exit 66
} ; } done

echo 'you finished the game !'
echo "$VNS_SAVE_DIR" >&3
} 3>&1 1>&2

