CC=gcc

all: build

build: repl.brain
	brain ./repl.brain --io=repl -S && $(CC) repl.s -o repl && rm repl.s
