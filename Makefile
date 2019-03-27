CC = g++
OPTS = -Wall -Werror

all: main.cpp helper.o
	$(CC) $(OPTS) $^ -o main

helper.o : helper.cpp helper.h
	$(CC) $(OPTS) -c $< -o $@

.PHONY: clean
clean:
	rm main *.o