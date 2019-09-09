#ifndef _ASMTOOLS_H_
#define _ASMTOOLS_H_

#include <vector>
using namespace std;

#include "Token.h"

void initialize(vector <Token> &Tokens, string &buffer)
{
    buffer +=
    "\nfunction_size:\n"
    "  pop ebx\n"
    "  pop edx\n"
    "  xor eax, eax\n"
    "  jmp check\n"
    "  top:\n"
    "  inc edx\n"
    "  inc eax\n"
    "  check:\n"
    "  cmp byte [edx], 0\n"
    "  jnz top\n"
    "  push eax\n"
    "  push ebx\n"
    "ret\n\n"
    ;
    Token sizer;
    sizer.makeFunc("size");
    sizer.makePublic();
    sizer.ParameterAmount = 1;
    sizer.makeReturnable();
    Tokens.push_back(sizer);


    buffer += 
    "function_malloc:\n"
    "  push dword 0\n"
    "  push dword -1\n"
    "  push dword 0x22\n" //0x22 == heap
    "  push dword 0x03\n"
    "  push dword [esp+16]\n"
    "  push dword 0\n"
    "  mov eax, 0x5a\n"
    "  mov ebx, esp\n"
    "  int 0x80\n"
    "  add esp, 24\n"
    "  pop ebx\n"
    "  push eax\n"
    "jmp ebx\n\n"
    ;
    Token alloc;
    alloc.makeFunc("malloc");
    alloc.makePublic();
    alloc.ParameterAmount = 1;
    alloc.makeReturnable();
    Tokens.push_back(alloc);

    buffer += 
    "function_char:\n"
    "  pop edx\n"
    "  pop eax\n"
    "  mov ecx, 48\n"
    "  add eax, ecx\n"
    "  push eax\n"
    "  jmp edx\n"
    ;
    Token toChar;
    toChar.makeFunc("char");
    toChar.makePublic();
    toChar.ParameterAmount = 1;
    toChar.makeReturnable();
    Tokens.push_back(toChar);

}


#endif