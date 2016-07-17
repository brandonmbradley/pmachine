//Assignment 3 header

typedef struct {
    int kind;   //const, int proc
    char *name;   //obvs the name/identifier
    int value;    //ASCII value
    int level;    //L level
    int address;    //M address
    } symbols;
    

typedef struct {
    int op, l, m;
    } instruct;
    
    
typedef enum {
    lit = 1; opr, lod, sto, cal, inc, jmp, jpc, sioIN, sioOUT
    }vmInstruct;
    
char token;
LexemeList *LL;
int pointLL;
symbols *symTable;

//Prototypes
getToken();
void *getID(int i);
