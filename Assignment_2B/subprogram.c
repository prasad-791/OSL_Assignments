#include <stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>

// reversing the array
void reverse(int arr[],int n){
    int i=0,j=n-1;
    while(i<j){
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }
}

int main(int argc,char *argv[]){
    int n = argc;
    int arr[n];
    int ind = 0;
    printf("\nFrom new program\n");
    for(int i=0;i<n;i++){
        // converting into int
        arr[i] = atoi(argv[i]);
        printf("%d ",arr[i]);
    }
    printf("\n");

    reverse(arr,n);     // reverse the array

    printf("After Reversing\n");

    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");

    printf("New program completed\n");
    exit(0);
}