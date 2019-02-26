TITLE Program Project Q1Assign1.asm
;Ryan Lebeau - 104535367
;60-266 Assignment One
;09/02/2018
INCLUDE Irvine32.inc

.data
A SDWORD -210
B SDWORD 10
varC SDWORD ?
D SDWORD ?
Z SDWORD ?
strInputC BYTE "What is the value of C? ",0
strInputD BYTE "What is the value of D? ",0
strEquation BYTE "Z=(A-B)+(C-D)",0
strInbetween BYTE "   ;   ",0
strNewLine BYTE 10,0

.code
main PROC
	mov edx,OFFSET strInputC		;propmitng user for C variable
	call WriteString
	call ReadInt					;storing and returning C variable
	mov varC,eax
	call WriteInt
	mov edx,OFFSET strNewLine		;new line
	call WriteString
	
	mov edx,OFFSET strInputD		;prompting user for D variable
	call WriteString
	call ReadInt					;storing and reading D variable
	mov D,eax
	call WriteInt
	mov edx,OFFSET strNewLine		;new line
	call WriteString

	mov edx,OFFSET strEquation		;printing equation to the user
	call WriteString
	mov edx,OFFSET strNewLine		;new line
	call WriteString

	mov eax,A						;displaying all variable values
	call WriteInt
	mov edx,OFFSET strInbetween
	call WriteString
	mov eax,B
	call WriteInt
	call WriteString
	mov eax,varC
	call WriteInt
	call WriteString
	mov eax,D
	call WriteInt

	mov edx,OFFSET strNewLine		;new line
	call WriteString
	mov edx,OFFSET strNewLine		;new line
	call WriteString

	mov eax,A						;calculating value of Z
	sub eax,B
	mov Z,eax
	mov eax,varC
	sub eax,D
	add Z,eax
	
	mov eax,Z						;displaying value of Z in decimal
	call WriteInt
	mov edx,OFFSET strNewLine		;new line
	call WriteString
	call WriteBin					; display Z in binary
	mov edx,OFFSET strNewLine		;new line
	call WriteString
	call WriteHex					;display Z in hexidecimal

	exit
main ENDP
END main 