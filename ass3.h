//Assignment 3 header

#define MAX_SYMBOL_TABLE_SIZE 100;

typedef struct {
    int kind;   //const, int proc
    char name[12];   //obvs the name/identifier
    int value;    //ASCII value
    int level;    //L level
    int address;    //M address
    } symbol;
    

typedef struct {
    int op, l, m;
    } instruct;
    
    
typedef enum {
    lit = 1; opr, lod, sto, cal, inc, jmp, jpc, sioIN, sioOUT
    }vmInstruct;
    
char token;
// LexemeList *LL;
// int pointLL;
symbol *symTable;

//Prototypes
void getToken();
char *getID(int i);
void error(int errorNumber);
