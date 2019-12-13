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
	bool7 SDWORD 0
	int8 SDWORD 5
	int9 SDWORD 6
	int10 SDWORD 6
	int11 SDWORD 5
	str12 DWORD "L", 0
	int13 SDWORD 1
	int14 SDWORD 4
	int15 SDWORD 7
	int16 SDWORD 1
	str17 DWORD "5", 0
	int18 SDWORD 5
	str19 DWORD "f", 0
	int20 SDWORD 55
	int21 SDWORD 14
	int22 SDWORD 8
	int23 SDWORD 2
	int24 SDWORD 55
	int25 SDWORD 20
	int26 SDWORD 3
	int27 SDWORD 2
	int28 SDWORD 5
	int29 SDWORD 2
	int30 SDWORD 2
	int31 SDWORD 5
	str32 DWORD "df", 0
	int33 SDWORD 6
	int34 SDWORD 0
.DATA
	result10 SDWORD 0
	ty115 DWORD 0
	x115 SDWORD 0
	s115 DWORD ?
	t149 SDWORD 0
	x189 DWORD ?
	y189 SDWORD 0
	y221 SDWORD 0
	f115 SDWORD 0

.CODE

sum1 PROC a1 : SDWORD, b1 : SDWORD
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
		jz m0
		jnz m1
		je m1
m0:
	push 1
		jmp local1
	jmp e0
m1:
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
e0:
	push 0
		jmp local1
local1:
	pop eax
	ret
fuct2 ENDP

kam3 PROC b3 : SDWORD, a3 : DWORD
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

str4 PROC a4 : DWORD
	push offset str6
	pop a4

	push a4
		jmp local3
local3:
	pop eax
	ret
str4 ENDP

main PROC
	push bool7
	pop ty115

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
	push int8
	push int9
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop x115

	push int10
	pop x115

while1:
	mov eax, x115
	cmp eax, int11
		jg whileT1
		jl whileEnd1
whileT1:

push offset str12
call soutl
	push x115
	push int13
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop x115

	push int14
	pop t149

while2:
	mov eax, t149
	cmp eax, int15
		jl whileT2
		jg whileEnd2
whileT2:
	push t149
	push int16
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop t149


push offset str17
call soutl
jmp while2
whileEnd2:
jmp while1
whileEnd1:
	mov eax, x115
	cmp eax, int18
		jg m2
		jl m3
		je m3
m2:
	push offset str19
	pop x189

	push int20
	push int21
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push int22
	pop eax
	pop ebx
	mul ebx
	push eax
	push int23
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop y189


push x189
call soutl
	jmp e1
m3:
	push int24
	pop y221

e1:
	push int25
	push int26
	push int27
		call power
	push eax
	push int28
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push int29
	pop eax
	pop ebx
	mul ebx
	push eax
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop x115

	push int30
	push int31
		call sum1
	push eax
	pop f115

	push offset str32
		call str4
	push eax
	pop s115

	push int33
		call fuct2
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