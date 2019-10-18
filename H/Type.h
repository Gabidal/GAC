#ifndef _TYPE_H_
#define _TYPE_H_
#include "Token.h"
#include "Func.h"
#include "Assembly_Definitions.h"

class Type : public Father
{
  public:
    bool initted = false;
    vector<Token*> Functions;
    void addFunc(Func *func);
    void InitType(string &output);
};


#endif
