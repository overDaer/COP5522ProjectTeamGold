README:
In order to use run the iterative FFT use the following steps.
1. generate necessary files using command "make" in linux terminal
2. run the program using the following format, where N is number of samples 2^N (exponential, less than 23 recommended)
format:  ./serial <N>  //optionally, add "--print" to verify results (for small data sets)
example: ./serial 22
3. run command "make clean" to remove generate object and executable files

