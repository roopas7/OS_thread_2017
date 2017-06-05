#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#define STACK_SIZE 1024*1024
typedef enum {
    RUNNING, // The thread is currently running.
    READY,   // The thread is not running, but is runnable.
    BLOCKED, // The thread is not running, and not runnable.
    DONE     // The thread has finished. 
  } state_t;

struct mutex
{
int held;
struct queue waiting_threads;

};

struct condition
{

     struct queue waiting_threads;

}; 


struct thread
{
  unsigned char *stack_pointer;
  void (*initial_function)(void*);
  void* initial_argument;
  state_t state;
  struct mutex m;
  struct condition c;
};

void scheduler_begin();
struct thread* thread_fork(void(*target)(void*), void * arg);
void yield();
void scheduler_end();

extern struct thread * current_thread;
void thread_start(struct thread * old, struct thread * new);
void thread_switch(struct thread * old, struct thread * new);

void mutex_init(struct mutex *);
void mutex_lock(struct mutex *);
void mutex_unlock(struct mutex *);


   void condition_init(struct condition *);
   void condition_wait(struct condition *, struct mutex *);
   void condition_signal(struct condition *);
   void condition_broadcast(struct condition *);
