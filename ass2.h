//Alana Arjune
//Brandon Bradley

//identifier array
char m_identifier [11];
int identifierCount;

//number array
char m_number[5];
int numberCount;

//Scanning word flag
int scanningWord;

//Scanning digit flag
int scanningDigit;

//Scanning comment flag
int scanningComment;

//Divide or comment flag
int scanningDivideOrComment;

//Ending comment flag
int endingComment;

//Multiply or comment flag
int scanningMultiplyOrComment;

//Skip closing comment flag
int skipEndComment;

//Becomesym flag
int becomes;

//Less equal flag
int lesseq;

//Greater equal flag
int greateq;

//Error flag
int m_error;

//Declaration of token types
typedef	enum	{
nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5, multsym = 6,
slashsym = 7, oddsym = 8,  eqlsym = 9, neqsym = 10, lessym = 11, leqsym = 12,
gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17,
semicolonsym = 18, periodsym = 19, becomessym = 20, beginsym = 21, endsym = 22,
ifsym = 23, thensym = 24, whilesym = 25, dosym = 26, callsym = 27, constsym = 28,
varsym = 29, procsym = 30, writesym = 31, readsym = 32, elsesym = 33 }
token_type;

//Instruction struct
typedef struct {

	//operation code (opcode)
	int op;

	//lexicographical level
	int l;

	//varying arithmetic/logical operation
	int m;

}instruct;

typedef struct {
	int *list;
	long size;
	long numID;
	char **symbols;
} LexemeList;

LexemeList *LL;
int pointLL;




