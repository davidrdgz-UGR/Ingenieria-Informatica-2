.text

_start: .globl _start
        movl  $1, %eax    # exit
        xorl  %ebx, %ebx  # valor de retorno 0
        int   $0x80       # llamada a exit
