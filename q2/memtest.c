
#include "types.h"
#include "stat.h"
#include "user.h"

int global_var = 123;

int
main(void)
{
  int p[2];
  int pid;
  int before_fork, after_fork, after_wait;
  int parent_pa, child_pa;
  char c = 'x';
  char *addr;

  printf(1, "\n===== MEMORY STATISTICS TEST =====\n");

  // 1. Check free pages at startup.
  printf(1, "Free pages at startup: %d\n", freepages());

  // 2. Allocate 10 pages.
  addr = sbrk(10 * 4096);

  if(addr == (char*)-1){
    printf(1, "sbrk failed\n");
    exit();
  }

  printf(1, "Free pages after allocating 10 pages: %d\n",
         freepages());

  // 3. Translate the address of a global variable.
  printf(1, "\nGlobal variable address: 0x%x\n",
         (uint)&global_var);

  printf(1, "Physical address: 0x%x\n",
         va2pa((int)&global_var));

  // 4. Test an invalid address.
  printf(1, "\nTesting invalid address 0x7fffffff:\n");
  printf(1, "Translation result: %d\n",
         va2pa(0x7fffffff));

  // 5. Create a pipe to keep the child alive.
  if(pipe(p) < 0){
    printf(1, "Pipe creation failed\n");
    exit();
  }

  before_fork = freepages();

  pid = fork();

  if(pid < 0){
    printf(1, "Fork failed\n");
    close(p[0]);
    close(p[1]);
    exit();
  }

  if(pid == 0){
    // Child process.
    close(p[1]);

    child_pa = va2pa((int)&global_var);

    printf(1, "\nChild virtual address: 0x%x\n",
           (uint)&global_var);
    printf(1, "Child physical address: 0x%x\n",
           child_pa);

    // Wait until parent finishes checking memory.
    read(p[0], &c, 1);

    close(p[0]);
    exit();
  }

  // Parent process.
  close(p[0]);

  parent_pa = va2pa((int)&global_var);

  printf(1, "\nParent virtual address: 0x%x\n",
         (uint)&global_var);
  printf(1, "Parent physical address: 0x%x\n",
         parent_pa);

  after_fork = freepages();

  printf(1, "\nFree pages before fork: %d\n", before_fork);
  printf(1, "Free pages after fork: %d\n", after_fork);

  // Allow child to exit.
  write(p[1], &c, 1);
  close(p[1]);

  wait();

  after_wait = freepages();

  printf(1, "Free pages after child exit and wait: %d\n",
         after_wait);

  printf(1, "\nFree pages restored: %s\n",
         after_wait == before_fork ? "YES" : "NO");

  printf(1, "===== TEST COMPLETE =====\n");

  exit();
}

