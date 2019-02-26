TITLE Assignment 5 (Ass5-Q2.asm)
;Ryan Lebeau - 104535367
;60-266 Assignment Five
;30/03/2018

INCLUDE Irvine32.inc

.data
	wordOne BYTE "Factorial of ",0
	wordTwo BYTE " is ",0
	numOne DWORD ?

.code
fac PROC
	mov ecx, eax
	dec ecx
	LOOP_main:
		mul ecx

	LOOP LOOP_main
	done:
	ret
fac ENDP

main proc
	mov numOne, 6d
	mov edx, OFFSET wordOne
	call WriteString
	mov eax, numOne
	call writedec
	mov eax, numOne
	call fac

	mov edx, OFFSET wordTwo
	call WriteString
	call writedec
	call crlf
	exit
main endp
end main