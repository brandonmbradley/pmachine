//Alana Arjune
//Brandon Bradley

/********************************************
//virtualmachine.h

//This will show up as an addition change. It will also show what was removed.
*******************************************/

//Constants
#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVEL 3

//Instruction struct
typedef struct INSTRUCTION_DATA {

	//operation code (opcode)
	int OP;

	//lexicographical level
	int L;

	//modifier
	int M;

}instruction;

//OP code array includes
//"" for empty
//lit = literal
//opr = operation
//lod = load
//sto = store
//cal = call (a function)
//inc = increment (increase a counter/pointer/register place number)
//jmp = jump
//jpc = jump if top stack element is 0
//sio = read input and store at top of stack and halt the machine
char *const OPCODES[] = {"", "lit", "opr", "lod", "sto", "cal", "inc", "jmp", "jpc", "sio", "sio"};


// Struct for our 4 main registers: PC, BP, SP, and IR
// PC = Program Counter -> the number it has is the address of instruction currently being executed
// BP = Base Pointer -> points to the base aka the bottom of the activation record
// SP = Stack Pointer -> looks to the top of the stack
// IR = Instruction Register -> After the current instruction is fetched the IR holds on to it
//reg short for register
typedef struct CPU_REGISTERS
{
    int PC;
    int BP;
    int SP;
    instruction IR;
} reg;


//Halt flag
int halt = 0;

////////////Global vars//////////////
//Init stack array
int stack [MAX_STACK_HEIGHT];

//Init code memory store
instruction code[MAX_CODE_LENGTH];

//Prototypes
/*******************************************
//PROPOSED - I’m pretty sure prototypes will change as we implement, minor changes will be needed to run virtual machine.
Input should always be mcode.txt, no parameter passing needed
void readInFile();

Augments main function - start fetch-execute cycle
void startVirtualMachine();

*******************************************/

void runPM0(FILE* filein, FILE* fileout);
void execute(FILE *fileout, instruction code[], int stack[], reg *registers);
int base(int l, int base, int stack[]);
void printDisplay(int stack[], reg registers, FILE* fileout);
void debug(char* text);

/*******************************************

We might need to put in more #define's
I think maybe for code length (once we do code generation...
just trying to plan that out as well)

Also do you want to send each other our past codes so that way we can coordinate
on the function names and such?

I think this header should be dedicated to the variables and structs from
ass. #2 and then we should have another header dealing with the stuff from ass. #1.
There might also need to be one for ass. #3 with all the code he gave us in the doc.


*******************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define some variables from constraints
#define INITIAL_MAX_FILE_SIZE 1 << 10

//Identifiers can be a maximum of 11 characters in length
#define MAX_ID_LENGTH 11

//Numbers can be a maximum of 5 digits in length
#define MAX_NUMBER_DIGITS 5

//Number of Reserved Words (Counted from line 36)
#define RESERVED_WORDS 14

//ENUM: This is all of the Lexical Conventions for PL/0
//All of there are given in the HW document Appendix B
typedef enum {
    nulsym = 1, identsym, numbersym, plussym, minussym,
    multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
    periodsym, becomessym, beginsym, endsym, ifsym, thensym,
    whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
    readsym , elsesym
    } token_type;


//RESERVED WORDS
char *word[] = {"const", "var", "procedure", "call", "begin", "end", "if", "then", "else", "while", "do", "read", "write", "odd"};


//Symbols for Reserved Words
int wordSymbol[] = {constsym, varsym, procsym, callsym, beginsym, endsym, ifsym, thensym, elsesym, whilesym, dosym, readsym, writesym, oddsym};


//Array of size 256 for List of Special Symbols
//Given in Lecture 5
int ssym[256];

//Variables to be used later
int MAXSIZE;
char *buff;


/*******************************************

Here we might need to put in a struct for the lexeme list

*******************************************/



//PROTOTYPES: More on the functions below
void globalVars();
void debug(char* text);

