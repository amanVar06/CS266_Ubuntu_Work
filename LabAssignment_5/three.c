#include <stdio.h>
#include <stdlib.h>

//Shortest remaining time first scheduling
//Criteria Burst Time
//Mode Pre emptive

int main(int argc, char const *argv[])
{
    printf("------------------:Shortest Remaining Time First:------------------\n\n");
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    printf("\n");

    int rt[10], endTime, i, smallest;

    int remain = 0, time, sum_wait = 0, sum_turnaround = 0;

    int processes[10];
    int arrival[10];
    int burst[10];
    int start[10];
    // int start[p];
    // int finish[p];
    // int turnaround[p];
    // int waiting[p];

    for (i = 0; i < n; i++)
    {
        int pn, ft, bt;
        printf("Enter the process name, arrival time and burst time: ");
        scanf("%d %d %d",&processes[i],&arrival[i],&burst[i]);

        rt[i] = burst[i];
    }


    printf("\n   PName   |   ArrTime |  BurstTime |   Finish  |");
    printf(" TurnAround|  Waiting  |\n");

    rt[9] = 9999;

    for (time = 0; remain != n; time++)

    {

        smallest = 9;

        for (i = 0; i < n; i++)

        {

            if (arrival[i] <= time && rt[i] < rt[smallest] && rt[i] > 0)

            {
                smallest = i;
            }
        }

        rt[smallest]--;

        if (rt[smallest] == 0)

        {

            remain++;

            endTime = time + 1;
            

            printf("    %d      |     %d     |",processes[smallest],arrival[smallest]);
            printf("    %d      |     %d     |",burst[smallest],endTime);
            printf("    %d      |     %d     |\n",endTime - arrival[smallest],endTime - burst[smallest] - arrival[smallest]);


            sum_wait += endTime - burst[smallest] - arrival[smallest];

            sum_turnaround += endTime - arrival[smallest];
        }

    }
    
    printf("\nAverage waiting time = %f\n", sum_wait * 1.0 / n);

    printf("Average Turnaround time = %f\n", sum_turnaround * 1.0 / n);
    //findFirstArrival(arrival,burst,processes,p);

    //FOR CHECKING      
    // printArray(processes,p);
    // printArray(arrival,p);
    // printArray(burst,p);

    // printf("   PName   |   ArrTime | BurstTime |    Start  |   Finish  |");
    // printf(" TurnAround|  Waiting  |\n");

    // for (int i = 0; i < p; i++)
    // {
    //     printf("    %d      |     %d     |",processes[i],arrival[i]);
    //     printf("    %d      |     %d     |     %d     |",burst[i],start[i],finish[i]);
    //     printf("    %d      |     %d     |\n",turnaround[i],waiting[i]);
    // }


    // printf("Average Waiting time: %f\n",average(waiting,p));
    // printf("Average Turn Around time: %f\n",average(turnaround,p));
    


    
    return 0;
}

// Enter the number of processes you want to print: 5

// Enter the process name, arrival time and burst time: 1 3 1
// Enter the process name, arrival time and burst time: 2 1 4
// Enter the process name, arrival time and burst time: 3 4 2
// Enter the process name, arrival time and burst time: 4 0 6
// Enter the process name, arrival time and burst time: 5 2 3
//    PName   |   ArrTime | BurstTime |    Start  |   Finish  | TurnAround|  Waiting  |
//     1      |     3     |    1      |     3     |     4     |    1      |     0     |
//     2      |     1     |    4      |     2     |     6     |    5      |     1     |
//     3      |     4     |    2      |     6     |     8     |    4      |     2     |
//     5      |     2     |    3      |     8     |     11     |    9      |     6     |
//     4      |     0     |    6      |     10     |     16     |    16      |     10     |
