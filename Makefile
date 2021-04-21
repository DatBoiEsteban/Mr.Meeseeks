CC = gcc
CCFLAGS = -Wall -Wshadow -O2
LFLAGS = -lm -lpthread -lrt

box: Box.c tinyexpr.c
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)
	./$@