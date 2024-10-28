.global main
main:
    movb $100, %al
    movb $120, %ah
    addb %al, %ah
    ret
