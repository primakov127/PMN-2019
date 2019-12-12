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
	int0 SDWORD 35
	int1 SDWORD 174
	int2 SDWORD 175
	int3 SDWORD 10
	int4 SDWORD 6
	int5 SDWORD 5
	str6 BYTE "f", 0
	int7 SDWORD 55
	int8 SDWORD 14
	int9 SDWORD 8
	int10 SDWORD 2
	int11 SDWORD 55
	int12 SDWORD 2
	int13 SDWORD 2
	str14 BYTE "hello world", 0
	int15 SDWORD 0
.DATA
	result10 SDWORD 0
	t10 SDWORD 0
	x62 SDWORD 0
	x77 DWORD ?
	y77 SDWORD 0
	y109 SDWORD 0

.CODE

sum1 PROC a1 : SDWORD, b1 : SDWORD
	push a1
	push b1
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop result10

	push int0
	pop t10

	push int1
	pop t10

	push int2
	pop t10

	push result10
		jmp local0
local0:
	pop eax
	ret
sum1 ENDP

kam2 PROC b2 : SDWORD
	push b2
	push int3
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop b2

	push b2
		jmp local1
local1:
	pop eax
	ret
kam2 ENDP

main PROC
	push int4
	pop x62

	mov eax, x62
	cmp eax, int5
		jg m0
		jl m1
		je m1
m0:
	push offset str6
	pop x77

	push int7
	push int8
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push int9
	pop eax
	pop ebx
	mul ebx
	push eax
	push int10
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop y77


push x77
call sout
	jmp e0
m1:
	push int11
	pop y109

e0:
	push int12
	push int13
		call power
	push eax
	pop x62


push offset str14
call sout
	push 0
		jmp theend
theend:
	call SYSPAUSE
	push 0
	call ExitProcess
SOMETHINGWRONG:
	push offset null_division
	call soutl
	call SYSPAUSE
	push -1
	call ExitProcess
main ENDP
end main