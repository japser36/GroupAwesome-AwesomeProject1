package com;
// follows basic structure from the two posts in https://stackoverflow.com/questions/12704325/java-bounded-queue-using-array

import java.util.Collection;
import java.util.Iterator;
import java.util.Queue;

public class BoundedQueue implements Queue<Job>{
    private int enqueueIndex;
    private int dequeueIndex;

    final private int size;
    final private Job [] jobs;
    private int remainingSpaces;

    public BoundedQueue(int size) {
        enqueueIndex = 0;
        dequeueIndex = 0;

        this.size = size;
        remainingSpaces = size;
        jobs = new Job [size];
    }

    @Override
    public boolean offer(Job job){
        return offerImplementation(job);
    }

    @Override
    public Job poll() {
        return pollImplementation();
    }

    private synchronized boolean offerImplementation(Job job) {
        if (remainingSpaces > 0) {
            jobs[enqueueIndex] = job;
            enqueueIndex = ++enqueueIndex == jobs.length ? 0 : enqueueIndex;
            remainingSpaces--;
            return true;
        } else {
            throw new IllegalArgumentException();
        }
    }

    private synchronized Job pollImplementation() {
        if (remainingSpaces == size) {
            return null;
        } else {
            Job job = jobs[dequeueIndex];
            jobs[dequeueIndex] = null;
            dequeueIndex = ++dequeueIndex == jobs.length ? 0 : dequeueIndex;
            remainingSpaces++;
            return job;
        }
    }

    @Override
    public int size() {
        return 0;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    @Override
    public boolean contains(Object o) {
        return false;
    }

    @Override
    public Iterator<Job> iterator() {
        return null;
    }

    @Override
    public Object[] toArray() {
        return new Object[0];
    }

    @Override
    public <T> T[] toArray(T[] a) {
        return null;
    }

    @Override
    public boolean add(Job job) {
        return false;
    }

    @Override
    public boolean remove(Object o) {
        return false;
    }

    @Override
    public boolean containsAll(Collection<?> c) {
        return false;
    }

    @Override
    public boolean addAll(Collection<? extends Job> c) {
        return false;
    }

    @Override
    public boolean removeAll(Collection<?> c) {
        return false;
    }

    @Override
    public boolean retainAll(Collection<?> c) {
        return false;
    }

    @Override
    public void clear() {

    }

    @Override
    public Job remove() {
        return null;
    }

    @Override
    public Job element() {
        return null;
    }

    @Override
    public Job peek() {
        return null;
    }
}
