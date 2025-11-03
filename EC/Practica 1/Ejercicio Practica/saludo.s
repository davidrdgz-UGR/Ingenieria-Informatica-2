# saludo.s: Imprimir por pantalla
# "Hola a todos!"
# "Hello, World!"
# retorna: código retorno 0, programado en la penúltima línea
# comprobar desde línea de comandos bash con "echo $?"

# ================================================
# SECCIÓN DE DATOS (.data, variables globales inicializadas)
# ================================================
.section .data              # directivas comienzan por punto
                            # no son instrucciones máquina
                            # sirven para reservar memoria o definir datos

saludo:
    .ascii  "Hola a todos!\nHello, World!\n"   # \n = salto de línea

longsaludo:
    .int    . - saludo      # calcula la longitud del string automáticamente


# ================================================
# SECCIÓN DE CÓDIGO (.text, instrucciones máquina)
# ================================================
.section .text
.global _start              # punto de entrada del programa (como main en C)

_start:                     # inicio del programa en ensamblador

    # -----------------------------
    # Llamada al sistema WRITE
    # ssize_t write(int fd, const void *buf, size_t count)
    # -----------------------------
    mov     $4, %eax        # syscall 4 = sys_write
    mov     $1, %ebx        # fd = 1 (stdout)
    mov     $saludo, %ecx   # puntero al texto
    mov     longsaludo, %edx# longitud del texto
    int     $0x80           # interrupción → llamada al sistema


    # -----------------------------
    # Llamada al sistema EXIT
    # void _exit(int status)
    # -----------------------------
    mov     $1, %eax        # syscall 1 = sys_exit
    mov     $0, %ebx        # status = 0 (OK)
    int     $0x80           # interrupción → salir del programa
