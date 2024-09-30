#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#ifndef NULL //added NULL defintion 
#define NULL ((void*)0)
#endif
extern struct proc proc[NPROC]; //added struct definition


uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
// new function
uint64
sys_getfilenum(void) {
    int pid;

    // Retrieve the argument using argint
    argint(0, &pid);

    // Check if the pid is invalid
    if (pid < 0) {
        return -1;  // Invalid PID
    }

    struct proc *p = 0;
    int found = 0;  // Flag to check if process is found

    // Find the process by pid
    for (p = proc; p < &proc[NPROC]; p++) {
        if (p->pid == pid && p->state != UNUSED) {
            found = 1;  // Process found
            break;      // Exit loop when process is found
        }
    }

    // Check if we found the process
    if (!found) {
        return -1;  // Process not found or invalid
    }

    // Now count the number of open files for the found process
    int open_files = 0;
    for (int i = 0; i < NOFILE; i++) {
        if (p->ofile[i] != NULL) {
            open_files++;
        }
    }

    // Return the number of open files
    return open_files;
}
