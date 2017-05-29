# Inline comment
    /* Block comment */

    # void thread_start(struct thread* old, struct thread* new);
    # void thread_wrap();

    .globl thread_start 

    thread_start:
      pushq %rbx           # callee-save
      pushq %rbp           # callee-save
      pushq %r12           # callee-save
      pushq %r13           # callee-save
      pushq %r14           # callee-save
      pushq %r15           # callee-save
      movq  %rsp, (%rdi)   # *x = %rbx
      movq  (%rsi), %rsp
      jmp thread_wrap
      ret                  # return
