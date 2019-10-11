#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <string>
#include <vector>
#include "Register.h"

using namespace std;

//creators
#define KeyWord (1<<0)
#define Public (1<<1)
#define Member (1<<2)
#define Useful (1<<3)
#define Real (1<<4)
#define Func (1<<6)
#define Macro (1<<7)
#define Type (1<<8)
#define Define (1<<9)
//Variables
#define Number (1<<10)
#define Ptr (1<<11)
#define Var (1<<12)
#define Array (1<<13)
#define Equ (1<<14)
//Logical
#define If (1<<15)
#define Else (1<<16)
#define While (1<<17)
#define Returning (1<<18)
//Arithmetic
#define Math (1<<19)

//Personan
#define Registered (1<<20)
#define Stacked (1<<21)
#define Stored (1<<22)
#define Original (1<<23)
#define Parameter (1<<24)
#define Prototype (1<<25)
#define Private (1<<26)

class Token
{
 public:
    int Flags = 0;
    int Size = 0;
    int Value = 0;
    int StackOffset = 0;
    int ParameterCount = 0;
    int AddedOffset = 0;
    Token *ParentType;
    Token *ParentFunc;
    string Name = "";
    Register Reg;

    vector <Token> Childs;

    bool is(int flag);
    string getFullName();
    Register getNewRegister();
    string getReg();
};


#endif