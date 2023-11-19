all: main

main: main
	gcc -o main main.c -lm

clean:
	\rm main