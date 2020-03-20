#ifndef _USR_H_
#define _USR_H_
#include <vector>
#include <string>
#include <map>
using namespace std;


class Symbol_Table {
public:
	virtual map<string, Symbol_Table*> Get_Member_Pointter() = 0;
	virtual map<string, void*> Get_Member_Data() = 0;
};

class output : public Symbol_Table {
public:
	map<string, Symbol_Table*> Get_Member_Pointter();
	map<string, void*> Get_Member_Data();
	string Source_File;
	string Destination_File;
	string OS;
	string Architecture;
	string Obj_Type;
	int Bits_Mode = 4;
};

class Usr
{
public:
	output Info;
	Usr(char** in, int count)
	{
		Input = in;
		Argument_Amount = count;
		Create_Argument_Stats();
	}

	~Usr(){}

private:
	char** Input;
	int Argument_Amount;
	void Create_Argument_Stats();
	void Find_Source_File(int i);
	void Find_Destination_File(int i);
	void Find_OS(int i);
	void Find_Architecture(int i);
	void Find_Bits_Mode(int i);
	void Find_Obj_Type(int i);
};


#endif