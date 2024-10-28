.data
a: .word -1
b: .byte 0xaa, 99
c: .float 1.5
str: .asciz "Hola mundo\n"

.text
.global main
main:
    leaq a, %rdx
    movw (%rdx), %ax
    movb b+1, %al
    movl c, %edi
    movl str, %esi
    ret
    