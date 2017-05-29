#include "scheduler.h"
#include <stdio.h>
#include <unistd.h>

void print_nth_prime(void * pn) {
  int n = *(int *) pn;
  int c = 1, i = 1;
  while(c <= n) {
    ++i;
    int j, isprime = 1;
    for(j = 2; j < i; ++j) {
      if(i % j == 0) {
        isprime = 0;
        break;
      }
    }
    if(isprime) {
      ++c;
    }
    yield();
  }
  printf("%dth prime: %d\n", n, i);
 
}

void reading_aio(void *rd){

	char buff[10];
        int n;
	int f_handle = open("sample.txt", 0);
	n = read_wrap(f_handle, buff, 10);
	printf("%s\n",buff);
	printf("n= %d\n", n);
	n = read_wrap(f_handle, buff, 10);
	printf("%s\n",buff);
	printf("n= %d\n", n);

}

int main(void) {
  scheduler_begin();

  int n1 = 20000, n2 = 10000, n3 = 30000;
printf("forking\n");
  thread_fork(print_nth_prime, &n1);
printf("forking\n");
  thread_fork(print_nth_prime, &n2);
  thread_fork(print_nth_prime, &n3);
  thread_fork(reading_aio, &n1);

  scheduler_end();
}


