#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>

pthread_mutex_t mutex;
#define M 3 // no of resources
#define N 5 // no of processoses
int i = 0;
int j = 0;
pthread_mutex_t mutex;
int init[M];
int avail[M] = { 3, 3, 2 };
int allocmatrix[N][M] = {{0, 1, 0},  // P0    // Allocation Matrix
                         {2, 0, 0},  // P1
                         {3, 0, 2},  // P2
                         {2, 1, 1},  // P3
                         {0, 0, 2}}; // P4;

int MaxMatrix[N][M] = {{7, 5, 3},    // P0    // MAX Matrix
                       {3, 2, 2},    // P1
                       {9, 0, 2},    // P2
                       {2, 2, 2},    // P3
                       {4, 3, 3}};   // P4

int NeedMatrix[N][M];

void *procs(void *procsID)
{
    int pID = *(int *)procsID;
    int c = 0;
    while (c < 3)
    {
        sleep(1);
        int request[M];
        pthread_mutex_lock(&mutex);

        for (i = 0; i < M; i++)
        {
            if (NeedMatrix[pID][i] != 0)
            {
                request[i] = rand() % NeedMatrix[pID][i];
            }
            else
            {
                request[i] = 0;
            }
        }

        printVector(request);
        getRes(pID, request);
        pthread_mutex_unlock(&mutex);

        sleep(1);
        int releaseVector[M];
        pthread_mutex_lock(&mutex);

        for (i = 0; i < M; i++)
        {
            if (allocmatrix[pID][i] != 0)
            {
                releaseVector[i] = rand() % allocmatrix[pID][i];
            }
            else
            {
                releaseVector[i] = 0;
            }
        }
        printVector(releaseVector);
        relRes(pID, releaseVector);
        pthread_mutex_unlock(&mutex);

        c++;
    }
}

int getRes(int pID, int request[])
{
    if (casegreaterthanneed(pID, request) == -1)
    {
        printf("Number of requested Resources is more than Needed.\n");
        return -1;
    }
    printf("Resources are being allocated...\n");

    if (enoughtoalloccase(request) == -1)
    {
        printf("Not enough Resources.\n");
        return -1;
    }

    for (i = 0; i < M; ++i)
    {
        NeedMatrix[pID][i] -= request[i];
        allocmatrix[pID][i] += request[i];
        avail[i] -= request[i];
    }
    printf("Checking is the state is safe...\n");

    if (safemodecase() == 0)
    {
        printf("\nState is safe.\n");
        exit(1);
        return 0;
    }
    else
    {
        printf("\nState is not safe.\n");
        exit(1);
        return -1;
    }
}


int relRes(int pID, int releaseVector[])
{

    if (caseengoughtorel(pID, releaseVector) == -1)
    {
        printf("Not enought Resources.\n");
        return -1;
    }
    for (i = 0; i < M; i++)
    {
        allocmatrix[pID][i] -= releaseVector[i];
        NeedMatrix[pID][i] += releaseVector[i];
        avail[i] += releaseVector[i];
    }
    printf("Released.\nMetrix Available:\n");
    printVector(avail);
    printf("Metrix Allocated:\n");
    printMatrix(allocmatrix);
    printf("Metrix Need:\n");
    printMatrix(NeedMatrix);
    return 0;
}

int caseengoughtorel(int pID, int releaseVector[])
{
    for (i = 0; i < M; ++i)
    {
        if (releaseVector[i] <= allocmatrix[pID][i])
        {
            continue;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}

int casegreaterthanneed(int pID, int request[])
{

    for (i = 0; i < M; ++i)
    {
        if (request[i] <= NeedMatrix[pID][i])
        {
            continue;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}

int enoughtoalloccase(int request[])
{

    for (i = 0; i < M; ++i)
    {
        if (request[i] <= avail[i])
        {
            continue;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}

int checkIfSafe()
{
    //This algorithm may require an order of m × n2 operations to determine whether
    //a state is safe.
    int finish[N] = {0};
    int work[M];

    for (i = 0; i < M; i++)
    {
        work[i] = avail[i];
    }

    int k;
    for (i = 0; i < N; i++)
    {
        if (finish[i] == 0)
        {
            for (j = 0; j < M; j++)
            {
                if (NeedMatrix[i][j] <= work[j])
                {

                    if (j == M - 1)
                    {
                        finish[i] = 1;
                        for (k = 0; k < M; ++k)
                        {
                            work[k] += allocmatrix[i][k];
                        }

                        i = -1;
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            continue;
        }
    }

    for (i = 0; i < N; i++)
    {
        if (finish[i] == 0)
        {

            return -1;
        }
        else
        {
            continue;
        }
    }

    return 0;
}

void printVector(int vec[])
{
    for (i = 0; i < M; ++i)
    {
        printf("%d, ", vec[i]);
    }
    printf("\n");
}

void showMatrix(int[][] matrix)
{
    for (i = 0; i < N; ++i)
    {
        printf("{ ");
        for (j = 0; j < M; ++j)
        {
            printf("%d, ",matrix[i][j]);
        }
        printf("}\n");
    }
    return;
}


int main(int argc, char const *argv[])
{
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < M; ++j)
        {
            NeedMatrix[i][j] = MaxMatrix[i][j] - allocmatrix[i][j];
        }
    }

    printf("Available Vector is:\n");
    printVector(avail);

    printf("Allocation Matrix is:\n");
    printMatrix(allocmatrix);

    printf("Need Matrix is:\n");
    printMatrix(NeedMatrix);

    pthread_mutex_init(&mutex, NULL);
    pthread_attr_t attrDefault;
    pthread_attr_init(&attrDefault);
    pthread_t *tid = malloc(sizeof(pthread_t) * N);

    int *pid = malloc(sizeof(int) * N); // process ID

    for (i = 0; i < N; i++)
    {
        *(pid + i) = i;
        pthread_create((tid + i), &attrDefault, procs, (pid + i));
    }

    for (i = 0; i < N; i++)
    {
        pthread_join(*(tid + i), NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
