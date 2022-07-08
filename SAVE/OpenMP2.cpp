//#include <fstream>
//#include <iostream>
//#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <omp.h>
#include <string>
int x0 = 2;

int main()
{
    
    printf("Количество ядер %d \n",omp_get_num_procs());

    #pragma omp parallel num_threads(6)
    {
        printf("Hello OMP! # %d всего %d \n", omp_get_thread_num(),omp_get_num_threads() );
    }
    printf(" # %d всего %d  \n", omp_get_thread_num(), omp_get_num_threads());

}
