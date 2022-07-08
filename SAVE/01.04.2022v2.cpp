#include <fstream>
#include <mpi.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
int main(int argc, char* argv[])
{
    int size, rank, N, tempsize;
    N = 0;
    if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
    {
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    if (MPI_Comm_size(MPI_COMM_WORLD, &size) != MPI_SUCCESS)
    {
        MPI_Abort(MPI_COMM_WORLD, 2);
    }
    if (MPI_Comm_rank(MPI_COMM_WORLD, &rank) != MPI_SUCCESS)
    {
        MPI_Abort(MPI_COMM_WORLD, 3);
    }
    int* temp = new int[size];// массив с размерами
    std::srand(rank + 1);
    tempsize = std::rand() % 7 + 1;
    if (MPI_Gather(& tempsize, 1, MPI_INT, temp, 1, MPI_INT, 0, MPI_COMM_WORLD) != MPI_SUCCESS)
    {
        MPI_Abort(MPI_COMM_WORLD, 3);
    }
    double* output;
    if (rank == 0)
    {
        for (int i = 0; i < size; i++)
        {
            N = N + temp[i];
        }
        output = new double[N];
    }
    double* rgmass = new double[tempsize];
    for (int i = 0; i < tempsize; i++)
    {
        rgmass[i] = std::sqrt(rank);
    }
    int* displs = new int[size];
    displs[0] = 0;
    for (int i = 1; i < size; i++)
    {

        displs[i] = displs[i - 1]+ temp[i - 1];
    }
    if (MPI_Gatherv(rgmass, tempsize, MPI_DOUBLE, output, temp,displs , MPI_DOUBLE, 0, MPI_COMM_WORLD) != MPI_SUCCESS)
    {
        MPI_Abort(MPI_COMM_WORLD, 2);
    }
    if (rank == 0)
    {
        std::ofstream fout;
        fout.open("output2.txt");
        for (int i = 0; i < N; i++)
        {
            fout << i;
            fout << " - ";
            fout << output[i];
            fout << "\n";
        }
        fout.close();
    }


    MPI_Finalize();
   
}
