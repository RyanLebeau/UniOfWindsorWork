TITLE Assignment 5 (Ass5-Q3.asm)
;Ryan Lebeau - 104535367
;60-266 Assignment Five
;30/03/2018

INCLUDE Irvine32.inc

.data
	wordOne BYTE "Fibonacci seqence with N = ", 0
	wordTwo BYTE " is: ",0
	wordThree BYTE " ",0
	num BYTE ?

.code
main proc
	call ReadDec
	mov DWORD PTR num, eax
	movzx ecx, num
	mov edx, OFFSET wordOne
	call WRITESTRING
	call WRITEDEC
	mov edx, OFFSET wordTwo
	call WRITESTRING
	mov eax, 0
	mov ebx, 1
	call WRITEDEC
	
	fib:
		mov edx, eax
		add edx, ebx
		mov eax, ebx
		mov ebx, edx
		mov edx, OFFSET wordThree
		call WRITESTRING
		call WRITEDEC
	loop fib

	call crlf
	exit
main endp
end main