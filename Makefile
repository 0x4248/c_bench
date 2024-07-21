# C Bench (Makefile)
# A single and multi-threaded benchmark made in the C programming language
# Github:https://www.github.com/0x4248/c_bench
# Licence: GNU General Public License v3.0
# By: 0x4248

OUTPUT = bin/c_bench
CC = gcc
CFLAGS = -pthread -Wall

SRC = src
SOURCES = $(wildcard $(SRC)/*.c)
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