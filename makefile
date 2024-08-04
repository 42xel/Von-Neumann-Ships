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
CFLAGS = -I. -Wall -Wextra
# Linker flags
LDFLAGS =

# Automatically find all .c files in src and its subdirectories
SRCS = $(shell find src -name '*.c' | grep -vF src/main.c)
_SRCDIRS = $(shell dirname $$(find src -name '*.c' | grep -vF src/main.c))
SRCDIRS = $(_SRCDIRS:%=%/)

# TODO headers before objs
# headers
# OUTLINES = $(SRCS:src/%.c=headers/%.ouline)
HDRDIRS = $(SRCDIRS:src/%=headers/%)

# Generate the corresponding .o filenames
OBJS = $(SRCS:src/%.c=obj/%.o)
OBJDIRS = $(SRCDIRS:src/%=obj/%)

# Define the output executable
TARGET = build/vns

# tests
TSTS = $(SRCS:src/%.c=unit_tests/log/%.log)
# TSTSRCS = $(TSTS:unit_tests/log/%.log=unit_tests/src/%.c)
TSTSRCDIRS = $(SRCDIRS:%=unit_tests/%)
TSTDIRS = $(TSTSRCDIRS:unit_tests/src/%=unit_tests/log/%)
# TSTBINS = $(TSTS:unit_tests/log/%.log=unit_tests/bin/%)
TSTBINDIRS = $(TSTDIRS:unit_tests/log/%=unit_tests/bin/%)

.PHONY: tests clean

# Default rule
all: $(TARGET)
# all: $(OBJS)

# # Rule to link the executable
$(TARGET): $(OBJS) | build/
	$(CC) $(LDFLAGS) $(OBJS) src/main.c -o $@

# Tests rule
tests: $(TSTS)
	! grep KO $(TSTS)

unit_tests/log/%.log: unit_tests/bin/% | $(TSTDIRS)
	$< > $@ 2>&1

# -I$$(dirname $@) allows to use relative path for includes.
# todo: change to account for the fact that header files are in header.
unit_tests/bin/%: unit_tests/src/%.c $(OBJS) | $(TSTBINDIRS)
	$(CC) $(CFLAGS) $$(echo $(OBJS) | perl -- parse_test_obj.pl $< ) -o $@

.PRECIOUS: unit_tests/src/%.c
unit_tests/src/%.c: src/%.c headers/%.outline | $(TSTSRCDIRS)
	perl generate_tests.pl $< < headers/$*.outline > $@

# .SECONDARY: headers/%.outline
.NOTINTERMEDIATE: headers/%.outline
# .PRECIOUS: headers/%.outline
headers/%.outline: src/%.c | $(HDRDIRS)
	perl outline.pl < $< > $@

# Rule to compile source files to object files
# -I$$(dirname $@) allows to use relative path for includes.
# todo: change to account for the fact that header files are in header.
obj/%.o: src/%.c | $(OBJDIRS)
	$(CC) $(CFLAGS) -c $< -o $@

%/:
	mkdir -p $@

# obj/__dirs:
# 	mkdir -p $@ $(OBJDIRS)

# Clean rule
clean:
#	find $(TARGET) -path "obj/*" -path "headers/*" -path "unit_tests/*" -type f -delete
	rm -rf obj/ headers/ unit_tests/ $(TARGET)

# TODO clean_headers (separately)

