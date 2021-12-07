# Problem - Chapter 5 task 56
Write a program to implement the three disk-arm scheduling algorithms. Write a driver program  that  generates  a  sequence  of  cylinder  numbers  (0–999)  at  random,  runs  the three  algorithms  for  this  sequence  and  prints  out  the  total  distance  (number  of cylinders) the arm needs to traverse in the three algorithms

## Solution description

Disk scheduling is done by operating systems to schedule I/O requests arriving for the disk. Disk scheduling is also known as I/O scheduling.

### Implemented algorithms: 
#### First Comes Firs Serves (FCFS)
It is the simplest of all the Disk Scheduling Algorithms. In FCFS, the requests are addressed in the order they arrive in the disk queue.
##### Advantages:
* Every request gets a fair chance
* No indefinite postponement

##### Disadvantages:
* Does not try to optimize seek time
* May not provide the best possible service

#### Shortest Seek Time First (SSTF)
Requests having shortest seek time are executed first. So, the seek time of every request is calculated in advance in the queue and then they are scheduled according to their calculated seek time. As a result, the request near the disk arm will get executed first.
##### Advantages:
* Average Response Time decreases
* Throughput increases

##### Disadvantages:
* Overhead to calculate seek time in advance
* Can cause Starvation for a request if it has higher seek time as compared to incoming requests
* High variance of response time as SSTF favours only some requests

#### C-SCAN (Circular Elevator)

Circular SCAN (C-SCAN) scheduling algorithm is a modified version of SCAN disk scheduling algorithm that deals with the inefficiency of SCAN algorithm by servicing the requests more uniformly. Like SCAN (Elevator Algorithm) C-SCAN moves the head from one end servicing all the requests to the other end. However, as soon as the head reaches the other end, it immediately returns to the beginning of the disk without servicing any requests on the return trip (see chart below) and starts servicing again once reaches the beginning. This is also known as the “Circular Elevator Algorithm” as it essentially treats the cylinders as a circular list that wraps around from the final cylinder to the first one.

##### Advantages:
* High throughput
* Low variance of response time
* Average response time
* Provides more uniform wait time compared to SCAN

##### Disadvantages:
* Long waiting time for requests for locations just visited by disk arm

### To execute:
1. `python generator.py` - to generate input file
1. `gcc solution.c -o solution` - to compile
2. `./solution` - to execute

#### Resourses:
Theoretical information was used from website:
`https://www.geeksforgeeks.org/disk-scheduling-algorithms/?ref=lbp`

```
    Made by Anastasiia Kuklina 
    Innopolis University
    Group BS20-04
    For Operating Systems course
```
