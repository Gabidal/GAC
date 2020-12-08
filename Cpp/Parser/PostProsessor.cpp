#include "../../H/Parser/PostProsessor.h"
#include "../../H/Docker/Mangler.h"

extern Node* Global_Scope;
long long LNumber = 0;

void PostProsessor::Factory() {
	Transform_Component_Into_Node();
	for (int i = 0; i < Parent->Defined.size(); i++) {
		Type_Definer(i);
	}
	for (int i = 0; i < Parent->Defined.size(); i++) {
		//the prototypes needs the types to have sizes to determine the number parameters assosiative type.
		Handle_Imports(i);
	}
	//Define_Sizes(Parent);
	for (int i = 0; i < Input.size(); i++) {
		Operator_Overload(i);
		Member_Function(i);
		Open_Function_For_Prosessing(i);
		Open_Condition_For_Prosessing(i);
		Open_Loop_For_Prosessing(i);
		//Combine_Conditions(i);
		Combine_Member_Fetching(Input[i]);
		Algebra_Laucher(i);
		Determine_Return_Type(i);
		Determine_Array_Type(i);
		Open_Call_Parameters_For_Prosessing(i);
		Find_Call_Owner(Input[i]);
		Analyze_Global_Variable_Changes(i);
		Change_Local_Strings_To_Global_Pointters(i);
	}
	for (int i = 0; i < Input.size(); i++)
		Combine_Condition(i);
	for (int i = 0; i < Input.size(); i++)
		Move_Global_Varibles_To_Header(i);
}

void PostProsessor::Transform_Component_Into_Node()
{
	//<summary>
	//Extracts the Node ptr's from the component tokens
	//</summary>
	for (auto i : Components) {
		if (i.node == nullptr)
			continue;
		Node* n = i.node;
		Input.push_back(n);
	}
	return;
}

void PostProsessor::Type_Definer(int i)
{
	//<summary>
	//stack type info
	//</summary>
	if (Parent->Defined[i]->Type != CLASS_NODE)
		return;

	//combine inheritted memebrs
	Parent->Defined[i]->Get_Inheritted_Class_Members();

	//update members sizes
	Parent->Defined[i]->Update_Members_Size();

	//update the member stack offsets
	Parent->Defined[i]->Update_Members_Mem_Offset();

	return;
}

void PostProsessor::Member_Function(int i)
{
	//<summary>
	//check if the funciton node has inherittes '.'
	//and sets the function into types function list
	//and changes the parent pointter into the class type
	//</summary>
	if (Input[i]->Type != FUNCTION_NODE)
		return;
	if (Input[i]->is(".") == -1)
		return;

	Node* func = Input[i];
	
	//get the parent type that this member function belong to.
	Node* type = Parent->Find(
		func->Inheritted[
			(size_t)func->is(".") - 1
		], 
		func->Parent
	);

	//for member variables accessing
	func->Parent = type;

	type->Member_Functions.push_back(func);

	return;
}

void PostProsessor::Open_Function_For_Prosessing(int i)
{
	if (!Input[i]->is(FUNCTION_NODE))
		return;
	//here we just go trugh the insides of the function
	//for optimization and other cool stuff :D
	for (auto j : Input[i]->Parameters)
		if (j->is("type") != -1)
			return;

	PostProsessor p(Input[i]);
	p.Input = Input[i]->Childs;

	//preprare the local variables
	p.Define_Sizes(Input[i]);

	p.Factory();

	for (auto& i : Input[i]->Defined)
		Analyze_Variable_Address_Pointing(i);

	return;
}

void PostProsessor::Open_Condition_For_Prosessing(int i)
{
	if (!Input[i]->is(IF_NODE) && !Input[i]->is(ELSE_IF_NODE) && !Input[i]->is(ELSE_NODE))
		return;
	//this add the L number to it
	Input[i]->Name += to_string(LNumber++);

	if (!Input[i]->is(ELSE_NODE)) {
		//here we pass the condition operator into algebra optimizer
		Algebra a(Input[i]);
		a.Input = &Input[i]->Parameters;
		a.Factory();
	}

	//here we now postprosess also the insides of the condition
	PostProsessor p(Input[i]);
	p.Input = Input[i]->Childs;

	//preprare the local variables
	p.Define_Sizes(Input[i]);
	p.Factory();

	return;
}

