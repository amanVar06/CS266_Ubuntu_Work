#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

//int fib[10];

void allocateMemoryToProcess(int totalMemory, int  ptr[], int len){
    int i = 1;
    int k;
    int index;
    // for (int i = 0; i < len; i++)
    // {
    //     printf("%d, ", ptr[i]);
    // }

    while (totalMemory >= 8)
    {
        printf("Process No. %d\t",i);
        i++;

        for (k = 6; k < len; k++)
        {
            if (ptr[k] > totalMemory)
            {
                index = k - 1;
                break;
            }
            else{
                index = len -1;
            }
        }

        printf("Memory allocated: %d\t",ptr[index]);
        totalMemory = totalMemory - ptr[index];
        printf("remaining memory: %d\n",totalMemory);

    }

}

// int returnIndex(int * arr, int key, int length){
//     for (int i = 0; i < length; i++)
//     {
//         if(arr[i] == key){
//             return i-1;
//         }
//     }

// }


int fibonacciNumberAtIndex(int i)
{
    if (i == 0)
    {
        return 0;
    }
    else
    {
        int f1 = 0;
        int f2 = 1;
        int next;
        while (i > 1)
        {
            next = f1 + f2;
            f1 = f2;
            f2 = next;
            i--;
        }
        return f2;
    }
}

void storeFibonacciInArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = fibonacciNumberAtIndex(i);
    }

    // printf("The elements of the array are: \n");
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d, ", arr[i]);
    // }
}

int main(int argc, char const *argv[])
{
    int arr[1000];
    int n = 1000;
    srand(time(0));
    int reqArr[10];
    
    for (int i = 0; i < 10; i++)
    {
        reqArr[i] = rand() % 1000;
    }
    
    
    //int random = rand() % 1000;
    storeFibonacciInArray(&arr[0],n);
    //printf("%d\n",random);

    for (int i = 0; i < 10; i++)
    {
        printf("Request No. %d\n",i+1);
        printf("Memory size to allocate : %d\n",reqArr[i]);
        allocateMemoryToProcess(reqArr[i],arr,n);
        printf("\n");

    }
    
    
    

    // int ans = fibonacciNumberAtIndex(8);
    // printf("%d\n", ans);

    return 0;
}
