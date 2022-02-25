#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"



int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  int status;
  if(argint(0, &status) < 0){
    return -1;
  }
  exit(status);
  return status;
}

int
sys_wait(void)
{
  int* status;
  if(argptr(0, (char**) &status, sizeof(int*)) < 0){
    return -1;
  }
  return wait(status);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

///--------------- [+] Addendums --------------------------///

int sys_debug(void)
{
  cprintf("\n\n:::------Process Fields-----:::\n");
  cprintf( "Name:  %d\n", myproc()->name);
  cprintf( "Parent PID:  %d\n", myproc()->parent->pid);
  cprintf("Size:  %d\n", myproc()->sz);
  cprintf("PID:  %d\n", myproc()->pid);
  cprintf("Killed?:  %d\n", myproc()->killed);
  cprintf("Status:  %d\n", myproc()->status);
  cprintf("State:  %d\n", myproc()->state);
  cprintf("Priorityu:  %d\n", myproc()->priority);
  return 0;
}

//Passes int into the kernal function, filters it out if its <0. Then calls set_priority() in proc.c using that value as the new priority
int sys_set_priority(void){
  int priority_value;
  if(argint(0, &priority_value) < 0){
    return -1;
  }
  return set_priority(priority_value);
}
///---------------\ Addendums--------------------------///

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_add(void){
  int a = 66;
  int b = 77;
  return a+b;
}

int sys_waitpid(void){

  int pid = 0;
  int options = 0;
  int* exit_status;
  if(argint(0, &pid) < 0){
    return -1;
  }

  if(argptr(1, (void*) &exit_status, sizeof(exit_status)) < 0){
    return -1;
  }

  if(argint(2, &options) < 0){
    return -1;
  }

  return waitpid(pid, exit_status, options);
}

