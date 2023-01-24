#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//FCFS scheduling
//Criteria Arrival time
//Mode Non pre-emptive

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

//sort arrival time and burst and process
void sortAccordingToArrivalTime(int at[], int bt[], int p[], int len){
    int pos, temp;
    for (int i = 0; i < len; i++)
    {
        pos=i;
        for(int j=i+1;j<len;j++)
        {
            if(at[j]<at[pos])
                pos=j;
        }
  
        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;
  
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;

        temp=at[i];
        at[i]=at[pos];
        at[pos]=temp;
    }
}


void findStartingTime(int at[], int bt[], int st[], int p){
    st[0] = at[0];//minimum arrival time
    for (int i = 1; i < p; i++)
    {
        if(at[i] > st[i -1] + bt[i-1]){
            st[i] = at[i];
        }
        else{
            st[i] = st[i -1] + bt[i-1];
        }
        
    }
    
}

void findCompletionTime(int st[], int bt[], int ct[], int p){
    
    ct[0] = st[0] + bt[0];
    
    for (int i = 1; i < p; i++)
    {
        ct[i] = st[i] + bt[i];
    }
    
}

void findTurnAroundTime(int ar[], int ct[], int ta[], int p){
    for (int i = 0; i < p; i++)
    {
        ta[i] = ct[i] -  ar[i];
    }
    
}


void findWaitingTime(int bt[], int ta[], int wt[], int p){
    for (int i = 0; i < p; i++)
    {
        wt[i] = ta[i] - bt[i];
    }
    

}

int main(int argc, char const *argv[])
{

    printf("------------------:First Come First Serve:------------------\n\n");
    int p;
    printf("Enter the number of processes: ");
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

    sortAccordingToArrivalTime(arrival,burst,processes,p);
    findStartingTime(arrival,burst,start,p);
    findCompletionTime(start,burst,finish,p);
    findTurnAroundTime(arrival,finish,turnaround,p);
    findWaitingTime(burst,turnaround,waiting,p);

    //FOR CHECKING      
    // printArray(processes,p);
    // printArray(arrival,p);
    // printArray(burst,p);
    // printArray(start,p);
    // printArray(finish,p);

    //check case when same arrival time

    printf("\n");
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


// Enter the number of processes you want to print: 4

// Enter the process name, arrival time and burst time: 1 2 4
// Enter the process name, arrival time and burst time: 2 0 3
// Enter the process name, arrival time and burst time: 3 1 1
// Enter the process name, arrival time and burst time: 4 2 2

//    PName   |   ArrTime | BurstTime |    Start  |   Finish  | TurnAround|  Waiting  |
//     2      |     0     |    3      |     0     |     3     |    3      |     0     |
//     3      |     1     |    1      |     3     |     4     |    3      |     2     |
//     1      |     2     |    4      |     4     |     8     |    6      |     2     |
//     4      |     2     |    2      |     8     |     10     |    8      |     6     |
// Average Waiting time: 2.500000
// Average Turn Around time: 5.000000


// Enter the number of processes you want to print: 4

// Enter the process name, arrival time and burst time: 1 0 2
// Enter the process name, arrival time and burst time: 2 4 3
// Enter the process name, arrival time and burst time: 3 0 1
// Enter the process name, arrival time and burst time: 4 9 4

//    PName   |   ArrTime | BurstTime |    Start  |   Finish  | TurnAround|  Waiting  |
//     1      |     0     |    2      |     0     |     2     |    2      |     0     |
//     3      |     0     |    1      |     2     |     3     |    3      |     2     |
//     2      |     4     |    3      |     4     |     7     |    3      |     0     |
//     4      |     9     |    4      |     9     |     13     |    4      |     0     |
// Average Waiting time: 0.500000
// Average Turn Around time: 3.000000
