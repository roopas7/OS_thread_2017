#include "scheduler.h"
struct thread* current_thread = 0;
struct queue* ready_list = 0;
void yield() {

  if (current_thread->state != DONE && current_thread->state != BLOCKED ) {
    current_thread->state = READY;
    thread_enqueue(ready_list, current_thread);
  }
  struct thread* temp_thread = current_thread;
  current_thread = thread_dequeue(ready_list);
  current_thread->state = RUNNING;
  thread_switch(temp_thread, current_thread);
}

void thread_wrap() {
  current_thread->initial_function(current_thread->initial_argument);
  mutex_lock(&current_thread->m);
  current_thread->state = DONE;
  condition_broadcast(&(current_thread->c));
  mutex_unlock(&current_thread->m);
  yield();
}

void scheduler_begin() {

  current_thread = malloc(sizeof(*current_thread));
  current_thread->state = RUNNING;
  ready_list = malloc(sizeof(*ready_list));
  ready_list->head = NULL;
  ready_list->tail = NULL;
}
struct thread* thread_fork(void(*target)(void*), void * arg) {
  struct thread* new_thread= malloc(sizeof(*new_thread));
  new_thread->initial_function = target;
  new_thread->initial_argument = arg;
  new_thread->stack_pointer = malloc(STACK_SIZE) + STACK_SIZE;
  new_thread->state = RUNNING;
  struct thread* temp_thread = current_thread;
  temp_thread->state = READY;
  thread_enqueue(ready_list,temp_thread);
  current_thread = new_thread;
  mutex_init(&(current_thread->m));
  thread_start(temp_thread, current_thread);
  return new_thread;
}


void scheduler_end() {
    while (!is_empty(ready_list)) {
      yield();
    }
}



void mutex_init(struct mutex *m )
{
// initialize mutex to unlocked state
  m->held = 0;
  
}

void mutex_lock(struct mutex *m)
{

	if(m->held == 0)
	{
// if unlocked, just lock it and proceed. current thread now has the lock and can proceed
		m->held = 1;
	}	
	else
	{
// some other thread has the lock. We enqueue current thread to waiting queue and yield. Current thread will be blcoked and not busy waiting.
		thread_enqueue(&(m->waiting_threads), current_thread );
		current_thread->state = BLOCKED;
		yield();
	}	

	

}

void mutex_unlock(struct mutex *m)
{

	if(is_empty(&(m->waiting_threads)))
	{
// if no thread is blocked on this lock ie; queueed, just release the lock
		m->held = 0;
	}
	else
	{
// ELSE, Pop off top of waiting queue and push it into ready queue. Anything in ready queue will be picked up by scheduler
	struct thread *temp = thread_dequeue(&(m->waiting_threads));
	thread_enqueue(ready_list, temp);
	}


}

void condition_wait(struct condition *c, struct mutex *m)
{
   
//	if(m->held = 1)
// The mutex aspects are not clear
	//	mutex_unlock(m);
// push current thread to waiting queue of conditional variable. Block the current thread and yield.
if (!is_empty(ready_list)) {
		thread_enqueue(&(c->waiting_threads), current_thread);
		current_thread->state = BLOCKED;
		mutex_unlock(m);
}
		yield();
	
	// else	
	

// change the mutex m to not held
//  add current thread to waiting list of c
//  change current thread to blocking
//  yield

}

void condition_signal(struct condition* c) {
// if there are threads which are blocked on condition c, pop off just on thread from that queue and put it into ready queue
if (!is_empty(&(c->waiting_threads))) {
//printf("here4\n");
    struct thread *temp = thread_dequeue(&(c->waiting_threads));
           thread_enqueue(ready_list, temp);	
}
//printf("here5\n");
//pop queue off c and put it in ready list
}


void condition_broadcast(struct condition* c) {

// pop off all threads off the waiting queue of c and push into ready queue	
	while(!is_empty(&(c->waiting_threads)))
	{
		struct thread *temp = thread_dequeue(&(c->waiting_threads));
		       thread_enqueue(ready_list, temp);
	
		
	}
//pop all threads off queue of c and put in ready list
}

void thread_join(struct thread* t) 
{
// this will be called by parent thread. it calls conditional wait to make sure child thread t is completed.
//printf("here6\n");
     mutex_lock(&(t->m));
//printf("here7\n");
//printf("threads state is %d\n", t->state);
//printf("thread id is %p\n", t);
     while (t->state != DONE) {
       condition_wait(&(t->c), &(t->m));
     }
   //  mutex_unlock(&(t->m));
//printf("here8\n");
}



