//#include <fstream>
//#include <iostream>
//#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <omp.h>
#include <string>
int main()
{
#pragma omp parallel num_threads(6)
    {
        #pragma omp single
        {
            printf("Директива 1, нить %d \n", omp_get_thread_num());
        }
        printf("Номер работ. нити # %d \n", omp_get_thread_num());
        #pragma omp single
        {
            printf("Директива 2, нить %d \n", omp_get_thread_num());
        }
    }
}
