#include "../../H/Back/Generator.h"
#include "../../H/Selector/Selector.h"
extern Selector* S;
extern vector<string> Pre_Defined_Tokens;
extern int _SYSTEM_BIT_TYPE;
bool Double_Tasking = false;

void Generator::Factory()
{
	for (int i = 0; i < Input.size(); i++)
	{
		//Detect_Prefixes(Input.at(i));
		Detect_Pointters(Input.at(i));
		Detect_Address_Pointing(Input.at(i));
		Detect_Condition(Input.at(i));
		Detect_Function(Input.at(i));
		Detect_Operator(Input.at(i));
		Detect_Parenthesis(Input.at(i));
		Detect_Pre_Defined_Tokens(Input.at(i));
	}
}

void Generator::Detect_Function(Token* t)
{
	if (t->Type == "type")
		return;
	if (t->is(_Constructor_))
	{
		//make a label OpC*
		Detect_Prefixes(t);
		IR* ir = new IR;
		ir->ID = "label";
		ir->PreFix = t->Name;
		ir->add(_Start_Of_Label);
		Double_Tasking = false;
		//make the stackfrmae
		if (t->is(_Need_For_Space_))
		{
			Double_Tasking = true;
			//save ebp
			//stack base
			Token* ebp = new Token;
			ebp->Name = "ebp";
			ebp->Size = _SYSTEM_BIT_TYPE;
			ebp->add(_Register_);
			ebp->add(Task_For_Type_Address_Basing);
			//mov ebp, esp
			IR* push = new IR;
			push->ID = "push";
			push->Parameters.push_back(ebp);
			ir->Childs.push_back(push);
			//load the atm stack head
			//stack head
			Token* esp = new Token;
			esp->Name = "esp";
			esp->Size = _SYSTEM_BIT_TYPE;
			esp->add(_Register_);
			esp->add(Task_For_Type_Address);
			//mov ebp, esp
			IR* movebpesp = new IR;
			movebpesp->ID = "ldr";
			movebpesp->Parameters.push_back(ebp);
			movebpesp->Parameters.push_back(esp);
			ir->Childs.push_back(movebpesp);
			if (t->Reservable_Size > 0)
			{
				//make the register
				Token* esp = new Token;
				esp->add(_Register_);
				esp->add(Task_For_Type_Address);
				esp->Name = "reserve memory please!";
				esp->Size = _SYSTEM_BIT_TYPE;
				//make the number to subtract from esp
				Token* num = new Token;
				num->Name = to_string(t->Reservable_Size);
				num->Size = _SYSTEM_BIT_TYPE;
				num->add(_Number_);
				//make the IR token
				IR* space = new IR;
				space->ID = "-";
				space->Parameters.push_back(esp);
				space->Parameters.push_back(num);
				ir->Childs.push_back(space);
			}
		}
		//make the insights of this constructor
		Generator g;
		g.Input.push_back(t->Right_Side_Token);
		g.Types = this->Types;
		g.Factory();
		//get the output as the new IR's childs.
		Append(&ir->Childs, g.Output);
		Output.push_back(ir);
	}
	else if (t->is(_Call_))
	{
		//make a callation OpC*
		IR* ir = new IR;
		ir->ID = "call";
		//when we give the token call, (name) to it and in parser defined as
		//_External_ it can do something like this: call [banana] ; as a global variable.
		ir->Parameters.push_back(t);
		//generate the parameters as IR tokens
		Generator g;
		g.Input.push_back(t->Left_Side_Token);
		g.Types = this->Types;
		g.Factory();
		//get the output from the generator and store then into the parent IR operator.
		//ir->Childs = g.Output;
		//make better reverser so that ur pointter loading wont be also reversed XD!!
		//reverse(g.Output.begin(), g.Output.end());
		Append(&Output, g.Output);
		Output.push_back(ir);
		//handle
		Token* T = new Token;
		T->add(_Register_);
		T->add(Task_For_Returning);
		T->Name = t->Name;
		T->Size = _SYSTEM_BIT_TYPE;
		Handle = T;
		//check if this has init some objects so that we can reserve stack for it.
		if (t->Reservable_Size > 0)
		{
			//make the register
			Token* esp = new Token;
			esp->add(_Register_);
			esp->add(Task_For_Type_Address);
			esp->Name = "reserve memory please!";
			esp->Size = _SYSTEM_BIT_TYPE;
			//make the number to subtract from esp
			Token* num = new Token;
			num->Name = to_string(t->Reservable_Size);
			num->Size = _SYSTEM_BIT_TYPE;
			num->add(_Number_);
			//make the IR token
			IR* space = new IR;
			space->ID = "+";
			space->Parameters.push_back(esp);
			space->Parameters.push_back(num);
			Output.push_back(space);
		}
	}
}

