## vns_game
The CLI (unstable) version of the game.
SYNOPSIS
	vns_game [run] [OPTIONS ...] [--] [TARGETS ...]
DESCRIPTION
	vns_game helps you play the game, by mostly handling savegames, progression, and level submissions.
Without options, it opens the default save folder, (re)creating it if neededd.
It then checks the level solutions in order, printing information to stderr along the way.
It finally stops at the first level unsolved, if any, and outputs the path to its dir in stdin.

OPTIONS
        In case of contradicting options, the last one overides the others.
    Verifications
        WIP --check (default)
        TODO --no-check skip the log check to know whether a level has been solved, effectively assuming they are not solved.

        TODO --check-time(defaut ?) check the last modification times of sources log and solution to now whether to rerun the tests. Decide the granularity of what to run at the level test case level.
        WIP --no-check-time do not checks the last modification time of files, effectively assuming they are up to date. For each level that is to be ran, rerun all the test cases.

        WIP --run rerun all the solutions against the test
        WIP --no-run do not run test, prints to stderr what would have been ran instead.

        TODO --all(default when explicit levels are individually provided unless overriden) runs all the level, even if some are in error. Provides no guarranty on the order in which the testcases are run.
        WIP --sequential(default) runs the test in order one after the other, stops at the first error.

    TARGETS
        TODO --save-dir <save_dir> specifies the directory of the save to use. By default...
        TODO --level-dir : a way to specify custom levels
        TODO --levels-dir : a way to specify custom campaigns
        TODO --levels <level_id> [SOLUTION] [--case <test_case_no>...] ... specifies the levels and cases to run. If no levels are specified, all of them are considered. If a level is specified but not its test cases, all of them are considered (see verification options to see which levels and cases are actually ran). +-= notation for relative offset.
        If solution is not provided, the save directory is used.
        Is this option implied ? or maybe -- is sufficient ? if it's the only list.
        TODO level range ? with my dumbass numeration, I can't even leverage seq.
        SOLUTION
            TODO --solution <save_dir> the level directory to use. Implies --level prefix, errors if the prefix is bad and the level is not otherwise given with level.
            TODO --solution <save_file> the level file to use when applicable (no garranty is made that the solution to levels will always be a single file). Implies --level prefix, errors if the prefix is bad and the level is not otherwise given with level. As a particular case, '-' denotes stdin, in which case specifying the level is mandatory. If you want to run the next level with stdin in a single command without substitution, use `--level +0` (checked) or `--level +1` (unchecked)


