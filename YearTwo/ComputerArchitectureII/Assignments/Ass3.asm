TITLE Program Project Ass3.asm
;Ryan Lebeau - 104535367
;60-266 Assignment Three
;02/03/2018

INCLUDE Irvine32.inc
 
.data
Vector DWORD 50 DUP(?)
N DWORD ?
tempN DWORD ?
isEmpty DWORD 1
 
inputStr BYTE "What do you want to do? > ",0
inputStrN BYTE "What is the size of vector N? > ",0
strVecVal1 BYTE "What are the ",0
strVecVal2 BYTE "values in the vector? >",0
strSizeN BYTE "The size of Vector is N = ",0
vecStr BYTE "Vector = ",0
visStr BYTE "Vector is ",0
siStr BYTE "Stack is ",0
strB_AtoS BYTE "before ArraytoStack.",0
strA_AtoS BYTE "after ArraytoStack.",0
strB_StoA BYTE "before StacktoArray.",0
strA_StoA BYTE "after StacktoArray.",0
strB_SR BYTE "before StackReverse.",0
strA_SR BYTE "after StackReverse.",0
emptyStr BYTE "The stack is empty.",0
nonEmptyStr BYTE "The stack is not empty.",0
spaceStr BYTE " ",0
 
.code
main PROC
    start:
		MOV edx, OFFSET inputStr	
		CALL WriteString
		CALL ReadInt
		CALL crlf
		CMP eax, 0						;jump to 0
		JE initCall
		CMP eax, 1						;jump to 1
		JE AtoS
		CMP eax, 2						;jump to 2
		JE StoA
		CMP eax, 3						;jump to 3 
		JE SR
		JMP mainDone					;jumpt ot mainDone
	initCall:							;first option
		LEA esi, Vector
		CALL Initialize
		JMP start
	AtoS:								;second option 
		LEA esi, Vector
		CALL ArraytoStack
		JMP start
	StoA:								;third option
		LEA esi, Vector
		CALL StacktoArray
		JMP start
	SR:									;fourth option
		LEA esi, Vector
		CALL StackReverse
		JMP start
	MainDone:
main ENDP

Initialize PROC
	MOV N, 0
	MOV edx, OFFSET inputStrN			;save vector size to N
	CALL WriteString
	CALL ReadInt
	MOV N, eax
	MOV edx, OFFSET strVecVal1
	CALL WriteString
	mov eax, N
	CALL WriteInt
	MOV edx, OFFSET strVecVal2
	CALL WriteString
    CALL ReadVector
	MOV edx, OFFSET strSizeN			;size output
	CALL WriteString
	MOV eax, N
	CALL WriteInt
	CALL crlf
	MOV edx, OFFSET vecStr				;vector output
	CALL WriteString
	LEA esi, Vector
	CALL WriteVector
	CALL crlf
	CMP isEmpty, 1						;if the stack is empty
	JNE notEmpty						;if not empty jump to notEmpty
	MOV edx, OFFSET emptyStr			
	CALL WriteString
	CALL crlf
	CALL crlf
	RET
	notEmpty:							;output of notEmpty
		MOV edx, OFFSET nonEmptyStr	
		CALL WriteString
		CALL crlf
		CALL crlf
		RET
Initialize ENDP

ArraytoStack PROC				;ArraytoStack
	MOV isEmpty, 0
	MOV ecx, N							
	LEA esi, Vector
	PushonStack:					;adding to stack
		MOV ebx, [esi]					;adding to ebx
		PUSH ebx						
		ADD esi, 4						
		Loop PushonStack				

	MOV edx, OFFSET visStr			
	CALL WriteString
	LEA esi, Vector
	CALL WriteVector
	MOV edx, OFFSET strB_AtoS
	CALL WriteString
	CALL crlf
	MOV edx, OFFSET sisStr			;stack output
	CALL WriteString
	MOV ecx, N							
	PrintStack:						
		POP eax							;pop to eax
		CALL WriteInt					
		MOV edx, OFFSET spaceStr		;add space
		CALL WriteString
		Loop PrintStack					;inc loop count
	MOV edx, OFFSET strA_AtoS		
	CALL WriteString
	CALL crlf
	CMP isEmpty, 1					;if stack is empty
	JNE notEmpty					;if not empty jump to notEmpty
	MOV edx, OFFSET emptyStr		
	CALL WriteString
	CALL crlf
	RET
	notEmpty:						
		MOV edx, OFFSET nonEmptyStr	
		CALL WriteString
		CALL crlf
		RET
