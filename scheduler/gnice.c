#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
  if (argc <= 1) {
    printf(1, "Usage: gnice [PID]\n");
    exit();
  }

  int pid = atoi(argv[1]);
  int nice = getnice(pid);

  if (pid <= 0) {
    printf(1, "Invalid PID number\n");
    exit();
  }

  if (nice != -1)
    printf(1, "Process %d's nice value is %d now\n", pid, nice);
  else
    printf(1, "Couldn't find process %d\n", pid);

  exit();
}
