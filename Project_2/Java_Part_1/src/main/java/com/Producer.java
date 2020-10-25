package com;


import util.Util;

import java.time.LocalDateTime;
import java.util.Queue;


/**
 * Producer class
 * tracks the number of jobs created
 */
public class Producer extends Thread {
    int taskCount = 0;
    Queue<Job> queue;

    public Producer(Queue<Job> queue){
        this.queue = queue;
    }

    @Override
    public void run(){
        //infinite loop, this will not stop running unless there is an interrupt.
        while (true){
            //creates a new job.
            int waitTime = Util.getInt(Main.JobLength);
            int nextSleep = Util.getInt(Main.producerWaitTime);

            Job job = new Job(taskCount++, waitTime );


            boolean result;
            do {
                //tries to insert the job into the queue, As the LinkedBlockingQueue is part of java's concurrent package.
                //The use of synchronize is not needed as it is handled internally.
                //if the insert fails due to the queue being full, it will return fails.
                //https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/LinkedBlockingQueue.html
                result = queue.offer(job);
                if(!result){
                    try {
                        //Wait for a second and try again.
                        System.out.println("Producer: fails to offer request ID " + taskCount + " due to queue being full"  );
                        sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }

                //if the job fails to insert then we want to try to re add it.
            }while (!result);
            System.out.println("Producer: produced request ID "+taskCount+", length "+waitTime+" seconds at time "+ LocalDateTime.now() +" Producer: sleeping for " + nextSleep +" seconds");
                try {
                    //Wait for the random wait time.
                    sleep(nextSleep*1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
        }
    }
}
