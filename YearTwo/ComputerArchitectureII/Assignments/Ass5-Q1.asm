TITLE Assignment 5 (Ass5-Q1.asm)
;Ryan Lebeau - 104535367
;60-266 Assignment Five
;30/03/2018

INCLUDE Irvine32.inc

.data
	wordOne BYTE "GCD of ",0
	wordTwo BYTE " and ",0
	wordThree BYTE " is ",0
	numOne DWORD ?
	numTwo DWORD ?

.code
gcd PROC
	cmp ecx, 0  
	jle done	
		sub edx, edx
		div ecx 
		mov eax, ecx	
		mov ecx, edx	
		call gcd
	done:
	ret
gcd ENDP

main proc
	mov numOne, 20d
	mov numTwo, 5d
	mov edx, OFFSET wordOne
	call WriteString
	mov eax, numOne
	call writedec
	mov edx, OFFSET wordTwo
	call WriteString
	mov eax, numTwo
	call writedec
	mov eax, numOne
	mov ecx, numTwo
	call gcd
	mov edx, OFFSET wordThree
	call WriteString
	call writedec
	call crlf

	main proc
	mov numOne, 5d
	mov numTwo, 20d
	mov edx, OFFSET wordOne
	call WriteString
	mov eax, numOne
	call writedec
	mov edx, OFFSET wordTwo
	call WriteString
	mov eax, numTwo
	call writedec
	mov eax, numOne
	mov ecx, numTwo
	call gcd
	mov edx, OFFSET wordThree
	call WriteString
	call writedec
	call crlf

	mov numOne, 24d
	mov numTwo, 18d
	mov edx, OFFSET wordOne
	call WriteString
	mov eax, numOne
	call writedec
	mov edx, OFFSET wordTwo
	call WriteString
	mov eax, numTwo
	call writedec
	mov eax, numOne
	mov ecx, numTwo
	call gcd
	mov edx, OFFSET wordThree
	call WriteString
	call writedec
	call crlf

	mov numOne, 11d
	mov numTwo, 7d
	mov edx, OFFSET wordOne
	call WriteString
	mov eax, numOne
	call writedec
	mov edx, OFFSET wordTwo
	call WriteString
	mov eax, numTwo
	call writedec
	mov eax, numOne
	mov ecx, numTwo
	call gcd
	mov edx, OFFSET wordThree
	call WriteString
	call writedec
	call crlf

	mov numOne, 432d
	mov numTwo, 226d
	mov edx, OFFSET wordOne
	call WriteString
	mov eax, numOne
	call writedec
	mov edx, OFFSET wordTwo
	call WriteString
	mov eax, numTwo
	call writedec
	mov eax, numOne
	mov ecx, numTwo
	call gcd
	mov edx, OFFSET wordThree
	call WriteString
	call writedec
	call crlf

	mov numOne, 0d
	mov numTwo, 0d
	mov edx, OFFSET wordOne
	call WriteString
	mov eax, numOne
	call writedec
	mov edx, OFFSET wordTwo
	call WriteString
	mov eax, numTwo
	call writedec
	mov eax, numOne
	mov ecx, numTwo
	call gcd
	mov edx, OFFSET wordThree
	call WriteString
	call writedec
	call crlf

	exit
main endp
end main