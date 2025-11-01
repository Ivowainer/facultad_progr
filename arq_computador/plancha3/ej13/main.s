.text
.global fact1
.global fact2
fact1:
    movq $1, %rax
    call fact_func_recur
    ret

fact_func_recur:
    pushq %rbp
    movq %rsp, %rbp
    #---------------
    cmp $0, %rdi
    jz return_fact

    mul %rdi
    decq %rdi
    call fact_func_recur
return_fact:
    #---------------
    movq %rbp, %rsp
    popq %rbp
    ret

fact2:
    movq $1, %rax
    call fact_func_recur_it
    ret

fact_func_recur_it:
    pushq %rbp
    movq %rsp, %rbp
    #----------------------
    movb %dil, %cl
fact_2_loop:
    mulq %rcx
    loop fact_2_loop

    #----------------------
    movq %rbp, %rsp
    popq %rbp
    ret
