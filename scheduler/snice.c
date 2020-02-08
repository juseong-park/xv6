#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
  if (argc <= 2) {
    printf(1, "Usage: snice [PID] [NICE]\n");
    exit();
  }

  int pid = atoi(argv[1]);
  int value = atoi(argv[2]);
  int cur_nice = getnice(pid);

  if (pid <= 0) {
    printf(1, "Invalid PID number\n");
    exit();
  }

  if (value < 0 || value > 40) {
    printf(1, "Invalid nice value\n");
    exit();
  }

  if (setnice(pid, value) != -1)
    printf(1, "Successful update %d to %d\n", cur_nice, value);
  else
    printf(1, "Unsuccessful update\n");

  exit();
}
