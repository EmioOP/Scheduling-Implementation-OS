#include <stdio.h>

typedef struct
{
    int pid;
    int at;
    int bt;
    int ct;
    int pr;
    int rt;
    int wt;
    int tat;
} Process;

int findHighestPriority(Process p[], int n, int current_time)
{
    int highest = -1;
    int prev_priority = 99999;

    for (int i = 0; i < n; i++)
    {
        if (p[i].at <= current_time && p[i].rt > 0 && p[i].pr < prev_priority)
        {
            highest = i;
            prev_priority = p[i].pr;
        }
    }

    return highest;
}

void priority(Process p[], int n)
{
    int current_time = 0;
    int completed = 0;

    while (completed < n)
    {
        int shortest = findHighestPriority(p,n,current_time);

        if (shortest == -1)
        {
            current_time++;
        }
        else
        {
            p[shortest].rt--;
            current_time++;

            if (p[shortest].rt == 0)
            {
                completed++;
                p[shortest].ct = current_time;
                p[shortest].tat = p[shortest].ct - p[shortest].at;
                p[shortest].wt = p[shortest].tat - p[shortest].bt;
            }
        }
    }
}

void display(Process p[], int n)
{
    float total_wt = 0, total_tat = 0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("Avarage Waiting Time: %2f",total_wt/n);
    printf("Avarage Turnaround Time: %2f",total_tat/n);

}

int main(){
    int n;
    printf("Enter number of processes\n");
    scanf("%d",&n);

    Process p[10];

    printf("Enter the process Details\n");
    for(int i =0;i<n;i++){
        printf("Enter the AT BT and Priority of the process %d:\n",i+1);
        p[i].pid = i+1;
        scanf("%d%d%d",&p[i].at,&p[i].bt,&p[i].pr);
        p[i].rt = p[i].bt;
    }

    priority(p,n);
    display(p,n);


    return 0;


}