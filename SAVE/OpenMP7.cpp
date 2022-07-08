#include <fstream>
#include <iostream>
//#include <cmath>
//#include <cstdlib>
//#include <cstdio>
#include <iostream>
#include <omp.h>
//#include <string>
int main()
{
    
    
    int count = 0;
#pragma omp parallel num_threads(4)
    {
        for (int i = 0; i < 100; i ++)
        {
            #pragma omp atomic
            count++;
        }
       
    } / home / lfi202220 / 18.02.2022
    
    printf("count = %d\n", count);
}

