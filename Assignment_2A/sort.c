// Name: Prasad Sanjay Khalkar
// Roll No; 33138
// TE-09 K-09

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>

// array and no of elements
int *arr,n;

// printing array
void printarr(){
	for(int i=0;i<n;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}

// comparator for sorting array in ascending order;
int ascendcmp(const void *a,const void *b){
	return ( *(int *)a - *(int *)b);
}

// comparator for sorting array in descending order;
int descendcmp(const void *a,const void *b){
	return (-1)*( *(int *)a - *(int *)b);
}

// sort arr function
void forkexe(){
	pid_t id = fork();
	if(id==0){
		// child process
		printf("\nInside child process\n");
		
		// sorting in ascending order
		qsort(arr,n,sizeof(int),ascendcmp);
		printf("Printing the array in child process after sorting in ascending order\n");
		printarr();
		printf("Bye from child :)\n\n");
		// child process executed
	}else if(id>0){
		printf("\nInside parent process\n");
		wait(NULL);
		
		// sorting in descending order
		qsort(arr,n,sizeof(int),descendcmp);
		printf("Printing the array in parent process after sorting in descending order\n");
		printarr();
		printf("Bye from parent :)\n\n");
		// parent process executed;
	}
}

void orphan(){
	pid_t id = fork();
	if(id==0){
		
		sleep(5);

		printf("\nChild has become orphan(pid,ppid): %d, %d\n\n",getpid(),getppid());

		printf("Bye from child :)\n");
		exit(0);
		// child process executed
	}else if(id>0){
		printf("\nInside parent process: %d\n",getpid());
		
		printf("Bye from parent :)\n\n");
		// parent process executed;
	}
}

void zombie(){
	pid_t id = fork();
	if(id==0){
		// child process
		printf("\nInside child process\n");
		printf("Childs ID %d\n",getpid());
		printf("Inside Child, Parents ID %d\n",getppid());

		printf("Bye from child :)");
		printf("\nZombie state\n");
		// child process executed
	}else if(id>0){
		printf("\nInside parent process with id %d\n",getpid());
		printf("Parent sleeping\n");

		sleep(10);
		printf("Bye from parent :)\n\n");
		// parent process executed;
	}
}

int main(){
	// taking no of elements from user
	printf("Enter the no of elements in the array\n");
	scanf("%d",&n);

	printf("Enter %d integers\n",n);
	
	arr = (int *)malloc(n*sizeof(int));
	
	// reading array
	for(int i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	int choice;
	printf("\nEnter 1 to execute the fork and wait process\nEnter 2 to execute the orphan process\nEnter 3 to execute the zombie process\n");
	printf("\nEnter your choice\n");
	// taking the choice as input
	scanf("%d",&choice);

	switch(choice){
		case 1:
			forkexe();
		break;
		case 2:
			orphan();
		break;
		case 3:
			zombie();
		break;
	}
	free(arr);
}
