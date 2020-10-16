#ifndef _X86_H_
#define _X86_H_

#include <vector>
#include <string>
#include <map>

using namespace std;

#include "../Nodes/Token.h"
#include "../Nodes/IR.h"
#include "../Flags.h"

namespace x86_64_Win {
	int SIZE;
	vector<Token*> Registers;
	vector<Token*> Parameter_Registers;
	vector<IR*> Opcodes;


	string Seperator = ",";
	string Register_Pre_Fix = "";
	string Number_Pre_Fix = "";
	string Label_Post_Fix = ":";
	void Init();
}

#endif