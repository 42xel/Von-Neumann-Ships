# What would it take to release a MVP in the wild ?
[v] Interactive run
    [v] Printing the tape.
    [v] Step by step.
    [x] Help menu, filtering the relevant part of the documentation
[v] Documentation a comprehensive README, with all the instructions to install and run the game (including make -e ?).
	[v] all commands ahave a help menu
[v] I'd need a CONTRIBUTE.md thingy
[x] A compiler ? customasm is annoying with the rule that you can't go above parent directory. Maybe I should wrap it. For now, make and shell script glue well enough.
[ ] A summary description of the machine and of each assembly instruction and machine code.
[v] a way to run the game from within a level folder, so as to suggest looping using `cd $(./vns_game.sh)` from both outside the game and inside each level.
[x] 27 or so levels
    [ ] a working loop instruction
    [ ] a working conditional instruction
[v] a release branch (trunk) separate from the current one (trunk=>root) containing generated headers.
    [ ] Minimizes dependencies necessary to play
        [ ] Opens a lot more possibilities beyond perl for code generation (lua + LPEG or Raku)
    [ ] Allows dirty hand fix of broken generated headers
    [x] Allows to remove the test cases solutions
    [ ] Maybe some binaries ?


# Player interface
-> CLI interface
Zellij interface
tmux interface
normal (ncurse or whatever) TUI

backup load wipe|new
navigate ? sh cd ls tree kak !broot(way too big) C

# tooling
A cheat option in the root branch to more easily work on and solve new levels ? or maybe work directly in the source folder, using the existing `--solution` option.
macro try and ptry (perror(), try(...)) ?

# later
perl   => raku or lua + LPEG. Less portable but so much better.
zellij => Tmux (+ fennel ?) Tmux is so much better, fennel is just flex
C      => zig ? only if need arises. But I don't know when need will arise...
git    => ? Whatever Florent Becker has been doing ?
man    => a way to print the man pages ? man pages, typesetters run-off (troff) were inintially meant to be printed. Using a real life ancient prining format would be both a salute to and a flex on Zackgames retro papers manuals.

# Other

TODO develop ideas for interactive problems
allows to pause the navigation at any point, navigate it backward and forward, set breakpoints.
But the really innovative thing would be to allow to manually modify the code mid run. On regular problems, it would invalidate your solution, but you would have a solution to rebase/fixup your solution, using git/lazygit, or some other version control tool (preferably something more quirky, but I don't know any front for version control is as good as lazygit).
There would also be special problems where mid fly editing would be valid and the scoring would account for it (ideally encouraging it while still having the goal to minimize it).
(too ambitious ?) Some time limited levels where the goal is to make and use an interactive interfaces (ala powerusers)

