// Name: Prasad Sanjay Khalkar
// Roll No; 33138
// TE-09 K-09

#include <stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>

// comparator for qsort
int ascendcmp(const void *a,const void *b){
	return ( *(int *)a - *(int *)b);
}

// print array function
void print(int arr[],int n){
    for(int i=0;i<n;i++)
        printf("%d ",arr[i]);
    printf("\n");
}

int main(int argc,char *argv[]){
    int n;
    printf("Enter the no of integers\n");
    scanf("%d",&n);
    printf("Enter %d integers\n",n);
    int arr[n];
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);
    
    // sorting the array
    qsort(arr,n,sizeof(int),ascendcmp);
    pid_t id = fork();  // calling fork command

    // inside child
    if(id==0){
        printf("\nIn Child Process\n");
        char *newargv[n+2];     // the arguements to be passed
        newargv[0] = argv[1];
        for(int i=0;i<n;i++){
            newargv[i] = (char *)malloc(5*sizeof(char));
            // converting from int to string
            sprintf(newargv[i],"%d",arr[i]);
        }
        newargv[n+1] = NULL;
        char *newenviron[] = {NULL};

        // execve for the second program to run
        if(execve(argv[1],newargv,newenviron)==-1){
            perror("Could not execve\n");
        }

    }else if(id>0){     // In parent process
        printf("\nIn Parent process\n");
        // before the second program
        wait(NULL);
        // after the second program
        printf("\nParent Process Completed\n");
    }
}