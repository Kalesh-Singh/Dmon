CC = g++
OPTS = -g -Wall -Werror -std=c++11
SRCS = $(wildcard *.cpp)
INCS = $(wildcard *.h)
OBJS = $(SRCS:.cpp=.o)

all: main

main: ${OBJS}
	$(CC) $(OPTS) $^ -o $@

%.o: %.c ${INCS}
	$(CC) $(OPTS) -c $< -o $@

.PHONY: clean
clean:
	rm main *.o