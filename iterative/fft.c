#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fft.h"

void recursiveFFT(struct complex *inputArray, int length) {
    int n = length;
    int half = n / 2;

    if (n == 1) {
        return;
    }

    //allocate memory of even and odd
    struct complex *oddArray = malloc(half * sizeof(struct complex));
    struct complex *evenArray = malloc(half * sizeof(struct complex));
    for (int i = 0; 2 * i < n; i++) {
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
    for (int i = 0; i < n / 2; i++) {
        struct complex w;
        w.real = cos(2.0 * M_PI * (double) (i) / (double) (n));
        w.imag = -sin(2.0 * M_PI * (double) (i) / (double) (n));
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

// Adapted from http://shorturl.at/msuy5
void iterativeFFT(struct complex *inputArray, struct complex *outputArray, int length) {
    if (length == 1) {
        outputArray[0] = inputArray[0];
        return;
    }

    int halfLength = length / 2;

    for (int skip = length, i = 0, shuffle = 0; i < halfLength; i++) {
        struct complex evenArray = inputArray[shuffle];
        struct complex oddArray = inputArray[shuffle + halfLength];

        outputArray[i * 2] = AddComplex(evenArray, oddArray);
        outputArray[i * 2 + 1] = SubtractComplex(evenArray, oddArray);

        if (i == 0 || isPowerOf2(i + 1)) {
            skip /= 2;
            shuffle = skip / 2;
        } else {
            shuffle += skip;
        }
    }

    for (unsigned int evenToOdd = 2; evenToOdd < length; evenToOdd *= 2) {
        double angle = -M_PI / evenToOdd;

        struct complex partialRotation;
        partialRotation.real = cos(angle);
        partialRotation.imag = sin(angle);

        struct complex currentRotation;
        currentRotation.real = 1;
        currentRotation.imag = 0;

        for (unsigned int i = 0, toEven = 0; i < halfLength; i++, toEven++) {
            if (i % evenToOdd == 0) {
                toEven = 2 * i;
                currentRotation.real = 1;
                currentRotation.imag = 0;
            }

            struct complex *even = outputArray + toEven;
            struct complex *odd = even + evenToOdd;

            const struct complex oddRotated = MultiplyComplex(*odd, currentRotation);
            *odd = SubtractComplex(*even, oddRotated);
            *even = AddComplex(*even, oddRotated);
            currentRotation = MultiplyComplex(currentRotation, partialRotation);
        }
    }
}

_Bool isPowerOf2(int n) {
    return (n & n - 1) == 0;
}

void PrintComplexArray(struct complex *printingArray, int length) {
    int n = length;
    for (int i = 0; i < n; i++) {
        printf("[%i]: %lf, %lfi\n", i, printingArray[i].real, printingArray[i].imag);
    }
}

/*(a + bi) * (c + di) = (ac − bd) + (ad + bc)i*/
struct complex MultiplyComplex(struct complex a, struct complex b) {
    struct complex result;
    result.real = (a.real * b.real - a.imag * b.imag);
    result.imag = (a.real * b.imag + a.imag * b.real);
    return result;
}

struct complex AddComplex(struct complex a, struct complex b) {
    struct complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

struct complex SubtractComplex(struct complex a, struct complex b) {
    struct complex result;
    result.real = a.real - b.real;
    result.imag = a.imag - b.imag;
    return result;
}

/*A sine wave of frequency f with amplitude r and phase θ is equivalently a complex number r*cos(θ) + ir*sin(θ) */
struct complex *GenerateSineArray(int samples, int frequency, int amplitude) {
    struct complex *sineArray = malloc(samples * sizeof(struct complex));
    for (int i = 0; i < samples; i++) {
        sineArray[i].real = amplitude * cos(frequency * 2 * M_PI * i / samples);
        sineArray[i].imag = amplitude * sin(frequency * 2 * M_PI * i / samples);
    }
    return sineArray;
}