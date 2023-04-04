# C Bench (makefile)

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