void PostProsessor::Find_Call_Owner(Node* n)
{
	if (!n->is(CALL_NODE))
		return;
	if (n->Template_Function != nullptr)
		return;
	//<summary>
	//this function tryes to find the function to call
	//</summary>
	//first try to find if this fucntion is a virtual function
	Node* defition = Parent->Find(n->Name, Parent);
	//other wise we have normal functions
	//now lets check for template arguments-
	//as parameters on the function this callation calls

	Node* OgFunc = nullptr;
	//also the returning type of this callation is not made,
	//we can determine it by the operations other side objects type.
	//if the 

	//first ignore the template parameters for now
	for (int f = 0; f < Global_Scope->Defined.size(); f++) {
		if (Global_Scope->Defined[f]->Name != n->Name)
			continue;
		//check for template return types.
		if (!Check_If_Template_Function_Is_Right_One(Global_Scope->Defined[f], n))
			continue;
		int g_i = 0;
		bool Has_Template_Parameters = false;
		for (auto g : Global_Scope->Defined[f]->Parameters) {
			if (g->Is_Template_Object) {
				Has_Template_Parameters = true;
				if (!Check_If_Template_Function_Is_Right_One(g, n->Parameters[g_i]))
					goto Wrong_Template_Function;
				else
					continue;
			}
			else if (g->Get_Inheritted(Global_Scope->Defined[f]->is(IMPORT), true, false) == n->Parameters[g_i]->Get_Inheritted(n->is(IMPORT), true, false))
				continue;
			else
				goto Wrong_Template_Function;

			g_i++;
		}
		if (Has_Template_Parameters && !Global_Scope->Defined[f]->is(IMPORT)) {
			OgFunc = Global_Scope->Defined[f];
			goto Non_Imported_Template_Function_Usage;
		}
		n->Template_Function = Global_Scope->Defined[f];
		return;
		Wrong_Template_Function:;
	}
	Non_Imported_Template_Function_Usage:;
	//if the code gets here it means the og-function has template paramters!
	//and its not external fucntion.
	/*for (auto f : Global_Scope->Defined) {
		if (!f->is(FUNCTION_NODE) && !f->is(PROTOTYPE) && !f->is(IMPORT))
			continue;
		if (n->is("ptr") == -1)
			if (f->Name != n->Name)
				continue;
		bool Direct_Type = false;
		if (f->is(IMPORT))
			Direct_Type = true;
		if (f->Parameters.size() != n->Parameters.size())
			continue;
		if (f->Get_Inheritted("", false, true) != n->Get_Inheritted("", false, true))
			continue;
		for (int p = 0; p < f->Parameters.size(); p++) {
			if (Direct_Type && f->Parameters[p]->Name == "type")
				continue;
			else if (!Direct_Type && f->Parameters[p]->is("type") != -1)
				continue;	//just ignore the template parameters for now.
			//here we will determine if this function is the og-fucntion or not.
			else if (Direct_Type && (f->Parameters[p]->Name != n->Parameters[p]->Get_Inheritted((string)"")))
				goto Next_Function;
			else if (!Direct_Type && f->Parameters[p]->Get_Inheritted("") != n->Parameters[p]->Get_Inheritted("")) {
				goto Next_Function;
			}
		}
		//here if we get this function is the og-function.
		OgFunc = f;
		break;
	Next_Function:;
	}*/

	//this can also mean that the function returns an pointter of somesort!!!
	//if (n->is("ptr") != -1)
	//	return;

	if (OgFunc == nullptr) {
		cout << "Error: Can't find suitable funciton to call " << n->Name << " with parameters:\n";
		for (int j = 0; j < n->Parameters.size(); j++) {
			cout << "  " << n->Parameters[j]->Name << "\n";
		}
		cout << endl;
	}

	if (OgFunc->is(PROTOTYPE))
		for (auto j : OgFunc->Parameters)
			if (j->Name == "type")		//REMEBER THE DIRECT TYPING!!	
				cout << "Error: Can't copy a foreingh function " << OgFunc->Name << "." << endl;

	Node* func = nullptr;
	if (!OgFunc->is(PROTOTYPE)) {
		//now we want to copy that function again but this time we will put the called parameter types
		func = OgFunc->Copy_Node(OgFunc, Parent);

		//now we want to through the templates and put on them the right parameter infos
		for (int p = 0; p < func->Parameters.size(); p++) {
			vector<string> tmp = func->Parameters[p]->Inheritted;
			//update the parent
			func->Parameters[p]->Parent = func;

			func->Parameters[p]->Inheritted = n->Parameters[p]->Inheritted;
			//now iterate the leftover types like ptr
			for (string s : tmp) {
				if (s == "type")
					continue;
				if (func->Parameters[p]->is(s) == -1)
					func->Parameters[p]->Inheritted.push_back(s);
			}
			//alsoset the defined types into right inheritance.
			func->Find(func->Parameters[p]->Name, func)->Inheritted = func->Parameters[p]->Inheritted;
		}
	}
	else {
		func = OgFunc;
	}
	n->Template_Function = func;
	func->Mangled_Name = func->Get_Mangled_Name();
	
	PostProsessor p(func);
	p.Input = func->Childs;
	p.Factory();

	Update_Used_Object_Info(func);

	//now we want to inject it to global scope to be reached next time.
	Global_Scope->Childs.push_back(func);
	Global_Scope->Defined.push_back(func);

	return;
}

