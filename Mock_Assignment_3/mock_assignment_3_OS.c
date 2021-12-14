/*
    Name: Prasad Sanjay Khalkar
    Roll No: 33138
    TE-09 L-09
    Problem Statement: Implement the C program for CPU Scheduling Algorithms: Shortest Job First(Preemptive) and Round Robin with different arrival time.
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Process structure
typedef struct Process{
    int no, arrival, burst;
} Process;

// variable for context switches
int context_switches = -1;

// ready queue for round robin
int rq[100];

// comparator for sorting the processes based on arrival time
bool cmp(Process a,Process b){
    return a.arrival < b.arrival;
}

// Shortest Job First algorithms
int shortest_job_first(Process p[],int ct[],int rt[],int n){

    // completed keeps track of the no of processes completed
    int completed = 0,curr_time=0;
    int minremtime = __INT_MAX__;   // used to find minimum remaining time
    bool ispresent = false;     // checks if there is any process available for execution
    int ind=-1,prevind=-1;      

    while(completed!=n){

        // searches for the process whose arrival time is less than the current time and selects that process whose burst time is minimum
        for(int i=0;i<n;i++){
            if(p[i].arrival <= curr_time && p[i].burst < minremtime && p[i].burst!=0){
                ind = i;
                minremtime = p[i].burst;
                ispresent = true;
            }
        }

        // checks if there is any process present for execution if not then simply the curr time is incremented
        if(ispresent==false){
            curr_time++;
            continue;
        }
        // checks if the process gets its first response, if yes the response time is recorded
        if(rt[ind] == -1){
            rt[ind] = curr_time - p[ind].arrival;
        }
        // checks if the same process is continuing exection if not then context swithces is incremented
        if(prevind != ind){
            prevind = ind;
            context_switches++;
        }
        curr_time++;
        p[ind].burst--;
        minremtime = p[ind].burst;
        // if the burst time of a process becomes 0 then it is marked as completed and the completion time is recorded
        if(p[ind].burst == 0){
            completed++;
            ct[ind] = curr_time;
            minremtime = __INT_MAX__;
            ispresent = false;
        }
    }
    return curr_time;       // returning the scheduling length
}

// it is used to shift all the process to the front of the queue
int shiftleft(int size){
    for(int i=0;i<size-1;i++){
        rq[i] = rq[i+1];
    }
    return size-1;  // returns the reduced size
}

// Round Robin Algorithm
int round_robin(Process p[],int ct[],int rt[],int n,int q){
     // completed keeps track of the no of processes completed and the size is the size of the ready queue at the particular instance 
    int curr_time=0,completed=0,ind,size=0;
    int inq[n];     // for storing if the process is already in queue
    // initialising the inq
    for(int i=0;i<n;i++){
        inq[i] = 0;
    }

    // checks if there is any process available for execution
    for(int i=0;i<n;i++){
        if(curr_time>=p[i].arrival && inq[p[i].no]==0){
            rq[size++] = p[i].no;
            inq[p[i].no] = 1;
        }
    }

    while(completed!=n){
        // checks if there is any process then it is executed
        if(size!=0){

            ind = rq[0];
            size = shiftleft(size);     // pops out the top of the queue and continues the execution
            if(rt[ind]==-1){
                rt[ind] = curr_time - p[ind].arrival;
            }
            // if the burst time is more than time quantum
            if(p[ind].burst > q){
                curr_time += q;
                p[ind].burst -= q;
            }else{
                // if not then the process execution is done completely
                curr_time += p[ind].burst;
                p[ind].burst = 0;
                completed++;
                ct[ind] = curr_time;
            }
            // checks if there is any new process available
            for(int i=0;i<n;i++){
                if(curr_time >= p[i].arrival && inq[p[i].no]==0){
                    rq[size++] = p[i].no;
                    inq[p[i].no] = 1;
                }
            }
            // incrementing context switches
            context_switches++;
            if(p[ind].burst!=0){
                // if the process that was executed has not finished its execution completely then it is again pushed back in the ready queue
                rq[size++] = ind;
            }

        }else{
            // if there were no any process then this loop tries to find if there are any after incrementing the current time
            curr_time++;
            for(int i=0;i<n;i++){
                if(curr_time>=p[i].arrival && inq[p[i].no]==0){
                    rq[size++] = p[i].no;
                    inq[p[i].no] = 1;
                }
            }
        }
    }

    return curr_time;       // returning scheduling length

}

// returns the sum of array: used to calculating total turn around time and total waiting time
int sum(int arr[],int n){
    int total = 0;
    for(int i=0;i<n;i++){
        total += arr[i];
    }
    return total;
}

// displays the output in proper format
void print(int arr[],int burs[],int ct[],int tat[],int wt[],int rt[],int n,int sl){

    printf("\n|    Process|   Arrival Time|    Burst Time|    Completion Time|    Turn Around Time|    Waiting Time|    Response Time|\n");
    for(int i=0;i<n;i++){
        printf("|%10d|%15d|%13d|%18d|%19d|%15d|%16d|\n",i+1,arr[i],burs[i],ct[i],tat[i],wt[i],rt[i]);
    }

    printf("\nAverage Turn Around time = %f \n",sum(tat,n)/(float)n);
    printf("\nAverage Waiting time = %f \n",sum(wt,n)/(float)n);
    printf("\nScheduling Length = %d\n",sl);
    printf("\nThroughPut = %d/%d = %f\n",n,sl,(float)n/sl);
    printf("\nNo of Context Switches = %d\n\n",context_switches);
}

int main(){
    int n,tq;   // no of processes and the time quantum variable
    printf("\nEnter the no of Processes\n");
    scanf("%d",&n);
    Process proc[n];    // n processes
    // other required variables
    int arr[n],burst[n],ct[n],wt[n],tat[n],rt[n];
    int scheduling_len,choice;
    memset(rt,-1,sizeof(rt));   // initialising the response time to -1

    printf("\nEnter the arrival and burst time for each process\n");
    int x,y;    
    for(int i=0;i<n;i++){
        scanf("%d%d",&x,&y);    // arrival and burst time are taken as input
        arr[i] = x;
        burst[i] = y;
        proc[i].no =  i;
        proc[i].arrival = x;
        proc[i].burst = y;
    }

    // options for user
    printf("\nEnter 1 for Shortest Job First(Preemptive)\n");
    printf("Enter 2 for Round Robin\n");

    printf("\nEnter your choice\n");
    scanf("%d",&choice);        // choice as input

    switch(choice){
        case 1:
            scheduling_len = shortest_job_first(proc,ct,rt,n);      // SJF
            break;
        case 2:
            printf("\nEnter the time quantum value\n");
            scanf("%d",&tq);
            qsort(proc,n,sizeof(int),cmp);      // Sorting the processes based on arrival time
            scheduling_len = round_robin(proc,ct,rt,n,tq);      // Round Robin
            break;
        default:
            printf("\nEnter valid choice\n");
    }

    // calculating turn around time and waiting time
    for(int i=0;i<n;i++){
        tat[i] = ct[i] - arr[i];
        wt[i] = tat[i] - burst[i];
        wt[i] = wt[i]<=0 ? 0 : wt[i];
    }

    print(arr,burst,ct,tat,wt,rt,n,scheduling_len);

}

/*
SJF
    6 
    0 6
    1 4
    2 1
    3 2
    4 1
    5 3


RR
    6
    0 4
    1 5
    2 6
    3 3
    4 2
    5 4
    2
*/