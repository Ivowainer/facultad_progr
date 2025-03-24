.global main
main:
    movb $120, %al
    movb $-56, %ah
    subb %ah, %al
    ret