void PostProsessor::Open_Call_Parameters_For_Prosessing(int i)
{
	if (!Input[i]->is(CALL_NODE))
		return;

	//give the post prosessor a way to reach the parameters that might have member fetching/ math
	PostProsessor p(Parent, Input[i]->Parameters);
}

void PostProsessor::Algebra_Laucher(int i)
{
	if (!Input[i]->is(FUNCTION_NODE))
		return;
	Algebra a(Input[i]);
	a.Input = &Input[i]->Childs;
	a.Factory();
}

void PostProsessor::Combine_Member_Fetching(Node* n)
{
	if (n->Name != ".")
		return;
	//Remember: Dot is constructed as any normal operator.
	//((((a.b).c[..]).d()).e) = 123
	//We have to go first to the most left sided operator.
	Combine_Member_Fetching(n->Left);
	//set the left side
	Node* Left = Get_From_AST(n->Left);
	//we must also update the current left side to inherit the members from the inherit list
	Left->Get_Inheritted_Class_Members();
	Left->Update_Members_Size();

	//get the left side of the dot operator, this is getted from most left because it can be also an AST.
	Node* Right = n->Get_Most_Left(n->Right);

	if (Right->Name == "size") {
		Node* n = Right->Find("size", Left);
		if (n == nullptr || n->is("const")) {
			//this means it is definetly a size get request
			Right->Name = to_string(Left->Get_Size());
			Right->Type = NUMBER_NODE;
		}
		else
			//load the needed information from the parent
			*Right = *n->Find(Right->Name, Left);
	}
	else
		//load the needed information from the parent
		*Right = *n->Find(Right->Name, Left);

	//set the parent as a fechable
	Right->Fetcher = Left;

	//now remove the current dot operator and replace it with the new fetched member
	*n = *Right;
}

Node* PostProsessor::Get_From_AST(Node* n)
{
	//((((a.b).c[..]).d()).e) = 123
	if (n->is(CONTENT_NODE)) {
		//childs can have only one start node for the AST because that is how math just works :/
		//(a.b + a.c) 
		//				n is parent because of the local scope
		PostProsessor p(n, n->Childs);
		return Get_From_AST(n->Childs[0]);
	}
	else if (n->is(OPERATOR_NODE)) {
		PostProsessor p(Parent, { n });
		return Get_From_AST(n);	//this call the same funciton again because the structure of the AST might have been changed.
	}
	else if (n->is(ARRAY_NODE)) {
		PostProsessor p(Parent, { n });
		return n->Get_Most_Left();
	}
	else if (n->is(CALL_NODE)) {
		PostProsessor p(Parent, n->Parameters);	//prosess the parameters.
		return n;
	}
	else  {
		return n;
	}
}

void PostProsessor::Define_Sizes(Node* p)
{
	//here we set the defined size of the variable
	for (Node* d : p->Defined) {
		d->Update_Members_Size();
		d->Update_Members_Mem_Offset();
	}
}

