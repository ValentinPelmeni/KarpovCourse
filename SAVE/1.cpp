//#include <fstream>
//#include <iostream>
#include <cmath>
//#include <cstdlib>
//#include <cstdio>
#include <iostream>
#include <omp.h>
//#include <string>
int main()
{
    double temp1,temp2;
    double st = 2;
    double sum=0;
    int N = 10000;
    //std::cin >> N;
    st = 2 / double(N);
    for (int i = 0; i < N; i++)
    {
        temp1 = std::sqrt(4 - ((i*st)*(i*st)));
        temp2 = std::sqrt(4 - (((i+1) * st) * ((i+1) * st)));
        temp1 = (temp1 + temp2) / 2;
        sum += temp1 * st;
    }
    std::cout << sum;
}

