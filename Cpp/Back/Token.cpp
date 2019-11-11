
#include <string>
#include "../../H/Back/Token.h"
#include "../../H/Back/Register.h"
#include "../../H/Back/Assembly_Definitions.h"
using namespace std;

int RegisterTurn = 0;

bool Token::is(int flag)
{
    return (Flags & flag) == flag;
}

string Token::getFullName()
{
    string name;
    
    if (is(Public))
    {
        name = Name;
    }
    else
    {
        if (is(Parameter))
        {
            name = EBP->Name + OFFSET + to_string(StackOffset);
        }
        else
        {
            name = EBP->Name + DEOFFSET + to_string(StackOffset);
        }
    }
    return name;
}

Register *Token::getNewRegister()
{
    if (RegisterTurn == 0)
    {
        return EAX;
        RegisterTurn = 1;
    }
    else if (RegisterTurn == 1)
    {
        return EBX;
        RegisterTurn = 2;
    }
    else if (RegisterTurn == 2)
    {
        return ECX;
        RegisterTurn = 3;
    }
    else if (RegisterTurn == 3)
    {
        return EDX;
        RegisterTurn = 4;
    }
    else if (RegisterTurn == 4)
    {
        return ESI;
        RegisterTurn = 5;
    }
    else if (RegisterTurn == 5)
    {
        return EDI;
        RegisterTurn = 0;
    }
    return NUL;
}

Register *Token::getReg()
{
    if (Reg->Name == "null")
    {
        this->Reg = getNewRegister();
    }
    return Reg;
}

string Token::InitVariable()
{
    string result = "";
    if (_NULL(this->Reg->Name))
    {

        if (this->is(Member))
        {
            Register *ParentReg = this->ParentFunc->Reg;
            if (_NULL(ParentReg->Name))
            {
                //allocate new Register for class address place holding.
                this->ParentFunc->Reg = this->getReg();
                output += MOV + ParentReg->Name + FROM + FRAME(ParentType->getFullName()) + NL;
            }
            output += MOV + this->Reg->Name + FROM + DWORD + FRAME(ParentReg->Name + OFFSET + to_string(this->StackOffset)) + NL;
        }
        else if (this->is(Public))
        {
            output += MOV + this->Reg->Name + FROM + DWORD + FRAME(this->getFullName()) + NL;
        }
        else if (this->is(Equ))
        {
            output += MOV + this->Reg->Name + FROM + this->getFullName() + NL;
        }
        result = this->Reg->Name;
    }
    else
    {
        result = this->Reg->Name;
    }
    return result;
}

string Token::MOVE(Token *Source)
{
    output += MOV + this->InitVariable() + FROM + Source->InitVariable();
    return this->Reg->Name;
}

string Token::SUM(Token *Source)
{
    output += ADD + this->InitVariable() + FROM + Source->InitVariable();
    return this->Reg->Name;
}

string Token::SUBSTRACT(Token *Source)
{
    output += SUB + this->InitVariable() + FROM + Source->InitVariable();
    return this->Reg->Name;
}

string Token::MULTIPLY(Token *Source)
{
    output += IMUL + this->InitVariable() + FROM + Source->InitVariable();
    return this->Reg->Name;
}

string Token::DIVIDE(Token *Source)
{
    output += IDIV + this->InitVariable() + FROM + Source->InitVariable();
    return this->Reg->Name;
}

string Token::COMPARE(Token *Source)
{
    output += CMP + this->InitVariable() + FROM + Source->InitVariable();
    return this->Reg->Name;
}

string Token::MOVEINSTACK()
{
    output += PUSH(this->getFullName());
    return this->getReg()->Name;
}

void Token::addChild(Token local) 
{
    Childs.push_back(local);
    local.ParentFunc = this;
    local.StackOffset = this->StackOffset;
    this->StackOffset += local.Size;
    this->Size += local.Size;
	local.Flags |= Private;
}

void Token::addParameter(Token Param)
{
    Parameters.push_back(Param);
    Param.ParameterOffset = this->ParameterOffset;
    this->ParameterOffset += Param.Size;
}

void Token::InitFunction()
{
    if (is(Member))
    {
        output += LABEL(TYPE(ParentType->Name, FUNC(this->Name)));
    }
    else
    {
        output += LABEL(FUNC(this->Name));
    }
}

void Token::addFunc(Token func)
{
    func.ParentType = this;
    Functions.push_back(func);
}

void Token::InitType()
{
    if (initted)
    {
        return;
    }
    for (Token t : Childs)
    {
        if (t.is(Used) != true)
        {
            output += COMMENT("Variable not used!");
        }
        else
        { 
            output += MOV + FRAME(t.getFullName()) + FROM + to_string(t.Value) + NL;
        }
    }
}

Token &Token::operator=(const Token& name)
{
    Flags = name.Flags;
    Size = name.Size;
    Value = name.Value;
    StackOffset = name.StackOffset;
    ParameterCount = name.ParameterCount;
    AddedOffset = name.AddedOffset;
    ParameterOffset = name.ParameterOffset;
    ID = name.ID;
    Offsetter = name.Offsetter;
    ParentType = name.ParentType;
    ParentFunc = name.ParentFunc;
    Parameters = name.Parameters;
    Childs = name.Childs;
    Name = name.Name;
    Reg = name.Reg;
    output = name.output;
    initted = name.initted;
    Origin = name.Origin;
    Functions = name.Functions;
    return *this;
}