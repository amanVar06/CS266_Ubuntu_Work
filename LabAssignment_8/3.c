#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// global variables delaration;
#define M 3 // no of resources
#define N 5 // no of processes

int i = 0;
int j = 0;

pthread_mutex_t mutex;
int init[M];
int available[M] = { 3, 3, 2 };
int allocmatrix[N][M] = {{0, 1, 0},  // P0    
                         {2, 0, 0},  // P1
                         {3, 0, 2},  // P2
                         {2, 1, 1},  // P3
                         {0, 0, 2}}; // P4;

int MaxMatrix[N][M] = {{7, 5, 3},    // P0   
                       {3, 2, 2},    // P1
                       {9, 0, 2},    // P2
                       {2, 2, 2},    // P3
                       {4, 3, 3}};   // P4

int NeedMatrix[N][M];

void *processes(void *processID)
{
    int pID = *(int *)processID;
    int c = 0;
    while (c < 3)
    {
        // generate random requests
        sleep(2);
        int request[M];
        pthread_mutex_lock(&mutex);

        // Initialize the NeedMatrix vector 
        for (i = 0; i < M; i++)
        {
            if (NeedMatrix[pID][i] != 0)
            {
                //storing random values
                request[i] = rand() % NeedMatrix[pID][i];
            }
            else
            {
                request[i] = 0;
            }
        }

        printArray(request);
        getResources(pID, request);
        pthread_mutex_unlock(&mutex);

        // generate the random release vector
        sleep(2);
        int releaseVector[M];
        pthread_mutex_lock(&mutex);

        // Initialize the release vector
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

        printArray(releaseVector);
        releaseResources(pID, releaseVector);
        pthread_mutex_unlock(&mutex);

        c++;
    }
}

//function for getting resources from banker
int getResources(int pID, int request[])
{
    if (isCaseGreaterThanNeeded(pID, request) == -1)
    {
        printf("Number of requested Resources is more than Needed.\n");
        return -1;
    }
    printf("Resources are being allocated...\n");

    if (isEnoughToAllCase(request) == -1)
    {
        printf("Not enough Resources.\n");
        return -1;
    }

    for (i = 0; i < M; ++i)
    {
        NeedMatrix[pID][i] -= request[i];
        allocmatrix[pID][i] += request[i];
        available[i] -= request[i];
    }
    printf("Checking if the state is safe or not?\n");

    if (checkIfSafe() == 0)
    {
        printf("\nState is safe. \n");
        exit(1);
        return 0;
    }
    else
    {
        printf("\nState is not safe. \n");
        exit(1);

        return -1;
    }
}

// function used for releasing the resources
int releaseResources(int pID, int releaseVector[])
{

    if (isCaseEnoughToRelease(pID, releaseVector) == -1)
    {
        printf("Not enought Resources.\n");
        return -1;
    }
    for (i = 0; i < M; i++)
    {
        allocmatrix[pID][i] -= releaseVector[i];
        NeedMatrix[pID][i] += releaseVector[i];
        available[i] += releaseVector[i];
    }
    printf("Released.\nMatrix Available:\n");
    printArray(available);
    printf("Matrix Allocated:\n");
    showAllocationMatrix();
    printf("Matrix Need:\n");
    showNeedMatrix();
    return 0;
}

int isCaseEnoughToRelease(int pID, int releaseVector[])
{
    //checking if the case is enough to release
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

int isCaseGreaterThanNeeded(int pID, int request[])
{
    //checking if Number of requested Resources is more than Needed
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

int isEnoughToAllCase(int request[])
{
    // checking if Resources are enough
    for (i = 0; i < M; ++i)
    {
        if (request[i] <= available[i])
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

void showNeedMatrix()
{
    //printing need matrix
    for (i = 0; i < N; ++i)
    {
        printf("{ ");
        for (j = 0; j < M; ++j)
        {
            printf("%d, ", NeedMatrix[i][j]);
        }
        printf("}\n");
    }
    return;
}

void showAllocationMatrix()
{
    //printing allocation matrix
    for (i = 0; i < N; ++i)
    {
        printf("{ ");
        for (j = 0; j < M; ++j)
        {
            printf("%d, ", allocmatrix[i][j]);
        }
        printf("}\n");
    }
    return;
}

void printArray(int vec[])
{
    for (i = 0; i < M; ++i)
    {
        printf("%d, ", vec[i]);
    }
    printf("\n");
    return;
}

int checkIfSafe()
{
    //This algorithm may require an order of m × n2 operations to determine whether
    //a state is safe.
    int finish[N] = {0};
    int work[M];

    for (i = 0; i < M; i++)
    {
        work[i] = available[i];
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

int main()
{
    // Initialize the need matrix
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < M; ++j)
        {
            NeedMatrix[i][j] = MaxMatrix[i][j] - allocmatrix[i][j];
        }
    }

    printf("Available Vector is:\n");
    printArray(available);

    printf("Allocation Matrix is:\n");
    showAllocationMatrix();

    printf("Need Matrix is:\n");
    showNeedMatrix();

    pthread_mutex_init(&mutex, NULL);
    pthread_attr_t attrDefault;
    pthread_attr_init(&attrDefault);
    pthread_t *tid = malloc(sizeof(pthread_t) * N);

    int *pid = malloc(sizeof(int) * N); // process ID

    // initialize pid and create pthreads
    for (i = 0; i < N; i++)
    {
        *(pid + i) = i;
        pthread_create((tid + i), &attrDefault, processes, (pid + i));
    }

    // join all the threads
    for (i = 0; i < N; i++)
    {
        pthread_join(*(tid + i), NULL);
    }
    return 0;
}