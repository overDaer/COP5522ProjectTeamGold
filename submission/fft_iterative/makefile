CC=gcc
CFLAG= -Wall -I. -O3 -std=c11
LD=ld
LDFLAGS=-lm

TARGETS=iterative

all: $(TARGETS)

microtime.o: microtime.c microtime.h
	$(CC) $(CFLAG) -c $<
	
fft.o: fft.c fft.h
	$(CC) $(CFLAG) -c $< $(LDFLAGS)

iterative.o: fft_iterative.c fft.h microtime.h
	$(CC) $(CFLAG) -c $< $(LDFLAGS)
	
iterative: fft_iterative.o microtime.o fft.o
	$(CC) $(CFLAG) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o *~ core $(TARGETS)
