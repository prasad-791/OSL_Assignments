// Prasad Sanjay Khalkar
// 33138 TE-09 L-09


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<semaphore.h>

#define MAX_BUFFER  3;  // max buffer size

static pthread_mutex_t mutex;       // mutex 
int full=0;         // for full
int empty = MAX_BUFFER;     // for empty

static pthread_mutex_t prevcons;        // mutex for previous waiting consumer

// wait
void wait(int *s){

    while((*s)<=0){
    }
    *s = *s - 1;    // decrementing the semaphore
}
// signal
void signal(int *s){
    (*s) = (*s) + 1;        // incrementing the semaphore
}

// producer code
void* producer(void *args){
    printf("\nItem produced\n");

    // waits if the buffer is full
    wait(&empty);
    // locking the mutex
    pthread_mutex_lock(&mutex);
    
    // item adding to buffer
    printf("\nItem added to buffer by Producer#%d\n",((int *)args));

    pthread_mutex_unlock(&mutex);
    signal(&full);  // signal full
}

// consumer code
void* consumer(void *args){

    // wait untils the previous consumer gets the item
    pthread_mutex_lock(&prevcons);
    // wait if the buffer is empty
    wait(&full);
    // locking the mutex
    pthread_mutex_lock(&mutex);

    // unlocking the consumer mutex as the item will be consumed by the current customer so the next waiting consumer can be unlocked
    pthread_mutex_unlock(&prevcons);
    
    printf("\nItem removed from buffer\n");
    printf("\nItem is consumed by Consumer#%d\n",((int *)args));
    
    pthread_mutex_unlock(&mutex);
    signal(&empty); // signal empty
}


int main(){
    int n;
    printf("\nEnter the no of thread\n");
    scanf("%d",&n);     // no of producer consumer threads
    pthread_t threads[n];
    int producerNo = 0,consuemerNo=0;
    printf("\nFor each thread enter whether to consume(0) or produce(1)\n");
    for(int i=0;i<n;){
        int choice;
        printf("\nEnter for thread %d\n",i);
        scanf("%d",&choice);        // choice for a consumer or producer thread
        int res;
        switch(choice){
            case 0: res = pthread_create(&threads[i],NULL,&consumer,(void *)(consuemerNo+1));
                consuemerNo++;
                i++;
                break;
            case 1: res = pthread_create(&threads[i],NULL,&producer,(void *)(producerNo+1));
                producerNo++;
                i++;
                break;
            default:
                printf("\nInvalid Choice\n");
        }
        if(res!=0){
            printf("\nError in thread creation\n");
        }
    }

    // joining the threads
    for(int i=0;i<n;i++){

        void* status;
        int t = pthread_join(threads[i],&status);
        if(t!=0){
            printf("Error in thread join = %d \n",t);
        }
    }
    return 0;
}




// static pthread_mutex_t mutex;
// sem_t full;
// sem_t empty;


// void* producer(void *args){
//     printf("\nItem produced\n");

//     sem_wait(&empty);
//     pthread_mutex_lock(&mutex);
    
//     printf("\nItem added to buffer\n");

//     pthread_mutex_unlock(&mutex);
//     sem_post(&full);
// }

// void* consumer(void *args){

//     sem_wait(&full);
//     pthread_mutex_lock(&mutex);

    
//     printf("\nItem removed from buffer\n");
//     printf("\nItem is consumed\n");
    
//     pthread_mutex_unlock(&mutex);
//     sem_post(&empty);
// }


// int main(){
//     int buffersize=MAX_BUFFER;
//     pthread_mutex_init(&mutex,NULL);
//     sem_init(&empty,0,buffersize);
//     sem_init(&full,0,0);
    

//     int n;
//     printf("\nEnter the no of thread\n");
//     scanf("%d",&n);
//     pthread_t threads[n];
//     printf("\nFor each thread enter whether to consume(0) or produce(1)\n");
//     for(int i=0;i<n;i++){
//         int choice;
//         printf("\nEnter for thread %d\n",i);
//         scanf("%d",&choice);
//         int res;
//         switch(choice){
//             case 0: res = pthread_create(&threads[i],NULL,&consumer,NULL);
//                 break;
//             case 1: res = pthread_create(&threads[i],NULL,&producer,NULL);
//                 break;
//         }
//         if(res!=0){
//             printf("\nError in thread creation\n");
//         }
//     }


//     for(int i=0;i<n;i++){

//         void* status;
//         int t = pthread_join(threads[i],&status);
//         if(t!=0){
//             printf("Error in thread join = %d \n",t);
//         }
//     }

//     pthread_mutex_destroy(&mutex);
//     sem_destroy(&empty);
//     sem_destroy(&full);
//     return 0;
// }

