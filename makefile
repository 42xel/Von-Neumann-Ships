# SHELL := /bin/dash

# C Compiler
CC = clang
# Compiler flags
CFLAGS = -Iinclude -Wall -Wextra
# Linker flags
LDFLAGS =

# Automatically find all .c files in src and its subdirectories
SRCS = $(shell find src -name '*.c')

# Generate the corresponding .o filenames
OBJS = $(SRCS:src/%.c=obj/%.o)
OBJDIRS = $(shell dirname $$(find src -name '*.c' | sed -e 's/^src/obj/'))

# Define the output executable
TARGET = build/vns

# tests
TSTS = $(SRCS:src/%.c=tests/src/%.o)
TSTSRCDIRS = $(shell dirname $$(find src -name '*.c' | sed -e 's/^src/tests\/src/'))
TSTOBJDIRS = $(shell dirname $$(find src -name '*.c' | sed -e 's/^src/tests\/obj/'))

# Default rule
# all: $(TARGET) | build/
all: $(OBJS)

# # Rule to link the executable
# $(TARGET): $(OBJS)
# 	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# %.o: %/
# 	#

# # TODO add header dependency
# # Rule to compile source files to object files
obj/%.o: src/%.c | obj/__dirs
	$(CC) $(CFLAGS) -c $< -o $@

%/:
	mkdir -p $@

obj/__dirs:
	mkdir -p $@ $(OBJDIRS)

# Clean rule
clean:
	rm -rf obj/ #$(TARGET)

# TODO clean_headers (separately)

