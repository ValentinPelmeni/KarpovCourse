#include <fstream>
#include <mpi.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>

int main(int argc, char* argv[]) {
    int size, rank;
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
    
    double* u, * unew, delta, maxdelta;
    double eps = 1.e-6;
    double h, tau;
    int N = 1;
    int i;
    int jbeg, jend ,tempsize;
    int* temp = new int[size];// массив с размерами



    FILE* ff;

    if (rank == 0)
    {
        if (argc != 2) {
            printf("Usage: exefile npoints\n");
            exit(-1);
        }

        N = atoi(argv[1]);
        if (N == 0) {
            printf("Set N to 1000\n");
            N = 1000;
        }
        else {
            printf("Set N to %d\n", N);
        }
    }
   
    if (MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD) != MPI_SUCCESS)
    {
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
   
    u = new double[N + 1];
 
    unew = new double[N + 1];

    for (i = 1; i < N; i++) {
        u[i] = 0;
    }

    unew[0] = u[0] = 1.0;
    unew[N] = u[N] = 0;

    h = 1.0 / N;
    tau = 0.5 * (h * h);
    if (rank == size - 1)
    {
        jbeg = (rank * ((N - 1) / size)) + 1;
        jend = N - 1;
    }
    else
    {
        jbeg = (rank * ((N - 1) / size)) + 1;
        jend = ((rank + 1) * ((N - 1) / size));
    }
    while (1) 
    {
        for (i = jbeg; i <= jend; i++)
        {
            unew[i] = u[i] + (tau / (h * h)) * (u[i - 1] - 2 * u[i] + u[i + 1]);
        }
        maxdelta = 0;
        for (i = jbeg; i <= jend; i++) 
        {
            delta = fabs(unew[i] - u[i]);
            if (delta > maxdelta) maxdelta = delta;
        }
        if (MPI_Reduce(&maxdelta, &delta, 1, MPI_DOUBLE, MPI_MAX, 0 , MPI_COMM_WORLD) != MPI_SUCCESS)
        {
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        maxdelta = delta;
        if (MPI_Bcast(&maxdelta, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD) != MPI_SUCCESS)
        {
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        if (maxdelta < eps) break;
        if (rank == 0)
        {
            if (MPI_Send(&unew[jend], 1, MPI_DOUBLE, 1, 2, MPI_COMM_WORLD) != MPI_SUCCESS)
            {
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
            if (MPI_Recv(&unew[jend + 1], 1, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD, NULL) != MPI_SUCCESS)
            {
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
        }
        else if (rank != size - 1)
        {
            if (MPI_Send(&unew[jbeg], 1, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD) != MPI_SUCCESS)
            {
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
            if (MPI_Send(&unew[jend], 1, MPI_DOUBLE, rank + 1, 2, MPI_COMM_WORLD) != MPI_SUCCESS)
            {
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
            if (MPI_Recv(&unew[jend + 1], 1, MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD, NULL) != MPI_SUCCESS)
            {
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
            if (MPI_Recv(&unew[jbeg - 1], 1, MPI_DOUBLE, rank - 1, 2, MPI_COMM_WORLD, NULL) != MPI_SUCCESS)
            {
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
        }
        else
        {
            if (MPI_Send(&unew[jbeg], 1, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD) != MPI_SUCCESS)
            {
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
            if (MPI_Recv(&unew[jbeg - 1], 1, MPI_DOUBLE, rank - 1, 2, MPI_COMM_WORLD, NULL) != MPI_SUCCESS)
            {
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
        }
        for (i = 1; i < N; i++) 
        {
            u[i] = unew[i];;
        }
    }
    tempsize = jend - jbeg + 1;
    if (MPI_Gather(&tempsize, 1, MPI_INT, temp, 1, MPI_INT, 0, MPI_COMM_WORLD) != MPI_SUCCESS)
    {
        MPI_Abort(MPI_COMM_WORLD, 3);
    }
    int* displs = new int[size];
    displs[0] = 1;
    for (int i = 1; i < size; i++)
    {

        displs[i] = displs[i - 1] + temp[i - 1];
    }
    if (MPI_Gatherv(&unew[jbeg], tempsize, MPI_DOUBLE, u, temp, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD) != MPI_SUCCESS)
    {
        MPI_Abort(MPI_COMM_WORLD, 2);
    }

    if ((ff = fopen("seqres", "w+")) == NULL) {
        printf("Can't open file\n"); free(u); free(unew);
        exit(-1);
    }

    if (rank == 0)
    {
        for (i = 0; i < N + 1; i++)
        {
            fprintf(ff, "%f ", u[i]);
        }
    }
    fclose(ff);
    MPI_Finalize();
}
