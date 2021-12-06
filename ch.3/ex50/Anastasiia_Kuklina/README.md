# Problem - Chapter 3 task 50
Plot a histogram and calculate the mean and median of the sizes of executable binary
files on a computer to which you have  access. On a Windows system, look at all ```.exe``` and  ```.dll```  files;  on  a  UNIX  system  look  at  all  executable  files  in ```/bin```, ```/usr/bin```, and ```/local/bin``` that are not scripts (or use the file utility to find all executables).  Determine the optimal page size for this computer just considering the code (not data). Consider internal fragmentation and page table size, making some reasonable assumption about the size of a page table entry. Assume that all programs are equally likely to be run and thus should be weighted equally

## Solution description

### Using commands:

```
find /bin/ -type f -executable -exec size {} 2>/dev/null \; | grep /bin/ > ~/out1.txt
find /usr/bin/ -type f -executable -exec size {} 2>/dev/null \; | grep /bin/ > ~/out2.txt
find /local/bin/ -type f -executable -exec size {} 2>/dev/null \; | grep /bin/ > ~/out3.txt
```
We will get sizes of all executable files in given directories (```/bin/```, ```/usr/bin/```, ```/local/bin/```)
It stored in files ```~/out1.txt```, ```~/out2.txt```, ```~/out3.txt``` respectively
#### Information will looks like (size given in bytes):

| text | data | bss	|  dec	|  hex	| filename |
|------|------|-----|-----|-----|-----|
| 4254 | 768 | 16 | 5038 | 13ae | /bin/tri-orig |
| 213734 | 16344 | 2688	| 232766 | 38d3e | /bin/debugfs |
| 565184 | 38017 | 152 |  603353 | 934d9 | /bin/qv4l2 |

We are interested only in ```first``` column ```text```, which is equal to code section
#### Then we go to pover of  ```spreadsheets```
Copy and paste recieved information into table and delete unnesessary columns 

We will get table like:
| text |
|------|
| 4254 |
| 213734 |
| 565184 |

#### Spreadsheets formulas:
* ```=median(A2:A500)``` - we can get median value
* ```=sum(A2:A5000) / count(A2:A5000)``` - mean value

#### On my computer:
* Total size = 1799635466 bytes = 1716 MB
* Total number of files: 4999
* Median = 22055 bytes = 21 KB
* Mean = 351 KB

### Description:
When an application is executed: then a corresponding process is started. This process in order to save on the usage of RAM adapts the paging. In the paging technique, memory is not allocated to the complete application, but part of the application is given the RAM, rest of the application is executed by constantly getting the needed part of application into the RAM. This concept is also known as the virtual memory. 
Page is fixed unit size into which the virtual memory for implementation of paging is divided. The page is stored in the RAM whereas is corresponding detailed memory block; page frame; is stored in the physical memory. The details of the page frame are stored in the page table, which contains the memory segment used, the offset values and other details for the same. In a 16-bit virtual memory address, first 4 bits are used to store the page number and rest 12 bits are used to maintain the offset for the file. This. allows loading 16 pages each having 4 MB data to be loaded in the virtual memory. 

It has been noticed that almost 50% times the pages loaded in the virtual memory do not contain any text or data, but are blank; creating internal fragments. If ```n``` segments are stored in the memory, each having a fixed page size of ```p``` bytes, then a total of ```(n x p) / 2``` bytes is held in the internal fragments created. 
The average size of each process is ```s``` bytes, stored with fixed page size of ```p``` bytes. The page entry to be stored in the page table uses ```e``` bytes each. Hence the count of pages created per process is ```s/p``` and the size of page table is ```(s*e)/p``` bytes. The internal fragmentation created is of size ```p/2``` (assuming 50%). 
Hence, the total overhead created is: ```overhead = (s*e)/p + p/2``` 

If the page size is small, then it increases the size of the page table due to count of entries and if the page size is large then it affects the internal fragmentation size. Hence the optimal page size is: ```p = sqrt(2*s*e)``` 
The average size of each process is (mean value): ```(total memory size) / (process count) = 351 KB``` The page table for the machine is 512 KB. Hence, the optimal page size for the machine is: ```= sqrt (2 x 351 x 512) = 600 KB``` . 

### Resourses:
Description was taken from previos year solution <br />
Link to the solution: https://github.com/thisisbeka/OS.Tanenbaum-Internship/blob/master/code/ch3-p50.pdf

```
    Made by Anastasiia Kuklina 
    Innopolis university
    Group BS20-04
    For Operating Systems course
```
