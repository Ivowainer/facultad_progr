.data
fact: .byte 5
print_fact: .asciz "%ld"

.text
.global main
main:

    movq $1, %rax
    xorq %rcx, %rcx

    movb fact, %dil # arg
    call fact_2


    movq %rax, %rsi
    lea print_fact, %rdi
    xorq %rax, %rax
    pushq %rbp
    call printf
    popq %rbp
    ret

fact_2:
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

    