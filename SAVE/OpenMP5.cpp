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
        #pragma omp sections
        {
            #pragma omp section
            {
                printf("Директива 1, нить %d \n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("Директива 2, нить %d \n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("Директива 3, нить %d \n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("Директива 4, нить %d \n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("Директива 5, нить %d \n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("Директива 6, нить %d \n", omp_get_thread_num());
            }
        }
        printf("Номер работ. нити # %d \n", omp_get_thread_num());
    }
}
