#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct process
{
	char name;
	int AT,BT,WT,TAT,RT,CT;

}	Q1[10],Q2[10],Q3[10];

//RT = remaining time

void printArray(struct process q[], int len){

    for (int i = 0; i < len; i++)
    {
        printf("\nProcess Name = %c \n",q[i].name);
        printf("AT = %d \n",q[i].AT);
        printf("BT = %d \n",q[i].BT);
        printf("WT = %d \n",q[i].WT);
        printf("TAT = %d \n",q[i].TAT);
        printf("RT = %d \n",q[i].RT);
        printf("CT = %d \n",q[i].CT);
        printf("\n");
    }
      
}

float averageWaitingTime(struct process q[], int len){
    float sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum = sum + q[i].WT;
    }
    
    return sum/(float)len;
}


float averageTurnAroundTime(struct process q[], int len){
    float sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum = sum + q[i].TAT;
    }
    
    return sum/(float)len;
}


void sortByArrivalTime(int n)
{
	struct process temp;
	for(int i = 0 ; i < n ; i++)
	{
		for(int j = i + 1 ; j < n ; j++)
		{
			if(Q1[i].AT>Q1[j].AT)
			{
				temp = Q1[i];
				Q1[i] = Q1[j];
				Q1[j] = temp;
			}
		}
	}
}

int main()
{
	int i,j,k = 0,r = 0,Time = 0,TQ1,TQ2,flag = 0;
    int stc = 0;//Start Time Controller
	char c;
    int num;
	printf("Enter the number of processes : ");
	scanf("%d",&num); 
	printf("\nEnter the time quantum values for Q1 and Q2 (RR Scheduling Algorithm): ");
	scanf("%d %d",&TQ1,&TQ2);

	srand(time(0));  							
	for(i = 0 , c = 'A' ; i < num ; i++ , c++ )
	{
		Q1[i].name = c;
		Q1[i].AT = 0; //(rand() % (9)) + 1;		//Random values between 1 to 9
		Q1[i].BT = (rand() % (15)) + 1;		//Random values between 1 to 15
		Q1[i].RT = Q1[i].BT;
	}
	
	sortByArrivalTime(num);
    //printArray(Q1,num);
    
    printf("\nAll the processes with their Arrival and Burst Time: \n");
    printf("\nProcess\t\tAT\t\tBT\t\t\n");
    for (int p = 0; p < num; p++)
    {
        printf("%c\t\t%d\t\t%d\t\t\n",Q1[p].name,Q1[p].AT,Q1[p].BT);
    }
    printf("\n");
    

	Time = Q1[0].AT;
    //stc = Time;
	
	//printf("\nProcess that completed in first queue (RR with TimeQuantum = %d)",TQ1);
    printf("\nProcesses in first queue (RR with TimeQuantum = %d)\n",TQ1);
	printf("\nProcess\t\tST\t\tBT\t\tCT\t\tRT\t\tWT\t\tTAT\t\t");

	for(i = 0 ; i < num ; i++)
	{
		if(Q1[i].RT <= TQ1)
  		{
            stc = Time;
	       	Time += Q1[i].RT;
	       	Q1[i].RT = 0;
	       	Q1[i].WT = Time-Q1[i].AT-Q1[i].BT;		//amount of time process has been waiting in the first queue
	       	Q1[i].TAT = Time-Q1[i].AT;
	       	printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d",Q1[i].name,stc,Q1[i].BT,Time,Q1[i].RT,Q1[i].WT,Q1[i].TAT);
	  	}
	  	else			//process moves to queue 2 
	  	{
            stc = Time;
            //Q2[k].WT = Time; //think
            Time += TQ1;
            Q1[i].RT -= TQ1;
            Q2[k].BT = Q1[i].RT;
            Q2[k].RT = Q2[k].BT;
            Q2[k].AT = Q1[i].AT;
            Q2[k].name = Q1[i].name;
            k++;
            flag = 1;
            printf("\n%c\t\t%d\t\t%d\t\t--\t\t%d\t\t--\t\t--",Q1[i].name,stc,Q1[i].BT,Q1[i].RT);
        }
	}

    printf("\n\n");
	
	if(flag == 1)
	{
		// printf("\n\nProcess that completed in second queue (RR with TQ = %d)",TQ2);
	  	// printf("\nProcess\t\tST\t\tBT\t\tRT\t\tWT\t\tTAT\t\t\n");
        printf("\nProcesses in second queue (RR with TimeQuantum = %d)\n",TQ2);
	    printf("\nProcess\t\tST\t\tBT\t\tCT\t\tRT\t\tWT\t\tTAT\t\t");

	}
	
	for(i = 0 ; i < k ; i++)
	{
	    if(Q2[i].RT <= TQ2)
	    {
           stc = Time;
	       Time += Q2[i].RT;
	       Q2[i].RT = 0;
	       Q2[i].WT = Time - Q2[i].AT - TQ1 - Q2[i].BT;	//amount of time process has been waiting in the ready queue
	       Q2[i].TAT = Time - Q2[i].AT;
	       printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d",Q2[i].name,stc,Q2[i].BT,Time,Q2[i].RT,Q2[i].WT,Q2[i].TAT);
	
	    }
	    else			//process moves to queue 3 with FCFS
	    {
          stc = Time;
	      Q3[r].AT = Q2[i].AT;
	      Time += TQ2;
	      Q2[i].RT -= TQ2;
	      Q3[r].BT = Q2[i].RT;
	      Q3[r].RT = Q3[r].BT;
	      Q3[r].name = Q2[i].name;
	      r++;
	      flag = 2;
          printf("\n%c\t\t%d\t\t%d\t\t--\t\t%d\t\t--\t\t--",Q2[i].name,stc,Q2[i].BT,Q2[i].RT);
	    }
	}
	
    //printf("\nProcess\t\tST\t\tRT\t\tWT\t\tTAT\t\t\n");
	if(flag == 2){
        printf("\n\nProcesses in third queue (FCFS)\n");
	    printf("\nProcess\t\tST\t\tBT\t\tCT\t\tRT\t\tWT\t\tTAT\t\t");
    }
		//printf("\n\nProcess that completed in third queue (FCFS) ");
		
	for( i = 0 ; i < r ; i++)
	{
        stc = Time;
	    if(i == 0){
            
            Q3[i].CT = Q3[i].BT + Time;
            Time = Q3[i].CT;
        }
	        
	    else{
            Q3[i].CT = Q3[i-1].CT+Q3[i].BT;
            Time = Q3[i].CT;
        }
        Q3[i].RT = 0;
        Q3[i].TAT = Q3[i].CT - Q3[i].AT;
	    Q3[i].WT = Q3[i].TAT - Q3[i].BT -TQ1 -TQ2;
	    printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t",Q3[i].name,stc,Q3[i].BT,Time,Q3[i].RT,Q3[i].WT,Q3[i].TAT);
	        
	}
	
	// for( i = 0 ; i < r ; i++)
	// {
	//     Q3[i].TAT = Q3[i].CT;
	//     Q3[i].WT = Q3[i].TAT-Q3[i].BT;
	//     printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t",Q3[i].name,Q3[i].AT,Q3[i].BT,Q3[i].WT,Q3[i].TAT);
	// }
	
	printf("\n\n");
	return 0;
}
