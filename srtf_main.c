#include <stdio.h>
typedef struct
{
    int pid;
    int at;
    int bt;
    int rt;
    int wt;
    int tat;
    int ct;
} Process;



int findShortestProcess(Process p[],int n,int current_time)
{
    int shortest = -1;
    int remaining_time = 99999;

    for(int i=0;i<n;i++){
        if(p[i].at <= current_time && p[i].rt > 0 && p[i].rt < remaining_time){
            shortest = i;
            remaining_time = p[i].rt;
        }
    }

    return shortest;
}

void calculateSRTF(Process p[],int n)
{
    int completed = 0;
    int current_time = 0;

    while(completed < n){
        int shortest = findShortestProcess(p,n,current_time);

        if(shortest == -1){
            current_time++;//no process came
        }else{
            p[shortest].rt--;
            current_time++;

            if(p[shortest].rt == 0){
                completed++;
                p[shortest].ct = current_time;
                p[shortest].tat = p[shortest].ct - p[shortest].at;
                p[shortest].wt = p[shortest].tat - p[shortest].bt;
            }
        }
    }
}

void display(Process p[],int n){
    printf("PID\tAT\tBT\tCT\tWT\tTAT\n");

    float total_waiting_time=0 , total_turnaround_time =0;

    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].wt,p[i].tat);
        total_waiting_time += p[i].wt;
        total_turnaround_time += p[i].tat;
    }

    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround_time / n);
    printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
}


int main(){
    int n;
    printf("Enter number of processes\n");
    scanf("%d",&n);

    Process p[10];

    printf("Enter the process Details\n");
    for(int i =0;i<n;i++){
        printf("Enter the AT BT of the process %d:\n",i+1);
        p[i].pid = i+1;
        scanf("%d%d",&p[i].at,&p[i].bt);
        p[i].rt = p[i].bt;
    }

    calculateSRTF(p,n);
    display(p,n);


    return 0;


}