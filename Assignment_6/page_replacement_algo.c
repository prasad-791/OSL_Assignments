// Prasad Sanjay Khalkar
// 33138 TE-09 L-09

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// isHit array for storing the whether each page has page fault or page miss
int *isHit;
int noOfPageFrames, noOfReferences;


// first in first out algorithm
void fifo(int pageFrame[noOfPageFrames][noOfReferences], int *pageRefString)
{
    int pageFrameIndex = noOfPageFrames - 1;
    int i = 1;
    pageFrame[pageFrameIndex][0] = pageRefString[0];
    pageFrameIndex--;
    while (i < noOfReferences){
        for (int j = 0; j < noOfPageFrames; j++){
            pageFrame[j][i] = pageFrame[j][i - 1];
        }

        for (int j = 0; j < noOfPageFrames; j++){
            if (pageFrame[j][i] == pageRefString[i]){
                isHit[i] = 1;
                break;
            }
        }

        if (isHit[i] == 0){
            pageFrame[pageFrameIndex][i] = pageRefString[i];
            if (pageFrameIndex == 0){
                pageFrameIndex = noOfPageFrames - 1;
            }
            else{
                pageFrameIndex--;
            }
        }
        i++;
    }
}

// least recently used algorithm
void leastRecentlyUsedPageReplacement(int pageFrame[noOfPageFrames][noOfReferences],int *pageRefString){
    int i=1;
    pageFrame[noOfPageFrames-1][0] = pageRefString[0];
    for(int j=noOfPageFrames-2;j>=0;j--){
        for(int k=0;k<noOfPageFrames;k++){
            pageFrame[k][i] = pageFrame[k][i-1];
        }
        pageFrame[j][i] = pageRefString[i];
        i++; 
    }   
    while(i<noOfReferences){
        for(int j=0;j<noOfPageFrames;j++){
            pageFrame[j][i] = pageFrame[j][i-1];
        }
        for (int j = 0; j < noOfPageFrames; j++){
            if (pageFrame[j][i] == pageRefString[i]){
                isHit[i] = 1;
                break;
            }
        }

        if(isHit[i] == 0){
            int isPresent[noOfPageFrames];
            memset(isPresent,0,sizeof(isPresent));
            int count=0,k=i-1;
            for(;k>=0 && count!=noOfPageFrames-1;k--){
                for(int j=0;j<noOfPageFrames && count!=noOfPageFrames-1;j++){
                    if(pageFrame[j][i] == pageRefString[k] && isPresent[j]==0){
                        isPresent[j] = 1;
                        count++;
                    }
                }
            }
            int j;
            for(j=0;j<noOfPageFrames && isPresent[j]==1;j++);
            pageFrame[j][i] = pageRefString[i];
        }
        i++;
    }
}

// optimal page replacement algorithm
void optimalPageReplacement(int pageFrame[noOfPageFrames][noOfReferences],int *pageRefString){
    int i=1;
    pageFrame[noOfPageFrames-1][0] = pageRefString[0];
    for(int j=noOfPageFrames-2;j>=0;j--){
        for(int k=0;k<noOfPageFrames;k++){
            pageFrame[k][i] = pageFrame[k][i-1];
        }
        pageFrame[j][i] = pageRefString[i];
        i++; 
    }   
    while(i<noOfReferences){
        for(int j=0;j<noOfPageFrames;j++){
            pageFrame[j][i] = pageFrame[j][i-1];
        }
        for (int j = 0; j < noOfPageFrames; j++){
            if (pageFrame[j][i] == pageRefString[i]){
                isHit[i] = 1;
                break;
            }
        }

        if(isHit[i] == 0){
            int isPresent[noOfPageFrames];
            memset(isPresent,0,sizeof(isPresent));
            int count=0,k=i+1;
            for(;k<noOfReferences && count!=noOfPageFrames-1;k++){
                for(int j=0;j<noOfPageFrames && count!=noOfPageFrames-1;j++){
                    if(pageFrame[j][i] == pageRefString[k] && isPresent[j]==0){
                        isPresent[j] = 1;
                        count++;
                    }
                }
            }
            int j;
            for(j=0;j<noOfPageFrames && isPresent[j]==1;j++);
            pageFrame[j][i] = pageRefString[i];
        }
        i++;
    }

}

