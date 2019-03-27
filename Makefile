CC = g++
OPTS = -Wall -Werror
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

all: main

main: ${OBJS}
	$(CC) $(OPTS) $^ -o $@

%.o: %.c %.h
	$(CC) $(OPTS) -c $< -o $@

.PHONY: clean
clean:
	rm main *.o