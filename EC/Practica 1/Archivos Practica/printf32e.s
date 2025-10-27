#################################################
# printf32e.s
# gcc -m32 printf32e.s -o printf32e
#################################################

.extern exit       # exit en otro sitio
.extern printf     # printf en otro sitio
.globl main        # función principal

#################################################

.data
i:      .int 12345         # variable entera
f:      .string "i = %d\n" # cadena de formato

#################################################

.text
main:   push %ebp          # preserva ebp
        mov %esp, %ebp     # copia esp
        and  $-16, %esp    # alinear pila a 16 bytes

        push i             # apila i
        push $f            # apila f
        call printf        # llamada a función
        add  $8, %esp      # restaura pila

        mov %ebp, %esp     # restaura esp
        pop %ebp           # restaura ebp
        xor %eax, %eax     # valor de retorno
        ret                # retorno a libc

#################################################
