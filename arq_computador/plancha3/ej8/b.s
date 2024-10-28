.global main
main:
    xorq %rax, %rax
    xorq %rdx, %rdx
    movw $-1, %ax
    movw $2, %cx
    mulw %cx
    sall $16, %edx
    orl %edx, %eax


