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
            //polls the next job from the queue, As the LinkedBlockingQueue is part of java's concurrent package.
            //The use of synchronize is not needed as it is handled internally.
            Job job = queue.poll();
            //poll returns null if there is no job in the queue
            if(job != null){
                //Print the job thing
                System.out.println("Consumer " + id + ": assigned request ID " + job.requestId +
                        ", processing request for the next " + job.requestLength + " seconds, current time is " + LocalDateTime.now());

                //run the job
                job.run();
                //Print the second job thing
                System.out.println("Consumer " + id + ": completed request ID " + job.requestId + " at time" + LocalDateTime.now());
            }
            try {
                //wait for half a second. This is to prevent over scheduling of threads.
                sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

    }

}
