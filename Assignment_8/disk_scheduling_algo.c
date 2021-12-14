
/*
    Name: Prasad Sanjay Khalkar
    Roll No: 33138
    TE-09 L-09
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}


int SSTF(int noOfRequests,int rwp,int noOfCylinders,int requests[],int headMovementSequence[]){
    int curr_pos = rwp;
    int completed=0;
    int isVisited[noOfRequests];
    for(int i=0;i<noOfRequests;i++){
        isVisited[i] = 0;
    }
    int k=0,noOfHeadMovements = 0;
    int minDist;
    while(completed!=noOfRequests){
        minDist = __INT_MAX__;
        int nextPos = -1;
        
        for(int i=0;i<noOfRequests;i++){
            if(minDist > abs(requests[i]-curr_pos) && isVisited[i]==0){
                nextPos = i;
                minDist = abs(requests[i]-curr_pos);
            }
        }
        noOfHeadMovements += abs(curr_pos - requests[nextPos]);
        curr_pos = requests[nextPos];
        isVisited[nextPos] = 1;
        headMovementSequence[k++] = requests[nextPos];
        completed++;
    }
    return noOfHeadMovements;
}

int SCAN(int noOfRequests,int rwp,int noOfCylinders,int requests[],int headMovementSequence[]){
    int noOfHeadMovements = 0, k=0;
    int temp[noOfRequests];
    for(int i=0;i<noOfRequests;i++){
        temp[i] = requests[i];
    }

    qsort(temp,noOfRequests,sizeof(int),cmpfunc);

    int start_index = -1, curr_index = -1;
    for(int i=0;i<noOfRequests;i++){
        if(temp[i] >= rwp){
            start_index = i;
            curr_index = i;
            break;
        }
    }
    noOfHeadMovements += abs(rwp-temp[start_index]);
    while(curr_index < noOfRequests){
        headMovementSequence[k++] = temp[curr_index];
        if(curr_index+1 < noOfRequests){
            noOfHeadMovements += abs(temp[curr_index]-temp[curr_index+1]);
        }
        curr_index++;
    }
    if(temp[curr_index-1] < noOfCylinders-1){
        noOfHeadMovements += abs(temp[curr_index-1]-(noOfCylinders-1));
    }
    curr_index = start_index-1;
    noOfHeadMovements += abs(temp[curr_index]-(noOfCylinders-1));
    while(curr_index >=0){
        headMovementSequence[k++] = temp[curr_index];
        if(curr_index-1>=0){
            noOfHeadMovements += abs(temp[curr_index]-temp[curr_index-1]);
        }
        curr_index--;
    }
    return noOfHeadMovements;
}

int CLOOK(int noOfRequests,int rwp,int noOfCylinders,int requests[],int headMovementSequence[]){
    int noOfHeadMovements = 0, k=0;
    int temp[noOfRequests];
    for(int i=0;i<noOfRequests;i++){
        temp[i] = requests[i];
    }

    qsort(temp,noOfRequests,sizeof(int),cmpfunc);

    int start_index = -1, curr_index = -1;
    for(int i=0;i<noOfRequests;i++){
        if(temp[i] >= rwp){
            start_index = i;
            curr_index = i;
            break;
        }
    }
    noOfHeadMovements += abs(rwp-temp[start_index]);
    while(curr_index < noOfRequests){
        headMovementSequence[k++] = temp[curr_index];
        if(curr_index+1 < noOfRequests){
            noOfHeadMovements += abs(temp[curr_index]-temp[curr_index+1]);
        }
        curr_index++;
    }
    if(start_index!=0){
        noOfHeadMovements += abs(temp[curr_index-1]-temp[0]);
    }
    curr_index = 0;
    while(curr_index < start_index){
        headMovementSequence[k++] = temp[curr_index];
        if(curr_index+1<start_index){
            noOfHeadMovements += abs(temp[curr_index]-temp[curr_index+1]);
        }
        curr_index++;
    }
    return noOfHeadMovements;
}

void print(int headMovementSequence[],int noOfRequests,int noOfHeadMovements){

    printf("\nThe Head Movement Sequence is as follows\n");
    for(int i=0;i<noOfRequests;i++){
        printf("%d ",headMovementSequence[i]);
    }
    printf("\n");
    printf("\nNo of Head Movements = %d\n",noOfHeadMovements);
}


int main(){
    int noOfRequests,initialReadWriteArmPosition,noOfCylinders;
    printf("\nEnter the no of Requests: ");
    scanf("%d",&noOfRequests);
    int requests[noOfRequests];
    printf("\nEnter the requests\n");
    for(int i=0;i<noOfRequests;i++){
        scanf("%d",&requests[i]);
    }

    printf("\nEnter the initial read write arm position\n");
    scanf("%d",&initialReadWriteArmPosition);

    printf("\nEnter the no of cylinders\n");
    scanf("%d",&noOfCylinders);

    int choice;
    do{
        printf("\nEnter 1 for SSTF\n");
        printf("Enter 2 for SCAN\n");
        printf("Enter 3 for C-LOOK\n");
        printf("Enter 4 to exit\n");

        printf("\nEnter your choice\n");
        scanf("%d",&choice);

        switch(choice){
            case 1:{
                int headMovementSequence[noOfRequests];
                for(int i=0;i<noOfRequests;i++){
                    headMovementSequence[i] = -1;
                }
                int noOfHeadMovements = SSTF(noOfRequests,initialReadWriteArmPosition,noOfCylinders,requests,headMovementSequence);
                print(headMovementSequence,noOfRequests,noOfHeadMovements);
                break;
            }
            case 2:{
                int headMovementSequence[noOfRequests];
                for(int i=0;i<noOfRequests;i++){
                    headMovementSequence[i] = -1;
                }
                int noOfHeadMovements = SCAN(noOfRequests,initialReadWriteArmPosition,noOfCylinders,requests,headMovementSequence);
                print(headMovementSequence,noOfRequests,noOfHeadMovements);
                break;
            }
            case 3:{
                int headMovementSequence[noOfRequests];
                for(int i=0;i<noOfRequests;i++){
                    headMovementSequence[i] = -1;
                }
                int noOfHeadMovements = CLOOK(noOfRequests,initialReadWriteArmPosition,noOfCylinders,requests,headMovementSequence);
                print(headMovementSequence,noOfRequests,noOfHeadMovements);
                break;
            }
            case 4:
                break;
            default:
                printf("\nInvalid Input\n");
        }
    }while(choice!=4);
}

// 82 170 43 140 24 16 190
