/*
Name: Prasad Sanjay Khalkar
Roll No: 33138
TE-09 L-09
*/

#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MAX_BUFFER 1024

int main(){
    int fileDescriptor1,fileDescriptor2 ;
    char *fifo1 = "FIFO1";
    char *fifo2 = "FIFO2",ch;

    char tempData[MAX_BUFFER] = 
        "This is Prasad Khalkar\nThis is OS\nHello World\nPICT";


    mkfifo(fifo1,0666);
    mkfifo(fifo2,0666);

    printf("\nEnter the sentences\nEnter # to exit\n");
    char data[MAX_BUFFER];
    int i = 0;
    char temp[MAX_BUFFER];
    while(1){
        fgets(temp,MAX_BUFFER,stdin);
        if(temp[0]=='#'){
            break;
        }
        for(int j=0;j<strlen(temp);j++){
            data[i++] = temp[j];
        }
    }
    data[i] = '\0';
    printf("\nWriting sentences in pipe1 completed\n");
    fileDescriptor1 = open(fifo1,O_WRONLY);
    write(fileDescriptor1,data,strlen(data)+1);
    close(fileDescriptor1);

    printf("\nReading the contents from pipe2");
    fileDescriptor2 = open(fifo2,O_RDONLY);
    read(fileDescriptor2,data,sizeof(data));
    printf("\nThe Data is as follows:\n");
    printf("%s",data);
    close(fileDescriptor2);
}