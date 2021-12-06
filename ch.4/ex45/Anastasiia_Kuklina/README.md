# Problem - Chapter 4 task 45
Write a program that scans all directories in a UNIX file system and finds and locates all i-nodes with a hard link count of two or more. For each such file, it lists together all file names that point to the file.

## Solution description

#### Theory:
The inode (index node) is a data structure in a Unix-style file system that describes a file-system object such as a file or a directory. Each inode stores the attributes and disk block locations of the object's data. File-system object attributes may include metadata (times of last change, access, modification), as well as owner and permission data.

A directory is a list of inodes with their assigned names. The list includes an entry for itself, its parent, and each of its children. 

```Sourse: Wikipedia - https://en.wikipedia.org/wiki/Inode```

#### Files: 
```solution.sh```
```
#!/bin/bash

echo -e "i-node  HardLinks  Path\n"
find / -links +1 -printf '%i \t %n \t %p\n' 2>/dev/null | sort -nk1
```

* `echo` - used to show the headers for better representation
* `find /` - start to search from directory `/` which is root of the system
* ` -links` - specify to check hardlinks of the files
* `+1` - list only content with more than 1 hardlink
* `-printf '%i \t %n \t %p\n'` - print the data in format: `%i`- i-node, `%n` - number of hard links, `%p`- path, `\t` - long space
* `/dev/null using 2>/dev/null` - to hide all errors
* `| sort -nk1` - pipe the output to `sort` command `-nk1` - to sort results based on i-node number


#### To execute:
In console: 
` path/solution.sh > path/output.txt`
* `path` - path to file
* `> path/output.txt` - need to redirect output of the script in file `output.txt`

```
    Made by Anastasiia Kuklina 
    Innopolis university
    Group BS20-04
    For Operating Systems course
```
