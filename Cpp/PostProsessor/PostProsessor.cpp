#include "../../H/PostProsessor/PostProsessor.h"

void PostProsessor::Factory() {
	Transform_Component_Into_Node();
	for (int i = 0; i < Input.size(); i++)
		Type_Definer(i);
	for (int i = 0; i < Input.size(); i++) {
		Operator_Overload(i);
		Member_Function(i);
		Open_Function_For_Prosessing(i);
		Combine_Conditions(i);
	}
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
	if (Input[i]->Type != CLASS_NODE)
		return;

	//point into the parents defined list not input list
	Node* type = Parent->Find(Input[i]->Name, Parent, true);

	//combine inheritted memebrs
	type->Get_Inheritted_Class_Members();

	//update members sizes
	type->Update_Members_Size();

	//update the member stack offsets
	type->Update_Members_Mem_Offset();

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
	if (Input[i]->is(".") == false)
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

void PostProsessor::Combine_Conditions(int i)
{
	if ((Input[i]->is(IF_NODE)) && (Input[i]->is(WHILE_NODE)))
		return;
	if ((size_t)i + 1 > Input.size() - 1)
		return;
	if (!Input[(size_t)i + 1]->is(ELSE_IF_NODE) && !Input[(size_t)i + 1]->is(ELSE_NODE))
		return;
	//<summary>
	//here we will combine the successor & Predecessor.
	//</sumarry>
	Input[i]->Succsessor = Input[(size_t)i + 1];
	Input.erase(Input.begin() + (size_t)i + 1);
	//update the sucessors Predecessor.
	Input[i]->Succsessor->Predecessor = Input[i];

	return;
}

void PostProsessor::Open_Function_For_Prosessing(int i)
{
	if (!Input[i]->is(FUNCTION_NODE))
		return;
	//here we just go trugh the insides of the function
	//for optimization and other cool stuff :D
	PostProsessor p(Input[i]);
	p.Input = Input[i]->Childs;
	p.Factory();

	return;
}

void PostProsessor::Function_Callation(int i)
{
	if (!Input[i]->is(CALL_NODE))
		return;
	//<summary>
	//this function tryes to find the function to call
	//</summary>
	//first try to find if this fucntion is a virtual function
	Node* defition = Parent->Find(Input[i]->Name, Parent);
	if ((defition != nullptr) && defition->is("ptr")) {
		//now we need to give it the appropriate memory offset-
		//so the virtual function can actually call itself.
		Input[i]->Memory_Offset = defition->Memory_Offset;
		Input[i]->Size = defition->Size;
		Input[i]->Scaler = defition->Scaler;
		Input[i]->Inheritted = defition->Inheritted;
		return;
	}
	//other wise we have normal functions
	//now lets check for template arguments-
	//as parameters on the function this callation calls

	//first make a mangled name outof the caller
	Input[i]->Mangled_Name = Input[i]->Get_Mangled_Name();

	//get the global scop where all the funciton are
	Node* Global_Scope = Parent->Find("GLOBAL_SCOPE", Parent);

	//first ignore the template parameters for now
	for (auto f : Global_Scope->Defined)
		if (f->Mangled_Name == Input[i]->Mangled_Name)
			//we dont need to do enything, everything is fine.
			return;

	Node* OgFunc = nullptr;

	//if the code gets here it means the og-function has template paramters!
	for (auto f : Global_Scope->Defined) {
		for (int p = 0; p < f->Parameters.size(); p++) {
			if (f->Parameters[p]->is("type"))
				continue;		//just ignore the template parameters for now.
			//here we will determine if this function is the og-fucntion or not.
			else if (f->Parameters[p]->Get_Inheritted("") != Input[i]->Parameters[p]->Get_Inheritted("")) {
				goto Next_Function;
			}
		}
		//here if we get this function is the og-function.
		OgFunc = f;
		break;
	Next_Function:
	}

	//now we want to copy that function again but this time we will put the called parameter types
	Node* func = Copy_Node(OgFunc);

	//now we want to through the templates and put on them the right parameter infos
	for (int p = 0; p < func->Parameters.size(); p++) {
		func->Parameters[p]->Inheritted = Input[i]->Parameters[p]->Inheritted;
		//alsoset the defined types into right inheritance.
		func->Find(func->Parameters[p]->Name, func)->Inheritted = Input[i]->Parameters[p]->Inheritted;
	}

	
	//now we want to inject it to global scope to be reached next time.
	Global_Scope->Childs.push_back(func);
	Global_Scope->Defined.push_back(func);

	return;
}

Node* PostProsessor::Copy_Node(Node* What_Node)
{
	//this will only copy the ptrs in list but we want to also copy what those ptr point to.
	Node* Result = new Node(*What_Node);

	//lets start from defined
	for (Node* d : Result->Defined)
		//also define theyre insides
		d = Copy_Node(d);

	for (Node* c : Result->Childs)
		c = Copy_Node(c);

	for (Node* m : Result->Member_Functions)
		m = Copy_Node(m);

	for (Node* o : Result->Operator_Overloads)
		o = Copy_Node(o);

	for (Node* p : Result->Parameters)
		p = Copy_Node(p);

	Result->Left = Copy_Node(Result->Left);
	Result->Right = Copy_Node(Result->Right);

	Result->Succsessor = Copy_Node(Result->Succsessor);
	Result->Predecessor = Copy_Node(Result->Predecessor);

	//now we have copyed every ptr into a new base to point.
	return Result;
}

void PostProsessor::Operator_Overload(int i)
{
	//todo: make the override syntax
}

void PostProsessor::Template_Parameter(int i)
{
}

void PostProsessor::Algebra()
{
}

void PostProsessor::Templates(int i)
{
}