.global main
main:
    movq $0x012bc23, %rax
    movq %rax, %rbx # Copio para ir modificando rcx
    xorb %al, %al # Guardo la cuenta de las veces que aparece 1
    movq $64, %rcx # Contador de las rotaciones a hacer


count_bits:
    rolq $1, %rbx
    adcb $0, %al
    decq %rdx
    loop count_bits

    ret


