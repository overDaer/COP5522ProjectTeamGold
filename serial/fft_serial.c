#include <stdio.h>
#include <stdlib.h>
#include "fft.h"


int main(int argc, char const *argv[])
{
    int length = 16;
    struct complex *sumWave = malloc(length * sizeof(struct complex));
    //create arbitrary sine waves to sum
    struct complex *sineWave1 = GenerateSineArray(length, 1, 10);
    struct complex *sineWave2 = GenerateSineArray(length, 2, 4);
    struct complex *sineWave3 = GenerateSineArray(length, 4, 5);
    //add sine waves into complex sumWave
    for (int i = 0; i < length; i++){
        sumWave[i].real = sineWave1[i].real + sineWave2[i].real + sineWave3[i].real;
        sumWave[i].imag = sineWave1[i].imag + sineWave2[i].imag + sineWave3[i].imag;
    }
    printf("Printing input Array\n");
    PrintComplexArray(sumWave, length);
    recursiveFFT(sumWave, length);
    printf("Printing output Array\n");
    PrintComplexArray(sumWave, length);
    free(sumWave);
    /* code */
    return 0;
}

