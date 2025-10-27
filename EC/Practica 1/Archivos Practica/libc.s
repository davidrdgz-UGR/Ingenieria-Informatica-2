#################################################
# printf64.s
# gcc -m64 printf64.s -o printf64
#################################################

.globl main

#################################################

.data
i:      .int 12345         # variable entera
f:      .string "i = %d\n" # cadena de formato

#################################################

.text
main:   mov  $f, %rdi       # formato
        mov  i, %rsi        # i
        xor  %rax, %rax     # registros vectoriales
        call printf         # llamada a función

        xor  %rdi, %rdi     # valor de retorno
        call exit           # llamada a función

#################################################
