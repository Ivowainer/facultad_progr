.global main
main:
    movb $-63, %al
    movb $-91, %ah
    addb %al, %ah
    ret
    