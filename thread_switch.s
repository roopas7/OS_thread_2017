 # Inline comment
/* Block comment */

 # void thread_switch(struct thread *old, struct thread *new);

 .globl thread_switch

 thread_switch:

 pushq %rbx
 pushq %rbp
 pushq %r12
 pushq %r13
 pushq %r14
 pushq %r15
 
 movq %rsp,(%rdi)
 
 movq (%rsi),%rsp
 popq %rbx
 popq %rbp
 popq %r12
 popq %r13
 popq %r14
 popq %r15
 
 ret
  
 
