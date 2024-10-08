# SHELL := /bin/dash

# TODO see if $(*D) is useable in any way instead of DIRS.
#  Then don't use it cause it's likely worse.
# TODO : write the conversion tables to a rsc/ binary file
#  and open it instead of generating at every launch of the game.
# TODO : make header files and outlines INTERMEDIATE (as well as SECONDARY ?) ?

# C Compiler
CC = clang
# CC = gcc
# Compiler flags
# -I. allows to include using "absolute" path, relative to the whole project
CFLAGS = -I. -Wall #-Wextra
# Linker flags
LDFLAGS = -v

# Automatically find all .c files in src and its subdirectories
SRCS = $(shell find src -type f -name '*.c' | grep -v 'src/main.*\.c')
_SRCDIRS = $(shell dirname $(SRCS))
SRCDIRS = $(_SRCDIRS:%=%/)

# outlines
OUTLINES = $(SRCS:src/%.c=headers/%.outline)

# headers
HDRS = $(SRCS:src/%.c=headers/%.h)
HDRDIRS = $(SRCDIRS:src/%=headers/%)

# corresponding .o filenames
OBJS = $(SRCS:src/%.c=obj/%.o)
OBJDIRS = $(SRCDIRS:src/%=obj/%)

# output executable(s)
MAINS = $(shell find src -type f -name '*.c' | grep 'src/main.*\.c')
TARGETS = $(MAINS:src/main%.c=target/vns%)

# unit_tests
TSTS = $(SRCS:src/%.c=unit_tests/log/%.log)
TSTSRCDIRS = $(SRCDIRS:%=unit_tests/%)
TSTDIRS = $(TSTSRCDIRS:unit_tests/src/%=unit_tests/log/%)
TSTBINDIRS = $(TSTDIRS:unit_tests/log/%=unit_tests/bin/%)

# levels
LVLSPATH = src/levels/levels/
LVLS = $(shell find $(LVLSPATH) -mindepth 2 -maxdepth 2 -type d)
LVLSTSTS = $(LVLS:%=%/.tests)

CLEAN_LEVELS = $(LVLS:%=%/.clean)

# Default rule
game: $(TARGETS) # levels

# Rle to make everything, including files considered secnodary in branch `root`
all: game headers

outlines: $(OUTLINES)

.PHONY: tests unit_tests level_tests outlines headers clean game all $(LVLSALL) $(LVLSTSTS) $(CLEAN_LEVELS) # levels

# The VM executable
target/vns_vm: src/main_vm.c $(OBJS) $(HDRS) | target/
	$(CC) $(CFLAGS) $(LDFLAGS) -I headers $(OBJS) $< -o $@

# Tests ruleS
tests: unit_tests level_tests
unit_tests: $(TSTS)
	! grep KO $(TSTS)

level_tests: $(LVLSTSTS)
# levels: $(LVLS)

$(LVLSTSTS): target/vns_vm | $(LVLSPATH)
	interpreter=$$(realpath $<) compilation_dir=$$(realpath src/levels/) make --directory $$(dirname $@) tests

$(LVLS): | $(LVLSPATH)
	make --directory $@

.PRECIOUS: unit_tests/log/%.log
.NOTINTERMEDIATE: unit_tests/log/%.log
unit_tests/log/%.log: unit_tests/bin/% | $(TSTDIRS)
	$< > $@ 2>&1

# -I$$(dirname headers/$*) allows to use relative path for includes.
# todo: change to account for the fact that header files are in headers/.
unit_tests/bin/%: unit_tests/src/%.c $(OBJS) $(HDRS) | $(TSTBINDIRS)
	$(CC) $(CFLAGS) $(LDFLAGS) -I$$(dirname src/$*) -I$$(dirname headers/$*) $$(echo $(OBJS) | perl -- ./toolchain/parse_test_obj.pl $< ) -o $@

# PRECIOUS for easier debugging of the toolchain.
.PRECIOUS: unit_tests/src/%.c headers/%.h headers/%.outline
.SECONDARY: unit_tests/src/%.c
unit_tests/src/%.c: src/%.c headers/%.outline | $(TSTSRCDIRS)
	perl ./toolchain/generate_tests.pl $< < headers/$*.outline > $@

# Rule to compile source files to object files
# -I$$(dirname headers/$*) allows to use relative path for includes.
# todo: change to account for the fact that header files are in header.
obj/%.o: src/%.c $(HDRS) | $(OBJDIRS)
	$(CC) $(CFLAGS) -I$$(dirname $<) -I$$(dirname headers/$*) -c $< -o $@

headers: $(HDRS)

.SECONDARY: headers/%.h
headers/%.h: headers/%.outline | $(HDRDIRS)
	perl ./toolchain/generate_headers.pl $* < $< > $@

.SECONDARY: headers/%.outline
headers/%.outline: src/%.c | $(HDRDIRS)
	perl ./toolchain/outline.pl < $< > $@

%/:
	mkdir -p $@

# Clean rule
clean: $(CLEAN_LEVELS)
	rm -rf obj/ $(TARGETS);
	grep -Fxq 'dev' ./.makeprofile && rm -rf headers/ unit_tests/

$(CLEAN_LEVELS): | $(LVLSPATH)
	make --directory $$(dirname $@) clean

