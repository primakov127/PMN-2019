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
	bool0 DWORD 1
	bool1 DWORD 0
	int2 SDWORD 0
	int3 SDWORD 1
	int4 SDWORD 1
	int5 SDWORD 1
	int6 SDWORD 0
	int7 SDWORD 10
	str8 BYTE "dfg", 0
	int9 SDWORD 0
	int10 SDWORD 5
	int11 SDWORD 6
	int12 SDWORD 6
	int13 SDWORD 2
	str14 BYTE "x", 0
	int15 SDWORD 0
	int16 SDWORD 1
	int17 SDWORD 20
	int18 SDWORD 3
	int19 SDWORD 2
	int20 SDWORD 5
	int21 SDWORD 2
	int22 SDWORD 2
	int23 SDWORD 5
	int24 SDWORD 5
	int25 SDWORD 0
.DATA
	result40 SDWORD 0
	ty145 DWORD 0
	x145 SDWORD 0
	s145 DWORD ?
	y181 SDWORD 0
	t145 SDWORD 0
	f145 SDWORD 0

.CODE

great1 PROC b1 : SDWORD, a1 : SDWORD
	mov eax, a1
	cmp eax, b1
		jg ifi1
		jle else1
ifi1:
	push 1
		jmp local0
	jmp ifEnd1
else1:
	push 0
		jmp local0
ifEnd1:
local0:
	pop eax
	ret
great1 ENDP

sum2 PROC b2 : SDWORD, a2 : SDWORD
	push a2
	push b2
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	cmp eax, 127
	jg overflow
	cmp eax, -128
	jl overflow
	mov result40, eax
	push result40
		jmp local1
local1:
	pop eax
	ret
sum2 ENDP

fuct3 PROC a3 : SDWORD
	mov eax, a3
	cmp eax, int2
		jz ifi2
		jnz else2
ifi2:
	push 1
		jmp local2
	jmp ifEnd2
else2:
	push a3
	push int4
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop eax
	cmp eax, 127
	jg overflow
	cmp eax, -128
	jl overflow
	mov a3, eax
	push a3
	push int5
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push a3
		call fuct3
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
	mov a3, eax
	push a3
		jmp local2
ifEnd2:
	push 0
		jmp local2
local2:
	pop eax
	ret
fuct3 ENDP

kam4 PROC a4 : DWORD, b4 : SDWORD
	push b4
	push int7
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	cmp eax, 127
	jg overflow
	cmp eax, -128
	jl overflow
	mov b4, eax
	push b4
		jmp local3
local3:
	pop eax
	ret
kam4 ENDP

strk5 PROC a5 : DWORD
	push offset str8
	pop a5

	push a5
		jmp local4
local4:
	pop eax
	ret
strk5 ENDP

main PROC
	push int9
	pop ty145

	mov eax, ty145
	cmp eax, 0
		jz ty1450T
		jnz ty1450F

ty1450T:

push offset false
call soutl

jmp ty1450

ty1450F:

push offset true
call soutl

ty1450:
	push int10
	push int11
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	cmp eax, 127
	jg overflow
	cmp eax, -128
	jl overflow
	mov x145, eax
	push int12
	pop eax
	cmp eax, 127
	jg overflow
	cmp eax, -128
	jl overflow
	mov x145, eax
while1:
	mov eax, x145
	cmp eax, int13
		jl whileT1
		jge whileEnd1
whileT1:

push offset str14
call soutl
	push int15
	pop eax
	cmp eax, 127
	jg overflow
	cmp eax, -128
	jl overflow
	mov y181, eax
	push x145
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
	mov x145, eax
jmp while1
whileEnd1:
	push int17
	push int18
	push int19
		call power
	push eax
	push int20
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push int21
	pop eax
	pop ebx
	mul ebx
	push eax
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop eax
	cmp eax, 127
	jg overflow
	cmp eax, -128
	jl overflow
	mov x145, eax
	push int22
	push int23
		call sum2
	push eax
	pop eax
	cmp eax, 127
	jg overflow
	cmp eax, -128
	jl overflow
	mov t145, eax
	push int24
	pop eax
	cmp eax, 127
	jg overflow
	cmp eax, -128
	jl overflow
	mov f145, eax

push f145
call noutl
	push 0
		jmp theend
theend:
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