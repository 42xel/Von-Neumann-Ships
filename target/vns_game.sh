#!/bin/sh

# TODO better messages (less noise, more better msg)
# TODO options for verbosity ?

{

logc=1
timec=
run=1
seq=1

root_dir="$(realpath $(dirname $(which $0))/..)"
levels_dir="$root_dir/src/levels"
levels=
save_dir="$root_dir/save"
interpreter="$root_dir/target/vns_vm"

            while [ $# -gt 0 ]; do
            # parsing the options
        case $1 in
    -r|--run) run=1 ;;
    -R|--no-run) run= ;;
    *) echo "Unknown parameter passed: $1" ;;
esac
    shift
done

# TODO options for path ?
# Set the PATH if needed
    {
command -v vns_vm && command -v vns_game && command -v vns_interactive && command -v vns_print ||
export PATH=$root_dir'/target:'$PATH
        command -v vns_vm || {
echo 'Missing interpreter! A file `vns_vm` should have been in the top level directoty `target`. Something might be wrong in the build or in the $PATH' >&2
exit 1 ; }
        command -v vns_game.sh ||
echo 'missing executable file `vns_game.sh`, by default in the top level `target` directory. Some functionalities will be broken.' >&2
        command -v vns_interactive.sh ||
echo 'missing executable file `vns_interactive.sh`, by default in the top level `target` directory. Some functionalities will be broken.' >&2
        command -v vns_print.sh ||
echo 'missing executable file `vns_print.sh`, by default in the top level `target` directory. Some functionalities will be broken.' >&2
} >/dev/null

        [ -e $save_dir -a ! -d $save_dir ] && {
        # establishing the save and dirs
echo $save_dir exists but is not a directory ; exit 65
        }
        [ -e $save_dir ] || {
        # copying the levels dir except hidden object, which contains solution for testing purposes.
# TODO make all those files readonly
rsync -av --exclude=".*" $levels_dir/ $save_dir/
}
[ -z $levels ] && levels=$(find $levels_dir/levels -type d -links 2 |sort)
# less portable than how it's done for the default campaign, but allows for a freer file structure.
# levels=$(find $levels_dir -mindepth 2 -maxdepth 2 -type d | sort)

            for level in $levels ; do
save_level=$save_dir/$(realpath --relative-to="$levels_dir" $level)
        # Create the individual level dir if it's missing
        [ -d $save_level ] || {
# TODO tracer l'erreur ?
mkdir -p $save_level
rsync -av --exclude=".*" $level/ $save_level/
}
        # Ensure a blanket solution exist
        [ -e $save_level'/solution.asm' ] ||
cp $levels_dir'/templates/solution.asm' $save_level
# run the levels
# TODO acount for the value of the run parameter
        [ -z $run ] && {
echo <<- EOS
compilation_dir=$save_dir make --directory $save_level solution.bin 
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
compilation_dir=$save_dir make --directory $save_level solution.bin 
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
echo "$root_dir" >&3
} 3>&1 1>&2

