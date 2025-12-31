bits 32
global start

start:
    ; Dirección base de la memoria de texto VGA
    mov     edi, 0xB8000

    ; Color: blanco sobre negro (0x0F)
    mov     ah, 0x0F

    ; H
    mov     al, 'H'
    mov     [edi], ax
    add     edi, 2

    ; o
    mov     al, 'o'
    mov     [edi], ax
    add     edi, 2

    ; l
    mov     al, 'l'
    mov     [edi], ax
    add     edi, 2

    ; a
    mov     al, 'a'
    mov     [edi], ax
    add     edi, 2

    ret
