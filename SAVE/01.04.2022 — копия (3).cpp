#include <fstream>
#include <mpi.h>
#include <iostream>
#include <cmath>

int main(int argc, char* argv[])
{
    int size, rank, temp, N;
    N = 0;
    temp = 0;
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

    for (int i = 1; i <= size; i++)
    {
        N += (i);
        N += (i - 1);
    }

    int* mass = new int[N];
    for (int i = 0; i < N; i++)
    {
        mass[i] = 0;
    }

    int* displs = new int[size];
    temp = 0;
    for (int i = 0; i < size; i++)
    {
        displs[i] = temp;
        temp += ((i + 1) * 2);
    }
    int* count = new int[size];
    for (int i = 0; i < size; i++)
    {
        count[i] = i + 1;
    }
    int* rgmass = new int[rank + 1];
    for (int i = 0; i < rank + 1; i++)
    {
        rgmass[i] = rank + 1;
    }

   if(MPI_Gatherv(rgmass, rank + 1 , MPI_INT, mass, count, displs,  MPI_INT,0 , MPI_COMM_WORLD) != MPI_SUCCESS)
   {
        MPI_Abort(MPI_COMM_WORLD, 2);
   }
   if (rank == 0)
   {
       std::ofstream fout;
       fout.open("output1.txt");
       for (int i = 0; i < N; i++)
       {
           fout << i;
           fout << " - ";
           fout << mass[i];
           fout << "\n";
       }
       fout.close();
   }

    MPI_Finalize();
   
}
