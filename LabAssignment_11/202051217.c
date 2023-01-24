#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void printArray(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        if (i == len - 1)
        {
            printf("%d ", arr[i]);
        }
        else
        {
            printf("%d, ", arr[i]);
        }
    }

    printf("\n");
}


int searchInArray(int arr[], int len, int key)
{
    int ret = 0;
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == key)
        {
            ret = 1;
            break;
        }
    }
    return ret;
}

int main()
{
    int maxFrames = 5;
    int x = 20;
    int index = -1;

    int incomingStream[x];
    int pageFaults = 0;
    int pages;

    srand(time(NULL)); // randomize seed

    for (int i = 0; i < x; i++)
    {
        incomingStream[i] = rand() % 10; // call the function to get a different value of n every time
    }

    printf("\nReference Incoming String: ");
    printArray(incomingStream, x);
    int frame_items[maxFrames];

    for (int i = 0; i < maxFrames; i++)
    {
        frame_items[i] = -1;
    }

   

    printf("\n--------------------Approach 1-------------------------\n\n");
    printf("Initial Frame Items: \n");
    printArray(frame_items, 5);
    int hits1 = 0;
    int miss1 = 0;

    for (int j = 0; j < x; j++)
    {

        if (searchInArray(frame_items, 5, -1) == 1)
        {

            if (searchInArray(frame_items, 5, incomingStream[j]) == 1)
            {
                hits1++;
                continue;
            }
            else
            {
                miss1++;
                index++;
                frame_items[index] = incomingStream[j];
                pageFaults++;
                continue;
            }
        }
        else
        {

            if (searchInArray(frame_items, 5, incomingStream[j]) == 1)
            {
                hits1++;
                continue;
            }
            else
            {
                miss1++;
                index = rand() % 5;
                frame_items[index] = incomingStream[j];
                pageFaults++;
                continue;
            }
        }
    }

    printf("Final frame items in 1st Approch: ");
    printArray(frame_items, 5);
    printf("Page Faults in 1st Approch = %d\n", pageFaults);
    printf("Hits in 1st Approch = %d\n", hits1);
    printf("Miss in 1st Approch = %d\n", miss1);


    printf("\n--------------------Approach 2-------------------------\n\n");
    int hits2 = 0;
    int miss2 = 0;
    int index2 = -1;
    int pageFaults2 = 0;
    int frame_items2[maxFrames];

    for (int i = 0; i < maxFrames; i++)
    {
        frame_items2[i] = -1;
    }

    printf("Initial Frame Items: \n");
    printArray(frame_items2, 5);

    for (int j = 0; j < x; j++)
    {

        if (searchInArray(frame_items2, 5, -1) == 1)
        {

            if (searchInArray(frame_items2, 5, incomingStream[j]) == 1)
            {
                hits2++;
                continue;
            }
            else
            {
                miss2++;
                index2++;
                frame_items2[index2] = incomingStream[j];
                pageFaults2++;
                continue;
            }
        }
        else
        {

            if (searchInArray(frame_items2, 5, incomingStream[j]) == 1)
            {
                hits2++;
                continue;
            }
            else
            {
                miss2++;
                int random = rand() % 10;
                switch (random)
                {
                case 0:
                    index2 = 0;
                    break;
                case 1:
                    index2 = 1;
                    break;

                case 2:
                    index2 = 1;
                    break;
                case 3:
                    index2 = 2;
                    break;
                case 4:
                    index2 = 2;
                    break;
                case 5:
                    index2 = 2;
                    break;

                case 6:
                    index2 = 2;
                    break;
                case 7:
                    index2 = 3;
                    break;
                case 8:
                    index2 = 3;
                    break;
                case 9:
                    index2 = 4;
                    break;

                default:
                    break;
                }

                frame_items2[index2] = incomingStream[j];
                pageFaults2++;
                continue;
            }
        }
    }
    printf("Final frame items in 2nd Approch: ");
    printArray(frame_items2, 5);
    printf("Page Faults in 2nd Approch = %d\n", pageFaults2);
    printf("Hits in 2nd Approch = %d\n", hits2);
    printf("Miss in 2nd Approch = %d\n", miss2);



    return 0;
}