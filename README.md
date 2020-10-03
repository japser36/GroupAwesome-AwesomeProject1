# GroupAwesome-AwesomeProject1

## 1. Accomplished Items
1. Seperation of the closh function into a separate execution function for code simplicity 
2. Established a time out handler via the alarm() function
3. A wait status to ensure that the parent process till wait till all childs have executed (Differentiating seq. and parallel processing)
4. Fixed issue with regards to IDE errors


Execution function: 
Simplifying the code by allowing calls to execution function to display current pid before program execution. And exit if the program has failed to run.


<s>Given main() parsing method as the parent process. All repeat of copies process will be child to the main. While the count specified (int 1 to 9) is not yet satisfied. The while loop runs till count is 0, and the wait status maintains child running before turning to parent</s>

### 1.1 Contributions
- Brian: documentation
- Brandon: coding
- Jasper: documentation
- Rachelle: documentation


## 2. Sample Output
### 2.1 Sample output for sequential output: 
```
closh> hostname
count> 8
  [p]arallel or [s]equential> s
timeout> 5

Current pid =7220
Win32
Current pid =7221
Win32
Current pid =7222
Win32
Current pid =7223
Win32
Current pid =7224
Win32
Current pid =7225
Win32
Current pid =7226
Win32
Current pid =7227
Win32
```

### 2.2 Sample output for parallel processing: 
```
closh> hostname
  count> 3
    [p]arallel or [s]equential> p
  timeout> 8
  
Current pid =7237
Current pid =7236
Current pid =7238
Win32
Win32
Win32
```

## 3. Instructions to Run Program
1. Clone repo
2. Navigate inside `GroupAwesome-AwesomeProject1` directory
3. Compile closh.c using the following command `gcc closh.c -o closh`
4. Run closh using the following command `./closh`
5. Use the sleephello.sh command by entering the following command `./sleephello.sh`
6. Enter your desired count, parallel or sequential execution and timeout
