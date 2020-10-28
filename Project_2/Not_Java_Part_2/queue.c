
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

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
    pthread_mutex_t mutex;
    Job* buffer[Capacity];
} Queue;

//simple method to memory allocate set and return a populated queue struct
 Queue* createQueue(){
     Queue* q = malloc(sizeof(Queue));
     //initialise the semaphores to carry across threads and locking values
     sem_init(&q->emtpy, 0, 0);
     sem_init(&q->full, 0, Capacity);
     q->size = 0;
     q->head = 0;
     q->tail = 0;
     return q;
 }




 int enqueue(Queue* q, Job* j){
     //check to see if queue is full, if not we can proceed else we have to wait until there is empty slot
     sem_wait(&q->full);
     //acquire lock
     pthread_mutex_lock(&q->mutex);

     q->buffer[q->tail] = j;
     q->tail = (q->tail + 1) % Capacity;
     q->size = q->size + 1;

     //release lock
     pthread_mutex_unlock(&q->mutex);
     //increment emtpy, as there is one more item in the queue
     sem_post(&q->emtpy);
     return 1;
 }


 Job* dequeue(Queue* q){
     //check to see if queue is empty, if not we can proceed else we have to wait until there is an item
     sem_wait(&q->emtpy);
     //acquire lock
     pthread_mutex_lock(&q->mutex);

     Job* j = q->buffer[q->head];
     q->buffer[q->head] = NULL;
     q->head = (q->head+1) % Capacity;
     q->size = q->size - 1;

     //release lock
     pthread_mutex_unlock(&q->mutex);
     //increment full, as there is one less item in the queue
     sem_post(&q->full);
     return j;
 }



