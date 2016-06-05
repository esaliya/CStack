//
// Created by Saliya on 7/6/2015.
//
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <pthread.h>
#include "program.h"

#include "mpi.h"

int procRank;
int procCount;

int pointCount = 0;
int dimension = 0;

void GenerateRandomPoints(int count, int dimension, double *pDouble);

void AllGather(double *partialBuffer, double *fullBuffer, int dimension, int lengths[], int pInt1[]);

void ComputeMessageLengths(int dimension, int lengths[]);

void PrintPointsByRank(char* prefix, int count, int dimension, double *points);

double currentTimeInSeconds(void);

int main(int argc, char* argv[])
{
    int rank, size, len;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    MPI_Comm_size(MPI_COMM_WORLD, &procCount);
    MPI_Get_library_version(version, &len);
    /*printf("Hello, world, I am %d of %d, (%s, %d)\n",
           procRank, procCount, version, len);*/

    pointCount = (int) strtol(argv[1], NULL, 10);
    dimension = (int) strtol(argv[2], NULL, 10);
    int iter = (int) strtol(argv[3], NULL, 10);

    int q = pointCount / procCount;
    int r = pointCount % procCount;

    int myPointCount = r > 0 && procRank < r ? q+1 : q;
    double *partialBuffer = malloc(myPointCount * dimension * sizeof(double));
    double *fullBuffer = malloc(pointCount * dimension * sizeof(double));

    GenerateRandomPoints(myPointCount, dimension, partialBuffer);

    int lengths[procCount];
    ComputeMessageLengths(dimension, lengths);
    int displas[procCount];
    displas[0] = 0;
    int i;
    for (i = 0; i < procCount - 1; ++i)
    {
        displas[i+1] = displas[i] + lengths[i];
    }

    double t = 0.0;
    for (i = 0; i < iter; ++i)
    {

        /*PrintPointsByRank("partial", myPointCount, dimension, partialBuffer);*/
        MPI_Barrier();
        double t1 = currentTimeInSeconds();
        AllGather(partialBuffer, fullBuffer, dimension, lengths, displas);
        double t2 = currentTimeInSeconds();
        t += (t2 - t1);
        /*PrintPointsByRank("full", pointCount, dimension, fullBuffer);*/
    }

    if (procRank == 0){
        printf("Allgatherv time %e seconds", t);
    }

    free(partialBuffer);
    free(fullBuffer);

    MPI_Finalize();

    return 0;
}

void PrintPointsByRank(char* prefix, int count, int dimension, double *points) {
    int rank;
    for (rank = 0; rank < procCount; ++rank){
        int buff[1];
        if (procRank == 0){
            buff[0] = rank;
        }
        MPI_Bcast(buff, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (buff[0] == procRank){
            printf("Rank: %d %s buffer ... \n", procRank, prefix);
            int i;
            for (i = 0; i < count; ++i){
                int j;
                for (j = 0; j < dimension; ++j){
                    printf("%lf\t", points[i*dimension+j]);
                }
                printf("\n");
            }
        }

    }
}

void AllGather(double *partialBuffer, double *fullBuffer, int dimension, int lengths[], int displas[])
{
    MPI_Allgatherv(partialBuffer, lengths[procRank], MPI_DOUBLE, fullBuffer, lengths, displas, MPI_DOUBLE, MPI_COMM_WORLD);
}

void ComputeMessageLengths(int dimension, int lengths[]) {
    int q = pointCount/procCount;
    int r = pointCount%procCount;
    int i;
    for (i = 0; i < procCount; ++i)
    {
        lengths[i] = dimension *(i < r ? q+1 : q);
    }
}

void GenerateRandomPoints(int count, int dimension, double *pDouble) {
    int i,j;
    for (i = 0; i < count; ++i){
        for (j = 0; j < dimension; ++j)
        {
            pDouble[i] = (((i+j) & 1) == 0 ? (0.9999995 / 1.0000023) : (1.0000023 / 0.9999995));
        }
    }
}

void print(char* msg, ...){
    if (procRank != 0) return;
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);
}

double currentTimeInSeconds(void)
{

    int flag;
    clockid_t cid = CLOCK_REALTIME; // CLOCK_MONOTONE might be better
    struct timespec tp;
    double timing;

    flag = clock_gettime(cid, &tp);
    if (flag == 0) timing = tp.tv_sec + 1.0e-9*tp.tv_nsec;
    else           timing = -17.0;         // If timer failed, return non-valid time

    return(timing);
};
