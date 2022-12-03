README:
In order to use run the openmp FFT use the following steps.
1. generate necessary files using command "make" in linux terminal
2. run the program using the following format, where N is 2^N samples, num_threads is number of threads (power of 2)
format:  ./parallel_openmp <N> <num_threads>
example: ./parallel_openmp 22 4
3. run command "make clean" to remove generate object and executable files

