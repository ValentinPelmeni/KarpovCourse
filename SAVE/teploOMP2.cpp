#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>

int main(int argc, char* argv[]) {

    double* u, * unew, delta, maxdelta;
    double eps = 1.e-6;
    double h, tau;
    int N;
    int i;


    FILE* ff;



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
    u = new double[N + 1];
    N = int(N)
    unew = new double[N + 1];

    for (i = 1; i < N; i++) {
        u[i] = 0;
    }

    unew[0] = u[0] = 1.0;
    unew[N] = u[N] = 0;

    h = 1.0 / N;
    tau = 0.5 * (h * h);

    while (1) {
        #pragma omp parallel for
        for (i = 1; i < N; i++) {
            unew[i] = u[i] + (tau / (h * h)) * (u[i - 1] - 2 * u[i] + u[i + 1]);
        }

        maxdelta = 0;
        #pragma omp parallel for reduction(max : maxdelta) private(delta)
        for (i = 1; i < N; i++) {
            delta = fabs(unew[i] - u[i]);
            if (delta > maxdelta) maxdelta = delta;
        }

        if (maxdelta < eps) break;


        #pragma omp parallel for
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
}
