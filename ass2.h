//Alana Arjune
//Brandon Bradley

//identifier array
char m_identifier [11];
int identifierCount = 0;

//number array
char m_number[5];
int numberCount = 0;

//Scanning word flag
int scanningWord = 0;

//Scanning digit flag
int scanningDigit = 0;

//Scanning comment flag
int scanningComment = 0;

//Divide or comment flag
int scanningDivideOrComment = 0;

//Ending comment flag
int endingComment = 0;

//Multiply or comment flag
int scanningMultiplyOrComment = 0;

//Skip closing comment flag
int skipEndComment = 0;

//Becomesym flag
int becomes = 0;

//Less equal flag
int lesseq = 0;

//Greater equal flag
int greateq = 0;

//Error flag
int m_error = 0;

//Declaration of token types
typedef	enum	{
nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5, multsym = 6,
slashsym = 7, oddsym = 8,  eqlsym = 9, neqsym = 10, lessym = 11, leqsym = 12,
gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17,
semicolonsym = 18, periodsym = 19, becomessym = 20, beginsym = 21, endsym = 22,
ifsym = 23, thensym = 24, whilesym = 25, dosym = 26, callsym = 27, constsym = 28,
varsym = 29, procsym = 30, writesym = 31, readsym = 32, elsesym = 33 }
token_type;

typedef struct {
	int *list;
	long size;
	long numID;
	char **symbols;
} LexemeList;

LexemeList *LL;
int pointLL;
/********************************************
//virtualmachine.h

//This will show up as an addition change. It will also show what was removed.
*******************************************/
/*
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

char *const OPCODES[] = {"", "lit", "opr", "lod", "sto", "cal", "inc", "jmp", "jpc", "sio", "sio"};


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
*/

//Prototypes
/*******************************************
//PROPOSED - I’m pretty sure prototypes will change as we implement, minor changes will be needed to run virtual machine.
Input should always be mcode.txt, no parameter passing needed
void readInFile();

Augments main function - start fetch-execute cycle
void startVirtualMachine();

*******************************************/
/*
void runPM0(FILE* filein, FILE* fileout);
void execute(FILE *fileout, instruction code[], int stack[], reg *registers);
int base(int l, int base, int stack[]);
void printDisplay(int stack[], reg registers, FILE* fileout);
void debug(char* text);


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

******************************************



//PROTOTYPES: More on the functions below
void globalVars();
void debug(char* text);

*/




