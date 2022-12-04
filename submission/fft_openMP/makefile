CC=gcc
CFLAG= -Wall -fopenmp -I. -O3 -std=c11
LD=ld
LDFLAGS=-lm

TARGETS=parallel_openmp

all: $(TARGETS)

microtime.o: microtime.c microtime.h
	$(CC) $(CFLAG) -c $<
	
fft.o: fft.c fft.h
	$(CC) $(CFLAG) -c $< $(LDFLAGS)

parallel_openmp.o: fft_openmp.c fft.h microtime.h
	$(CC) $(CFLAG) -c $< $(LDFLAGS)

parallel_openmp: fft_openmp.o microtime.o fft.o
	$(CC) $(CFLAG) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o *~ core $(TARGETS)
