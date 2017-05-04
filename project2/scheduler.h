#include<stdio.h>

void scheduler_begin();
void thread_fork(void (*target)(void*), void * arg);
void yield();
void scheduler_end();
typedef enum {

RUNNING , READY,BLOCKED, DONE 
		
	} state_t;
struct thread {

	unsigned char * stack_pointer ;
	state_t state;
	void (*initial_function)(void*);
	void *initial_argument;
};

extern struct thread *current_thread ;