void Generator::Detect_Condition(Token* t)
{
	//if (condition is not what wanted then jump into end of if)
	//(
	//	insides of condition if condition is true
	//)
	//looping condition if loop token
	//end of condition
	if (t->is(_Condition_))
	{
		//make the starting label token as a label pointter.
		IR* Condition = new IR;
		Condition->ID = "label";
		Condition->PreFix = t->Name + to_string(t->ID);
		Condition->add(_Start_Of_Label);
		//make IR tokens for condition.
		Generator g;
		g.Types = this->Types;
		g.Input.clear();
		g.Input.push_back(t->Left_Side_Token);
		g.Factory();
		//the back end for architecture specific allocates-
		//more IR tokens for example "CMP" and for the JMP condition.
		//So this is just a straight line of intermadiate-
		//assembly tokens that we can optimize and affect and etc...
		Condition->Childs = g.Output;
		//Now we need the Insides of the condition to be placed into here:
		g.Input.clear();
		g.Output.clear();
		g.Input.push_back(t->Right_Side_Token);
		g.Factory();
		Append(&Condition->Childs, g.Output);
		//Check if this condition need for repeating itself.
		if (t->Name == "while")
		{
			//this jumps straigt to start of the condition loop
			IR* Loop = new IR;
			Loop->PreFix = "jmp";
			Loop->ID = t->Name + to_string(t->ID);
			Condition->Childs.push_back(Loop);
		}
		//Now we need to make the exit label for the condition.
		IR* Exit_Label = new IR;
		Exit_Label->PreFix = t->Name + to_string(t->ID) + "END";
		Exit_Label->ID = "label";
		Exit_Label->add(_End_Of_Label);
		Condition->Childs.push_back(Exit_Label);
		Output.push_back(Condition);
	}
}

void Generator::Scaler(Token* l, Token* r)
{
	if (l->is(_Number_))
	{
		if (l->Size < r->Size)
		{
			l->Size = r->Size;
		}
	}
	if (r->is(_Number_))
	{
		if (r->Size < l->Size)
		{
			r->Size = l->Size;
		}
	}
}

void Generator::Detect_Operator(Token* t)
{
	if (t->is(_Operator_) != true)
		return;
	if (t->is(_Generated_) == true)
		return;
	t->add(_Generated_);
	// a = a + 1 + a
	// mov eax, [a]
	// cvsi2sd xmm0, eax
	// mov [a], xmm0
	//basic tools:
	if (t->Right_Side_Token->is(_Number_) || t->Left_Side_Token->is(_Number_))
	{
		Scaler(t->Right_Side_Token, t->Left_Side_Token);
	}
	Token* Left_Token = nullptr;
	Token* Right_Token = nullptr;
	bool Normal_Left = false;
	bool Normal_Right = false;
	//now do the same but for right side.
	Generator g;
	g.Input.push_back(t->Right_Side_Token);
	g.Factory();
	//save the information gived by the generator yet again.
	Append(&Output, g.Output);
	//check if right side has more complex instruction.
	if (g.Handle != nullptr)
		Right_Token = g.Handle;
	//if normal right side.
	else
		Normal_Right = true;
	//create a new IR token.
	IR* opCode = new IR;
	opCode->ID = t->Name;
	opCode->add(_Operator_);
	//give the new ir generator the left side of operation.
	g.Output.clear();
	g.Input.clear();
	g.Handle = nullptr;
	g.Input.push_back(t->Left_Side_Token);
	g.Factory();
	//save the information that the new generator gived.
	Append(&Output, g.Output);
	//check if left side holds a more complex instruction for loading into a register.
	if (g.Handle != nullptr)
		Left_Token = g.Handle;
	//if not then probably just a normal number/variable
	else
		Normal_Left = true;
	//check if this is a storing opcode:
	bool Storing = (t->Name == "=" || t->Name == "str");
	//b:0 = a:0
	//lea edi, [(ebp-offset)+ecx*size]
	if (Normal_Left)
	{
		if (Storing)
		{
			Left_Token = t->Left_Side_Token;
		}
		else
		{
			//make a handle register
			Token* Reg = new Token;
			Reg->add(Task_For_General_Purpose);
			Reg->add(_Register_);
			Reg->Name = "Reg1_" + t->Left_Side_Token->Name;
			Reg->Size = t->Left_Side_Token->Size;
			Left_Token = Reg;
			//make the loading IR token
			IR* load = new IR;
			load->ID = "ldr";
			load->Parameters.push_back(Reg);
			load->Parameters.push_back(t->Left_Side_Token);
			Output.push_back(load);
			//more check if the destination is too big for the loaded register, in Emulator
		}
	}
	if (Normal_Right)
	{
		//make a handle register
		Token* Reg = new Token;
		Reg->add(Task_For_General_Purpose);
		Reg->add(_Register_);
		Reg->Name = "Reg2_" + t->Right_Side_Token->Name;
		Reg->Size = t->Right_Side_Token->Size;
		Right_Token = Reg;
		//make the loading IR token
		IR* load = new IR;
		load->ID = "ldr";
		load->Parameters.push_back(Reg);
		load->Parameters.push_back(t->Right_Side_Token);
		Output.push_back(load);
	}
	opCode->Parameters.push_back(Left_Token);
	opCode->Parameters.push_back(Right_Token);
	Handle = Left_Token;
	Output.push_back(opCode);
}

