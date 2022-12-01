#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fft.h"


// Adapted from https://github.com/rshuston/FFT-C
void iterativeFFT(struct complex *inputArray, int length)
{
    shuffle(inputArray, length);
    evaluate(inputArray, length);
}

// Adapted from https://github.com/rshuston/FFT-C
void shuffle(struct complex *data, int length)
{
    int N = 1 << length;
    int Nd2 = N >> 1;
    int Nm1 = N - 1;
    int i;
    int j;

    for (i = 0, j = 0; i < N; i++) {
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

// Adapted from https://github.com/rshuston/FFT-C
void evaluate(struct complex *data, int length)
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

    for (r = 1; r <= length; r++)
    {
        m = 1 << r;
        md2 = m >> 1;
        theta = theta_2pi / m;
        Wm.real = cos(theta);
        Wm.imag = sin(theta);

        for (n = 0; n < N; n += m)
        {
            Wmk.real = 1.f;
            Wmk.imag = 0.f;
            for (k = 0; k < md2; k++)
            {
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