#include <fstream>
//#include <mpi.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>

int main(int argc, char* argv[]) {
  /*  int size, rank;
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
    */
    double* u, * unew, delta, maxdelta;
    double eps = 1.e-6;
    double h, tau;
    int N;
    int i;


    FILE* ff;

    printf("Enter N from 1 to 1000\n");
    N = 1000;
    if (N == 0) {
        printf("Set N to 1000\n");
        N = 1000;
    }
    else {
        printf("Set N to %d\n", N);
    }

    u = new double[N + 1];
 
    unew = new double[N + 1];

    // begin & bound values

    for (i = 1; i < N; i++) {
        u[i] = 0;
    }

    unew[0] = u[0] = 1.0;
    unew[N] = u[N] = 0;

    h = 1.0 / N;
    tau = 0.5 * (h * h);

    while (1) {
        for (i = 1; i < N; i++) {
            unew[i] = u[i] + (tau / (h * h)) * (u[i - 1] - 2 * u[i] + u[i + 1]);
        }

        maxdelta = 0;
        for (i = 1; i < N; i++) {
            delta = fabs(unew[i] - u[i]);
            if (delta > maxdelta) maxdelta = delta;
        }
        if (maxdelta < eps) break;

        for (i = 1; i < N; i++) {
            u[i] = unew[i];;
        }
    }

    if ((ff = fopen("seqres", "w+")) == NULL) {
        printf("Can't open file\n"); free(u); free(unew);
        exit(-1);
    }

    for (i = 0; i < N + 1; i++)
        fprintf(ff, "%f ", unew[i]);

    fclose(ff);
    //MPI_Finalize();
}
