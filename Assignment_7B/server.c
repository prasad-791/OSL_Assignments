/*
Name: Prasad Sanjay Khalkar
Roll No: 33138
TE-09 L-09
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>

#define MAX_BUFFER 1024

int main(){

    char *shared_memory;
    char data[MAX_BUFFER];

    // Shared memory ID
    int shmdID = shmget((key_t)2345,1024,0666|IPC_CREAT);
    printf("\nKey of shared memory = %d",shmdID);

    // Attaching to the Shared Memory
    shared_memory = (char *)shmat(shmdID,NULL,0);
    printf("\nProcess attached to %p\n",shared_memory);

    printf("Enter some data that is to be written in shared memory\n");
    fgets(data,MAX_BUFFER,stdin);
    // Writing into shared memory
    strcpy(shared_memory,data);
    printf("\nWriting data into shared memory completed\n");
}
