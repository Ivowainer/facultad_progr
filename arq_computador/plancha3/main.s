.data
len: .byte 10

.text
.global main
main:
    movq len, %rax
    ret

