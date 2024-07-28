# SHELL := /bin/dash

# TODO use .SECONDARY when relevant
# TODO : write the conversion tables to a rsc/ binary file
# and open it instead of generating at every launch of the game.
# make it .PRECIOUS

# C Compiler
CC = clang
# Compiler flags
# -I. allows to include using "absoltue" path, relative to the whole project
CFLAGS = -I. -Wall -Wextra
# Linker flags
LDFLAGS =

# Automatically find all .c files in src and its subdirectories
SRCS = $(shell find src -name '*.c' | grep -vF src/main.c)
_SRCDIRS = $(shell dirname $$(find src -name '*.c' | grep -vF src/main.c))
SRCDIRS = $(_SRCDIRS:%=%/)

# TODO headers before objs

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
# all: $(TARGET) | build/
all: $(OBJS)

# # Rule to link the executable
# $(TARGET): $(OBJS)
# 	$(CC) $(OBJS) src/main.c -o $@ $(LDFLAGS)

# Tests rule
tests: $(TSTS)

# what of stderr ?
unit_tests/log/%.log: unit_tests/bin/% $(TSTDIRS)
	$< > $@

# -I$(dirname $@) allows to use relative path for includes.
# todo: change to account for the fact that header files are in header.
unit_tests/bin/%: unit_tests/src/%.c $(TSTBINDIRS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(dirname $@) $< -o $@

unit_tests/src/%.c: src/%.c $(TSTSRCDIRS)
	perl -f ./generate_tests.pl $< $@

# Rule to compile source files to object files
# -I$(dirname $@) allows to use relative path for includes.
# todo: change to account for the fact that header files are in header.
obj/%.o: src/%.c $(OBJDIRS)
	$(CC) $(CFLAGS) -I$(dirname $@) -c $< -o $@

%/:
	mkdir -p $@

# obj/__dirs:
# 	mkdir -p $@ $(OBJDIRS)

# Clean rule
clean:
	find -type f -delete obj/ #unit_tests/ #$(TARGET)

# TODO clean_headers (separately)

