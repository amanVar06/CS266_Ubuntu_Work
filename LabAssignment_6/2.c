
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct process 
{
	char name;
	int at, bt, ct, wt, tt;
	int completed;
	float ntt;
} p[10];

int n;

void sortByArrival()
{
	struct process temp;
	int i, j;

	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {

			if (p[i].at > p[j].at) {

				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
}

void main()
{
	int i, j, t, sum_bt = 0;
	char c;
	float avgwt = 0, avgtt = 0;
	n = 5;
	srand(time(0));

	int arriv[n];
	for(int i = 0 ; i < n ; i++)
	{
		arriv[i] = rand() % (21);   		//Random values between 0 to 20
	}

	int burst[n];
	for(int i = 0 ; i < n ; i++)
	{
		burst[i] = (rand() % (21)) + 1;		//Random values between 1 to 20
	}

	for (i = 0, c = 'A'; i < n; i++, c++) {
		p[i].name = c;
		p[i].at = arriv[i];
		p[i].bt = burst[i];

		p[i].completed = 0;

		sum_bt += p[i].bt;
	}

	sortByArrival();
	printf("\nName\tArrival Time\tBurst Time\tWaiting Time");
	printf("\tTurnAround Time\t Normalized TT");
	for (t = p[0].at; t < sum_bt;) {

		// Set lower limit to response ratio
		float hrr = -9999;

		float temp;

		int loc;
		for (i = 0; i < n; i++) {

			if (p[i].at <= t && p[i].completed != 1) {

				temp = (p[i].bt + (t - p[i].at)) / p[i].bt;

				if (hrr < temp) {

					// Storing Response Ratio
					hrr = temp;

					// Storing Location
					loc = i;
				}
			}
		}

		t += p[loc].bt;

		p[loc].wt = t - p[loc].at - p[loc].bt;

		p[loc].tt = t - p[loc].at;

		avgtt += p[loc].tt;

		p[loc].ntt = ((float)p[loc].tt / p[loc].bt);

		p[loc].completed = 1;

		avgwt += p[loc].wt;
		printf("\n%c\t\t%d\t\t", p[loc].name, p[loc].at);
		printf("%d\t\t%d\t\t", p[loc].bt, p[loc].wt);
		printf("%d\t\t%f", p[loc].tt, p[loc].ntt);
	}
	printf("\nAverage waiting time:%f\n", avgwt / n);
	printf("Average Turn Around time:%f\n", avgtt / n);
}

