#include "../../H/BackEnd/x86.h"

void x86_64_Win::Init()
{
	size = 8;	//64 bit arch

	Seperator = ",";
	Register_Pre_Fix = "";
	Number_Pre_Fix = "";
	Label_Post_Fix = ":";

	Token* AL = new Token(TOKEN::RETURNING, "al", 1, {});
	Token* AH = new Token(TOKEN::RETURNING, "ah", 1, {});
	Token* AX = new Token(TOKEN::RETURNING, "ax", 2, { AH, AL });
	Token* EAX = new Token(TOKEN::RETURNING, "eax", 4, { AX });
	Token* RAX = new Token(TOKEN::RETURNING, "rax", 8, { EAX });

	Token* BL = new Token(TOKEN::NONVOLATILE, "bl", 1, {});
	Token* BH = new Token(TOKEN::NONVOLATILE, "bh", 1, {});
	Token* BX = new Token(TOKEN::NONVOLATILE, "bx", 2, { BH, BL });
	Token* EBX = new Token(TOKEN::NONVOLATILE, "ebx", 4, { BX });
	Token* RBX = new Token(TOKEN::NONVOLATILE, "rbx", 8, { EBX });

	Token* CL = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "cl", 1, {});
	Token* CH = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "ch", 1, {});
	Token* CX = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "cx", 2, { CH, CL });
	Token* ECX = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "ecx", 4, { CX });
	Token* RCX = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "rcx", 8, { ECX});

	Token* DL = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "dl", 1, {});
	Token* DH = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "dh", 1, {});
	Token* DX = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "dx", 2, { DH, DL });
	Token* EDX = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "edx", 4, { DX });
	Token* RDX = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "rdx", 8, { EDX });

	Token* DIL = new Token(TOKEN::NONVOLATILE, "dil", 1, {});
	//Token* DIH = new Token(TOKEN::NONVOLATILE, "dih", 1, {});
	Token* DI = new Token(TOKEN::NONVOLATILE , "di", 2, {DIL });
	Token* EDI = new Token(TOKEN::NONVOLATILE, "edi", 4, { DI });
	Token* RDI = new Token(TOKEN::NONVOLATILE, "rdi", 8, { EDI });

	Token* SIL = new Token(TOKEN::NONVOLATILE, "sil", 1, {});
	//Token* SIH = new Token(TOKEN::NONVOLATILE, "sih", 1, {});
	Token* SI = new Token(TOKEN::NONVOLATILE , "si", 2, {SIL });
	Token* ESI = new Token(TOKEN::NONVOLATILE, "esi", 4, { SI });
	Token* RSI = new Token(TOKEN::NONVOLATILE, "rsi", 8, { ESI });


	Token* BPL = new Token(TOKEN::VOLATILE, "bpl", 1, {});
	Token* BP = new Token(TOKEN::VOLATILE, "bp", 2, { BPL });
	Token* EBP = new Token(TOKEN::VOLATILE, "ebp", 4, { BP });
	Token* RBP = new Token(TOKEN::VOLATILE, "rbp", 8, { EBP });

	Token* SPL = new Token(TOKEN::STACK_POINTTER, "spl", 1, {});
	Token* SP = new Token(TOKEN::STACK_POINTTER, "sp", 2, { SPL });
	Token* ESP = new Token(TOKEN::STACK_POINTTER, "esp", 4, { SP });
	Token* RSP = new Token(TOKEN::STACK_POINTTER, "rsp", 8, { ESP });

	Token* XMM0 = new Token(TOKEN::VOLATILE  | TOKEN::RETURNING | TOKEN::PARAMETER | TOKEN::DECIMAL, "xmm0", 12, {});
	Token* XMM1 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL, "xmm1", 12, {});
	Token* XMM2 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL, "xmm2", 12, {});
	Token* XMM3 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL, "xmm3", 12, {});
	Token* XMM4 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm4", 12, {});
	Token* XMM5 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm5", 12, {});
	Token* XMM6 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm6", 12, {});
	Token* XMM7 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm7", 12, {});
	Token* XMM8 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm8", 12, {});
	Token* XMM9 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm9", 12, {});
	Token* XMM10 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xm10", 12, {});
	Token* XMM11 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm11", 12, {});
	Token* XMM12 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm12", 12, {});
	Token* XMM13 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm13", 12, {});
	Token* XMM14 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm14", 12, {});
	Token* XMM15 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm15", 12, {});

	Token* R8B = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "r8b", 1, {});
	Token* R8W = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "r8w", 2, { R8B });
	Token* R8D = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "r8d", 4, { R8W });
	Token* R8 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "r8", 8, { R8D });

	Token* R9B = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "r9b", 1, {});
	Token* R9W = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "r9w", 2, { R9B });
	Token* R9D = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "r9d", 4, { R9W });
	Token* R9 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "r9", 8, { R9D });

	Token* R10B = new Token(TOKEN::VOLATILE, "r10b", 1, {});
	Token* R10W = new Token(TOKEN::VOLATILE, "r10w", 2, { R10B });
	Token* R10D = new Token(TOKEN::VOLATILE, "r10d", 4, { R10W });
	Token* R10 = new Token(TOKEN::VOLATILE , "r10", 8, { R10D });

	Token* R11B = new Token(TOKEN::VOLATILE, "r11b", 1, {});
	Token* R11W = new Token(TOKEN::VOLATILE, "r11w", 2, { R11B });
	Token* R11D = new Token(TOKEN::VOLATILE, "r11d", 4, { R11W });
	Token* R11 = new Token(TOKEN::VOLATILE , "r11", 8, { R11D });

	Token* R12B = new Token(TOKEN::NONVOLATILE, "r12b", 1, {});
	Token* R12W = new Token(TOKEN::NONVOLATILE, "r12w", 2, { R12B });
	Token* R12D = new Token(TOKEN::NONVOLATILE, "r12d", 4, { R12W });
	Token* R12 = new Token(TOKEN::NONVOLATILE , "r12", 8, { R12D });

	Token* R13B = new Token(TOKEN::NONVOLATILE, "r13b", 1, {});
	Token* R13W = new Token(TOKEN::NONVOLATILE, "r13w", 2, { R13B });
	Token* R13D = new Token(TOKEN::NONVOLATILE, "r13d", 4, { R13W });
	Token* R13 = new Token(TOKEN::NONVOLATILE , "r13", 8, { R13D });

	Token* R14B = new Token(TOKEN::NONVOLATILE, "r14b", 1, {});
	Token* R14W = new Token(TOKEN::NONVOLATILE, "r14w", 2, { R14B });
	Token* R14D = new Token(TOKEN::NONVOLATILE, "r14d", 4, { R14W });
	Token* R14 = new Token(TOKEN::NONVOLATILE , "r14", 8, { R14D });

	Token* R15B = new Token(TOKEN::NONVOLATILE, "r15b", 1, {});
	Token* R15W = new Token(TOKEN::NONVOLATILE, "r15w", 2, { R15B });
	Token* R15D = new Token(TOKEN::NONVOLATILE, "r15d", 4, { R15W });
	Token* R15 = new Token(TOKEN::NONVOLATILE , "r15", 8, { R15D });


	Parameter_Registers = { RCX, RDX, R8, R9, XMM0, XMM1, XMM2, XMM3 };
	Registers = { 
		RAX, EAX, AX, AH, AL,
		RBX, EBX, BX, BH, BL,
		RCX, ECX, CX, CH, CL,
		RDX, EDX, DX, DH, DL,
		RDI, EDI, DI, DIL,
		RSI, ESI, SI, SIL,
		RBP, EBP, BP,
		RSP, ESP, SP,
		XMM0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6, XMM7, XMM8, XMM9, XMM10, XMM11, XMM12, XMM13, XMM14, XMM15,
		R8, R8B, R8D, R8W,
		R9, R9B, R9D, R9W,
		R10, R10B, R10D, R10W,
		R11, R11B, R12D, R12W,
		R12, R12B, R12D, R12W,
		R13, R13B, R13D, R13W,
		R14, R14B, R14D, R14W,
		R15, R15B, R15D, R15W,
	};
	using namespace TOKEN;
	Token* Register = new Token(REGISTER | NONVOLATILE | VOLATILE | RETURNING | QUOTIENT | REMAINDER);
	Token* Scalar = new Token(NUM, {
		new Token(NUM, "1"),
		new Token(NUM, "2"),
		new Token(NUM, "4"),
		new Token(NUM, "8")
		}, "scaler");	
	Token* Const = new Token(NUM, "const");
	Token* Memory = new Token(MEMORY, {
			{ new Token(REGISTER), 2},
			{ new Token(SCALER | ALL_ARGS_SAME_SIZE, {
				{{Register, {1, 8}}, {Scalar, {1, 8}}},
				{{Scalar, {1, 8}}, {Register, {1, 8}}},
				{{Scalar, {1, 8}}, {Scalar, {1, 8}}}
				}), 1},
			{ new Token(OFFSETTER | ALL_ARGS_SAME_SIZE, {
				{{Register, {1, 8}}, {Register, {1, 8}}},
				{{Register, {1, 8}}, {Const, {1, 8}}},
				{{Const, {1, 8}}, {Register, {1, 8}}},
				{{Const, {1, 8}}, {Const, {1, 8}}},
				}), INT32_MAX},
			{ new Token(DEOFFSETTER | ALL_ARGS_SAME_SIZE, {
				{{Register, {1, 8}}, {Register, {1, 8}}},
				{{Register, {1, 8}}, {Const, {1, 8}}},
				{{Const, {1, 8}}, {Register, {1, 8}}},
				{{Const, {1, 8}}, {Const, {1, 8}}},
				}), INT32_MAX}
		}, "memory");
	Token* Label = new Token(LABEL, "label");

	Utility = {
		Register,
		Scalar,
		Const,
		Memory,
		Label
	};

	Token* BYTE = new Token(SIZE_INDENTIFIER, "byte", 1);
	Token* WORD = new Token(SIZE_INDENTIFIER, "word", 2);
	Token* DWORD = new Token(SIZE_INDENTIFIER, "dword", 4);
	Token* QWORD = new Token(SIZE_INDENTIFIER, "qword", 8);

	Size_Identifiers = {
		BYTE,
		WORD,
		DWORD,
		QWORD
	};

	//2reg, 1mul, inf*const, inf*operator
	//*(reg, const) | *(const, const) | *(const, reg)
	//+-(reg, reg) | +-(reg, const) | +-(const, reg) | +-(const, const)
	
	IR* MOV = new IR("move", new Token(OPERATOR, "mov"), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} }
		});

	IR* SET = new IR("=", new Token(OPERATOR, "mov"), {
			{{Register, {1, 8}}, {Memory, {1, 8}} },
			{{Memory, {1, 8}}, {Register, {1, 8}} },
			{{Register, {1, 8}}, {Register, {1, 8}} },
			{{Register, {1, 8}}, {Const, {1, 8}} },
			{{Memory, {1, 8}}, {Const, {1, 8}} }
		});

	IR* LEA = new IR("evaluate", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "lea"), {
		{ {Register, { 1, 8 }}, { Memory, {1, 8} } }
		});

	IR* ADD = new IR("+", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "add"), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} }
		});

	IR* SUB = new IR("-", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "sub"), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} }
		});

	IR* MUL = new IR("*", new Token(OPERATOR), vector<IR*>{
		new IR("move", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "mov"), {
			{ {new Token(QUOTIENT), { 1, 8 }}, { Register, {1, 8} } },
			{ {new Token(QUOTIENT), {1, 8}}, {Const, {1, 8}} },
			{ {new Token(QUOTIENT), {1, 8}}, {Memory, {1, 8}} },	//mov from register into a remainder like eax the other value for the mul
		}),
		new IR("mul", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "mul"), {
			{ {Register, { 1, 8 }}},
			{ {Memory, { 1, 8 }}},		//give mul the other value
		}),
		new IR("move", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "mov"), {
			{ {Memory, { 1, 8 }}, { new Token(QUOTIENT), {1, 8} } },
			{ {Register, { 1, 8 }}, { new Token(QUOTIENT), {1, 8} } }
		})
	});

	IR* DIV = new IR("/", new Token(OPERATOR), vector<IR*>{
		new IR("move", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "mov"), {
			REMAINDER, new Token(NUM, "0")
			}), 
		new IR("move", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "mov"), {
			{ {new Token(QUOTIENT), { 1, 8 }}, { Register, {1, 8} } },
			{ {new Token(QUOTIENT), {1, 8}}, {Const, {1, 8}} },
			{ {new Token(QUOTIENT), {1, 8}}, {Memory, {1, 8}} },	//mov from register into a remainder like eax the other value for the mul
			}),
		new IR("div", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "div"), {
			{ {Register, { 1, 8 }}},
			{ {Memory, { 1, 8 }}},		//give mul the other value
			}),
		new IR("move", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "mov"), {
			{ {Memory, { 1, 8 }}, { new Token(QUOTIENT), {1, 8} } },
			{ {Register, { 1, 8 }}, { new Token(QUOTIENT), {1, 8} } }
			})
	});

	IR* CMP = new IR("compare", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "cmp"), {
		{{Register, {1, 8}}, {Register, {1, 8}}},
		{{Register, {1, 8}}, {Memory, {1, 8}}},
		{{Memory, {1, 8}}, {Register, {1, 8}}},
		{{Register,  {1, 8}}, {Const, {1, 8}}}
		});

	IR* JMP = new IR("jump", new Token(FLOW, "jmp"), { {{Label, {0, 0}}} });
	IR* JE = new IR("==", new Token(FLOW, "je"), { {{Label, {0, 0}}} });
	IR* JNE = new IR("!=", new Token(FLOW, "jne"), { {{Label, {0, 0}}} });
	IR* JL = new IR("<", new Token(FLOW, "jl"), { {{Label, {0, 0}}} });
	IR* JLE = new IR("<=", new Token(FLOW, "jle"), { {{Label, {0, 0}}} });
	IR* JNL = new IR("!<", new Token(FLOW, "jnl"), { {{Label, {0, 0}}} });
	IR* JG = new IR(">", new Token(FLOW, "jg"), { {{Label, {0, 0}}} });
	IR* JGE = new IR(">=", new Token(FLOW, "jge"), { {{Label, {0, 0}}} });
	IR* JNG = new IR("!>", new Token(FLOW, "jng"), { {{Label, {0, 0}}} });

	IR* RET = new IR("return", new Token(FLOW, "ret"), vector<vector<pair<Token*, pair<int, int>>>>{});

	IR* PUSH = new IR("push", new Token(OPERATOR, "push"), {
	{{Memory, {2, 8}}},
	{{Register, {2, 8}}},
	{{Const, {1, 4}}},
		}); 
	IR* POP = new IR("pop", new Token(OPERATOR, "pop"), {
	{{Memory, {2, 8}}},
	{{Register, {2, 8}}},
			});

	IR* CALL = new IR("call", new Token(TOKEN::CALL, "call"), {
		{{Label, {0, 0}}}
		});

	Opcodes = {
		MOV,
		LEA,
		ADD,
		SUB,
		MUL,
		DIV,
		CMP,
		JMP,
		JE,
		JNE,
		JL,
		JLE,
		JNL,
		JG,
		JGE,
		JNG,
		RET,
		SET,
		PUSH,
		POP,
		CALL
	};
}