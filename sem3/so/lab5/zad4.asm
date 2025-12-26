section .bss
  inBuffer   resb  32
  outBuffer  resb  32

section .text
  global _start

_start:
  mov eax, 3
  mov ebx, 0
  mov ecx, inBuffer
  mov edx, 32
  int 80h

  mov eax, 0
  mov ebx, 0
  mov esi, inBuffer

convertLoop:
  mov bl, [esi]
  cmp bl, 0xA
  je calculateSum
  cmp bl, '0'
  jb calculateSum
  sub bl, '0'
  imul eax, 10
  add eax, ebx
  inc esi
  jmp convertLoop

calculateSum:
  mov edi, 0
  mov ebx, 10

sumLoop:
  mov edx, 0
  div ebx
  add edi, edx 
  test eax, eax
  jnz sumLoop

  mov eax, edi
  mov esi, outBuffer + 31
  mov byte [esi], 10
    
printLoop:
  dec esi
  mov edx, 0
  mov ebx, 10
  div ebx
  add dl, '0'
  mov [esi], dl
  test eax, eax
  jnz printLoop

  mov ecx, esi
  mov edx, outBuffer + 32
  sub edx, esi
  mov eax, 4
  mov ebx, 1
  int 80h

  mov eax, 1
  mov ebx, 0
  int 80h