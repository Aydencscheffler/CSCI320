#include "kernel/pstat.h"
#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  struct pstat pinfo;
  if (getpinfo(&pinfo) == 0) {
    for (int i = 0; i < NPROC; i++) {
      if (pinfo.inuse[i]) {
        printf("PID: %d, Tickets: %d, Ticks: %d\n", pinfo.pid[i], pinfo.tickets[i], pinfo.ticks[i]);
      }
    }
  } else {
    printf("Error retrieving process info\n");
  }
  exit(0);
}
