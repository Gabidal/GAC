.intel_syntax noprefix
.file 1 "Tests/IO/NameSpace.e"
.file 2 "../../IO/cstd.e"
.file 3 "sys.e"
.file 4 "win32.asm.obj"
.file 5 "asm.h"
.file 6 "win32.asm"
.file 7 "STD.e"
.file 8 "List.e"
Code_Start:
.global main
.global Start_Test
.section .text
Start_Test_START:
.loc 1 30 1
Start_Test:
.cfi_startproc 
.cfi_def_cfa_offset 16
push rbx
sub rsp, 28
lea rcx, qword ptr [rsp + 8 ] ; this
.loc 1 31 11
mov rcx, rcx
call Banana
lea rcx, qword ptr [rsp + 8 ] ; this
.loc 1 32 14
mov rcx, rcx
call Get
mov ebx, eax
lea rcx, qword ptr [rsp + 8 ]
mov rcx, rcx
mov edx, 1
call Set
add ebx, eax
mov dword ptr [rsp + 16 ], ebx
mov ecx, dword ptr [rip + Banana_Y ]
mov r8d, dword ptr [rip + Apple_Y ]
.loc 1 33 18
add ecx, r8d
sub ecx, dword ptr [rsp + 16 ]
mov eax, ecx
add rsp, 28
pop rbx
ret 
add rsp, 28
pop rbx
ret 
Start_Test_END:


.cfi_endproc 
main_START:
.loc 1 36 1
main:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 37 2
call Start_Test
.loc 1 38 2
mov eax, 1
ret 
ret 
main_END:


.cfi_endproc 
Banana_START:
.loc 1 8 1
Banana:
.cfi_startproc 
.cfi_def_cfa_offset 16
mov qword ptr [rsp + 8 ], rcx
mov rcx, qword ptr [rsp + 8 ]
.loc 1 12 8
mov dword ptr [rcx + 0 ], 1
.loc 1 8 1
mov rax, qword ptr [rsp + 8 ]
ret 
ret 
Banana_END:


.cfi_endproc 
Set_START:
.loc 1 14 2
Set:
.cfi_startproc 
.cfi_def_cfa_offset 16
mov qword ptr [rsp + 12 ], rcx ; this
mov dword ptr [rsp + 8 ], edx ; value
mov rcx, qword ptr [rsp + 12 ] ;this
.loc 1 15 5
mov r8d, dword ptr [rsp + 8 ] ;value
mov dword ptr [rcx + 0 ], r8d ; this->X = value
mov rcx, qword ptr [rsp + 12 ] ; this
.loc 1 16 12
add dword ptr [rcx + 0 ], 1 ;this->X++
mov eax, dword ptr [rcx + 0 ] ; return this->X
ret 
ret 
Set_END:


.cfi_endproc 
Get_START:
.loc 1 20 11
Get:
.cfi_startproc 
.cfi_def_cfa_offset 16
mov qword ptr [rsp + 8 ], rcx ; this
mov ecx, dword ptr [rip + Banana_Y ]
mov r8, qword ptr [rsp + 8 ] ; this
.loc 1 12 2
mov r8d, dword ptr [r8 + 0 ] ; ??
.loc 1 21 11
add ecx, r8d
mov eax, ecx
ret 
ret 
Get_END:


