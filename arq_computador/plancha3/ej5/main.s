.global main
main:
  movq $0x1122334455667788, %rax    # Mover el valor inmediato de 64 bits a %rax
  movq $0x1122334455667788, %rbx    # Mover el mismo valor inmediato a %rbx
  addq %rbx, %rax                   # Sumar el valor de %rbx a %rax
  ret
