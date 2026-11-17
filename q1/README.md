# Operating Systems Lab Examination

**Name:** Sofiya Attar  
**Roll Number:** 2401MC24  
**Set:** 1

## Question 1: Counting Semaphores

Implemented counting semaphores in xv6 using a kernel-level semaphore table containing 8 semaphore IDs (0–7), protected by a spinlock.
Implemented the system calls `sem_init()`, `sem_wait()`, and `sem_post()` to initialize, decrement, and increment semaphore values. Processes sleep when a semaphore value is zero and are awakened when another process posts to the semaphore.
Created `synctest.c`, which forks three child processes to print A, B, and C in strict sequence, five times each.

**Expected Output:**
```text
ABCABCABCABCABC
Done
```

**Files:** `sem.c`, `synctest.c`, and the modified xv6 kernel, syscall, and Makefile files.

**Screenshot:** `screenshots/Q1_output.png`
