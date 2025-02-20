.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib "..\Debug\PMN_LIB.lib"

ExitProcess PROTO:DWORD 
SYSPAUSE PROTO 
nout PROTO : SDWORD 
sout PROTO : BYTE 
soutl PROTO : BYTE 
noutl PROTO : SDWORD 
power PROTO  : SDWORD, : SDWORD 
abser PROTO  : SDWORD 

.STACK 4096

.CONST
	null_division BYTE 'ERROR: DIVISION BY ZERO', 0
	OVER_FLOW BYTE 'ERROR: OVERFLOW', 0
	true BYTE 'true', 0
	false BYTE 'false', 0
	int0 SDWORD 0
	int1 SDWORD 1
	int2 SDWORD 1
	int3 SDWORD 1
	int4 SDWORD 0
	str5 BYTE "gdsgds", 0
	int6 SDWORD 101
	int7 SDWORD 4
	int8 SDWORD -2
	int9 SDWORD 12
	int10 SDWORD -2
	int11 SDWORD 0
	int12 SDWORD 10
	int13 SDWORD 2
	int14 SDWORD 0
	str15 BYTE "i not even", 0
	int16 SDWORD 1
.DATA
	stroka163 DWORD ?
	num63 SDWORD 0
	i63 SDWORD 0
	p122 SDWORD 0

.CODE

just1 PROC a1 : DWORD
	push a1
		jmp local0
local0:
	pop eax
	ret
just1 ENDP

fact2 PROC x2 : SDWORD
	mov eax, x2
	cmp eax, int0
		jz ifi1
		jnz else1
ifi1:
	push 1
		jmp local1
	jmp ifEnd1
else1:
	push x2
	push int2
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop eax
	cmp eax, 127
	jg overflow
	cmp eax, -128
	jl overflow
	mov x2, eax
	push x2
	push int3
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push x2
		call fact2
	push eax
	pop eax
	pop ebx
	mul ebx
	push eax
	pop eax
	cmp eax, 127
	jg overflow
	cmp eax, -128
	jl overflow
	mov x2, eax
	push x2
		jmp local1
ifEnd1:
	push 0
		jmp local1
local1:
	pop eax
	ret
fact2 ENDP

main PROC
	push offset str5
		call just1
	push eax
	pop stroka163

	push int6
	pop eax
	cmp eax, 127
	jg overflow
	cmp eax, -128
	jl overflow
	mov num63, eax

push stroka163
call sout

push num63
call noutl
	push int7
	push int8
		call abser
	push eax
		call power
	push eax
	push int9
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	push int10
	pop eax
	pop ebx
	mul ebx
	push eax
	pop eax
	cmp eax, 127
	jg overflow
	cmp eax, -128
	jl overflow
	mov num63, eax

push num63
call noutl
	push int11
	pop eax
	cmp eax, 127
	jg overflow
	cmp eax, -128
	jl overflow
	mov i63, eax
while1:
	mov eax, i63
	cmp eax, int12
		jl whileT1
		jge whileEnd1
whileT1:
	push i63
	push int13
	pop ebx
	pop eax
	cmp ebx,0
	je SOMETHINGWRONG
	cdq
	idiv ebx
	push edx
	pop eax
	cmp eax, 127
	jg overflow
	cmp eax, -128
	jl overflow
	mov p122, eax
	mov eax, p122
	cmp eax, int14
		jz ifi2
		jnz else2
ifi2:

push i63
call noutl
	jmp ifEnd2
else2:

push offset str15
call soutl
ifEnd2:
	push i63
	push int16
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	cmp eax, 127
	jg overflow
	cmp eax, -128
	jl overflow
	mov i63, eax
jmp while1
whileEnd1:
	call SYSPAUSE
	push 0
	call ExitProcess
SOMETHINGWRONG::
	push offset null_division
	call soutl
jmp konec
overflow::
	push offset OVER_FLOW
	call soutl
konec:
	call SYSPAUSE
	push -1
	call ExitProcess
main ENDP
end main