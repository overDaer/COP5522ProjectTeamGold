#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define M_PI  3.14159265358979323846

struct complex {
    double real;
    double imag;
};

void recursiveFFT(struct complex *inputArray, int length);
void printComplexArray(struct complex *printingArray, int length);
struct complex MultiplyComplex(struct complex a, struct complex b);

int main(int argc, char const *argv[])
{
    int length = 16;
    //allocate memory
    struct complex *inputTestArray = malloc(length * sizeof(struct complex));
    //initialize values
    for (int i = 0; i < length; i ++){
        inputTestArray[i].real = i+1;
        inputTestArray[i].imag = 0;
    }
    for (int i = 0; i < length; i ++){
        printf("initialArray[%i]: %lf ,%lfi\n", i ,inputTestArray[i].real, inputTestArray[i].imag);
    }
    recursiveFFT(inputTestArray, length);
    //printComplexArray(inputTestArray, 4);
    /* code */
    return 0;
}

void recursiveFFT(struct complex *inputArray, int length){
    int n = length;
    int half = n / 2;
    
    if (n == 1) {
        return;
    }

    //allocate memory of even and odd
    struct complex *oddArray = malloc(half * sizeof(struct complex));;
    struct complex *evenArray = malloc(half * sizeof(struct complex));;
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
    printf("array size: %i\n",n);
    double angle = 2 * M_PI / n;
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
    printComplexArray(inputArray, n);
}

void printComplexArray(struct complex *printingArray, int length){
    int n = length;
    for (int i = 0; i < n; i++){
        printf("result[%i]: %lf, %lfi\n", i, printingArray[i].real, printingArray[i].imag);
    }
}
struct complex MultiplyComplex(struct complex a, struct complex b){
    struct complex result;
    result.real = (a.real * b.real - a.imag * b.imag);
    result.imag = (a.real * b.imag + a.imag * b.real);
    return result;
}