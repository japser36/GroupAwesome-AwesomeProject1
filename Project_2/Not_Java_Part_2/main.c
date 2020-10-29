#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "queue.c"

//Configuration
//The queue capacity configuration can be found at the top of the queue.c file
#define NumberOfConsumers 5
#define ProducerMinWait 1
#define ProducerMaxWait 2
#define JobMinWait 1
#define JobMaxWait 5

typedef struct {
    Queue* q;
    int consumerId;
} Thread_Args;

//thread args struct used to pass two arguments to the new thread.
Thread_Args* createThread_Args(Queue* q, int consumerId){
    Thread_Args* b = malloc(sizeof(Thread_Args));
    b->q = q;
    b->consumerId = consumerId;
    return b;
}

int randomNumber(int min, int max){
    //Basic random number generator.
    //rand() get a number from 0 to max int then mod with the size out our range + 1 as inclusive.
    //This creates a num from 0 to range size, then add min to shit the number from min to max inclusive.
    return (rand() % (max - min + 1)) + min;
}


void* producerFunction(void* arg){
    int NextRequestId = 0;
    //time variable
    time_t t;
    //Save the queue reference to the thread as a Queue struct
    Queue *queue = arg;

    while (1) {
        Job* job = createJob(NextRequestId++, randomNumber(JobMinWait, JobMaxWait));
        enqueue(queue, job);

        time(&t);
        printf("Producer: produced request ID %d, length %d seconds at time %s", job->requestId, job->requestWaitTime, ctime(&t));
        fflush(stdout);
        int sleepTime = randomNumber(ProducerMinWait, ProducerMaxWait);
        printf("Producer: sleeping for %d seconds\n", sleepTime );
        fflush(stdout);

        sleep(sleepTime);
    }
    return NULL;
}

void* consumerFunction(void* arg){
    //time variable
    time_t t;
    //Pars the two variables into their respective locations.
    Thread_Args *b = arg;
    int id = b->consumerId;
    Queue *queue = b->q;

    while (1) {
        Job *job = dequeue(queue);
        time(&t);
        printf("Consumer %d: assigned request ID %d, processing request for the next %d seconds, current time is %s",id, job->requestId, job->requestWaitTime, ctime(&t));
        fflush(stdout);
        sleep(job->requestWaitTime);
        time(&t);
        printf("Consumer %d: completed request ID %d at time %s", id, job->requestId, ctime(&t));
        fflush(stdout);
    }

    return NULL;
}


int main(){
    //Create queue in main as we want both the producer and consumers to have accesses to it.
    Queue* queue = createQueue();
    //Allocate space for the thread arguments. We keep them as long as the thread is alive or we ran into issues of
    //the struct being over writen before the thread could save the data.
    Thread_Args* args[NumberOfConsumers + 1];
    //Create an array of threads. index 0 is the producers, everything else is a consumer
    pthread_t threads[NumberOfConsumers + 1];

    //create the producer thread and pass the queue reference to it
    pthread_create(&threads[0], NULL, producerFunction, queue );
    //create all of the consumers
    for(int i = 1; i <= NumberOfConsumers; i++  ){
        //we need to pass two variables to the consumer thread, so we make a struct that can contain that data and pass
        //it to the thread.
        args[i] = createThread_Args(queue, i);
        pthread_create(&threads[i], NULL, consumerFunction, args[i]);
    }

    //use thread join to wait for the threads to finish before continuing.
    for(int i=0; i <= NumberOfConsumers; i++){
        pthread_join(threads[i], NULL);
    }
}


