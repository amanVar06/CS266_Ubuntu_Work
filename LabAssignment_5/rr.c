#include <stdio.h>

int main()
{
    int i, j, n, time, remain, flag = 0, ts;
    int sum_wait = 0, sum_turnaround = 0, at[10], bt[10], rt[10], process[10];

    printf("------------------:Round Robin:------------------\n\n");
    printf("Enter no of Processes : ");
    scanf("%d", &n);

    remain = n;

    for (i = 0; i < n; i++)
    {
        printf("Enter process name, arrival time and burst time: ");
        scanf("%d %d %d",&process[i], &at[i], &bt[i]);
        
        rt[i] = bt[i];
    }

    printf("Enter time slice/ Quantum value: ");
    scanf("%d", &ts);

    printf("\n   PName   |   ArrTime | BurstTime |   Finish  |");
    printf(" TurnAround|  Waiting  |\n");
    //printf("\n\nProcess\t|Turnaround time|waiting time\n\n");

    for (time = 0, i = 0; remain != 0;)
    {
        if (rt[i] <= ts && rt[i] > 0)
        {
            time += rt[i];
            rt[i] = 0;
            flag = 1;
        }
        else if (rt[i] > 0)
        {
            rt[i] -= ts;
            time += ts;
        }
        if (rt[i] == 0 && flag == 1)
        {
            remain--;
            printf("    %d      |     %d     |",process[i],at[i]);
            printf("    %d      |     %d     |",bt[i],time);
            printf("    %d      |     %d     |\n",time - at[i],time - at[i] - bt[i]);
            //printf("P[%d]\t|\t%d\t|\t%d\n", i + 1, time - at[i], time - at[i] - bt[i]);
            sum_wait += time - at[i] - bt[i];
            sum_turnaround += time - at[i];
            flag = 0;
        }
        if (i == n - 1)
            i = 0;
        else if (at[i + 1] <= time)
            i++;
        else
            i = 0;
    }
    printf("\nAverage waiting time = %f\n", sum_wait * 1.0 / n);
    printf("Average turn around time = %f\n", sum_turnaround * 1.0 / n);
    return 0;
}