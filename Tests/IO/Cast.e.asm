.intel_syntax noprefix
.file 1 "Tests/IO/Cast.e"
.file 2 "../../IO/cstd.e"
.file 3 "sys.e"
.file 4 "win32.asm.obj"
.file 5 "asm.h"
.file 6 "win32.asm"
.section .text
Code_Start:
.global main
.global Start_Test
Base_START:
.loc 1 3 1
Base:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 4 11
mov dword ptr [rcx + 0 ], 0
.loc 1 3 1
mov rax, rcx
ret 
ret 
Base_END:


.cfi_endproc 
Mid_START:
.loc 1 7 1
Mid:
.cfi_startproc 
.cfi_def_cfa_offset 16
mov rbx, rcx
push rbx
mov rcx, rbx
call Base
.loc 1 8 7
mov dword ptr [rbx + 0 ], 1
mov ecx, 1074261268
mov dword ptr [rbx + 4 ], ecx
.loc 1 7 1
mov rax, rbx
pop rbx
ret 
pop rbx
ret 
Mid_END:


.cfi_endproc 
test_all_format_casts_START:
.loc 1 17 1
test_all_format_casts:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 18 8
mov ecx, 1
cvtsi2ss xmm0, ecx
.loc 1 20 10
movss xmm0, xmm0
.loc 1 18 2
cvtsi2sd xmm1, ecx
.loc 1 21 11
movsd xmm1, xmm1
.loc 1 20 2
cvttss2si r8d, xmm0
.loc 1 23 4
mov ecx, r8d
.loc 1 21 2
cvttsd2si r8d, xmm1
.loc 1 24 4
mov ecx, r8d
cvtsd2ss xmm1, xmm1
movss xmm0, xmm1
cvtss2sd xmm0, xmm0
movsd xmm1, xmm0
.loc 1 17 1
ret 
test_all_format_casts_END:


.cfi_endproc 
Start_Test_START:
.loc 1 30 1
Start_Test:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 8
.loc 1 31 2
call test_all_format_casts
lea rcx, qword ptr [rsp ]
.loc 1 32 8
mov rcx, rcx
call Mid
.loc 1 9 2
movss xmm0, dword ptr [rsp + 4 ]
cvttss2si ecx, xmm0
.loc 1 33 2
mov eax, ecx
add rsp, 8
ret 
add rsp, 8
.loc 1 30 1
ret 
Start_Test_END:


.cfi_endproc 
main_START:
.loc 1 36 1
main:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 38 2
mov eax, 1
ret 
.loc 1 36 1
ret 
main_END:


