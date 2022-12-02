#define M_PI  3.14159265358979323846

struct complex {
    double real;
    double imag;
};

void recursiveFFT(struct complex *inputArray, int length);
void iterativeFFT(struct complex *inputArray, int length);
void evaluate(struct complex *data, int length);
void shuffle(struct complex *data, int length);
void PrintComplexArray(struct complex *printingArray, int length);
struct complex MultiplyComplex(struct complex a, struct complex b);
struct complex * GenerateSineArray(int samples, int frequency, int amplitude);
