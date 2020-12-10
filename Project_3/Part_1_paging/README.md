# GroupAwesome-AwesomeProject1-Project3-Part1

## Contributions

- Brian: Code, Documentation
- Jasper: Code, Documentation

## Accomplished Items

1. Bitwise operator for virtual address page and offset info
2. File IO to read input file for addresses to process
3. File IO for user specified file and file path
4. Feedback to user regarding program status
5. 16-bit mask as per requirement

## 1 Build instructions   

### Part 1: Paging
1. We start by compiling the file by executing `gcc pageTable.c` which returns a file named `a.out`
2. Run `a.out` by the command `./a.out`
  - While running `a.out` input the file directory as `./test.txt` to access the sample file we have provided
  - Sample output should look like:

![The sample output of the file read](/images/bitwise.png)

## 2 Discussion of process  

**2.1 C Program**  

The file I/O portion was relatively straight forward. Give it a file, load the file, and iterate through the results. I ran in to a lot of trouble trying to distinguish when I needed to put `&` before a variable and when not to. My dev. env. did not provide much error detection and I had to rely on the error messages when `gcc` tried to compile `pageTable.c`. Due to a lack of familiarity with C, it was hard to determine a good method to iterate through the target file. A lot of data mismatch and random errors due to typos later, I was finally able to complete it.

## 3 Appendix

**3.1 Test file setup**

Our test file has integers that were powers of 2, 3, and 5. Thus, many of the numbers fall right on the page limit given it was a power of 2. To demonstrate that our bitwise operator worked with other values. Integers multiplied to powers of 3 and 5 were included as well. To show values within pages with a proper offset value.

The setup of our test file is setting the first two values n and m are both 8 to follow the assumption given in the assignment that `n + m is 16`. The following values are virtual address that are to be processed.

**3.2 Binary file uncertainty**

We were not sure in what format the virtual addresses would be in. We have ran inputs with pure binary numbers, as well as, normal integers. We decided to use simple integer numbers generated through the process mentioned above. Which was chosen for its simplicity while allowing us to test and demonstrate the working program.

**3.3 16-bit addressing**

Following the process outlined in the project requirements, we used a mask to make the virtual address comply to the 16-bit limit. If the integers within the test file exceed that limit, it will overflow and return a zero value in the output. The overflow is seen in the sample output file.
