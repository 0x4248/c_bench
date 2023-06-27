# C Bench (Makefile)
# A single and multi-threaded benchmark made in the C programming language
# Github:https://www.github.com/lewisevans2007/c_bench
# Licence: GNU General Public License v3.0
# By: Lewis Evans

OUTPUT = bin/c_bench
CC = gcc
CFLAGS = -pthread

SOURCES = src/main.c

INCLUDE = -I include

all: init build

init:
	@mkdir -p bin

build: $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CC) $(CFLAGS) $(CONFIG) $(INCLUDE) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(CONFIG) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(SOURCES:%.c=%.o) $(OUTPUT)