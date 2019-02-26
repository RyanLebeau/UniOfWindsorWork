TITLE Program Project Q2Assign1.asm
;Ryan Lebeau - 104535367
;60-266 Assignment One Q2
;09/02/2018
INCLUDE Irvine32.inc

.data
bigEndian BYTE ?, ?, ?, ?
littleEndian DWORD ?
inbetween BYTE " , ",0
userPrompt BYTE "Enter in 4byte value: ",0

.code
main PROC
	mov edx,OFFSET userPrompt		;prompting user for input and storing in littleEndian
	call WriteString
	call ReadHex
	mov littleEndian, eax

	mov al, bigEndian+4				;reverse's order of little endian into big endian
	mov bigEndian, al
	mov al, bigEndian+5
	mov bigEndian+1, al
	mov al, bigEndian+6
	mov bigEndian+2, al
	mov al, bigEndian+7
	mov bigEndian+3, al

	movzx eax, bigEndian			;displaying each hex byte of big endian
	call WriteHex
	mov edx,OFFSET inbetween
	call WriteString
	mov al, bigEndian+1
	call WriteHex
	call WriteString
	mov al, bigEndian+2
	call WriteHex
	call WriteString
	mov al, bigEndian+3
	call WriteHex
	call Crlf
	
	exit
main ENDP
END main 