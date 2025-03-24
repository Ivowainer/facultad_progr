.global main
main:
    movb $-91, %al
    movb $120, %ah
    subb %ah, %al
    ret
