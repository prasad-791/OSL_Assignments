// Prasad Sanjay Khalkar
// 33138 TE-09 L-09

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


int main(){
    int n,r;
    printf("\nEnter the no of processes and no of resources\n");
    scanf("%d%d",&n,&r);        // no of processes and no of resources

    int allocated[n][r],max_req[n][r],available[r],need[n][r];      // allocated max_req available and need matrix
    bool isExecuted[n];     // to check if all processes are executed or not

    printf("\nEnter the no of resources already allocated to the processes\n");
    for(int i=0;i<n;i++){
        isExecuted[i] = false;      // initially isExecuted for each process is false
        printf("\nEnter for Process %d : ",i+1);
        for(int j=0;j<r;j++){
            scanf("%d",&allocated[i][j]);   // initial allocated resources for each process
        }
    }

    printf("\nEnter the max no of resources required by each process\n");
    for(int i=0;i<n;i++){
        printf("\nEnter for Process %d : ",i+1);
        for(int j=0;j<r;j++){
            scanf("%d",&max_req[i][j]);     // max resources required for each process
            need[i][j] = max_req[i][j] - allocated[i][j];       // the need for each process 
        }
    }

    printf("\nEnter the available instances for each resources\n");
    for(int i=0;i<r;i++){
        printf("\nEnter for Resource %d : ",i+1);
        scanf("%d",&available[i]);      // available instances of resources
    }

    int seq[n],completed=0,k=0;     // seq array to store the safe sequence
    bool isSafe = true;

    // if all the process are not yet executed and the state is safe then continue the algorithm
    while(completed!=n && isSafe){
        bool isPresent = false;     // checks if there is any resource present whose need<=available

        for(int i=0;i<n;i++){
            if(!isExecuted[i]){
                // if process is not executed
                int j;
                for(j=0;j<r && need[i][j]<=available[j];j++);   // checks if need for each resource is less than or equal to the available instance of the resource
                if(j==r){
                    // this condition states that the need<= available and hence the process is executed

                    isPresent = true;   
                    seq[k++] = i+1;     // storing the index in the sequence
                    // after execution the resources that this particular process was holding have become free and can be used by others
                    // so the available instance of each resources is changed or incremented
                    for(int x=0;x<r;x++){
                        available[x] += allocated[i][x];
                    }
                    completed++;    // the process is executed
                    isExecuted[i] = true;  
                }
            }
        }
        if(!isPresent){
            // if there is no any resource present whose need<=available then it is unsafe state
            printf("\nIt is in Unsafe State\n");
            isSafe = false;     // terminating the loop
        }
    }
    if(isSafe){
        // if the loop is terminated and it is still in safe state hence it shows that all the processes are executed
        printf("\nProcesses |  Allocated | MaxRequired|    Need    |\n");
        for(int i=0;i<n;i++){
            printf("\n    P%d    |",(i+1));
            for(int j=0;j<r;j++){
                printf(" %3d",allocated[i][j]);
            }
            printf("|");
            for(int j=0;j<r;j++){
                printf(" %3d",max_req[i][j]);
            }
            printf("|");
            for(int j=0;j<r;j++){
                printf(" %3d",need[i][j]);
            }
            printf("|\n");
        }
        printf("\nThe Sequence is as follows\n");
        printf("P%d",seq[0]);
        for(int i=1;i<n;i++){
            printf(" -> P%d",seq[i]);
        }       
        printf("\n");
    }
}