void PostProsessor::Combine_Condition(int i)
{
	if (!Input[i]->is(IF_NODE))
		return;

	Node* current_condition = Input[i];
	int j;
	//loop through the next nodes if theyre else ifs
	for (j = i + 1; j < Input.size(); j++) {
		if (Input[j]->is(ELSE_IF_NODE) || Input[j]->is(ELSE_NODE)) {
			//give the else if the parent as the if
			Input[j]->Predecessor = current_condition;
			//give the if the child as successor else if
			current_condition->Succsessor = Input[j];
			//give the successor as the current pointter
			current_condition = Input[j];
		}
		else {
			break;
		}
	}

	//now remove the elses
	Input.erase(Input.begin() + i + 1, Input.begin() + j);
}

void PostProsessor::Determine_Return_Type(int i)
{
	if (!Input[i]->is(OPERATOR_NODE) && !Input[i]->is(CONDITION_OPERATOR_NODE) && !Input[i]->is(ASSIGN_OPERATOR_NODE))
		return;

	if (Input[i]->Right->is(CALL_NODE) && MANGLER::Is_Based_On_Base_Type(Input[i]->Right)) {
		PostProsessor l(Parent, vector<Node*>{Input[i]->Left });
		Input[i]->Right->Inheritted = Input[i]->Left->Inheritted;
		PostProsessor r(Parent, vector<Node*>{ Input[i]->Right});
	}
	else if (Input[i]->Left->is(CALL_NODE) && MANGLER::Is_Based_On_Base_Type(Input[i]->Left)) {
		PostProsessor r(Parent, vector<Node*>{ Input[i]->Right});
		Input[i]->Left->Inheritted = Input[i]->Right->Inheritted;
		PostProsessor l(Parent, vector<Node*>{Input[i]->Left });
	}
	else {
		PostProsessor r(Parent, vector<Node*>{ Input[i]->Right, Input[i]->Left });
	}


	//try to find a suitable operator overload if there is one
	for (auto overload : Input[i]->Left->Operator_Overloads) {
		//the syntax still needs to be done!

		//the operator overloads return type is the same as the operator type for this.
		Input[i]->Inheritted = overload->Inheritted;
		return;
	}	

	int Left_Size = 0;
	int Right_Size = 0;

	for (auto j : Input[i]->Left->Get_Inheritted(false, true)) {
		if (Lexer::GetComponents(j)[0].is(Flags::KEYWORD_COMPONENT))
			continue;
		Left_Size += Parent->Find(j, Parent)->Get_Size();
	}	
	for (auto j : Input[i]->Right->Get_Inheritted(false, true)) {
		if (Lexer::GetComponents(j)[0].is(Flags::KEYWORD_COMPONENT))
			continue;
		Right_Size += Parent->Find(j, Parent)->Get_Size();
	}

	if (Left_Size >= Right_Size)
		Input[i]->Inheritted = Input[i]->Left->Inheritted;
	else
		Input[i]->Inheritted = Input[i]->Right->Inheritted;
}

void PostProsessor::Determine_Array_Type(int i)
{
	if (!Input[i]->is(ARRAY_NODE))
		return;

	PostProsessor r(Parent, vector<Node*>{ Input[i]->Right, Input[i]->Left });

	//Who is gay and does not pay taxes also farts in public 
	for (auto overload : Input[i]->Left->Operator_Overloads) {
		//the syntax still needs to be done!

		//the operator overloads return type is the same as the operator type for this.
		Input[i]->Inheritted = overload->Inheritted;
		return;
	}

	//give the type inheritance to this array operator so that the upper function can check the do-ability
	Input[i]->Inheritted = Input[i]->Left->Inheritted;
}

void PostProsessor::Operator_Type_Definer(Node* n)
{
	//go trhough the ast tree
	if (n->is(OPERATOR_NODE)) {
		Operator_Type_Definer(n->Left);
		Operator_Type_Definer(n->Right);
	}
	if (n->is(CONTENT_NODE))
		for (Node* i : n->Childs)
			Operator_Type_Definer(i);

	//now set the values
	if (n->is(OPERATOR_NODE)) {
		n->Inheritted = n->Left->Inheritted;
		if (n->Inheritted.size() == 0)
			//for callation instances
			n->Inheritted = n->Right->Inheritted;
	}
	if (n->is(CONTENT_NODE)) {
		n->Inheritted = n->Childs[0]->Inheritted;
	}
	return;
}

