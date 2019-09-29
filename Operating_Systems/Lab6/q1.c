#include <stdio.h>
#include <stdlib.h>

void display(int arrival[], int BURST[], int final_time[], int temp)
{
    printf("\n");
    for(int i = 0; i < temp; i++)
    {
        printf("Process: %d\tArrival Time: %d\tBurst Time: %d\tFinal Time: %d\t\n", (i+1), arrival[i], BURST[i], final_time[i]);
    }
}
int main()
{
    int process[10];
    int burst_time[10];
    int BURST[10];
    int final_time[10];
    int arrival[10];
    int i = 0, j = 0, k = 0;
    int t = 0;
    int n;
    int num_of_proc = 0;
    int temp = 0;
    printf("Enter the time at which the last process arrives: ");
    scanf("%d", &n);
    while(t <= n)
    {
        printf("t = %d\nDo you have a process that gets added at this time ?: (Y/N)", t);
        char c;
        scanf("%c", &c);
        scanf("%c", &c);
        if(c == 'Y')
        {
            printf("Enter the burst time: ");
            scanf("%d", &burst_time[temp]);
            BURST[temp] = burst_time[temp];
            arrival[temp++] = t;
        }
        
        if(burst_time[i])
            burst_time[i] -= 1;
        if(burst_time[i] == 0)
        {
            final_time[i] = t;
            i++;
        }
        t++;
    }
    while(i < temp)
    {
        while(burst_time[i])
        {
            burst_time[i] -= 1;
            t++;
        }
        final_time[i++] = t;
    }
    i = 0;
    float tat[10] = {0.0};
    float wt[10] = {0.0};
    printf("Number of Processes: %d\n", temp);
    display(arrival, BURST, final_time, temp);
    for(i = 0; i < temp; i++)
    {
        tat[i] = (float)(final_time[i] - arrival[i]);
        wt[i] = tat[i] - (float)(BURST[i]);
    }
    float a_tat = 0;
    float a_wt = 0;
    for(i = 0; i < temp; i++)
    {
        a_tat += tat[i];
        a_wt += wt[i];
    }

    printf("Average TAT = %f\n", (a_tat/4.0));
    printf("Average WT = %f\n", (a_wt/4.0));
}