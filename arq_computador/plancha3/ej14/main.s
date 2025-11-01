.data
print_args: .asciz "Cantidad de argumentos ingresados: %d. La suma es %d\n"
print_no_args: .asciz "Ingrese al menos un argumento\n"

test_s: .asciz "Arg: %s\n"

.text
.global main
main:
    mov %rdi, %rcx # argc
    mov %rsi, %r10 # argv
    decq %rcx
    movq %rcx, %rbx

    xorq %r11, %r11 # acumulación suma cuadrado

    cmpq $0, %rcx
    jng no_args
llamar_por_cada_arg:
    movq (%r10, %rcx, 8), %rdi
    xorq %rax, %rax

    pushq %rcx 
    pushq %r10
    pushq %r11
    call atoi
    popq %r11
    popq %r10
    popq %rcx

    movq %rax, %rdi
    call cuadrado

    loop llamar_por_cada_arg

    lea print_args, %rdi
    movq %rbx, %rsi
    movq %r11, %rdx
    xorq %rax, %rax
    pushq %rbp
    call printf
    popq %rbp
    ret

cuadrado:
    pushq %rbp
    movq %rsp, %rbp
    #-------------------
    mul %rax
    addq %rax, %r11

    #-------------------
    movq %rbp, %rsp
    popq %rbp
    ret


no_args:
    pushq %rbp
    xorq %rax, %rax
    lea print_no_args, %rdi
    call printf
    popq %rbp

    ret
