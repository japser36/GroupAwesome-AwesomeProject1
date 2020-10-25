package com;

import java.util.Queue;
import java.util.concurrent.LinkedBlockingQueue;

public class Main {

    //This is the program configuration

    //Job length {min, max}
    public static final int[] JobLength = {1,5};
    // producerWaitTime {min, max}
    public static final int[] producerWaitTime = {1,5};
    public static final int numberOfConsumers = 5;
    public static final int QueueCapacity = 5;



    //Start the program
    public static void main(String[] args){
        Main program = new Main();
    }


    //Still starting the program
    public Main(){
        Queue<Job> queue = new BoundedQueue(QueueCapacity);

        //creating the consumer threads with the queue
        Thread[] threads = new Thread[numberOfConsumers+1];
        for(int i = 0; i < numberOfConsumers; i++){
            threads[i] =  new Consumer(queue, i);
        }
        //creating the producer thread with the queue
        threads[numberOfConsumers] =  new Producer(queue);

        //starting all of the threads
        for(int i = 0; i < numberOfConsumers+1; i++){
            threads[i].start();
        }



    }
}
