.intel_syntax noprefix
.file 1 "Tests/IO/Type.e"
.file 2 "Tests/IO/../../IO/cstd.e"
.file 3 "Tests/IO/../../IO/sys.e"
.file 4 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm.obj"
.file 5 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm"
.file 6 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm.obj"
.file 7 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm"
.file 8 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm.obj"
.file 9 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm"
.file 10 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm.obj"
.file 11 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm"
.file 12 "Tests/IO/../../IO/STD.e"
.file 13 "Tests/IO/../../IO/Memory.e"
.file 14 "Tests/IO/../../IO/List.e"
Code_Start:
.global main
.global Start_Test
.section .text
Fruit_START:
.loc 1 7 1
Fruit:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 8
mov qword ptr [rsp + 0 ], rcx
mov rcx, qword ptr [rsp + 0 ]
.loc 1 8 12
mov dword ptr [rcx + 20 ], 4
add rsp, 8
ret 
Fruit_END:


.cfi_endproc 
Get_Sugar_START:
.loc 1 18 1
Get_Sugar:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 8
mov qword ptr [rsp + 0 ], rcx
mov rcx, qword ptr [rsp + 0 ]
.loc 1 19 2
mov eax, dword ptr [rcx + 16 ]
add rsp, 8
ret 
add rsp, 8
ret 
Get_Sugar_END:


.cfi_endproc 
is_Banana_START:
.loc 1 22 1
is_Banana:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 8
mov qword ptr [rsp + 0 ], rcx
.loc 1 23 9
mov rcx, qword ptr [rsp + 0 ]
call Get_Sugar
mov eax, eax
add rsp, 8
ret 
add rsp, 8
ret 
is_Banana_END:


.cfi_endproc 
Start_Test_START:
.loc 1 26 1
Start_Test:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 24
lea rcx, qword ptr [rsp ]
.loc 1 27 11
mov rcx, rcx
call Banana
lea rcx, qword ptr [rsp ]
.loc 1 28 9
mov rcx, rcx
call is_Banana
mov eax, eax
add rsp, 24
ret 
add rsp, 24
ret 
Start_Test_END:


.cfi_endproc 
main_START:
.loc 1 31 1
main:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 32 2
call Start_Test
.loc 1 33 2
mov eax, 1
ret 
ret 
main_END:


.cfi_endproc 
char_START:
.loc 2 11 1
char:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 8
mov qword ptr [rsp + 0 ], rcx
mov rax, qword ptr [rsp + 0 ]
add rsp, 8
ret 
add rsp, 8
ret 
char_END:


.cfi_endproc 
____Deallocate_BYTE_POINTER__START:
.loc 14 1 1
____Deallocate_BYTE_POINTER_:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 16
mov qword ptr [rsp + 0 ], rcx
.loc 13 18 2
mov rcx, qword ptr [rsp + 0 ]
mov edx, 8
call _V19internal_deallocatePhx
add rsp, 16
ret 
____Deallocate_BYTE_POINTER__END:


.cfi_endproc 
Banana_START:
.loc 1 11 1
Banana:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 8
mov qword ptr [rsp + 0 ], rcx
mov rcx, qword ptr [rsp + 0 ]
call Fruit
mov rcx, qword ptr [rsp + 0 ]
.loc 1 12 12
mov dword ptr [rcx + 16 ], 1
mov rcx, qword ptr [rsp + 0 ]
.loc 1 13 14
mov dword ptr [rcx + 12 ], 2
mov rcx, qword ptr [rsp + 0 ]
.loc 1 14 11
mov dword ptr [rcx + 8 ], 6
mov rcx, qword ptr [rsp + 0 ]
.loc 1 15 7
mov dword ptr [rcx + 20 ], 5
.loc 1 11 1
mov rax, qword ptr [rsp + 0 ]
add rsp, 8
ret 
add rsp, 8
ret 
Banana_END:


.cfi_endproc 
____Deallocate_Banana__START:
.loc 14 1 1
____Deallocate_Banana_:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 16
mov qword ptr [rsp + 0 ], rcx
.loc 13 18 2
mov rcx, qword ptr [rsp + 0 ]
mov r8, qword ptr [rsp + 0 ]
.loc 1 14 2
mov r8d, dword ptr [r8 + 8 ]
.loc 13 18 2
mov edx, r8d
call _V19internal_deallocatePhx
add rsp, 16
ret 
____Deallocate_Banana__END:


