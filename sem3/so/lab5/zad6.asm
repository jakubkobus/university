section .data
  PREFIX  db  "0x", 0
  NUMBER  dd  123456789
  N_L     db  0xA

section .bss
  outBuffer  resb  8

section .text
  global _start

_start:
  mov eax, 4
  mov ebx, 1
  mov ecx, PREFIX
  mov edx, 2
  int 80h

  mov eax, [NUMBER]
  mov esi, outBuffer
  mov ecx, 8

hexLoop:
  rol eax, 4
  mov bl, al
  and bl, 0x0F
  cmp bl, 9
  ja isLetter

isDigit:
  add bl, '0'
  jmp store

isLetter:
  add bl, 'A' - 10

store:
  mov [esi], bl
  inc esi
  dec ecx
  jnz hexLoop

  mov eax, 4
  mov ebx, 1
  mov ecx, outBuffer
  mov edx, 8
  int 80h

  mov eax, 4
  mov ebx, 1
  mov ecx, N_L
  mov edx, 1
  int 80h

  mov eax, 1
  mov ebx, 0
  int 80h