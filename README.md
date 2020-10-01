# GroupAwesome-AwesomeProject1

Like any other shell, closh takes as input the name of the program to run (e.g.,
hostname, pwd, echo, etc.). However, closh also takes three additional inputs: 
1. The number of copies (processes) of the program to run. This is an integer from 1 to 9.
2. Whether the processes should execute concurrently or sequentially.
3. Optionally, a timeout (also an integer from 1 to 9) specifying the maximum
duration of each process in seconds (reset between processes if running
sequentially). If a process takes longer than the timeout, it is terminated. A
timeout value of zero specifies no timeout.

Given main() parsing method as the parent process. All repeat of copies process will be child to the main. While the count specified (int 1 to 9) is not yet satisfied. The while loop runs till count is 0, and the wait status maintains child running before turning to parent. 