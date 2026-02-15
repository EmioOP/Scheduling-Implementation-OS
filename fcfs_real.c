#include <stdio.h>

typedef struct
{
    int pid;
    int at;
    int bt;
    int ct;
    int rt;
    int wt;
    int tat;
} Process;

int firstCome(Process p[], int n, int current_time)
{
    int first = -1;
    int prev_first = 99999;

    for (int i = 0; i < n; i++)
    {
        if (p[i].at <= current_time && p[i].rt > 0 && p[i].at < prev_first)
        {
            first = i;
            prev_first = p[i].at;
        }
    }

    return first;
}

void fcfs(Process p[], int n)
{
    int completed = 0;
    int current_time = 0;

    while (completed < n)
    {
        int first = firstCome(p, n, current_time);
        if (first == -1)
        {
            current_time++;
        }
        else
        {
            p[first].rt = p[first].rt - p[first].bt;//
            current_time += p[first].bt;

            if (p[first].rt == 0)
            {
                completed++;
                p[first].ct = current_time;
                p[first].tat = p[first].ct - p[first].at;
                p[first].wt = p[first].tat - p[first].bt;
            }
        }
    }
}

void display(Process p[], int n)
{
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("Avarage Waiting Time: %2f", total_wt / n);
    printf("Avarage Trunaround Time: %2f", total_tat / n);
}

int main()
{
    int n;
    Process p[10];

    printf("Enter the number of processes: \n");
    scanf("%d", &n);

    printf("Enter the process details");

    for (int i = 0; i < n; i++)
    {
        printf("enter AT,BT of the process %d:", i + 1);
        p[i].pid = i + 1;
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }
    fcfs(p, n);
    display(p, n);

    return 0;
}
