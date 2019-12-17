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
	true BYTE 'true', 0
	false BYTE 'false', 0
	int0 SDWORD 0
	int1 SDWORD 1
	int2 SDWORD 1
	int3 SDWORD 1
	int4 SDWORD 0
	int5 SDWORD 10
	str6 DWORD "dfg", 0
	int7 SDWORD 5
	int8 SDWORD 6
	int9 SDWORD 6
	int10 SDWORD 2
	str11 DWORD "x", 0
	int12 SDWORD 0
	int13 SDWORD 1
	int14 SDWORD 20
	int15 SDWORD 3
	int16 SDWORD 2
	int17 SDWORD 5
	int18 SDWORD 2
	int19 SDWORD 2
	int20 SDWORD 5
	int21 SDWORD 5
	int22 SDWORD 2
	int23 SDWORD 2
	int24 SDWORD 2
	int25 SDWORD 2
	int26 SDWORD -14
	int27 SDWORD 1
	int28 SDWORD 0
.DATA
	result10 SDWORD 0
	ty115 DWORD 0
	x115 SDWORD 0
	s115 DWORD ?
	y147 SDWORD 0
	t115 SDWORD 0
	f115 SDWORD 0

.CODE

sum1 PROC b1 : SDWORD, a1 : SDWORD
	push a1
	push b1
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop result10

	push result10
		jmp local0
local0:
	pop eax
	ret
sum1 ENDP

fuct2 PROC a2 : SDWORD
	mov eax, a2
	cmp eax, int0
		jz ifi1
		jnz else1
ifi1:
	push 1
		jmp local1
	jmp ifEnd1
else1:
	push a2
	push int2
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop a2

	push a2
	push int3
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push a2
		call fuct2
	push eax
	pop eax
	pop ebx
	mul ebx
	push eax
	pop a2

	push a2
		jmp local1
ifEnd1:
	push 0
		jmp local1
local1:
	pop eax
	ret
fuct2 ENDP

kam3 PROC a3 : DWORD, b3 : SDWORD
	push b3
	push int5
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop b3

	push b3
		jmp local2
local2:
	pop eax
	ret
kam3 ENDP

strk4 PROC a4 : DWORD
	push offset str6
	pop a4

	push a4
		jmp local3
local3:
	pop eax
	ret
strk4 ENDP

main PROC
	mov eax, ty115
	cmp eax, 0
		jz ty1150T
		jnz ty1150F

ty1150T:

push offset false
call soutl

jmp ty1150

ty1150F:

push offset true
call soutl

ty1150:
	push int7
	push int8
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop x115

	push int9
	pop x115

while1:
	mov eax, x115
	cmp eax, int10
		jl whileT1
		jge whileEnd1
whileT1:

push offset str11
call soutl
	push int12
	pop y147

	push x115
	push int13
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop x115

jmp while1
whileEnd1:
	push int14
	push int15
	push int16
		call power
	push eax
	push int17
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push int18
	pop eax
	pop ebx
	mul ebx
	push eax
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop x115

	push int19
	push int20
		call sum1
	push eax
	pop t115

	push int21
	pop f115

	push int22
	push int23
	push int24
		call power
	push eax
	push int25
		call power
	push eax
	push int26
		call abser
	push eax
		call sum1
	push eax
	pop eax
	pop ebx
	mul ebx
	push eax
	push int27
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop f115


push f115
call noutl
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