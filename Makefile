CC = gcc
OPTS = -std=c99

all: main.c helper.o rules.o
	$(CC) $(OPTS) $^ -o main

helper.o : helper.c helper.h
	$(CC) $(OPTS) -c $< -o $@

rules.o: rules.c rules.h
	$(CC) $(OPTS) -c $< -o $@

.PHONY : clean
clean:
	rm main helper.o rules.o
