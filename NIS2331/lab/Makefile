main: main.c mm.s
	arm-linux-gnueabi-gcc main.c mm.s -o main -static

.PHONY: run test

run: main
	qemu-arm -L /usr/arm-linux-gnueabi main

test: main
	python3 grade.py