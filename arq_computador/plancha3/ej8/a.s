.global main
main:
    movl $-1, %eax
    movl $2, %ecx
    imull %ecx
    salq $32, %rdx
    orq %rdx, %rax
    ret
    
    