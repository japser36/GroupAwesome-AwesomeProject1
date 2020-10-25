package com;

import java.time.LocalDateTime;
import java.util.Queue;


/**
 * Consumer class
 *
 */
public class Consumer extends Thread{
    private int id = -1;
    Queue<Job> queue;

    public Consumer(Queue<Job> queue,int id){
        this.id = id;
        this.queue = queue;
    }

    @Override
    public void run(){
        //infinite loop, this will not stop running unless there is an interrupt.
        while (true){
            Job job = queue.poll(); // Consumer waits until a job is available

            //Print the job thing
            System.out.println("Consumer " + id + ": assigned request ID " + job.requestId +
                    ", processing request for the next " + job.requestLength + " seconds, current time is " + LocalDateTime.now());
            //run the job
            job.run();
            //Print the second job thing
            System.out.println("Consumer " + id + ": completed request ID " + job.requestId + " at time" + LocalDateTime.now());
        }

    }

}