.cfi_endproc 
Code_End:
.section .data
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
.byte 0
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
.byte 7
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
.byte 8
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
.byte 9
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
.byte 11
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
.byte 12
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
_BYTE_POINTER_START:
.byte 4
.byte 1
.asciz "BYTE_POINTER"
.byte 8
.byte 13
.byte 1
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 13
.byte 1
.long _long_START-Debug_Info_Start
.byte 0
_Fruit_START:
.byte 4
.byte 1
.asciz "Fruit"
.byte 4
.byte 1
.byte 3
.byte 3
.byte 20
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 3
.long _long_START-Debug_Info_Start
.byte 0
.byte 8
.byte 2
.byte 145
.byte 0
.asciz "this"
.byte 1
.byte 7
.long _Fruit_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 3
.long _long_START-Debug_Info_Start
.byte 3
.byte 20
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
_Banana_START:
.byte 9
.byte 1
.asciz "Banana"
.byte 16
.byte 1
.byte 11
.long _Fruit_START-Debug_Info_Start
.byte 3
.byte 20
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 16
.asciz "Sugar"
.byte 1
.byte 12
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "Protein"
.byte 1
.byte 13
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "size"
.byte 1
.byte 14
.long _int_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 11
.long _long_START-Debug_Info_Start
.byte 0
.byte 5
.quad Get_Sugar_START
.long Get_Sugar_END-Get_Sugar_START
.byte 1
.byte 87
.asciz "Get_Sugar"
.byte 1
.byte 18
.byte 8
.byte 2
.byte 145
.byte 0
.asciz "b"
.byte 1
.byte 18
.long _Banana_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 11
.long _long_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "size"
.byte 1
.byte 14
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "Protein"
.byte 1
.byte 13
.long _int_START-Debug_Info_Start
.byte 3
.byte 16
.asciz "Sugar"
.byte 1
.byte 12
.long _int_START-Debug_Info_Start
.byte 3
.byte 20
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
.byte 5
.quad is_Banana_START
.long is_Banana_END-is_Banana_START
.byte 1
.byte 87
.asciz "is_Banana"
.byte 1
.byte 22
.byte 8
.byte 2
.byte 145
.byte 0
.asciz "f"
.byte 1
.byte 22
.long _Fruit_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 3
.long _long_START-Debug_Info_Start
.byte 3
.byte 20
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
.byte 10
.quad Start_Test_START
.long Start_Test_END-Start_Test_START
.byte 1
.byte 87
.asciz "Start_Test"
.asciz "Start_Test"
.byte 1
.byte 26
.byte 11
.byte 2
.byte 145
.byte 0
.asciz "x"
.byte 1
.byte 27
.long _Banana_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 11
.long _long_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "size"
.byte 1
.byte 14
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "Protein"
.byte 1
.byte 13
.long _int_START-Debug_Info_Start
.byte 3
.byte 16
.asciz "Sugar"
.byte 1
.byte 12
.long _int_START-Debug_Info_Start
.byte 3
.byte 20
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
.byte 12
.quad main_START
.long main_END-main_START
.byte 1
.byte 87
.asciz "main"
.asciz "main"
.byte 1
.byte 31
.byte 5
.quad ____Deallocate_BYTE_POINTER__START
.long ____Deallocate_BYTE_POINTER__END-____Deallocate_BYTE_POINTER__START
.byte 1
.byte 87
.asciz "____Deallocate_BYTE_POINTER_"
.byte 14
.byte 1
.byte 8
.byte 2
.byte 145
.byte 0
.asciz "Address"
.byte 13
.byte 17
.long _BYTE_POINTER_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 13
.byte 1
.long _long_START-Debug_Info_Start
.byte 0
.byte 3
.byte 20
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 16
.asciz "Sugar"
.byte 1
.byte 12
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "Protein"
.byte 1
.byte 13
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "size"
.byte 1
.byte 14
.long _int_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 11
.long _long_START-Debug_Info_Start
.byte 5
.quad ____Deallocate_Banana__START
.long ____Deallocate_Banana__END-____Deallocate_Banana__START
.byte 1
.byte 87
.asciz "____Deallocate_Banana_"
.byte 14
.byte 1
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 11
.long _long_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "size"
.byte 1
.byte 14
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "Protein"
.byte 1
.byte 13
.long _int_START-Debug_Info_Start
.byte 3
.byte 16
.asciz "Sugar"
.byte 1
.byte 12
.long _int_START-Debug_Info_Start
.byte 3
.byte 20
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
Debug_Info_End:
.section .debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"
.FILE_NAME:
.asciz "Tests/IO/Type.e"
.DIRECTORY:
.asciz "Tests/IO/"
.section .LINE_TABLE
.LINE_TABLE:
