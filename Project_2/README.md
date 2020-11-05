# GroupAwesome-AwesomeProject1

## 1. Accomplished Items  

**Java program**
1. Monitor implemented
2.  

**C Program**
1. Producer production with wait time
2. Consumer consumption with wait time
3. Process sleeps to allow for process completions
4. Formatted output file as per requirements
5. Implemented with pthreads library

## 1.1 Build instructions   

**C Program**
1. Clone repo
2. Navigate inside `GroupAwesome-AwesomeProject1` directory
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
2. Navigate inside `GroupAwesome-AwesomeProject1` directory
3. Compile program by running


## 1.2 Contributions

- Brian: documentation
- Brandon: coding
- Jasper: coding
- Rachelle: documentation

## 2 Discussion of process

Some of the problems I had while trying to make this for java is that the question makes me print things from the consume and the job, which means I can't use interfaces.

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
