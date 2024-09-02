#!/bin/sh

# TODO better messages (less noise, more better msg)
# TODO options for verbosity ?

logc=1
timec=
run=1
seq=1

root_dir="$(realpath $(dirname $0)/..)"
levels_dir="$root_dir/src/levels"
levels=
save_dir="$root_dir/save"
interpreter="$root_dir/target/vns"

            while [ $# -gt 0 ]; do
            # parsing the options
        case $1 in
    -r|--run) run=1 ;;
    -R|--no-run) run= ;;
    *) echo "Unknown parameter passed: $1" ;;
esac
    shift
done

        [ -e $save_dir -a ! -d $save_dir ] && {
        # establishing the save and dirs
echo $save_dir exists but is not a directory ; exit 65
}
        [ -e $save_dir ] || {
        # copying the levels dir except hidden object, which contains solution for testing purposes.
# TODO make all the files readonly, except solution
rsync -av --exclude=".*" $levels_dir $save_dir
}
[ -z $levels ] && levels=$(find $levels_dir/levels -type d -links 2 |sort)
# less portable than how it's done for the default campaing, but allows for a freer file structure.
# levels=$(find $levels_dir -mindepth 2 -maxdepth 2 -type d | sort)

            for level in $levels ; do
            # run the levels
save_level=$save_dir/$(realpath --relative-to="$levels_dir" $level)
# TODO crate the individual level dir if it's missing ?
        [ -z $level ] && {
echo "stuff happening"
} || {
compilation_dir=$save_dir make --directory $save_level solution.bin 1>&2
    level_dir=$level interpreter=$interpreter $level/check < $save_level/solution.bin > $save_level/solution.log &&
    ! grep KO $save_level/solution.log &&
    echo '[v] level '$level' completed!' 1>&2 || {
echo '[X] work necessary on level: ' 1>&2
echo  $save_level
exit 66
} ; } done

echo 'you finished the game !' 1>&2