.cfi_endproc 
Code_End:
.section .data
Banana_Y:
.long 2
Apple_X:
.long 2
Apple_Y:
.long 3
.section .debug_abbrev
debug_abbrev:
.byte 1
.byte 17
.byte 1
.byte 37
.byte 14
.byte 19
.byte 5
.byte 3
.byte 14
.byte 16
.byte 23
.byte 27
.byte 14
.byte 17
.byte 1
.byte 85
.byte 23
.byte 0
.byte 0
.byte 2
.byte 36
.byte 0
.byte 3
.byte 8
.byte 62
.byte 11
.byte 11
.byte 11
.byte 58
.byte 11
.byte 59
.byte 11
.byte 0
.byte 0
.byte 3
.byte 52
.byte 0
.byte 56
.byte 5
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 0
.byte 0
.byte 4
.byte 2
.byte 1
.byte 54
.byte 11
.byte 3
.byte 8
.byte 11
.byte 11
.byte 58
.byte 11
.byte 59
.byte 11
.byte 0
.byte 0
.byte 5
.byte 46
.byte 1
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 0
.byte 0
.byte 6
.byte 46
.byte 1
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 110
.byte 8
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 63
.byte 25
.byte 0
.byte 0
.byte 7
.byte 52
.byte 0
.byte 2
.byte 24
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 0
.byte 0
.byte 8
.byte 46
.byte 0
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 110
.byte 8
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 63
.byte 25
.byte 0
.byte 0
.byte 9
.byte 5
.byte 0
.byte 2
.byte 24
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 0
.byte 0
.byte 10
.byte 46
.byte 1
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 0
.byte 0
.byte 0
.section .debug_info
Debug_Info_Start:
.long Debug_Info_End-Debug_Info
Debug_Info:
.word 4
.secrel32 debug_abbrev
.byte 8
.byte 1
.secrel32 .COMPILER_NAME
.word 0x29A
.secrel32 .FILE_NAME
.secrel32 .LINE_TABLE
.secrel32 .DIRECTORY
.quad Code_Start
.long Code_End-Code_Start
_int_START:
.byte 2
.asciz "int"
.byte 5
.byte 4
.byte 2
.byte 3
_short_START:
.byte 2
.asciz "short"
.byte 5
.byte 2
.byte 2
.byte 7
_char_START:
.byte 2
.asciz "char"
.byte 6
.byte 1
.byte 2
.byte 11
_float_START:
.byte 2
.asciz "float"
.byte 4
.byte 4
.byte 2
.byte 15
_double_START:
.byte 2
.asciz "double"
.byte 4
.byte 8
.byte 2
.byte 20
_long_START:
.byte 2
.asciz "long"
.byte 5
.byte 8
.byte 2
.byte 25
_string_START:
.byte 2
.asciz "string"
.byte 6
.byte 1
.byte 2
.byte 29
_Banana_START:
.byte 4
.byte 1
.asciz "Banana"
.byte 8
.byte 1
.byte 8
.byte 3
.byte 0
.asciz "X"
.byte 1
.byte 12
.long _int_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Y"
.byte 1
.byte 13
.long _int_START-Debug_Info_Start
.byte 0
_Apple_START:
.byte 4
.byte 1
.asciz "Apple"
.byte 8
.byte 1
.byte 24
.byte 3
.byte 0
.asciz "X"
.byte 1
.byte 26
.long _int_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Y"
.byte 1
.byte 27
.long _int_START-Debug_Info_Start
.byte 0
.byte 6
.quad Start_Test_START
.long Start_Test_END-Start_Test_START
.byte 1
.byte 87
.asciz "Start_Test"
.asciz "Start_Test"
.byte 1
.byte 30
.byte 7
.byte 2
.byte 145
.byte 8
.asciz "b"
.byte 1
.byte 31
.long _Banana_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Y"
.byte 1
.byte 13
.long _int_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "X"
.byte 1
.byte 12
.long _int_START-Debug_Info_Start
.byte 7
.byte 2
.byte 145
.byte 16
.asciz "B_X"
.byte 1
.byte 32
.long _int_START-Debug_Info_Start
.byte 0
.byte 8
.quad main_START
.long main_END-main_START
.byte 1
.byte 87
.asciz "main"
.asciz "main"
.byte 1
.byte 36
.byte 9
.byte 2
.byte 145
.byte 8
.asciz "this"
.byte 1
.byte 8
.long _Banana_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "X"
.byte 1
.byte 12
.long _int_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Y"
.byte 1
.byte 13
.long _int_START-Debug_Info_Start
Debug_Info_End:
.section .debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"
.FILE_NAME:
.asciz "Tests/IO/NameSpace.e"
.DIRECTORY:
.asciz "Tests/IO/"
.section .LINE_TABLE
.LINE_TABLE:
