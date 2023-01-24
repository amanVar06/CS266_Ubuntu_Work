/*
Name : Aman Varshney
ID: 202051217
IMPLEMEMTING FIBONACCI BUDDY SYSTEM
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// void allocateMemoryToProcess(int totalMemory, int * ptr, int len){
//     int i = 1;
//     while (totalMemory > 0)
//     {
//         printf("Process No. %d",i);
//         printf("Memory allocated: %d",ptr[returnIndex(ptr,totalMemory,len)]);
//         totalMemory = totalMemory - ptr[returnIndex(ptr,totalMemory,len)];
//         printf("remaining memory: %d\n",totalMemory);

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

void storeFibonacciInArray(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = fibonacciNumberAtIndex(i);
    }

    printf("The elements of the array are: \n");
    for (int i = 0; i < n; ++i)
    {
        printf("%d, ", arr[i]);
    }
}

// int returnIndex(int *arr, int key, int length){
//     for (int i = 0; i < length; i++)
//     {
//         if(arr[i] == key){
//             return i-1;
//         }
//     }

// }

int main()
{

    // This pointer will hold the
    // base address of the block created
    int *ptr;
    int n;

    // Get the number of elements for the array
    // printf("Enter number of elements:");
    // scanf("%d",&n);
    // printf("Entered number of elements: %d\n", n);
    n = 10;

    // allocateMemory(ptr, n);
    printf("\n");
    // printFibonacciUpToNTerms(20);
    storeFibonacciInArray(ptr, n);
    // printf("\n%d\n", fibonacciNumberAtIndex(6));
    // printf("\n");

    // allocateMemoryToProcess(50,ptr,n);
    // int ans = BuddySystem(ptr,10, 23);
    // printf("%d\n",ans);

    return 0;
}
