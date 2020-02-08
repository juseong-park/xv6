#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

#define NUM_THREADS 4
#define MAX_NUM_THREADS 64
#define BUF_SIZE 100
#define DATA_SIZE 1000

int buffer[BUF_SIZE];
int pro_counter = 0;
int con_counter = 0;
int data = 0;
int in = 0, out = 0;

int empty, full, mutex;

void*
producer(void *num)
{
  sleep(10);
  printf(1, "Producer thread %d: started...\n", (int)num);
  while (pro_counter < DATA_SIZE) {
    sem_wait(empty);
    sem_wait(mutex);

    sleep(0);
    buffer[in] = pro_counter++;
    printf(1, "Producer: %d\n", pro_counter);
    in = (in + 1) % BUF_SIZE;
    sleep(0);

    sem_signal(mutex);
    sem_signal(full);
  }
  exit();
}

void*
consumer(void *num)
{
  sleep(10);
  printf(1, "Consumer thread %d: started...\n", (int)num);
  while (con_counter < DATA_SIZE) {
    sem_wait(full);
    sem_wait(mutex);

    sleep(0);
    int val = buffer[out];
    printf(1, "Consumer: %d\n", val);
    out = (out + 1) % BUF_SIZE;
    con_counter++;
    sleep(0);

    sem_signal(mutex);
    sem_signal(empty);
  }
  exit();
}

int
main(int argc, char **argv)
{
  int i;
  int sem_size = 1;
  
  if ((empty = sem_create(DATA_SIZE)) < 0) {
    printf(1, "main: error initializing semaphore %d\n");
    exit();
  }

  if ((full = sem_create(sem_size)) < 0) {
    printf(1, "main: error initializing semaphore %d\n");
    exit();
  }

  if ((mutex = sem_create(sem_size)) < 0) {
    printf(1, "main: error initializing semaphore %d\n");
    exit();
  }

  printf(1, "main: running with %d threads...\n", NUM_THREADS);

  int pid[MAX_NUM_THREADS];

  for (i=0; i<NUM_THREADS; i++) {
    if (i % 2 == 0) {
      pid[i] = hufs_thread_create(producer, (void*)i);
      if (pid[i] == -1)
        printf(1, "main: failed to creat a %d-th thread with pid %d\n", i);
      else
        printf(1, "main: created thread with pid %d\n", pid[i]);
    } else {
      pid[i] = hufs_thread_create(consumer, (void*)i);
      if (pid[i] == -1)
        printf(1, "main: failed to creat a %d-th thread with pid %d\n", i);
      else
        printf(1, "main: created thread with pid %d\n", pid[i]);
    }
  }
  
  for (i=0; i<NUM_THREADS; i++) {
    printf(1, "before joining... \n");
    if (pid[i] != -1) 
      printf(1, "main: thread %d joined...\n", hufs_thread_join(pid[i]));
  }

  sem_destroy(empty);
  sem_destroy(full);
  sem_destroy(mutex);

  exit();
}
