section .data
  MESSAGE_SUM   db   "Suma elementow: ", 0
  LENGTH_SUM    equ  $ - MESSAGE_SUM

  MESSAGE_DIAG  db   0xA, "Suma przekatnej: ", 0
  LENGTH_DIAG   equ  $ - MESSAGE_DIAG

  N_L           db   0xA

section .bss
  matrixSize  resb  9
  outBuffer   resb  32

section .text
  global _start

_start:
  pop ecx
  pop edi
  dec ecx
  cmp ecx, 9
  jne exitError
  mov esi, 0

parseArgments:
  pop edi
  movzx eax, byte [edi]
  sub eax, '0'
  mov [matrixSize + esi], al
  inc esi
  loop parseArgments

  mov eax, 0
  mov ecx, 0

sumLoop:
  movzx edx, byte [matrixSize + ecx]
  add eax, edx
  inc ecx
  cmp ecx, 9
  jl sumLoop

  push eax
  mov eax, 4
  mov ebx, 1
  mov ecx, MESSAGE_SUM
  mov edx, LENGTH_SUM
  int 80h
  pop eax
  call printNumber

  mov eax, 0
  movzx edx, byte [matrixSize + 0]
  add eax, edx
  movzx edx, byte [matrixSize + 4]
  add eax, edx
  movzx edx, byte [matrixSize + 8]
  add eax, edx

  push eax
  mov eax, 4
  mov ebx, 1
  mov ecx, MESSAGE_DIAG
  mov edx, LENGTH_DIAG
  int 80h
  pop eax
  call printNumber

  mov eax, 4
  mov ebx, 1
  mov ecx, N_L
  mov edx, 1
  int 80h

  mov eax, 1
  mov ebx, 0
  int 80h

exitError:
  mov eax, 1
  mov ebx, 1
  int 80h

printNumber:
  push ebx
  push ecx
  push edx
  push esi
  mov esi, outBuffer + 31

  .convertLoop:
    dec esi
    mov edx, 0
    mov ebx, 10
    div ebx
    add dl, '0'
    mov [esi], dl
    test eax, eax
    jnz .convertLoop

    mov ecx, esi
    mov edx, outBuffer + 31
    sub edx, esi
    mov eax, 4
    mov ebx, 1
    int 80h

    pop esi
    pop edx
    pop ecx
    pop ebx
    ret