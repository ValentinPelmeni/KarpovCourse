#include <fstream>
#include <mpi.h>
#include <iostream>
#include <cmath>

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
int main(int argc , char *argv[])
{
    int size, rank;
    double data,output;
    int N;
    output = 0;
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
    //for (int i = 0; i < size; i++)
    //{
        if (rank == 0)
        {
            std::ifstream textfile;
            textfile.open("data.txt");
            textfile >> N;
            textfile.close();
            data = 0;
            for (int j = 1; j < size; j++)
            {
                if (MPI_Send(&N, 1, MPI_INT, j, 1, MPI_COMM_WORLD) != MPI_SUCCESS)
                {
                    MPI_Abort(MPI_COMM_WORLD, 1);
                }
            }
            for (int j = 1; j < size; j++)
            {
                if (MPI_Recv(&data, 1, MPI_DOUBLE, j, 2, MPI_COMM_WORLD, NULL) != MPI_SUCCESS)
                {
                    MPI_Abort(MPI_COMM_WORLD, 1);
                }
                output = output + data;
            }

            std::cout << output << "\n";
           
        }
        else 
        {
            if (MPI_Recv(&N, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, NULL) != MPI_SUCCESS)
            {
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
            int ibeg = (rank - 1) * (int(N) / size);
            int iend;
            if (rank != size - 1)
            {
                iend = (rank) * (int(N) / size) - 1;
            }
            else
            {
                iend = N - 1;
            }
            double start, stop;
            start = (float(ibeg) / N) * 2;
            stop = (float(iend) / N) * 2;
            data = sum(start, stop, iend - ibeg);
            if (MPI_Send(&data, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD) != MPI_SUCCESS)
            {
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
        }
    //}

    MPI_Finalize();
}
