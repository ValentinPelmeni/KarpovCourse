#include <fstream>
#include <iostream>
#include <cmath>
#include <omp.h>

double sum(double start, double stop, int N)
{
    double sum = 0;
    double st = (stop - start) / N;
    double temp1, temp2;
    for (int i = 0; i <= N; i++)
    {
        temp1 = (i * st) + start;
        temp1 = temp1 * temp1;
        temp1 = 4 - temp1;
        temp1 = std::sqrt(temp1);
        temp2 = std::sqrt(float(4 - ((((i + 1) * st) + start) * (((i + 1) * st) + start))));
        temp1 = (temp1 + temp2) / 2;
        sum += temp1 * st;
      
    }
    return sum;

}
int main(int argc, char* argv[])
{
    double output = 0;
    int N;
    std::ifstream textfile;
    textfile.open("data.txt");
    textfile >> N;
    textfile.close();
#pragma omp parallel num_threads(6) reduction(+:output)
    {
    int size, rank;
    size = omp_get_num_threads();
    rank = omp_get_thread_num();
    
    
 
        int ibeg = (rank) * (int(N) / size);
        int iend;
        if (rank != size - 1)
        {
            iend = (rank + 1) * (int(N) / size) - 1;
        }
        else
        {
            iend = N - 1;
        }
        double start, stop;
        start = (float(ibeg) / N) * 2;
        stop = (float(iend) / N) * 2;
        output = sum(start, stop, iend - ibeg);
    }
std::cout << output;
}
