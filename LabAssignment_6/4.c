//1 & 2. Implementng Multilevel Feedback Queue scheduling


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sw = 0;
int st = 0;

struct process
{
	char name;
	int AT,BT,WT,TAT,RT,CT;

}	Q1[10],Q2[10],Q3[10];

//RT = remaining time


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
		Q1[i].AT = (rand() % (20)) + 1;		
		Q1[i].BT = (rand() % (15)) + 1;		
		Q1[i].RT = Q1[i].BT;
	}
	
	sortByArrivalTime(num);
    
    printf("\nAll the processes with their Arrival and Burst Time: \n");
    printf("\nProcess\t\tAT\t\tBT\t\t\n");
    for (int p = 0; p < num; p++)
    {
        printf("%c\t\t%d\t\t%d\t\t\n",Q1[p].name,Q1[p].AT,Q1[p].BT);
    }
    printf("\n");
    

	Time = Q1[0].AT;
    
    printf("\nProcesses in first queue (RR with TimeQuantum = %d)\n",TQ1);
	printf("\nProcess\t\tST\t\tBT\t\tCT\t\tRT\t\tWT\t\tTAT\t\t");

	for(i = 0 ; i < num ; i++)
	{
		if (Q1[i].AT > Time)
		{
			Time = Q1[i].AT;
		}
		
		if(Q1[i].RT <= TQ1)
  		{
            stc = Time;
	       	Time += Q1[i].RT;
	       	Q1[i].RT = 0;
	       	Q1[i].WT = Time-Q1[i].AT-Q1[i].BT;		
	       	Q1[i].TAT = Time-Q1[i].AT;
            sw += Q1[i].WT;
            st += Q1[i].TAT;
	       	printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d",Q1[i].name,stc,Q1[i].BT,Time,Q1[i].RT,Q1[i].WT,Q1[i].TAT);
	  	}
	  	else			
	  	{
            stc = Time;
            Time += TQ1;
            Q1[i].RT -= TQ1;
            sw += 0;
            st += 0;
            //Q1[i].WT = 0;
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
        printf("\nProcesses in second queue (RR with TimeQuantum = %d)\n",TQ2);
		printf("EXCEPT THOSE PROCESSES WHICH ALREADY COMPLETED IN FIRST QUEUE\n");
	    printf("\nProcess\t\tST\t\tBT\t\tCT\t\tRT\t\tWT\t\tTAT\t\t");

	}
	
	for(i = 0 ; i < k ; i++)
	{
		if (Q2[i].AT > Time)
		{
			Time = Q2[i].AT;
		}

	    if(Q2[i].RT <= TQ2)
	    {
           stc = Time;
	       Time += Q2[i].RT;
	       Q2[i].RT = 0;
	       Q2[i].WT = Time - Q2[i].AT - TQ1 - Q2[i].BT;	
	       Q2[i].TAT = Time - Q2[i].AT;
           sw += Q2[i].WT;
           st += Q2[i].TAT;
	       printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d",Q2[i].name,stc,Q2[i].BT,Time,Q2[i].RT,Q2[i].WT,Q2[i].TAT);
	
	    }
	    else			
	    {
          stc = Time;
	      Q3[r].AT = Q2[i].AT;
	      Time += TQ2;
	      Q2[i].RT -= TQ2;
          sw += 0;
          st += 0;
          //Q2[i].WT = 0;
	      Q3[r].BT = Q2[i].RT;
	      Q3[r].RT = Q3[r].BT;
	      Q3[r].name = Q2[i].name;
	      r++;
	      flag = 2;
          printf("\n%c\t\t%d\t\t%d\t\t--\t\t%d\t\t--\t\t--",Q2[i].name,stc,Q2[i].BT,Q2[i].RT);
	    }
	}
	
	if(flag == 2){
        printf("\n\nProcesses in third queue (FCFS)\n");
		printf("EXCEPT THOSE PROCESSES WHICH ALREADY COMPLETED IN FIRST AND SECOND QUEUE\n");
	    printf("\nProcess\t\tST\t\tBT\t\tCT\t\tRT\t\tWT\t\tTAT\t\t");
    }
		
	for( i = 0 ; i < r ; i++)
	{
		if (Q3[i].AT > Time)
		{
			Time = Q3[i].AT;
		}
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
		sw += Q3[i].WT;
        st += Q3[i].TAT;
	    printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t",Q3[i].name,stc,Q3[i].BT,Time,Q3[i].RT,Q3[i].WT,Q3[i].TAT);
	        
	}

    float awt,att;
    awt = sw/(float)num;
    att = st/(float)num;

    printf("\n\nAverage Waiting Time: %f",awt);
    printf("\nAverage TurnAround Time: %f",att);
	
	printf("\n\n");
	return 0;
}
