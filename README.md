A [Zach-like](https://itch.io/games/tag-zach-like) game where [your code modifies itself](https://en.wikipedia.org/wiki/Self-modifying_code).

# Table of Contents
* [Table of Contents](https://github.com/42xel/Von-Neumann-Ships#table-of-contents)
* [About](https://github.com/42xel/Von-Neumann-Ships#about)
* [Installation](https://github.com/42xel/Von-Neumann-Ships#installation)
	* [Requirements/dependencies](https://github.com/42xel/Von-Neumann-Ships#requirements/dependencies)
	* [Installation](https://github.com/42xel/Von-Neumann-Ships#installation)
* [Instructions](https://github.com/42xel/Von-Neumann-Ships#instructions)
	* [Launching your first game](https://github.com/42xel/Von-Neumann-Ships#launching-your-first-game)
	* [Solving your first level](https://github.com/42xel/Von-Neumann-Ships#solving-your-first-level)
	* [Debugging](https://github.com/42xel/Von-Neumann-Ships#debugging)
	* [Explore!](https://github.com/42xel/Von-Neumann-Ships#explore!)
* [Contributing](https://github.com/42xel/Von-Neumann-Ships#contributing)
	* [Ideas and player feedback](https://github.com/42xel/Von-Neumann-Ships#ideas-and-player-feedback)
	* [Bugs reports](https://github.com/42xel/Von-Neumann-Ships#bugs-reports)
	* [Hands on participation](https://github.com/42xel/Von-Neumann-Ships#hands-on-participation)


# About
At the beginning, [there were punched cards](https://en.wikipedia.org/wiki/Punched_card).
Then came [a computer architecture treating its instructions as data, and capable, in turn, to treat its data as instructions](https://en.wikipedia.org/wiki/Harvard_architecture).
It lead to essential breakthroughs, mundane and ubiquitous tools nowadays, but revolutionary at the time:
[code editors](https://kakoune.org/), [debuggers](https://en.wikipedia.org/wiki/Lisp_(programming_language)), [operating systems](https://www.gnu.org/software/emacs/), and ultimately [full blown Integrated Development Environments](https://en.wikipedia.org/wiki/Software_bloat).
[Ironically](https://en.wikipedia.org/wiki/Eternal_return) [though](https://www.winestockwebdesign.com/Essays/Eternal_Mainframe.html), the routine of the modern programmer, [waiting hours for their code to compile](https://www.rust-lang.org/) in between moments of code tweaking, is conceptually no different than that of our punching cards ancestors.

This game explores a different path, where programs stayed mutable at runtime.
All the while, [hopefully](https://knowyourmeme.com/editorials/guides/what-does-copium-mean-and-why-is-everyone-saying-cope-online), remaining a game.

# Installation
## Requirements/dependencies
In order to install and run the game, you need:
+ (Optional\*) [customasm](https://github.com/hlorenzi/customasm#installation)
+ A C compiler ([Clang](https://clang.llvm.org/), [gcc](https://gcc.gnu.org/))
+ A UNIX-like operating system ([Linux](https://kernel.org/), [Redox](https://www.redox-os.org/), [freeBSD](https://www.freebsd.org/), [illuminos](https://illumos.org/), [SerenityOS](https://serenityos.org/), ...)
+ A POSIX Shell
+ GNU linux ? For now, probably. If you wanna try without it, let me know how it goes.

\* Not really

## Installation
Download this present repository, for example using:
```console
git clone git@github.com:42xel/Von-Neumann-Ships.git
```
Run make:
```console
make
```
(Optional )[Add the target folder to your path](https://itsfoss.com/add-directory-to-path-linux/).
For example, assuming bash:
```console
echo "export PATH=$(realpath target)"':$PATH' >> ~/.bashrc
```
I guess, I don't know, I use [an interactive shell](https://fishshell.com/), and only temporarilly add target to path.

The target contains the following commands:
- `vns_game.sh`, the game script, handling your progression
- `vns_vm` , the game interpreter (Virtual Machine), running the machines
- `vns_interactive.sh`, a visual interactive interpreter
- `vns_print.sh`, a command used to print the state of memory, mainly used by `vns_interactive.sh`

Install [customasm](https://github.com/hlorenzi/customasm#installation).

# Instructions
(Work in progress)
## Launching your first game
Open your favorite [terminal (emulator)](https://wezfurlong.org/wezterm/what-is-a-terminal.html) and [shell](https://techterms.com/definition/shell)\*.
Run the command `vns_game.sh`.
You should be welcomed with a wall of text and a half, which should end by telling you the next level you need to work on, and its instructions.
The command `vns_game.sh` created a directory `save` containing the following:
+ `levels/`: an arborescence with each leaf directory corresponding to an individual level
+ `asm/`: the customasm definitions of the assembly language
    + in particular, `asm/definitions.asm` contains the commented definition of the whole assembly, including the whole instructions set.
+ other stuffs to [make the world go round](https://en.wikipedia.org/wiki/Boilerplate), [so to speak](https://www.facebook.com/weknowearthisflat/)

The command `vns_game.sh` [prints](https://en.wikipedia.org/wiki/Standard_streams) mostly on [`stderr`](https://linux.die.net/man/3/stderr).
Its [output](https://linux.die.net/man/3/stdout) consists in the next level directory, so that you can use:
```console
cd $(vns_game.sh)
```
to go to the next level.

Don't worry about running `vns_game` repeatedly, it [won't create things in double](https://en.wikipedia.org/wiki/Idempotence) or [erase all your hard work](https://www.urbandictionary.com/define.php?term=trust%20me%20bro).


\* As of now, the game is not fully contained and self sufficient, [willingly so](https://github.com/42xel/Von-Neumann-Ships#design-philosophy), hence the need for a shell.

## Solving your first level
In each level directory, you will [find](https://www.man7.org/linux/man-pages/man1/ls.1.html) something along these lines:
+ `instructions.md`: the instructions of the level
+ `in_i.asm`, `out_i.asm` `out_x.asm`, ... : a test case
+ `solution.asm`: a solution template for you to complete
+ `makefile`: the makefile to turn [`.asm`](https://en.wikipedia.org/wiki/Assembly_language) files into [`.bin`](https://en.wikipedia.org/wiki/Binary_file)
+ `check`: [a copy of the program used to check the solution](https://en.wikipedia.org/wiki/Glasnost).

To solve a level, write your solution in `solution.asm`.
Early on, instructions should introduce you to the assembly idoms necessary to solve the level.
Then, run `vns_game.sh`.
Provided you have `customasm` installed, it will [make](https://www.gnu.org/software/make/) `solution.bin` and run it against test case(s).
If there are any mistakes, they should be written in `solution.log`.

## Debugging
If you want a more interactive programming experience, use the command `vns_interactive.sh`.
It will run your solution against a test case one step at a time.
The intermediary state is stored in a file `tape.bin`, delete it if you want to start over.

Do try the option `vns_interactive.sh -l` as well.

If you want to change how `vns_interactive.sh`  displays the state, you can alter or shadow `vns_print.sh`.
You can also use `vns_print.sh` directly to view files like `tape.bin`.


## Explore!
The good thing about a Composite Gaming and Learning Environment is the great modularity it offers.

Try `--help` on any of the `vns command` to uncover its details and advanced use;
use them to have more than one save, or to make your own levels.

Dive deep into customasm and flex with your own assembly.

Or [edit](https://git.sr.ht/~aleksi/teehee) the [binary](https://linuxhandbook.com/xxd-command/) [yourself](http://www.catb.org/esr/jargon/html/story-of-mel.html), in between rounds of using `vns_interactive.sh`.

Use a your [favorite](https://zellij.dev/) [mulitiplexer](https://github.com/tmux/tmux/wiki) or [composable](https://en.wikipedia.org/wiki/Windowing_system) [terminal](https://sw.kovidgoyal.net/kitty/) along with [`watch`](https://linuxize.com/post/linux-watch-command/) to edit your solution and see the changes live.

And practically infinite combinations of tools.

# Contributing
Do not hesitate get in touch via [mail](https://github.com/42xel), [discord](https://support.discord.com "4xel4587") or GitHub issue.
I'll probably answer within a week
## Ideas and player feedback
Welcome.

Currently, I can use ideas for puzzles and user interface, and soon, I'll need feedback on the instructions set (how to reduce it likey).

## Bugs reports
Make issues here, don't overthink it the code base is still very volatile.

## Hands on participation
Head to the developping branch.

