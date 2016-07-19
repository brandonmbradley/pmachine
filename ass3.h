//Assignment 3 header

#define MAX_SYMBOL_TABLE_SIZE 100;

typedef struct {
    int kind;   //const, int proc
    char name[12];   //obvs the name/identifier
    int value;    //ASCII value
    int level;    //L level
    int address;    //M address
    } symbol;

//symbol *symTab;

typedef struct {
    int op, l, m;
    } instruct;


typedef enum {
    lit = 1, opr, lod, sto, cal, inc, jmp, jpc, sioIN, sioOUT
    }vmInstruct;

int token;
// LexemeList *LL;
// int pointLL;


//Prototypes
void getToken();
char *getID(int i);
void error(int errorNumber);
void displayLexemeList(LexemeList *lists, FILE *fileout);
void getToken();
char *getID(int i);
int getTablesize();
int makeSymbolTable();