void print(int pageFrame[noOfPageFrames][noOfReferences],int *pageRefString)
{
    int totalFault = 0, totalHit = 0,noOfLines=0;
    printf("\n");
    printf("    ");
    for (int i = 0; i < noOfReferences; i++){
        noOfLines += printf("%5d |", pageRefString[i]);
    }
    printf("\n");
    noOfLines+=4;
    for(int i=0;i<noOfLines;i++){
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < noOfPageFrames; i++)
    {
        printf("F%d |", noOfPageFrames - i);
        for (int j = 0; j < noOfReferences; j++)
        {
            if (pageFrame[i][j] == -1)
            {
                printf("      |");
            }
            else
            {
                printf("%5d |", pageFrame[i][j]);
            }
        }
        printf("\n");
    }
    for(int i=0;i<noOfLines;i++){
        printf("-");
    }
    printf("\n");
    printf("    ");
    for (int i = 0; i < noOfReferences; i++)
    {
        if (isHit[i] == 0)
        {
            totalFault++;
            printf(" Fault|");
        }
        else
        {
            totalHit++;
            printf("   Hit|");
        }
    }
    printf("\n\n");

    printf("Total Fault = %d\nTotal Hit = %d\n", totalFault, totalHit);
    printf("Miss Ratio = %d/%d = %f\n",totalFault,noOfReferences,(float)totalFault/noOfReferences);
    printf("Hit Ratio = %d/%d = %f\n",totalHit,noOfReferences,(float)totalHit/noOfReferences);
}

int main()
{
    printf("\nEnter the no of Page Frames and the no of Page references\n");
    scanf("%d%d", &noOfPageFrames, &noOfReferences);        // no of page frames and references from user

    int pageRefString[noOfReferences];
    printf("\nEnter the page no of each page reference\n");
    for (int i = 0; i < noOfReferences; i++)
    {   // scanning page reference string
        scanf("%d", &pageRefString[i]);
    }

    int choice;
    do{
        // choices for different algorithms
        printf("\nEnter 1 for FIFO Page Replacement\n");
        printf("Enter 2 for Optimal Page Replacement\n");
        printf("Enter 3 for Least Recently Used Page Replacement\n");
        printf("Enter 4 to exit\n");

        printf("\nEnter your choice\n");
        scanf("%d",&choice);    // choice input

        switch (choice){
            case 1:{
                // initialising pageframe and ishit array
                int pageFrame[noOfPageFrames][noOfReferences];
                memset(pageFrame, -1, sizeof(pageFrame));

                isHit = (int *)malloc(noOfReferences*sizeof(int));
                memset(isHit, 0, sizeof(isHit));
    
                fifo(pageFrame, pageRefString);
                print(pageFrame,pageRefString);
                break;
            }
            case 2:{
                // initialising pageframe and ishit array
                int pageFrame[noOfPageFrames][noOfReferences];
                memset(pageFrame, -1, sizeof(pageFrame));

                isHit = (int *)malloc(noOfReferences*sizeof(int));
                memset(isHit, 0, sizeof(isHit));

                optimalPageReplacement(pageFrame,pageRefString);
                print(pageFrame,pageRefString);
                break;
            }
            case 3:{
                // initialising pageframe and ishit array
                int pageFrame[noOfPageFrames][noOfReferences];
                memset(pageFrame, -1, sizeof(pageFrame));

                isHit = (int *)malloc(noOfReferences*sizeof(int));
                memset(isHit, 0, sizeof(isHit));

                leastRecentlyUsedPageReplacement(pageFrame,pageRefString);
                print(pageFrame,pageRefString);
                break;
            }
            case 4:
                break;
            default:
                printf("\nInvalid Choice\n");
        }
    }while(choice!=4);
}

// 7 0 1 2 0 3 0 4 2 3 0 3 1 2 0

// 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1