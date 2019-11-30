#ifndef _OPTIMIZER_H_
#define _OPTiMIZER_H_

#include "../Back/Token.h"
#include <vector>
#include <string>
#include "../Linux/Linux.h"

class Optimizer
{
private:
    /* data */
    //this class job is to search for those variables witch are used and mark em flags 'Used'
public:
    vector<Token*> Global; //the output
    vector<Token*> Input; //direct connect to the original tokens.
    bool Priority_For_Return = false;
    int Find(string name, int flag, vector<Token*> list);
    Token *GetAbsoluteDestination(Token *t);
    int GetSecondaryDestination(vector<Token*> t);
    void GetReturningToken(int i);
    void Factory();
    void Optimize_Sys_Functions(Token *t);
    void Optimize_Functions(int i);
    void Optimize_Types(int i);
    void Optimize_Condition_Variebles(Token *&T);
    void Optimize_Conditions(int i);
    void Optimize_Math(vector<Token*> &T);
    void Optimize_Variables(int i);
    void Optimize_Returning(int i);
    void Optimize_Function_Calls(int i);
    void Set_All_References(string name, int Flag, vector<Token*> &T);
    Optimizer(vector<Token*> &In)
    {
        Input = In;
    }
    ~Optimizer(){}
    Optimizer(Optimizer & other)
    {
        Global.insert(Global.end(), other.Global.begin(), other.Global.end());
        Global.insert(Global.end(), other.Input.begin(), other.Input.end());
        Input = other.Input;
        Priority_For_Return = other.Priority_For_Return;
    }
};



#endif