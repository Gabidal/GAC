#include "../../H/UI/Usr.h"
#include <cstring>
#include <iostream>
#include <optional>

void Symbol_Table::Load()
{
	Member_Pointters = Get_Member_Pointters();
	Member_Data = Get_Member_Data();
	for (auto p : Member_Pointters) {
		p.second->Load();
	}
}

Symbol_Table::Symbol_Table() {
}

Symbol_Table* Symbol_Table::Get_Member_Pointter(string key) {
	auto i = Member_Pointters.find(key);
	if (i == Member_Pointters.end())
		return nullptr;
	return i->second;
}

Waiter* Symbol_Table::Get_Member_Data(string key) {
	auto i = Member_Data.find(key);
	if (i == Member_Data.end())
		return nullptr;
	return i->second;
}

map<string, Symbol_Table*> Usr::Get_Member_Pointters()
{
	/*
	output Info;
	*/
	return {
		std::make_pair(string("Info"), &Info)
	};
}

map<string, Waiter*> Usr::Get_Member_Data()
{
	return map<string, Waiter*>();
}

//main -in ~/test.g -out ~/test.asm -os win32 -arch x86 -mode 32
void Usr::Create_Argument_Stats()
{
	for (int i = 1; i < Argument_Amount; i++) {
		Find_Destination_File(i);
		Find_Source_File(i);
		Find_OS(i);
		Find_Architecture(i);
		Find_Bits_Mode(i);
	}
}

void Usr::Find_Source_File(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-in") == 0)
	{
		Info.Source_File = Input[i + 1];
		i++;
	}
}

void Usr::Find_Destination_File(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-out") == 0)
	{
		Info.Destination_File = Input[i + 1];
		i++;
	}
}

void Usr::Find_OS(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-os") == 0)
	{
		Info.OS = Input[i + 1];
		i++;
	}
}

void Usr::Find_Architecture(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-arch") == 0)
	{
		Info.Architecture = Input[i + 1];
		i++;
	}
}

void Usr::Find_Bits_Mode(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-mode") == 0)
	{
		Info.Bits_Mode = Input[i + 1];
		i++;
	}
}

void Usr::Find_Obj_Type(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-lib") == 0)
	{
		string tmp = string(Input[i + 1]);
		Info.Obj_Type = atoi(tmp.c_str());
		i++;
	}
}

map<string, Symbol_Table*> output::Get_Member_Pointters() {
	return std::map<string, Symbol_Table*>();
}

map<string, Waiter*> output::Get_Member_Data(){
	/*string Source_File;
	string Destination_File;
	string OS;
	string Architecture;
	string Obj_Type;
	int Bits_Mode = 4;*/
	return {
		std::make_pair(string("Source_File"), new Waiter(&Source_File)),
		std::make_pair(string("Destination_File"), new Waiter(&Destination_File)),
		std::make_pair(string("OS"),new Waiter(&OS)),
		std::make_pair(string("Architecture"),new Waiter(&Architecture)),
		std::make_pair(string("Obj_Type"), new Waiter(&Obj_Type)),
		std::make_pair(string("Bits_Mode"), new Waiter(&Bits_Mode))
	};
}

map<string, Symbol_Table*> SymbolTableList::Get_Member_Pointters()
{
	return map<string, Symbol_Table*>();
}

map<string, Waiter*> SymbolTableList::Get_Member_Data()
{
	return map<string, Waiter*>();
}

bool is_number(const string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

optional<int> If_Int(string s) {
	if (is_number(s))
	{
		return optional<int> {
			atoi(s.c_str())
		};
	}
	return nullopt;
}

Symbol_Table* SymbolTableList::Get_Member_Pointter(string index)
{
	if (auto i = If_Int(index))
	{
		return Items.at(i.value);
	}
	else
	{
		//if constant
	}
	
	throw runtime_error("k Boomer!");
}

Waiter* SymbolTableList::Get_Member_Data(string key)
{
	cout << "Ya mama suck!" << endl;
	return nullptr;
}
