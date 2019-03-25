all:
	gcc -std=c99 main.c -o main
.PHONY : clean
clean:
	rm main
