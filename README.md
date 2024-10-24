# CSCI320
I used a 3:2:1 ratio, giving the first process 300 tickets, the second 200, and the last 100. As expected, the fewer tickets a process has, the less CPU time it consumes. To implement this, I modified several files. In sysproc.c, I implemented sys_settickets and sys_getpinfo, and in proc.c, I implemented the lottery ticket scheduler. I added random.c and random.h to generate random numbers for the scheduler, and homework.c to help test processes and assign them a specified number of tickets. The Makefile was updated to compile random.c and homework.c. In syscall.h, I added SYS_settickets and SYS_getpinfo, and in proc.h, I added a tickets attribute to the proc structure to track the number of tickets per process, as well as a ticks attribute to track the number of time slices a process accumulates. I also added entries for Settickets and Getpinfo in usys.pl, and their prototypes in user.h. Additionally, I added pinfo.c to print the process ID, the number of tickets, and the number of ticks. Finally, I added prototypes for sys_settickets and sys_getpinfo in syscall.c. 

Below are the results from running homework.c and pinfo.c

xv6 kernel is booting

hart 1 starting
hart 2 starting
init: starting sh
$ homework 300 &
$ starting main
initialized

$ homework 200 &
$ starting main
initialized

$ homework 100 & 
$ starting main
initialized

$ pinfo
PID: 1, Tickets: 1, Ticks: 15
PID: 2, Tickets: 1, Ticks: 23
PID: 12, Tickets: 1, Ticks: 5
PID: 4, Tickets: 300, Ticks: 716
PID: 7, Tickets: 200, Ticks: 595
PID: 10, Tickets: 100, Ticks: 527
