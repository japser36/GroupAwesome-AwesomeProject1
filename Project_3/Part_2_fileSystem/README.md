# Part II: File Systems

## 1 Contributions
- Brandon: Coding
- Rachelle: Documentation

## 2 Design and Implementation Decisions
The instructions made it very clear and left room for unique implementation decisions. The most notable design challenge was having to use many pointers which proved difficult however that is the nature of C. 

## 3 Sample Output
For the sample input file `lab3input.txt` the following output is displayed:
```
file1.c
file2.c
file3.c
a.out
lab1.jav
file1.c
file2.c
file4.c
a.out
lab1.jav
file1.c
file2.c
file4.c
a.out
lab2.jav
```

## 4 Build Instructions   
1. Create the filesystem by building `CMakeLists.txt` with line `CMakeLists.txt:7` uncommented. Name the filesystem `disk0`
2. Move a copy of `lab3input.txt` to your cmake build folder so that it is in the same directory as the filesystem
3. Change the CmakeLists.txt to uncomment `Part_2_fileSystem/closh.c` to run part 2. (Be sure to re-comment line 7)
4. You can use `closhMode` by changing the `closhMode` variable to `1` on line `Part_2_fileSystem/closh.c:14`. This will change whether the program will run the script file or have an interactive console. 
