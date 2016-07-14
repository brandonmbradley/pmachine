
/*
Alana Arjune
Brandon Bradley
*/

//Given pMachine Constants
#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVEL 3

//PM/0 Initial/Default Values:
int SP;
int BP;
int PC;

//Init stack array
int m_nstack [MAX_STACK_HEIGHT];

//Instruction struct
typedef struct {

	//operation code (opcode)
	int op;

	//lexicographical level
	int l;

	//varying arithmetic/logical operation
	int m;

	//store corresponding line number for output
	int lineNum;

}instruction;

//IR and Initial value
instruction * IR;

//Halt flag
int halt;

//Init code memory store
instruction codeMemStore[MAX_CODE_LENGTH];

//Init lexicographical array
int lexicographicalLevel[MAX_LEXI_LEVEL];

//Lexicographical array pointer
int lexicographical;

void startVirtualMachine();


