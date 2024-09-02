# SHELL := /bin/dash

# TODO use .SECONDARY when relevant
# TODO see if $(*D) is useable in any way instead of DIRS.
#  Then don't use it cause it's likely worse.
# TODO : write the conversion tables to a rsc/ binary file
#  and open it instead of generating at every launch of the game.
#  make it .NOTINTERMEDIATE/an actual target

# C Compiler
CC = clang
# Compiler flags
# -I. allows to include using "absolute" path, relative to the whole project
CFLAGS = -I. -Wall #-Wextra
# Linker flags
LDFLAGS = -v

# Automatically find all .c files in src and its subdirectories
SRCS = $(shell find src -type f -name '*.c' | grep -v 'src/main.*\.c')
_SRCDIRS = $(shell dirname $(SRCS))
SRCDIRS = $(_SRCDIRS:%=%/)

# headers
# OUTLINES = $(SRCS:src/%.c=headers/%.outline)
HDRS = $(SRCS:src/%.c=headers/%.h)
HDRDIRS = $(SRCDIRS:src/%=headers/%)

# Generate the corresponding .o filenames
OBJS = $(SRCS:src/%.c=obj/%.o)
OBJDIRS = $(SRCDIRS:src/%=obj/%)

# Define the output executable
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
all: $(TARGETS) levels

.PHONY: tests unit_tests level_tests levels clean all $(LVLSALL) $(LVLSTSTS) $(CLEAN_LEVELS)

# Rule to link the executable
# TODO: remove the save directory creation from here, put it in test and/or target
target/vns: src/main.c $(OBJS) $(HDRS) | target/ save/
	$(CC) $(CFLAGS) $(LDFLAGS) -I headers $(OBJS) $< -o $@
# # TODO: remove the save directory creation from here.
# target/vns%: src/main%.c $(OBJS) $(HDRS) | target/ save
# 	$(CC) $(CFLAGS) $(LDFLAGS) -I headers $(OBJS) $< -o $@

# Tests ruleS
tests: unit_tests level_tests
unit_tests: $(TSTS)
	! grep KO $(TSTS)

level_tests: $(LVLSTSTS)
levels: $(LVLS)

$(LVLSTSTS): target/vns | $(LVLSPATH)
	interpreter=$$(realpath $<) compilation_dir=$$(realpath src/levels/) make --directory $$(dirname $@) tests

$(LVLS): | $(LVLSPATH)
	make --directory $@

.NOTINTERMEDIATE: unit_tests/log/%.log
unit_tests/log/%.log: unit_tests/bin/% | $(TSTDIRS)
	$< > $@ 2>&1

# -I$$(dirname headers/$*) allows to use relative path for includes.
# todo: change to account for the fact that header files are in headers/.
unit_tests/bin/%: unit_tests/src/%.c $(OBJS) $(HDRS) | $(TSTBINDIRS)
	$(CC) $(CFLAGS) $(LDFLAGS) -I$$(dirname src/$*) -I$$(dirname headers/$*) $$(echo $(OBJS) | perl -- parse_test_obj.pl $< ) -o $@

# .PRECIOUS: unit_tests/src/%.c
.NOTINTERMEDIATE: unit_tests/src/%.c
unit_tests/src/%.c: src/%.c headers/%.outline | $(TSTSRCDIRS)
	perl generate_tests.pl $< < headers/$*.outline > $@

# Rule to compile source files to object files
# -I$$(dirname headers/$*) allows to use relative path for includes.
# todo: change to account for the fact that header files are in header.
obj/%.o: src/%.c $(HDRS) | $(OBJDIRS)
	$(CC) $(CFLAGS) -I$$(dirname $<) -I$$(dirname headers/$*) -c $< -o $@

.NOTINTERMEDIATE: headers/%.h
.PRECIOUS: headers/%.h
headers/%.h: headers/%.outline | $(HDRDIRS)
	perl generate_headers.pl $* < $< > $@

.NOTINTERMEDIATE: headers/%.outline
# .PRECIOUS: headers/%.outline
headers/%.outline: src/%.c | $(HDRDIRS)
	perl outline.pl < $< > $@

%/:
	mkdir -p $@

# obj/__dirs:
# 	mkdir -p $@ $(OBJDIRS)

# Clean rule
clean: $(CLEAN_LEVELS)
	rm -rf obj/ headers/ unit_tests/ $(TARGETS);

# TODO clean_headers (separately)

$(CLEAN_LEVELS): | $(LVLSPATH)
	make --directory $$(dirname $@) clean


