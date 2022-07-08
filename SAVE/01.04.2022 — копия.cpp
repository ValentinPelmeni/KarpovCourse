#include <fstream>
#include <mpi.h>
#include <iostream>
#include <cmath>

int main(int argc , char *argv[])
{
    std::cout << "test \n";
    int size, rank, temp, N;
    N = 0;
    temp = 0;
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

    
    std::cout << "size"<< size <<" \n " ;
    
    for (int i = 1; i <= size; i++)
    {
        N += (i);
        N += (i - 1);
    }
    std::cout << " N - " << N << " \n ";
    int* mass = new int[N + 10];
    for (int i = 0; i < N; i++)
    {
    mass[i] = 0;
    }
    std::cout << " \n mass \n";
    for (int i = 0; i < N ; i++)
    {
        std::cout << i << " - " << mass[i]<< "\n";
    }
    int* count = new int[size];
    for (int i = 0; i < size; i++)
    {
        count[i] = i;//тут
    }
    std::cout << " \n count \n";
    for (int i = 0; i <size ; i++)
    {
        std::cout << i << " - " << count[i] << "\n";
    }
    int* rgmass = new int[rank + 1];
    for (int i = 0; i < rank + 1; i++)
    {
        rgmass[i] = rank + 1;
    }
    std::cout << " \n rgmass"<< rank << "\n";
    for (int i = 0; i <rank + 1 ; i++)
    {
        std::cout << i << " - " << rgmass[i] << "\n";
    }
    int* displs = new int[size];
    temp = 0;
    for (int i = 0; i < size; i++)
    {
        displs[i] = temp;
        // тут 
        temp += ((i + 1) * 2);
    }
    std::cout << " \n displs \n";
    for (int i = 0; i < size; i++)
    {
        std::cout << i << " - " << displs[i] << "\n";
    }

    if( MPI_Gatherv(&rgmass,1 , MPI_INT, &mass, displs,displs,  MPI_INT,0 , MPI_COMM_WORLD) != MPI_SUCCESS)
    {
        MPI_Abort(MPI_COMM_WORLD, 2);
    }
    if (rank == 0)
    {
        std::ofstream fout;
        fout.open("output.txt");
        for (int i = 0; i < N; i++)
        {
            fout << i;
            fout << " - ";
            fout << mass[i];
            fout << "\n";
        }
        fout.close();
        std::cout << " \n mass \n";
        for (int i = 0; i < N; i++)
        {
            std::cout << i << " - " << mass[i] << "\n";
        }
    }

    MPI_Finalize();
}
