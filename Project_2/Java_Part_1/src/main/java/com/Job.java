package com;


/**
 * Job class
 * Used to track the requestId and requestLength
 */
public class Job implements Runnable {
    int requestId = -1;
    int requestLength = -1;

    public Job(int requestId, int requestLength) {
        this.requestId = requestId;
        this.requestLength = requestLength;
    }

    @Override
    public void run() {
        try {
            //Sleeps the thread for x time
            Thread.sleep(requestLength*1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}