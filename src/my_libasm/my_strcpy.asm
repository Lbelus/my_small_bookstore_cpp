section .text
global _my_strcpy

_my_strcpy:
    ; rdi - dest
    ; rsi - source
    xor rax, rax ; counter

.loop:
    mov bl, byte [rsi + rax]
    cmp bl, 0
    je .done
    mov byte [rdi + rax], bl
    inc rax
    jmp .loop

.done:
    mov byte [rdi + rax], 0
    ret