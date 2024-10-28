.data
    a: .long 1, 2, 3, 4
    g: .quad 0x1122334455667788
    msg: .asciz "Imprime %c\n"
    c: .long 2

.text
.global main
main:
    xorq %rsp, %rsp
    subq $8, %rsp # rsp = 0xfffffffffffffff8 (si y solo si rsp es 0, entonces rsp es -8)
    movq $g, %rax # rax = 0x404040 (dirección de g)
    movl g+4, %eax # rax = 0x11223344 (al revés porque es little-endian)
    movq $3, %rbx # rbx = 0x3
    movb a(,%rbx,4), %al # rax = 0x11223304 ((a + (3*4)) => a+12=4)
    leaq msg, %rdi # rdi = 0x404048 (dirección de msg)
    movb (%rdi, %rbx, 2), %sil # sil = 0x65 (%rdi + 6 = letra e)
    xorl %eax, %eax # rax = 0x0
    call printf # rax = 0xa 
    /* addq $8, %rsp # rsp = 0x0 (-8+8)  */
    ret
