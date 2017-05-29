#include "scheduler.h"
struct thread* current_thread = 0;
struct queue* ready_list = 0;
void yield() {
  if (current_thread->state != DONE) {
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
  current_thread->state = DONE;
  yield();
}

void scheduler_begin() {

  current_thread = malloc(sizeof(*current_thread));
  current_thread->state = RUNNING;
  ready_list = malloc(sizeof(*ready_list));
  ready_list->head = NULL;
  ready_list->tail = NULL;
}
void thread_fork(void(*target)(void*), void * arg) {
  struct thread* new_thread= malloc(sizeof(*new_thread));
  new_thread->initial_function = target;
  new_thread->initial_argument = arg;
  new_thread->stack_pointer = malloc(STACK_SIZE) + STACK_SIZE;
  new_thread->state = RUNNING;
  struct thread* temp_thread = current_thread;
  temp_thread->state = READY;
  thread_enqueue(ready_list,temp_thread);
  current_thread = new_thread;
  thread_start(temp_thread, current_thread);
}


void scheduler_end() {
    while (!is_empty(ready_list)) {
      yield();
    }
}
