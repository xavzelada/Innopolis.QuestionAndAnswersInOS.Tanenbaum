# Problem - Chapter 4 task 46
Write a new version of the UNIX ls program. This version takes as an argument one or more directory names and for each directory lists all the files in that directory, one line per  file.  Each  field  should  be  formatted  in  a  reasonable  way  given its  type. List only the first disk address, if any.

## Solution description

### Code notes:
`char* concat(char *s1, char *s2)` - to merge two strings (sequences of chars)<br />
`void printTypeSize(char *path)` - to print type of the file (file, directory, symbolic link etc.) and its size in bytes<br />
`void ls(char *path)` - to check all entityes in directory and print information about it<br />

#### To execute:
1. `gcc solution.c -o solution` - to compile
2. `./solution args` - to execute, where `args` - path to directory to check
    * If no `args` - checks the current directory `./`  

#### Resourses:
https://man7.org/linux/man-pages/man2/lstat.2.html<br />
https://man7.org/linux/man-pages/man7/inode.7.html<br />
https://man7.org/linux/man-pages/man3/readdir.3.html<br />


```
    Made by Anastasiia Kuklina 
    Innopolis University
    Group BS20-04
    For Operating Systems course
```
