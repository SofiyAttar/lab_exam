
#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  int i;

  //initialize three semaphores.
  //A starts first, B waits for A, C waits for B.
  if(sem_init(0, 1) < 0 ||
     sem_init(1, 0) < 0 ||
     sem_init(2, 0) < 0){
    printf(1, "Semaphore initialization failed\n");
    exit();
  }

  //child A
  if(fork() == 0){
    for(i = 0; i < 5; i++){
      sem_wait(0);
      printf(1, "A");
      sem_post(1);
    }
    exit();
  }

  //child B
  if(fork() == 0){
    for(i = 0; i < 5; i++){
      sem_wait(1);
      printf(1, "B");
      sem_post(2);
    }
    exit();
  }

  //child C
  if(fork() == 0){
    for(i = 0; i < 5; i++){
      sem_wait(2);
      printf(1, "C");
      sem_post(0);
    }
    exit();
  }

  //parent waits for all three children.
  wait();
  wait();
  wait();

  printf(1, "\nDone\n");

  exit();
}

