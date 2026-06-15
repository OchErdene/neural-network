CC = gcc
NASM = nasm

all: bin/main

bin/main: src/main.c simd-lib/src/math.o
	$(CC) -o bin/main src/main.c simd-lib/src/math.o -lm

simd-lib/src/math.o: simd-lib/src/math.asm
	$(NASM) -f elf64 simd-lib/src/math.asm -o simd-lib/src/math.o

clean:
	rm -f bin/main simd-lib/src/math.o
