.data
a: .long 1, 2, 3

.text
.global main
main:
    xorq %rax, %rax

colocar_in:
    push a(, %rax, 4)
    incq %rax
    cmpq $3, %rax
    jnz colocar_in
    movq $0, %rax
colocar_out:
    pop a(, %rax, 4)
    incq %rax
    cmpq $3, %rax
    jnz colocar_out

    movl a, %eax
    movl a+4, %ecx
    movl a+8, %edx
    ret
