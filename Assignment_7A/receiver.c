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
    sleep(10);
    int fileDescriptor1,fileDescriptor2 ;
    char *fifo1 = "FIFO1";
    char *fifo2 = "FIFO2",ch;
    char data[MAX_BUFFER];

    printf("\nReading Sentences from pipe1\n");
    fileDescriptor1 = open(fifo1,O_RDONLY);
    read(fileDescriptor1,data,MAX_BUFFER);
    printf("Data is: \n%s \n",data);

    int i=0;
    int countChars=0,countLines=0,countSpaces=0;
    while(data[i]!='\0'){
        if(data[i]==' '){
            countSpaces++;
        }else if(data[i]=='\n'){
            countLines++;
        }else{
            countChars++;
        }
        i++;
    }
    int totalWords = countSpaces+countLines;
    close(fileDescriptor1);

    printf("\nWriting the contents in file info.txt\n");
    FILE* filePointer;
    filePointer = fopen("info.txt","w");
    fprintf(filePointer,"Number of Characters = %d\n",countChars);
    fprintf(filePointer,"Number of Spaces = %d\n",countSpaces);
    fprintf(filePointer,"Number of Words = %d\n",totalWords);
    fprintf(filePointer,"Number of Lines = %d\n",countLines);
    fclose(filePointer);

    filePointer = fopen("info.txt","r");
    ch = fgetc(filePointer);
    i=0;
    while(ch != EOF){
        data[i++] = ch;
        ch = fgetc(filePointer);
    }
    data[i] = '\0';
    fclose(filePointer);

    printf("\nWriting the contents of file info.txt into pipe2\n");
    fileDescriptor2 = open(fifo2,O_WRONLY);
    write(fileDescriptor2,data,strlen(data)+1);
    close(fileDescriptor2);
    printf("\nWriting Completed\n");
}
