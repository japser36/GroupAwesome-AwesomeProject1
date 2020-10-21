#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <semaphore.h>


#define Capacity 10

//struct for the task/job
typedef struct {
    int requestId;
    int requestWaitTime;
} Job;

//simple method to memory allocate set and return a populated job struct
Job* createJob(int requestId, int requestWaitTime){
    Job * j = malloc(sizeof(Job));
    j->requestId = 0;
    j->requestWaitTime = 0;

    j->requestId = requestId;
    j->requestWaitTime = requestWaitTime;
    return j;
}

//struct for our queue. Mostly taken from the notes
typedef struct {
    int head, tail, size;
    sem_t emtpy;
    sem_t full;
    Job* buffer[Capacity];
} Queue;

//simple method to memory allocate set and return a populated queue struct
 Queue* createQueue(){
     Queue* q = malloc(sizeof(Queue));
     q->size = 0;
     q->head = 0;
     q->tail = 0;
     return q;
 }


int isFull(Queue* q){
    int out = 0;
    if(q->size == Capacity-1){
        out = 1;
    }
    return out;
}

int isEmpty(Queue* q){
    int out = 0;
    if(q->size == 0){
        out = 1;
    }
    return out;

}

 int enqueueImp(Queue* q, Job* j){
     int out = 1;
     if(isFull(q)){
         out = 0;
     }
     q->buffer[q->tail+1] = j;
     q->tail = (q->tail + 1) % Capacity;
     q->size = q->size + 1;
     return out;
 }


 Job* dequeueImp(Queue* q){
     if(isEmpty(q)) {

     }
     Job* j = q->buffer[q->head];
     q->head = (q->head-1) % Capacity;
     q->size = q->size - 1;
     return j;
 }

 //Interface level access to the queues enqueue function
int enqueue(Queue* q, Job* job){
     return enqueueImp(q, job);

}

 //Interface level access to the queues dequeue function
Job* dequeue(Queue* q){
     return dequeueImp(q);
}



