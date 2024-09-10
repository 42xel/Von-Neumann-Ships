# What would it take to release a MVP in the wild ?
- Interactive run
    v Printing the tape.
    v Step by step.
    x Help menu, filtering the relevant part of the documentation
- Documentation a comprehensive README, with all the instructions to install and run the game (including make -e ?).
x A compiler ? customasm is annoying with the rule that you can't go above parent directory. Maybe I should wrap it. For now, it seems the makefile does the job.
- A summary description of the machine and of each assembly instruction and machine code.
x a way to run the game from within a level folder, so as to suggest looping using `cd $(./vns_game.sh)` from both outside the game and inside each level.
x 27 or so levels
- a release branch (trunk) separate from the current one (trunk=>root) containing generated headers.
    - Minimizes dependencies necessary to play
    - Allows dirty hand fix of broken generated headers
    - Opens a lot more possibilities beyond perl for code generation (lua + LPEG or Raku)
    - allows to remove the test cases solutions
    - Maybe some binaries ?


# Player interface
CLI interface
Zellij interface
tmux interface
normal (ncurse or whatever) TUI

backup load wipe|new
navigate ? sh cd ls tree kak !broot(way too big) C

# tooling
macro try and ptry (perror(), try(...)) ?

# later
perl   => raku or lua + LPEG. Less portable but so much better.
zellij => Tmux (+ fennel ?) Tmux is so much better, fennel is just flex
C      => zig ? only if need arises
git    => ? Whatever Florent B. has been doing ?
man    => a way to print the man pages ? man pages, typesetters run-off (troff) were inintially meant to be printed. Using a real life ancient prining format would be both a salute to and a flex flex on Zackgames retro papers manuals.
