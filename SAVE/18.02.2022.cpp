
#include <mpi.h>
#include <iostream>

int main(int argc , char *argv[])
{
    if (MPI_Init(&argc,&argv) != MPI_SUCCESS)
    {
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    
    
    std::cout << "Hello!\n";
    MPI_Finalize();

}
