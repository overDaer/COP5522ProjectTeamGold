#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "fft.h"
#include "microtime.h"

_Bool isPowerOf2(int n) {
    return n && (!(n & (n - 1)));
}

int main(int argc, char const *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "USAGE: %s [power of 2] [threads]\n", argv[0]);
        exit(-1);
    }

    int threads = atoi(argv[2]);

    if (!isPowerOf2(threads)) {
        fprintf(stderr, "Threads must be power of 2.\n");
        exit(-1);
    }

    int powerOf2 = atoi(argv[1]);
    int length = pow(2, powerOf2);

    omp_set_dynamic(0);
    omp_set_num_threads(threads);


    struct complex *sumWave = malloc(length * sizeof(struct complex));
    //create arbitrary sine waves to sum
    struct complex *sineWave1 = GenerateSineArray(length, 1, 10);
    struct complex *sineWave2 = GenerateSineArray(length, 2, 4);
    struct complex *sineWave3 = GenerateSineArray(length, 4, 5);
    //add sine waves into complex sumWave
    for (int i = 0; i < length; i++) {
        sumWave[i].real = sineWave1[i].real + sineWave2[i].real + sineWave3[i].real;
        sumWave[i].imag = sineWave1[i].imag + sineWave2[i].imag + sineWave3[i].imag;
    }

#ifdef DEBUG
    printf("Printing input Array\n");
    PrintComplexArray(sumWave, length);
#endif

    struct complex *output = malloc(length * sizeof(struct complex));
    double startTime = microtime();
    iterativeFFT(sumWave, powerOf2);
    double endTime = microtime();
#ifdef DEBUG
    printf("Printing output Array\n");
    PrintComplexArray(sumWave, length);
#endif

    free(sumWave);
    free(output);
    free(sineWave1);
    free(sineWave2);
    free(sineWave3);


    printf("\nTime = %g ms\n", (endTime - startTime) / 1000);
    printf("Timer Resolution = %g us\n", getMicrotimeResolution());
    /* code */

    return 0;
}

