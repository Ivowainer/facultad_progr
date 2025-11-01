.global main
main:
    movb $-63, %al
    movb $-56, %ah
    addb %al, %ah
    ret
