//3. Priority Scheduling

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int main()
{
    int bt[20],p[20],wt[20],tat[20],pr[20],i,j,n,total=0,pos,temp;
    float avg_wt,avg_tat;
    printf("\nEnter Total Number of Process : ");
    scanf("%d",&n);
 	
 	srand(time(0));
    printf("\nBurst Time and Priority:  \n");
    for(i = 0 ; i < n ; i++)
    {
        printf("\nP[%d]:\t",i+1);
        bt[i] = (rand() % (10));		//Random values between 0 to 9
        printf("Burst Time: %d, ",bt[i]);
        
        pr[i] = i + 1;			//Random values between 1 to n
        printf("Priority: %d",pr[i]);
        p[i] = i + 1;           
    }
 
    //sorting burst time, priority and process number in ascending order using selection sort
    for(i = 0 ; i < n ; i++)
    {
        pos = i;
        for(j= i + 1 ; j < n ; j++)
        {
            if(pr[j] < pr[pos])
                pos = j;
        }
 
        temp = pr[i];
        pr[i] = pr[pos];
        pr[pos] = temp;
 
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;
 
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }
 
    wt[0] = 0; 
 
    //calculate waiting time
    for(i = 1 ; i < n ; i++)
    {
        wt[i] = 0;
        for(j = 0 ; j < i ; j++)
            wt[i] += bt[j];
 
        total += wt[i];
    }
 
    avg_wt = total/(float)n;     
    total = 0;
 
    printf("\n\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for(i = 0 ; i < n ; i++)
    {
        tat[i] = bt[i] + wt[i];   
        total += tat[i];
        printf("\nP[%d]\t\t  %d\t\t    %d\t\t\t%d",p[i],bt[i],wt[i],tat[i]);
    }
 
    avg_tat = total/(float)n;     
    printf("\n\nAverage Waiting Time = %f",avg_wt);
    printf("\nAverage Turnaround Time = %f\n\n",avg_tat);
 
	return 0;
}
