
_start:
; 8 "/bin/cat"
push 0x00000000 ;
push 0x2f636174 ; t a c /
push 0x2f62696e ; n i b /
mov %esp, %ebx

xor %eax, %eax
mov $0x1, %al ; 0x1 is write
push $0x1 ; stdout
push %ebx
push $0x8
int 0x80 ; 
