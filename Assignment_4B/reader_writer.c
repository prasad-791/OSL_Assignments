// Prasad Sanjay Khalkar
// 33138 TE-09 L-09

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<semaphore.h>


sem_t wrt;     // semaphore for writers
pthread_mutex_t mutex;  // binary semaphore
int cnt = 1,numreader = 0;      // cnt is the variable on which the writer writes and the reader reads
// numreader is the number of readers

// Reader code
void* reader(void* read_number){
    pthread_mutex_lock(&mutex);     // locking if readers are reading then no writer is allowed to make change
    numreader++;    // current no of readers incremented

    if(numreader==1){
        printf("\nWriter is waiting\n");    
        sem_wait(&wrt);     // wait for writers while the readers are reading
    }
    pthread_mutex_unlock(&mutex);   
    // reading the variable
    printf("\nRead count for Reader #%d = %d\n",((int *)read_number),cnt);
    sleep(rand()%10);   // sleep for better visualisation

    pthread_mutex_lock(&mutex); 
    numreader--;        // decrementing the no of readers
    if(numreader==0){
        printf("\nNow Writer can write\n");
        sem_post(&wrt);     // if no of readers become 0 then the waiting writers can make changes respectively
    }

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);     // terminating the threads
}

// Writer Code
void* writer(void *writer_number){
    sem_wait(&wrt);     // wait if other writer is making changes
    cnt += 1;       // the change made by writer to the cnt variable
    printf("\nWriter #%d Modified count to %d\n",((int *)writer_number),cnt);
    sem_post(&wrt);     // signal after making changes
    sleep(rand()%10);   // sleep for better visualisation

    pthread_exit(NULL);     // terminating thread
}


int main(){


    pthread_mutex_init(&mutex,NULL);
    sem_init(&wrt,0,1);
    int n;
    int read_no,writer_no;
    read_no = writer_no = 0;
    printf("\nEnter the no of threads\n");
    scanf("%d",&n);     // no of threads 

    pthread_t threads[n];

    printf("\nFor each thread enter whether to read(0) or write(1)\n");
    for(int i=0;i<n;){
        printf("\nEnter your choice\n");
        int choice;
        scanf("%d",&choice);    // choice for a reader or writer thread
        switch(choice){
            case 0:
                pthread_create(&threads[i],NULL,reader,(void *)(read_no+1));
                read_no++;
                i++;
                break;
            case 1:
                pthread_create(&threads[i],NULL,writer,(void *)(writer_no+1));
                writer_no++;
                i++;
                break;
            default:
                printf("\nInvalid Choice\n");
        }
    }

    // joining threads
    for(int i=0;i<n;i++){
        void* status;
        int t = pthread_join(threads[i],&status);
        if(t!=0){
            printf("Error in thread join = %d \n",t);
        }
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}
