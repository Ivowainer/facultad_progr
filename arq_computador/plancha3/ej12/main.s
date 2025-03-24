.data
list: .long 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
length: .byte 10

print_sum: .asciz "Sum: %ld\n"
print_min_max: .asciz "Min: %ld, max: %ld\n"

.text
.global main
.global sumar
main:
    xorq %rcx, %rcx
    movb length, %cl # iteration
    xorq %rax, %rax # num args. float

    # suma
    call sumar
    lea print_sum, %rdi
    movq %r8, %rsi
    pushq %rbp
    call printf
    popq %rbp

    # max / min
    call max_min
    lea print_min_max, %rdi
    movq %r8, %rsi
    movq %r9, %rdx
    pushq %rbp
    call printf
    popq %rbp

sumar:
    pushq %rbp
    movq %rsp, %rbp
    #------------------

    xorq %r8, %r8
sumar_loop:
    addl list-4(, %rcx, 4), %r8d
    loop sumar_loop 

    #------------------
    movq %rbp, %rsp
    popq %rbp
    ret

max_min:
    pushq %rbp
    movq %rsp, %rbp
    #------------------
    xorq %r8, %r8 # min
    xorq %r9, %r9 # max

    movl list, %r8d
    movl list, %r9d

    movb length, %cl
max_min_loop:
    cmp list-4(, %rcx, 4), %r8d
    jg move_min

    cmp list-4(, %rcx, 4), %r9d
    jl move_max

    loop max_min_loop
    #------------------
    movq %rbp, %rsp
    popq %rbp
    ret
move_min:
    movl list-4(, %rcx, 4), %r8d
    jmp max_min_loop
move_max:
    movl list-4(, %rcx, 4), %r9d
    jmp max_min_loop

