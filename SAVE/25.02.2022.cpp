
#include <mpi.h>
#include <iostream>

int main(int argc , char *argv[])
{
    int size, rank;
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
    
    std::cout <<"Size = " << size << " , ";
    std::cout << "rank = " << rank << "\n";
    MPI_Finalize();

}
