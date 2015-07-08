//
// Created by Saliya on 7/6/2015.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "program.h"

#include "mpi.h"

int procRank;
int procCount;

int pointCount = 0;
int dimension = 0;

void GenerateRandomPoints(int count, int dimension, double *pDouble);

void AllGather(double *partialBuffer, double *fullBuffer, int dimension);

void ComputeMessageLengths(int dimension, int lengths[]);

void PrintPointsByRank(char* prefix, int count, int dimension, double *points);

int main(int argc, char* argv[])
{
    int rank, size, len;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    MPI_Comm_size(MPI_COMM_WORLD, &procCount);
    MPI_Get_library_version(version, &len);
    printf("Hello, world, I am %d of %d, (%s, %d)\n",
           procRank, procCount, version, len);

    pointCount = (int) strtol(argv[1], NULL, 10);
    dimension = (int) strtol(argv[2], NULL, 10);
    int iter = (int) strtol(argv[3], NULL, 10);

    int q = pointCount / procCount;
    int r = pointCount % procCount;

    int myPointCount = r > 0 && procRank < r ? q+1 : q;
    double *partialBuffer = malloc(myPointCount * dimension * sizeof(double));
    double *fullBuffer = malloc(pointCount * dimension * sizeof(double));

    int i;
    for (i = 0; i < iter; ++i)
    {
        GenerateRandomPoints(myPointCount, dimension, partialBuffer);
        PrintPointsByRank("partial", myPointCount, dimension, partialBuffer);
        AllGather(partialBuffer, fullBuffer, dimension);
        PrintPointsByRank("full", pointCount, dimension, fullBuffer);
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

void AllGather(double *partialBuffer, double *fullBuffer, int dimension) {
    int lengths[procCount];
    ComputeMessageLengths(dimension, lengths);
    int displas[procCount];
    displas[0] = 0;
    int i;
    for (i = 0; i < procCount - 1; ++i)
    {
        displas[i+1] = displas[i] + lengths[i];
    }
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
    srand((unsigned int) time(NULL));
    int total_doubles = count * dimension;
    int i;
    for (i = 0; i < total_doubles; ++i){
        pDouble[i] = (double)rand() / (double)RAND_MAX;
    }
}

void print(char* msg, ...){
    if (procRank != 0) return;
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);
}
