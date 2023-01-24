#include <stdio.h>
#include <stdlib.h>


//Shortest job first scheduling
//Criteria Burst Time
//Mode non pre-emptive

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

void findFirstArrival(int at[], int bt[], int p[], int len){
    int first = 0;//index
    int temp;
    for (int i = 1; i < len; i++)
    {
        if (at[first] > at[i])
        {
            first = i;
        }
        
    }

    temp = at[0];
    at[0] = at[first];
    at[first] = temp;

    temp = bt[0];
    bt[0] = bt[first];
    bt[first] = temp;

    temp = p[0];
    p[0] = p[first];
    p[first] = temp;
    
}

void findStartingTime(int at[], int bt[], int st[], int p){
    st[0] = at[0];//minimum arrival time (first arrived scheduled first)

    for (int i = 1; i < p; i++)
    {
        st[i] = -1;
    }
    

    int track = 0;
   
    for (int i = 1; i < p; i++)
    {
       for (int j = 1; j < p; j++)
       {
           if(at[j] > st[track] + bt[track]){
               continue;
           }
           else if (st[j] == -1){
                st[j] = st[track] + bt[track];
                track  = j;
                
                break;
           }
           else{
               continue;
           }
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


//sorting according to burst time
void sortAccordingToBurstTime(int bt[], int p[], int at[], int len){
    int pos, temp;
    for (int i = 1; i < len; i++)
    {
        pos=i;
        for(int j=i+1;j<len;j++)
        {
            if(bt[j]<bt[pos])
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

int main(int argc, char const *argv[])
{
    printf("------------------:Shortest Job First:------------------\n\n");
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

    //check case when same arrival time or burst time 

    for (int i = 0; i < p; i++)
    {
        int pn, ft, bt;
        printf("Enter the process name, arrival time and burst time: ");
        scanf("%d %d %d",&processes[i],&arrival[i],&burst[i]);

    }
    
    findFirstArrival(arrival,burst,processes,p);
    sortAccordingToBurstTime(burst,processes,arrival,p);

    //FOR CHECKING      
    // printArray(processes,p);
    // printArray(arrival,p);
    // printArray(burst,p);
    //printArray(start,p);
    //printArray(finish,p);


    findFirstArrival(arrival,burst,processes,p);
    sortAccordingToBurstTime(burst,processes,arrival,p);
    findStartingTime(arrival,burst,start,p);
    findCompletionTime(start,burst,finish,p);
    findTurnAroundTime(arrival,finish,turnaround,p);
    findWaitingTime(burst,turnaround,waiting,p);

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


// Enter the number of processes you want to print: 5

// Enter the process name, arrival time and burst time: 1 1 4
// Enter the process name, arrival time and burst time: 2 2 5
// Enter the process name, arrival time and burst time: 3 8 1
// Enter the process name, arrival time and burst time: 4 3 2
// Enter the process name, arrival time and burst time: 5 5 8
//    PName   |   ArrTime | BurstTime |    Start  |   Finish  | TurnAround|  Waiting  |
//     1      |     1     |    4      |     1     |     5     |    4      |     0     |
//     3      |     8     |    1      |     12     |     13     |    5      |     4     |
//     4      |     3     |    2      |     5     |     7     |    4      |     2     |
//     2      |     2     |    5      |     7     |     12     |    10      |     5     |
//     5      |     5     |    8      |     13     |     21     |    16      |     8     |
// Average Waiting time: 3.800000
// Average Turn Around time: 7.800000