void PostProsessor::Handle_Imports(int i)
{
	if (!Parent->Defined[i]->is(IMPORT))
		return;
	//import func new (4, ABC)
	//all numbers need to be redefined by type size.
	//and all other text is already classes.
	//pointters are inside the parameter as inheritance.
	for (int j = 0; j < Parent->Defined[i]->Parameters.size(); j++) {
		vector<string> Inheritted = Parent->Defined[i]->Parameters[j]->Inheritted;
		if (Parent->Defined[i]->Parameters[j]->is(NUMBER_NODE)) {
			*Parent->Defined[i]->Parameters[j] = *Global_Scope->Find(atoi(Parent->Defined[i]->Parameters[j]->Name.c_str()), Global_Scope, CLASS_NODE);
			Parent->Defined[i]->Parameters[j]->Inheritted.insert(Parent->Defined[i]->Parameters[j]->Inheritted.end(), Inheritted.begin(), Inheritted.end());
		}
		else if (Parent->Defined[i]->Parameters[j]->is(OBJECT_DEFINTION_NODE)) {
			if ((Parent->Defined[i]->Parameters[j]->Name == "type") || Parent->Defined[i]->Parameters[j]->is("type") != -1)
				continue;
			*Parent->Defined[i]->Parameters[j] = *Global_Scope->Find(Parent->Defined[i]->Parameters[j]->Name, Global_Scope, CLASS_NODE);
			Parent->Defined[i]->Parameters[j]->Inheritted.insert(Parent->Defined[i]->Parameters[j]->Inheritted.end(), Inheritted.begin(), Inheritted.end());
		}
	}
	//now all types are good to go.
	//although function calling might get tricky with just types as the parameters.
}

void PostProsessor::Open_Loop_For_Prosessing(int i)
{
	if (!Input[i]->is(WHILE_NODE))
		return;
	//this add the L number to it
	Input[i]->Name += to_string(LNumber++);

	//while (a + 1 < a * 2){..}
	//while (int i = 0, a + i < a * i*2, i++){..}
	//we dont necessarily need to seperate the condition operator.
	Algebra Alg(Input[i]);
	Alg.Input = &Input[i]->Parameters;
	Alg.Factory();

	//now just prosess the child tokens of while node as well.
	PostProsessor post(Input[i]);
	post.Input = Input[i]->Childs;

	//NOTE: this defined sizes might be reduntant!
	post.Define_Sizes(Input[i]);

	//haha brain go brr
	post.Factory();
}

void PostProsessor::Update_Used_Object_Info(Node* n)
{
	if (!n->is(FUNCTION_NODE))
		return;
	for (auto i : n->Get_all(OBJECT_NODE)) {
		i->Inheritted = n->Find(i->Name, i->Parent)->Inheritted;
		i->Update_Members_Size();
	}
	//do the same for parameters
	for (auto i : n->Get_all(PARAMETER_NODE)) {
		i->Inheritted = n->Find(i->Name, i->Parent)->Inheritted;
		i->Update_Members_Size();
	}
}

void PostProsessor::Operator_Overload(int i)
{
	//todo: make the override syntax
}

void PostProsessor::Template_Parameter(int i)
{
}

void PostProsessor::Templates(int i)
{
}

void PostProsessor::Analyze_Variable_Address_Pointing(Node* n)
{
	if (!n->is(OBJECT_DEFINTION_NODE) && !n->is(OBJECT_NODE))
		return;

	//if a variable is pointed to via a pointter or a function parameter address loader, use stack.
	//Other than that use registers.

	for (auto i : n->Parent->Childs) {
		if (i->is(ASSIGN_OPERATOR_NODE)) {
			if (i->Right->Get_Most_Left()->Name == n->Name) {
				int Left = Get_Amount("ptr", i->Left);
				int Right = Get_Amount("ptr", i->Right->Get_Most_Left());
				if (Left > Right)
					//Left is going to load right address.
					n->Requires_Address = true;
			}
		}
		else if (i->is(CALL_NODE)) {
			for (int j = 0; j < i->Parameters.size(); j++) {
				if (i->Parameters[j]->Name == n->Name) {
					int Left = Get_Amount("ptr", i->Template_Function->Parameters[j]);
					int Right = Get_Amount("ptr", i->Parameters[j]);
					if (Left > Right)
						//parameter is going to load right address.
						n->Requires_Address = true;
				}
			}
		}
	}

	if (n->Requires_Address) {
		n->Memory_Offset = n->Parent->Local_Allocation_Soace;
		n->Parent->Local_Allocation_Soace += n->Get_Size();
	}
}

