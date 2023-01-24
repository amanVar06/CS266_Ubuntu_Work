#include <stdio.h>
#include <stdlib.h>


//RR scheduling with quantum = 5
void printArray(int arr[], int len){

    for (int i = 0; i < len; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    
}

float average(int arr[], int len){
    float sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum = sum + arr[i];
    }
    
    return sum/(float)len;
}

int main(int argc, char const *argv[])
{
    int p;
    int quantum = 5;
    printf("Enter the number of processes you want to print: ");
    scanf("%d",&p);
    printf("\n");

    int processes[p];
    int arrival[p];
    int burst[p];
    int start[p];
    int finish[p];
    int turnaround[p];
    int waiting[p];

    for (int i = 0; i < p; i++)
    {
        int pn, ft, bt;
        printf("Enter the process name, arrival time and burst time: ");
        scanf("%d %d %d",&processes[i],&arrival[i],&burst[i]);

    }

    //FOR CHECKING      
    // printArray(processes,p);
    // printArray(arrival,p);
    // printArray(burst,p);

    printf("   PName   |   ArrTime | BurstTime |    Start  |   Finish  |");
    printf(" TurnAround|  Waiting  |\n");

    for (int i = 0; i < p; i++)
    {
        printf("    %d      |     %d     |",processes[i],arrival[i]);
        printf("    %d      |     %d     |     %d     |",burst[i],start[i],finish[i]);
        printf("    %d      |     %d     |\n",turnaround[i],waiting[i]);
    }


    printf("Average Waiting time: %f\n",average(waiting,p));
    printf("Average Turn Around time: %f\n",average(turnaround,p));
    


    
    return 0;
}
