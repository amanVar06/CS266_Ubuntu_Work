#include<stdio.h> 
#include<stdlib.h> 
void show (int job[4][5],int jobs); 
int max_time (int job[4][5],int jobs); 
int check (int job[4][5],int jobs); 
int main () 
{ 
 system("clear"); 
 int i=0,jobs=0; 
 printf("Enter the number of processes you want to compute : "); 
 scanf("%d",&jobs); 
 int job[jobs][5]; 
 for (i=0;i<jobs;i++) 
 { 
 printf("Enter the burst time for Job %d : ",i); 
 scanf("%d",&job[i][1]); 
 printf("Enter the arrival time for Job %d : ",i); 
 scanf("%d",&job[i][0]); 
 job[i][2]=job[i][1]; 
 //job[i][0]=i; 
 job[i][3]=0; 
 job[i][4]=0; 
 } 
 printf("\n\nTable Before Execution \n"); 
 show(job,jobs); 
 printf("\n\nMax time taken will be : %d\n\n",max_time(job,jobs)); 
 int time=0,comptime=0,c=0,tq=3,avgtat=0; 
 while (check(job,jobs)) 
 {  
 l: 
 if (c==jobs) 
 c=0; 
 if (job[c][0]<=time && job[c][2]!=0) 
 { 
 if (job[c][2]>tq) 
 { 
 job[c][2]=job[c][2]-tq; 
 time+=tq; 
 c++; 
 goto l; 
 } 
 if (job[c][2]<=tq) 
 { 
 time=time+job[c][2]; 
 job[c][2]=0; 
 job[c][3]=time; 
 job[c][4]=job[c][3]-job[c][0]; 
 c++; 
 } 
 } 
 else 
 c++; 
 //show (job,jobs); 
 } 
 printf("\n\nTable After Execution \n"); 
 show (job,jobs); 
 for (i=0;i<jobs;i++) 
 { 
 avgtat=avgtat+job[i][4]; 
 } 
 printf("\nAverage turn around time : %d\n",avgtat=avgtat/jobs); 
 printf("\n"); 
 return 0; 
} 
void show (int job[4][5],int jobs) 
{ 
 int i; 
 printf("\n----------------------------------------------------------------------------------------\n"); 
 printf("Name\tArrival time\tBurst time\tTime remaining\tComplete At time\tTAT\n"); 
 printf("----------------------------------------------------------------------------------------\n"); 
 for(i=0;i<jobs;i++) 
 { 
 printf(" P%d\t %d\t\t %d\t\t %d\t\t %d\t\t\t%d\n",i,job[i][0],job[i][1],job[i][2],job[i][3],job[i][4]); 
 } 
} 
int max_time (int job[4][5],int jobs) 
{ 
 int i=0,t=0; 
 for (;i<jobs;i++) 
 t=t+job[i][1]; 
 return t; 
} 
int check (int job[4][5],int jobs) 
{ 
 int i =0; 
 for (i=0;i<jobs;i++) 
 { 
 if (job[i][2]!=0) 
 return 1; 
 } 
 return 0; 
} 