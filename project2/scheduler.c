#include<stdlib.h>
#include"scheduler.h"
#include "queue.h"
#define STACK_SIZE 1024*1024

struct thread *current_thread;
struct queue *ready_list;

void thread_switch(struct thread* old, struct thread* new);
void thread_start(struct thread *old, struct thread *new);

void scheduler_begin()
{
	current_thread = (struct thread*) malloc(sizeof(struct thread));
	current_thread->state = RUNNING;
        ready_list = (struct queue*) malloc(sizeof (struct queue));

	ready_list->head = NULL;
	ready_list->tail = NULL;

}
void thread_fork(void (*target)(void*), void *arg)
{
	 struct thread *temp_thread;
	 temp_thread = (struct thread*) malloc(sizeof(struct thread));
	  temp_thread->stack_pointer = malloc(STACK_SIZE) + STACK_SIZE;
	current_thread->state = READY;
	thread_enqueue(ready_list,current_thread);
	temp_thread->state = RUNNING;
	


	struct thread* swap_thread = current_thread;
	current_thread = temp_thread;
        current_thread->initial_function = target;
        current_thread->initial_argument = arg;
     
	
	thread_start(swap_thread, current_thread); 
	
}



void yield()
{
	if(current_thread->state != DONE)
	{
		current_thread->state = READY;
		thread_enqueue(ready_list,current_thread);
	}  
	struct thread *inactive_thread = current_thread;

	current_thread = thread_dequeue(ready_list);
	current_thread->state = RUNNING;

	thread_switch(inactive_thread, current_thread);

}

void thread_wrap()
{
        current_thread->initial_function(current_thread -> initial_argument);
        
	current_thread->state = DONE;
        yield();
}

void scheduler_end()
{

	while(!is_empty(ready_list))
	{
		yield();
	}	
	


}

