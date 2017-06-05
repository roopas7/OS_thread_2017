# Inline comment
    /* Block comment */

    # void thread_switch(struct thread* old, struct thread* new);

    .globl thread_switch

    thread_switch:
      pushq %rbx           # callee-save
      pushq %rbp           # callee-save
      pushq %r12           # callee-save
      pushq %r13           # callee-save
      pushq %r14           # callee-save
      pushq %r15           # callee-save
      movq  %rsp, (%rdi)   # *x = %rbx
      movq  (%rsi), %rsp
      popq  %r15  
      popq  %r14 
      popq  %r13
      popq  %r12 
      popq  %rbp  
      popq  %rbx
      ret                  # return