int PostProsessor::Get_Amount(string t, Node* n)
{
	int result = 0;
	for (string s : n->Inheritted)
		if (s == t)
			result++;

	return result;
}

void PostProsessor::Analyze_Global_Variable_Changes(int i)
{
	if (!Input[i]->is(ASSIGN_OPERATOR_NODE))
		return;

	//check if the parent is global scope.
	if (Input[i]->Left->Parent->Name != "GLOBAL_SCOPE")
		return;

	Node* og = Parent->Find(Input[i]->Left->Name);

	if (Parent->Name == "GLOBAL_SCOPE") {
		//We are in global scope area.
		if (!Input[i]->Right->Get_Most_Left()->is(NUMBER_NODE) && !Input[i]->Right->Get_Most_Left()->is(STRING_NODE)) {
			Node* Right = Parent->Find(Input[i]->Right->Get_Most_Left()->Name);
			if (Right->is("const") == -1)
				if (og->is("const") != -1) {
					og->Inheritted.erase(og->Inheritted.begin() + og->is("const"));
				}
		}
	}
	else {
		//we are in a fucntion of some sort.
		//if this is the case the global variable cannot be a constant anymore.
		if (og->is("const") != -1) {
			og->Inheritted.erase(og->Inheritted.begin() + og->is("const"));
		}
	}
}

void PostProsessor::Change_Local_Strings_To_Global_Pointters(int i)
{
	if (!Input[i]->is(STRING_NODE))
		return;
	if (Parent->Name == "GLOBAL_SCOPE")
		return;
	//a = "123" to a = S0
	int Current_S_Count = 0;
	for (auto c : Global_Scope->Defined) {
		if (!c->is(LABEL_NODE))
			continue;
		Current_S_Count++;
		if (c->String == Input[i]->Name) {
			*Input[i] = *c;
			if (Input[i]->is("ptr") == -1)
				Input[i]->Inheritted.push_back("ptr");
			return;
		}
	}
	//if there is no string Sx make a new one.
	Node* s = new Node(LABEL_NODE);
	s->String = Input[i]->Name;
	s->Name = "S" + to_string(Current_S_Count);
	s->Inheritted = { Global_Scope->Find(1, Global_Scope, CLASS_NODE)->Name };
	if (s->is("ptr") == -1)
		s->Inheritted.push_back("ptr");
	s->Parent = Global_Scope;

	Node* init = new Node(ASSIGN_OPERATOR_NODE);
	init->Name = "=";
	init->Parent = Global_Scope;

	Node* value = new Node(STRING_NODE);
	value->Name = s->String;
	value->Parent = Global_Scope;
	value->Size = 1;	//byte

	init->Left = s;
	init->Right = value;

	Global_Scope->Header.push_back(init);
	Global_Scope->Defined.push_back(s);

	Change_Local_Strings_To_Global_Pointters(i);
}

void PostProsessor::Move_Global_Varibles_To_Header(int i)
{
	if (!Input[i]->is(ASSIGN_OPERATOR_NODE))
		return;
	if (Parent->Name != "GLOBAL_SCOPE")
		return;

	Parent->Find(Input[i]->Left->Name)->Type = OBJECT_NODE;

	Global_Scope->Header.push_back(Input[i]);

	Input.erase(Input.begin() + i);

	Move_Global_Varibles_To_Header(i);
}

bool PostProsessor::Check_If_Template_Function_Is_Right_One(Node* t, Node* c)
{
	//t = template
	//c = call
	//how many times we can skip a type
	int Type_Amount = Get_Amount("type", t);

	for (auto i : c->Inheritted) {
		if (Lexer::GetComponents(i)[0].is(Flags::KEYWORD_COMPONENT)) {
			if (t->is(i) == -1) {
				return false;	//teplate function must contain same keywords.
			}
		}
		else if (t->is(i) == -1) {
			if (Type_Amount > 0) {
				Type_Amount--;
				continue;
			}
			else
				return false;
		}
	}
	return true;
}