ArraytoStack ENDP				

StackReverse PROC					;StackReverse
	MOV isEmpty, 0
	MOV ecx, N
	LEA esi, Vector
	PushStack:							;push to stack
		MOV ebx, [esi]					;move to ebx
		PUSH ebx						;push to stack
		ADD esi, 4						
		Loop PushStack					;inc loop count
	MOV edx, OFFSET visStr				;output vector
	CALL WriteString
	LEA esi, Vector
	CALL WriteVector
	MOV edx, OFFSET strB_SR
	CALL WriteString
	CALL crlf
	CMP isEmpty, 1						;if stack is empty
	JNE notEmpty						;if not empty jump to notEmpty
	MOV edx, OFFSET emptyStr			
	CALL WriteString
	CALL crlf
	JMP skip							
	notEmpty:							
		MOV edx, OFFSET nonEmptyStr	
		CALL WriteString
		CALL crlf
	skip:								
	MOV isEmpty, 1
	MOV ecx, N
	LEA esi, Vector
	PushBackArray:						;adding to array
		POP eax							;pop to eax
		MOV [esi], eax					
		ADD esi, 4						
		Loop PushBackArray				;inc loop count
	MOV edx, OFFSET visStr				
	CALL WriteString
	LEA esi, Vector
	CALL WriteVector
	MOV edx, OFFSET strA_SR
	CALL WriteString
	CALL crlf
	CMP isEmpty, 1						;if stack is empty
	JNE notEmptyAfter					;if not empty jump to notEmpty
	MOV edx, OFFSET emptyStr			
	CALL WriteString
	CALL crlf
	RET
	notEmptyAfter:						
		MOV edx, OFFSET nonEmptyStr	
		CALL WriteString
		CALL crlf
		RET
StackReverse ENDP	

StacktoArray PROC					;StackToArray
	MOV isEmpty, 1
	MOV ecx, N
	LEA esi, Vector
	PushStack:						;adding to stack
		MOV ebx, [esi]				
		PUSH ebx					;push to ebx
		ADD esi, 4					
		Loop PushStack				
	MOV edx, OFFSET siStr			
	CALL WriteString
	MOV ecx, N
	PrintStack:							;print stack
		POP eax							;pop into eax
		CALL WriteInt					
		MOV edx, OFFSET spaceStr		
		CALL WriteString
		Loop PrintStack					;inc loop count
	MOV edx, OFFSET strB_StoA		
	CALL WriteString
	CALL crlf
	MOV ecx, N
	LEA esi, Vector
	PushBackStack:						
		MOV ebx, [esi]					
		PUSH ebx						;push ebx to stack
		ADD esi, 4						
		Loop PushBackStack				;inc loop count
	LEA esi, Vector
	MOV eax, N						
	MOV edx, 4							
	MUL edx								
	SUB eax, 4							;find beginning of last element
	MOV tempN, eax						
	MOV ecx, N
	ADD esi, tempN						;start from last element
	intoArray:						
		POP eax							;pop to eax
		MOV [esi], eax					
		SUB esi, 4						
		Loop intoArray					;inc loop count
	MOV edx, OFFSET visStr			
	CALL WriteString
	LEA esi, Vector
	CALL WriteVector
	MOV edx, OFFSET strA_StoA
	CALL WriteString
	CALL crlf
	CMP isEmpty, 1						;if stack is empty
	JNE notEmpty						;if not empty jump to notEmpty
	MOV edx, OFFSET emptyStr			
	CALL WriteString
	CALL crlf
	RET
	notEmpty:							
		MOV edx, OFFSET nonEmptyStr	
		CALL WriteString
		CALL crlf
		RET
StacktoArray ENDP						

WriteVector PROC					;WriteVector
    MOV ecx, N
    NextVec:						;print array
        MOV eax, [esi]
        CALL WriteInt
		MOV edx, OFFSET spaceStr
		CALL WriteString
        ADD esi, 4
        Loop NextVec
    RET
WriteVector ENDP

ReadVector PROC					;ReadVector
	MOV ecx, N			
    NextInt:						;adding to array
        CALL ReadInt
        MOV [esi], eax
        ADD esi, 4
        Loop NextInt
    RET
ReadVector ENDP									

END main