void Generator::Detect_Pointters(Token* t)
{
	if (t->Offsetter == nullptr)
		return;
	if (t->is(_Number_) || t->Offsetter->is(_Number_))
	{
		Scaler(t, t->Offsetter);
	}
	Token* Offsetter = new Token;
	*Offsetter = *t->Offsetter;
	Token* Address = new Token;
	*Address = *t;
	Address->Offsetter = nullptr;
	IR* Load_Token = new IR;
	if (t->is(_Pointting_))
	{
		//make a handle register
		Token* Reg = new Token;
		Reg->add(Task_For_General_Purpose);
		Reg->add(_Register_);
		Reg->Name = "tmp_" + t->Name;
		Reg->Size = t->Size;

		Load_Token->ID = "ldr";
		Load_Token->Parameters.push_back(Reg);
		Load_Token->Parameters.push_back(Address);
		t->Name = Reg->Name;
		t->add(Reg->get());
		t->add(_Pointting_);
		Output.push_back(Load_Token);
	}
	if (Offsetter->is(_Number_) != true)
	{
		Generator g;
		g.Input.push_back(Offsetter);
		g.Factory();
		g.Append(&Output, g.Output);
		IR* Load_Offsetter = new IR;
		if (g.Handle == nullptr)
		{
			//make a handle register
			Token* Reg = new Token;
			Reg->add(Task_For_General_Purpose);
			Reg->add(_Register_);
			Reg->Name = "tmp_" + Offsetter->Name;
			Reg->Size = Offsetter->Size;

			Load_Offsetter->ID = "ldr";
			Load_Offsetter->Parameters.push_back(Reg);
			Load_Offsetter->Parameters.push_back(Offsetter);
			*t->Offsetter = *Reg;
		}
		else
		{
			*t->Offsetter = *g.Handle;
		}
		Output.push_back(Load_Offsetter);
	}
}

void Generator::Detect_Address_Pointing(Token* t)
{
	if (t->is(_Giving_Address_) != true) return;
	//lea eax, [ebp -4 + ecx]
	//eax
	//make a token reg for to handle future of the pointers usage.
	Token* Reg = new Token;
	Reg->Name = t->Name;
	Reg->Size = t->Size;
	Reg->add(Task_For_General_Purpose);
	Reg->add(_Register_);

	IR* lea = new IR;
	lea->ID = ":";
	lea->Parameters.push_back(Reg);
	lea->Parameters.push_back((new Token(*t)));
	*t = *Reg;
	Output.push_back(lea);
}

void Generator::Detect_Parenthesis(Token* t)
{
	if (t->is(_Parenthesis_) && t->Childs.size() > 0)
	{
		Generator g;
		g.Input = t->Childs;
		g.Types = this->Types;
		g.Factory();
		Append(&Output, g.Output);
		if ((t->Childs.size() == 1) && (t->Childs.at(0)->is(_Operator_) == false))
		{
			Handle = t->Childs.at(0);
		}
	}
}

void Generator::Detect_Pre_Defined_Tokens(Token* t)
{
	for (string T : Pre_Defined_Tokens)
	{
		if (t->Type == T)
		{
			IR *ir = new IR;
			ir->ID = T;
			Generator g;
			g.Input.push_back(t->Right_Side_Token);
			g.Factory();
			Append(&Output, g.Output);
			if (g.Handle != nullptr)
			{
				ir->Parameters.push_back(g.Handle);
			}
			else
			{
				ir->Parameters.push_back(t->Right_Side_Token);
			}
			if (Double_Tasking)
				ir->add(_Double_Task_);
			Output.push_back(ir);
			return;
		}
	}
}

void Generator::Detect_Prefixes(Token* t)
{
	if (t->PreFix_Type != "")
	{
		IR* ir = new IR;
		ir->PreFix = t->PreFix_Type;
		ir->ID = t->Name;
		Output.push_back(ir);
	}
}

void Generator::Append(vector<IR*> *Dest, vector<IR*> Source)
{
	for (IR* i : Source)
	{
		Dest->push_back(i);
	}
}
