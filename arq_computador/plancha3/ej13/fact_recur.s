.data
fact: .byte 5

.text
.global main
main:
    movq $1, %rax

    movq fact, %rdi
    call fact

fact_func:
    pushq %rbp
    movq %rsp, %rbp
    #---------------
    cmp $0, %rdi
    jz return_fact

    mul %rdi
    decq %rdi
    call fact_func
    #---------------
    popq %rbp
    movq %rbp, %rsp

return_fact:
    #---------------
    popq %rbp
    movq %rbp, %rsp
    ret
