#include <fstream>
#include <mpi.h>
#include <iostream>
#include <cmath>

int main(int argc , char *argv[])
{
    int size, rank,temp;
    int data[120];
    int output[120];
    int N;
    for (int i = 0; i < 120; i++)
    {
        data[i] = -1;
        output[i] = -7;
    }
    if (MPI_Init(&argc,&argv) != MPI_SUCCESS)
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
    if (120 % size != 0)
    {
        if(rank == 0)std::cout << "eror 120%size != 0 \n";
    }else
    {
        temp = 120 / size;
            for (int i = rank * temp; i < ((rank + 1) * temp); i++)
            {
                data[i] = rank;
            }
            if (MPI_Gather(&data[rank * temp], temp, MPI_INT, &output, temp, MPI_INT, 0, MPI_COMM_WORLD) != MPI_SUCCESS)
            {
                MPI_Abort(MPI_COMM_WORLD, 3);
            }
            if (rank == 0)
            {
                std::ofstream fout;
                fout.open("output.txt");
                for (int i = 0; i < 120; i++)
                {
                    fout << i;
                    fout << " - ";
                    fout << output[i];
                    fout << "\n";
                }
                fout.close();
            }
    }
    

    MPI_Finalize();
}
