# GroupAwesome-AwesomeProject1-Project2

## 1.2 Contributions

- Brian: documentation
- Brandon: coding
- Jasper: coding
- Rachelle: documentation

## 1. Accomplished Items  

**Java program**
1. Monitor queue implemented
2. Configuration options for the program itself
3. Implemented with the `synchornized` keyword
4. Formatted output file as per requirements
5. Producer production and Consumer consumptions with wait time

**C Program**
1. Producer production with wait time
2. Consumer consumption with wait time
3. Process sleeps to allow for process completions
4. Formatted output file as per requirements
5. Implemented with pthreads library

## 1.1 Build instructions   

**C Program**
1. Clone repo
2. Navigate inside `GroupAwesome-AwesomeProject1` directory then to subfolder `Project_2`
    - C program located inside `Not_Java_Part_2`
3. Compile program by running `gcc main.c`

    - CMakeList already contains information that allows compilation including queue.c and pthread handling4
    - If you are on different compiler/platforms and run into error due to pthread. Try the following commands to:

| Compiler/Platform | Compilar command |
| ----------------- | ---------------- |
| GNU Linux         | gcc -pthread     |
| Intel Linux       | icc -pthread     |
| PGI Linux         | pgcc -lpthread   |

4. Run the compiled program using the following command `./main`

**Java program**  
1. Clone repo
2. Navigate inside `GroupAwesome-AwesomeProject1` directory then to subfolder `Project_2`
    - Java program located in `Java_Part_1`
3. Load the Java project into IDE of choice (by selecting the Java_Part_1 or via user preferred methods)
  - While loading project, users may encounter error where project setup files from the repo may cause wrongly set JRE versions
    - Can be resolved by going into IDE setting to set correct JRE env. installed on local machine (Eclipse issue)
    - No errors of such when running with Intellij Idea
4. Configure the program if users have specific parameters in mind, configuration for `JobLength, producerWaitTime, numberOfConsumers, and QueueCapacity` available in `Main.java`
5. Run program via run of IDE



## 2 Discussion of process  

### Design

Java:
When dealing with monitors (or class wide) locks, we can not gave the consumer notify the producer as java does not differentiate between different locks in different functions.
The design is based on a standard producer and consumer pattern with a monitor queue. When a queue is empty any consumer attempting to pull from the queue will wait for a notification from the producer. When the queue is full and the producer tries to add to the queue it will release its lock and sleep for one second. This number can be changed in the Producer.java file.

C:
The design is based on a standard producer and consumer pattern with a blocking queue. When a queue is empty any consumer attempting to pull from the queue it will be stopped by a semaphore and have to wait for a notification from the producer. When a queue is full and the producer attempts to put a task in the queue it will be stopped by a semaphore and have to wait for a notification from any consumer. To enforce concurrency there is a mutex that is used during add and remove process of the queue, this ensures that only one thread can add or remove items from the queue at one time.

### Difficulties

Some of the problems I had while trying to make this for java is that the question makes me print outputs from the consumer and the job, which means I can't use interfaces properly.

Some problems that I had with C are it is not an OOP, which is a pain. The different pointers' different variations made it challenging to determine which to use or where a particular variable is. Memory on the stack was a colossal pain where object overrides each other due to a slower thread or a new object replaced the stack as it was "no longer in use."

While troubleshooting, the C error messages are non-informative in saying something went wrong without stating the cause of the issue. There were instances of random error being thrown, i.e., in the main method with no threads on a for a loop. C prompted that this increment causes a segfault when it doesn't and shouldn't.

Also, the documentation is not up to standard, making it extremely difficult to find how to use anything or how it interacts with other methods, actions, etc. Resulting in the need for brute-forcing through lists of functions to find the function that matched my use case.

## 3 Sample outputs  

**C Program**  
"""
Producer: produced request ID 0, length 4 seconds at time Wed Nov  4 16:07:47 2020
Producer: sleeping for 1 seconds
Consumer 2: assigned request ID 0, processing request for the next 4 seconds, current time is Wed Nov  4 16:07:47 2020
Producer: produced request ID 1, length 3 seconds at time Wed Nov  4 16:07:48 2020
Producer: sleeping for 2 seconds
Consumer 3: assigned request ID 1, processing request for the next 3 seconds, current time is Wed Nov  4 16:07:48 2020
Producer: produced request ID 2, length 4 seconds at time Wed Nov  4 16:07:50 2020
Producer: sleeping for 2 seconds
Consumer 4: assigned request ID 2, processing request for the next 4 seconds, current time is Wed Nov  4 16:07:50 2020
Consumer 3: completed request ID 1 at time Wed Nov  4 16:07:51 2020
Consumer 2: completed request ID 0 at time Wed Nov  4 16:07:51 2020
Producer: produced request ID 3, length 2 seconds at time Wed Nov  4 16:07:52 2020
Producer: sleeping for 1 seconds
"""

**Java program**  
"""
Files\Java\jdk1.8.0_201\jre\lib\rt.jar;C:\Users\***\Desktop\P2\out\production\P2" com.Main
Consumer 0: assigned request ID 0, processing request for the next 4 seconds, current time is 2020-11-07T04:02:31.561
Producer: produced request ID 1, length 4 seconds at time 2020-11-07T04:02:31.561 Producer: sleeping for 4 seconds
Consumer 0: completed request ID 0 at time2020-11-07T04:02:35.562
Consumer 1: assigned request ID 1, processing request for the next 5 seconds, current time is 2020-11-07T04:02:35.562
Producer: produced request ID 2, length 5 seconds at time 2020-11-07T04:02:35.562 Producer: sleeping for 2 seconds
Consumer 2: assigned request ID 2, processing request for the next 5 seconds, current time is 2020-11-07T04:02:37.563
Producer: produced request ID 3, length 5 seconds at time 2020-11-07T04:02:37.564 Producer: sleeping for 5 seconds
Consumer 1: completed request ID 1 at time2020-11-07T04:02:40.563
Consumer 2: completed request ID 2 at time2020-11-07T04:02:42.564
Consumer 3: assigned request ID 3, processing request for the next 5 seconds, current time is 2020-11-07T04:02:42.565
Producer: produced request ID 4, length 5 seconds at time 2020-11-07T04:02:42.565 Producer: sleeping for 5 seconds
Consumer 4: assigned request ID 4, processing request for the next 5 seconds, current time is 2020-11-07T04:02:47.566

"""