.cfi_endproc 
Code_End:
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
.byte 110
.byte 14
.byte 3
.byte 14
.byte 62
.byte 11
.byte 11
.byte 11
.byte 58
.byte 11
.byte 59
.byte 11
.byte 63
.byte 25
.byte 0
.byte 0
.byte 3
.byte 52
.byte 0
.byte 2
.byte 24
.byte 110
.byte 14
.byte 3
.byte 14
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 63
.byte 25
.byte 0
.byte 0
.byte 4
.byte 46
.byte 1
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 110
.byte 14
.byte 3
.byte 14
.byte 58
.byte 11
.byte 59
.byte 11
.byte 63
.byte 25
.byte 0
.byte 0
.byte 5
.byte 5
.byte 0
.byte 2
.byte 24
.byte 110
.byte 14
.byte 3
.byte 14
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 63
.byte 25
.byte 0
.byte 0
.byte 6
.byte 2
.byte 1
.byte 54
.byte 11
.byte 110
.byte 14
.byte 3
.byte 14
.byte 11
.byte 11
.byte 58
.byte 11
.byte 59
.byte 11
.byte 63
.byte 25
.byte 0
.byte 0
.byte 7
.byte 2
.byte 1
.byte 54
.byte 11
.byte 110
.byte 14
.byte 3
.byte 14
.byte 11
.byte 11
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 63
.byte 25
.byte 0
.byte 0
.byte 8
.byte 52
.byte 0
.byte 64
.byte 24
.byte 110
.byte 14
.byte 3
.byte 14
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 63
.byte 25
.byte 0
.byte 0
.byte 9
.byte 46
.byte 1
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 3
.byte 14
.byte 58
.byte 11
.byte 59
.byte 11
.byte 0
.byte 0
.byte 10
.byte 46
.byte 0
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 3
.byte 14
.byte 58
.byte 11
.byte 59
.byte 11
.byte 0
.byte 0
.byte 11
.byte 46
.byte 1
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 110
.byte 14
.byte 3
.byte 14
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 63
.byte 25
.byte 0
.byte 0
.byte 0
.section .debug_info
.long Debug_Info_End-Debug_Info_Start
Debug_Info_Start:
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
.secrel32 i_MANGLE
.secrel32 int_NAME
.byte 5
.byte 4
.byte 2
.byte 3
_short_START:
.byte 2
.secrel32 s_MANGLE
.secrel32 short_NAME
.byte 5
.byte 2
.byte 2
.byte 7
_char_START:
.byte 2
.secrel32 c_MANGLE
.secrel32 char_NAME
.byte 6
.byte 1
.byte 2
.byte 11
_float_START:
.byte 2
.secrel32 f_MANGLE
.secrel32 float_NAME
.byte 4
.byte 4
.byte 2
.byte 15
_double_START:
.byte 2
.secrel32 d_MANGLE
.secrel32 double_NAME
.byte 4
.byte 8
.byte 2
.byte 20
_long_START:
.byte 2
.secrel32 l_MANGLE
.secrel32 long_NAME
.byte 5
.byte 8
.byte 2
.byte 25
_string_START:
.byte 2
.secrel32 string_MANGLE
.secrel32 string_NAME
.byte 6
.byte 1
.byte 2
.byte 29
_Base_START:
.byte 6
.byte 1
.secrel32 Base_MANGLE
.secrel32 Base_NAME
.byte 4
.byte 1
.byte 3
.byte 3
.byte 0
.secrel32 Type_MANGLE
.secrel32 Type_NAME
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
_Mid_START:
.byte 7
.byte 1
.secrel32 Mid_MANGLE
.secrel32 Mid_NAME
.byte 8
.byte 1
.byte 7
.long _Base_START-Debug_Info_Start
.byte 3
.byte 4
.secrel32 feature_MANGLE
.secrel32 feature_NAME
.byte 1
.byte 9
.long _float_START-Debug_Info_Start
.byte 0
_Top_START:
.byte 7
.byte 1
.secrel32 Top_MANGLE
.secrel32 Top_NAME
.byte 12
.byte 1
.byte 12
.long _Mid_START-Debug_Info_Start
.byte 0
.byte 4
.quad test_all_format_casts_START
.long test_all_format_casts_END-test_all_format_casts_START
.byte 2
.byte 145
.byte 0
.byte 1
.byte 87
.secrel32 test_all_format_casts_MANGLE
.secrel32 test_all_format_casts_NAME
.byte 1
.byte 17
.byte 8
.byte 2
.byte 145
.byte 0
.secrel32 a_MANGLE
.secrel32 a_NAME
.byte 1
.byte 20
.long _float_START-Debug_Info_Start
.byte 8
.byte 2
.byte 145
.byte 0
.secrel32 b_MANGLE
.secrel32 b_NAME
.byte 1
.byte 21
.long _double_START-Debug_Info_Start
.byte 0
.byte 5
.byte 0
.secrel32 this_MANGLE
.secrel32 this_NAME
.byte 1
.byte 3
.long _Base_START-Debug_Info_Start
Debug_Info_End:
.section .debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"
.FILE_NAME:
.asciz "Tests/IO/Cast.e"
.DIRECTORY:
.asciz "Tests/IO/"
i_MANGLE:
.asciz "i"
int_NAME:
.asciz "int"
s_MANGLE:
.asciz "s"
short_NAME:
.asciz "short"
c_MANGLE:
.asciz "c"
char_NAME:
.asciz "char"
f_MANGLE:
.asciz "f"
float_NAME:
.asciz "float"
d_MANGLE:
.asciz "d"
double_NAME:
.asciz "double"
l_MANGLE:
.asciz "l"
long_NAME:
.asciz "long"
string_MANGLE:
.asciz "string"
string_NAME:
.asciz "string"
Base_MANGLE:
.asciz "Base"
Base_NAME:
.asciz "Base"
Type_MANGLE:
.asciz "Type"
Type_NAME:
.asciz "Type"
Mid_MANGLE:
.asciz "Mid"
Mid_NAME:
.asciz "Mid"
feature_MANGLE:
.asciz "feature"
feature_NAME:
.asciz "feature"
Top_MANGLE:
.asciz "Top"
Top_NAME:
.asciz "Top"
test_all_format_casts_MANGLE:
.asciz "test_all_format_casts"
test_all_format_casts_NAME:
.asciz "test_all_format_casts"
i_NAME:
.asciz "i"
a_MANGLE:
.asciz "a"
a_NAME:
.asciz "a"
b_MANGLE:
.asciz "b"
b_NAME:
.asciz "b"
Start_Test_NAME:
.asciz "Start_Test"
m_MANGLE:
.asciz "m"
m_NAME:
.asciz "m"
main_NAME:
.asciz "main"
this_MANGLE:
.asciz "this"
this_NAME:
.asciz "this"
.section .LINE_TABLE
.LINE_TABLE:
