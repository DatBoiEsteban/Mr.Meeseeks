CC = gcc
CCFLAGS = -Wall -Wshadow -O2
LFLAGS = -lm -lpthread 

box: Box.c tinyexpr.c
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)
	./$@

test: test.c 
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)
	./$@
