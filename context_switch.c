#include<stdio.h>
#include<stdlib.h>
#define STACK_SIZE 1024*1024

struct thread {

	unsigned char * stack_pointer ;
	
	void (*initial_function)(void*);
	void *initial_argument;
};

struct thread *current_thread;
struct thread *inactive_thread;

int factorial(int n){
	
	return n==0 ? 1 : n * factorial(n-1);
}

void yield();
void fun_with_threads(void *arg)
{
	int n=*(int*) arg;
	for(int i =0;i<5;++i)
	{
	printf("%d!= %d\n",n,factorial(n));
	yield();
	}

}

void thread_wrap();
void thread_switch(struct thread* old, struct thread* new);
void thread_start(struct thread *old, struct thread *new);


void thread_wrap()
{
	current_thread->initial_function(current_thread -> initial_argument);
        yield();
}


int main()
{


	current_thread = (struct thread*) malloc(sizeof(struct thread));
	inactive_thread = (struct thread*) malloc(sizeof(struct thread));

	current_thread->stack_pointer = malloc(STACK_SIZE) + STACK_SIZE;
	current_thread->initial_function = fun_with_threads;
	
	int * p = malloc(sizeof(int));
	*p = 10;
	current_thread->initial_argument = p;
	thread_start(inactive_thread,current_thread);
	for(int j=0;j<5;++j)
	{
		printf("inside main thread %d\n",j);
		yield();
	}
}

void yield()
{

	struct thread *temp = current_thread;
	current_thread = inactive_thread;
	inactive_thread = temp;
	thread_switch(inactive_thread, current_thread);


}
