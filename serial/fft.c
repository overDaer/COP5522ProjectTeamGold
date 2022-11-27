#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fft.h"

void recursiveFFT(struct complex *inputArray, int length){
    int n = length;
    int half = n / 2;

    if (n == 1) {
        return;
    }

    //allocate memory of even and odd
    struct complex *oddArray = malloc(half * sizeof(struct complex));
    struct complex *evenArray = malloc(half * sizeof(struct complex));
    for (int i = 0; 2 * i < n; i++){
        //Copy even and odd to separate Arrays
        evenArray[i].real = inputArray[i * 2].real;
        evenArray[i].imag = inputArray[i * 2].imag;
        oddArray[i].real = inputArray[i * 2 + 1].real;
        oddArray[i].imag = inputArray[i * 2 + 1].imag;
    }
    //recursive call halves until size of arrays are n == 1

    recursiveFFT(evenArray, half);
    recursiveFFT(oddArray, half);
    //printf("array size: %i\n",n);
    //double angle = 2 * M_PI / n;
    for (int i = 0; i < n /2; i++){
        struct complex w;
        w.real = cos(2.0 * M_PI * (double)(i) / (double)(n));
        w.imag = -sin(2.0 * M_PI * (double)(i) / (double)(n));
        struct complex mulipliedResult = MultiplyComplex(w, oddArray[i]);
        inputArray[i].real = evenArray[i].real + mulipliedResult.real;
        inputArray[i].imag = evenArray[i].imag + mulipliedResult.imag;
        inputArray[i + n / 2].real = evenArray[i].real - mulipliedResult.real;
        inputArray[i + n / 2].imag = evenArray[i].imag - mulipliedResult.imag;
    }

    free(evenArray);
    free(oddArray);
    //printComplexArray(inputArray, n);
}

void PrintComplexArray(struct complex *printingArray, int length){
    int n = length;
    for (int i = 0; i < n; i++){
        printf("[%i]: %lf, %lfi\n", i, printingArray[i].real, printingArray[i].imag);
    }
}
/*(a + bi) * (c + di) = (ac − bd) + (ad + bc)i*/
struct complex MultiplyComplex(struct complex a, struct complex b){
    struct complex result;
    result.real = (a.real * b.real - a.imag * b.imag);
    result.imag = (a.real * b.imag + a.imag * b.real);
    return result;
}
/*A sine wave of frequency f with amplitude r and phase θ is equivalently a complex number r*cos(θ) + ir*sin(θ) */
struct complex* GenerateSineArray(int samples, int frequency, int amplitude){
    struct complex *sineArray = malloc(samples * sizeof(struct complex));
    for (int i = 0; i < samples; i ++){
        sineArray[i].real = amplitude * cos(frequency * 2 * M_PI * i / samples);
        sineArray[i].imag = amplitude * sin(frequency * 2 * M_PI * i / samples);
    }
    return sineArray;
}