#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
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
}

void iterativeFFT(struct complex *inputArray, int length) {
    shuffle(inputArray, length);
    evaluate(inputArray, length);
}

void shuffle(struct complex *data, int length) {

#pragma omp parallel default(none) shared(length, data)
    {
        //printf("omp_get_num_threads(): %d\n", omp_get_num_threads());
        //printf("shuffle() called by thread #%d\n", omp_get_thread_num());

        int i;
        int j = 0;
        int N = 1 << length;
        int Nd2 = N >> 1;
        int Nm1 = N - 1;

#pragma omp for nowait
        for (i = 0; i < N; i++) {
            if (j > i) {
                struct complex tmp = data[i];
                data[i] = data[j];
                data[j] = tmp;
            }

            int lszb = ~i & (i + 1);
            int mszb = Nd2 / lszb;
            int bits = Nm1 & ~(mszb - 1);
            j ^= bits;
        }
    }
}

void evaluate(struct complex *data, int length) {

#pragma omp parallel default(none) shared(data, length)
    {
        unsigned N;
        unsigned r;
        unsigned m, md2;
        unsigned n, k;
        unsigned i_e, i_o;
        double theta_2pi;
        double theta;
        struct complex Wm, Wmk;
        struct complex u, t;

        N = 1 << length;
        theta_2pi = -M_PI;
        theta_2pi *= 2;

#pragma omp for nowait
        for (r = 1; r <= length; r++) {
            m = 1 << r;
            md2 = m >> 1;
            theta = theta_2pi / m;
            Wm.real = cos(theta);
            Wm.imag = sin(theta);

            for (n = 0; n < N; n += m) {
                Wmk.real = 1.f;
                Wmk.imag = 0.f;
                for (k = 0; k < md2; k++) {
                    i_e = n + k;
                    i_o = i_e + md2;
                    u.real = data[i_e].real;
                    u.imag = data[i_e].imag;
                    t = MultiplyComplex(Wmk, data[i_o]);
                    data[i_e].real = u.real + t.real;
                    data[i_e].imag = u.imag + t.imag;
                    data[i_o].real = u.real - t.real;
                    data[i_o].imag = u.imag - t.imag;
                    t = MultiplyComplex(Wmk, Wm);
                    Wmk = t;
                }
            }
        }
    }
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

/*A sine wave of frequency f with amplitude r and phase θ is equivalently a complex number r*cos(θ) + ir*sin(θ) */
struct complex *GenerateSineArray(int samples, int frequency, int amplitude) {
    struct complex *sineArray = malloc(samples * sizeof(struct complex));
    for (int i = 0; i < samples; i++) {
        sineArray[i].real = amplitude * cos(frequency * 2 * M_PI * i / samples);
        sineArray[i].imag = amplitude * sin(frequency * 2 * M_PI * i / samples);
    }
    return sineArray;
}