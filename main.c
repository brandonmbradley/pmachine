#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ass1.h"
#include "ass2.h"
#include "ass3.h"

//Function declarations
void displayLexemeList(LexemeList *lists, FILE *fileout);
void getToken();
char *getID(int i);
int getTableSize();
int hashFunc(char* ID);
int makeSymbolTable();
void error(int errorNumber);
void program();
void block();
void statement();
void condition();
void expression();
void term();
void factor();
void gen(int op, int l, int m);
void enter(int type);
int find(char * ident);
int symbolType(char * ident);
int symbolLevel(char * ident);
int symbolAddress(char * ident);
int isRelationalOperator();
char * tokens[100][11];
char * identifier[11];
int number = 0;
int getTokenCounter = 0;
int c_error = 0;
int compileFlag = 0;
int lexLevel = 0;
int codeIdx = 0;
instruction i_code[MAX_CODE_LENGTH];
FILE * writeCode;

//Output code to mcode.txt for vm
void outputCode() {

    writeCode = fopen("mcode.txt", "w");

    if (writeCode == NULL) {

        printf("Error: Code file could not be opened!\n");
    }

    int i = 0;
    for (i = 0; i < codeIdx; i++) {

        fprintf(writeCode, "%i %i %i\n", i_code[i].op, i_code[i].l, i_code[i].m);
    }

}

void outputSymbolTable() {

        printf("\n\nSymbol Table:");
        int i = 0;
        for (i = 0; i < symbolTableIndex; i++) {

            printf("\nKind: %i Name: %s Value: %i  Level: %i  Address: %i\n", symbolTable[i].kind, symbolTable[i].name, symbolTable[i].value, symbolTable[i].level, symbolTable[i].address);

        }

}

//Inserts a new instruction into the code list
void gen(int op, int l, int m) {

    i_code[codeIdx].op = op;
    i_code[codeIdx].l = l;
    i_code[codeIdx].m = m;
    codeIdx++;

}

//Inserts a new symbol into the symbol table
void enter(int type) {


    //Store name
    strcpy(symbolTable[symbolTableIndex].name, identifier);

    //Store kind
    symbolTable[symbolTableIndex].kind = type;

    //For constants, you must store kind, name and value.
    if (type == 1) {

        //Store value
        symbolTable[symbolTableIndex].value = number;

    }

    //For variables, you must store kind, name, L and M.
    else if (type == 2) {

        symbolTable[symbolTableIndex].level = lexLevel;
        symbolTable[symbolTableIndex].address = codeIdx;

    }

    //For procedures, you must store kind, name, L and M
    else if (type == 3) {

        symbolTable[symbolTableIndex].level = lexLevel;

    }

    //Increment index
    symbolTableIndex++;

}

int find(char * ident) {

        //printf("Finding:%s\n", ident);

        int i = 0;

        for (i = 0; i < symbolTableIndex; i++) {

            //printf("Checking against:%s\n", symbolTable[i].name);

            int check = strcmp(ident, symbolTable[i].name);

            //printf("Check is %i \n", check);

            if (check == 0) {

                return 1;
            }

        }

        return 0;
}


//Returns the type of a symbol (const, var, proc)
int symbolType(char * ident) {

        //printf("Finding symbol type:%s\n", ident);

        int i = 0;

        for (i = 0; i < symbolTableIndex; i++) {

            //printf("Checking against:%s\n", symbolTable[i].name);

            int check = strcmp(ident, symbolTable[i].name);

            //printf("Check is %i \n", check);

            if (check == 0) {

                int kind = symbolTable[i].kind;
                //printf("Kind is %i\n", symbolTable[i].kind);
                return kind;
            }

        }

        return 0;
}

//Returns the level of a symbol
int symbolLevel( char * ident) {

        //printf("Finding symbol level:%s\n", ident);

        int i = 0;

        for (i = 0; i < symbolTableIndex; i++) {

            //printf("Checking against:%s\n", symbolTable[i].name);

            int check = strcmp(ident, symbolTable[i].name);

            //printf("Check is %i \n", check);

            if (check == 0) {

                int level = symbolTable[i].level;
                //printf("Level is %i\n", symbolTable[i].level);
                return level;
            }

        }

        return 0;
}

//Returns the address of a symbol
int symbolAddress(char * ident) {

        //printf("Finding symbol address:%s\n", ident);

        int i = 0;
        int address = 0;

        for (i = 0; i < symbolTableIndex; i++) {

            //printf("Checking against:%s\n", symbolTable[i].name);

            int check = strcmp(ident, symbolTable[i].name);

            //printf("Check is %i \n", check);

            if (check == 0) {

                address = symbolTable[i].address;
                //printf("Address is %i\n", symbolTable[i].address);
                return address;
            }

        }

        return 0;
}


//Get next Token
void getToken() {

    //Init current token
    char * curToken[11];

    //Copy token from token array
    strcpy(curToken, tokens[getTokenCounter]);

        //printf("\nCurrent token: %s \n", curToken);

    //Increment counter
    getTokenCounter++;

    //Convert token to numerical token
    int digit = 0;
    sscanf(curToken, "%d", &digit);

    //If token is identifier, save for symbol table
    if (digit == identsym) {


        strcpy(identifier, tokens[getTokenCounter]);
        getTokenCounter++;
    }

    //If token is number, save for symbol table
    else if (digit == numbersym) {


        number = digit;
        getTokenCounter++;

    }

    token = digit;
}

void error(int errorNumber) {

    printf("\nError number %d, ", errorNumber);
    switch (errorNumber) {
        case 1:
            printf("Use = instead of :=.\n");
            c_error = 1;
            break;

        case 2:
            printf("= must be followed by a number.\n");
            c_error = 1;
            break;

        case 3:
            printf("Identifier must be followed by =.\n");
            c_error = 1;
            break;

        case 4:
            printf("const, int, procedure must be followed by identifier.\n");
            c_error = 1;
            break;

        case 5:
            printf("Semicolon or comma missing.\n");
            c_error = 1;
            break;

        case 6:
            printf("Incorrect symbol after procedure declaration.\n");
            c_error = 1;
            break;

        case 7:
            printf("Statement expected.\n");
            c_error = 1;
            break;

        case 8:
            printf("Incorrect symbol after statement part in block.\n");
            c_error = 1;
            break;

        case 9:
            printf("Period expected.\n");
            c_error = 1;
            break;

        case 10:
            printf("Semicolon between statements missing.\n");
            c_error = 1;
            break;

        case 11:
            printf("Undeclared identifier.\n");
            c_error = 1;
            break;

        case 12:
            printf("Assignment to constant or procedure is not allowed.\n");
            c_error = 1;
            break;

        case 13:
            printf("Assignment operator expected.\n");
            c_error = 1;
            break;

        case 14:
            printf("call must be followed by an identifier.\n");
            c_error = 1;
            break;

        case 15:
            printf("Call of a constant or variable is meaningless.\n");
            c_error = 1;
            break;

        case 16:
            printf("then expected.\n");
            c_error = 1;
            break;

        case 17:
            printf("Semicolon or } expected.\n");
            c_error = 1;
            break;

        case 18:
            printf("do expected.\n");
            c_error = 1;
            break;

        case 19:
            printf("Incorrect symbol following statement.\n");
            c_error = 1;
            break;

        case 20:
            printf("Relational operator expected.\n");
            c_error = 1;
            break;

        case 21:
            printf("Expression must not contain a procedure identifier.\n");
            c_error = 1;
            break;

        case 22:
            printf("Right parenthesis missing.\n");
            c_error = 1;
            break;

        case 23:
            printf("The preceding factor cannot begin with this symbol.\n");
            c_error = 1;
            break;

        case 24:
            printf("An expression cannot begin with this symbol.\n");
            c_error = 1;
            break;

        case 25:
            printf("This number is too large.\n");
            c_error = 1;
            break;

    }

    if (c_error) {

        exit(1);
    }
}

//Program
void program() {

    getToken();

    block();

    if(token != periodsym) {

        //error period expected
        error(9);
        //return 9;
    }
}

//Block
void block() {
    
    lexLevel++;

    symbolTable[symbolTableIndex].address = codeIdx;
    gen(jmp, 0, 0);

    if(token == constsym) {

        //Gotta do a do while loop
        do {

        getToken();

        if(token != identsym) {

            //error
            error(4);
        }

        getToken();

        if(token != eqlsym) {

            //error
            error(1);
        }

        getToken();

        if(token != numbersym) {
            //error
            error(2);
        }

        //enter (constant, ident, number)
        enter(1);

        getToken();

        } while(token == commasym);

        if(token != semicolonsym) {

            //error
            error(5);
            getToken();

        }
    } //end 1

    if(token == varsym) {

        do{

        getToken();

        if(token != identsym) {

            //error
            error(4);
        }

        getToken();

        //enter (variable, ident, level)
        enter(2);

    } while(token == commasym);

    if(token != semicolonsym) {
        //error
        error(5);
    }

    getToken();
} //end 2

    while(token == procsym) {
        //do?
        getToken();

        if(token != identsym) {

            error(4);
        }

        //enter(procedure, ident)
        enter(3);

        getToken();

        if(token != semicolonsym) {

            error(5);
        }

        getToken();

        lexLevel++;
        block();

        if(token != semicolonsym) {

            error(5);
        }

        getToken();

    } //end 3



    gen(inc, 0, codeIdx);
    statement();
    gen(opr, 0, 0);
    //lexLevel--;
} //end 4

void statement() {

    //If token is an identifier
    if (token == identsym) {

        //printf("Statement token: %i\n", token);

        int i;

        //printf("Statement identifier: %s\n", identifier);

        i = find(identifier);

        //printf("Result of find %i", i);

        if (i == 0) {

            //Undeclared
            error(11);
        }

        int k;

        //Check identifier symbol type
        k = symbolType(identifier);

        //If identifier is not varsym
        if (k != 2) {

            //Error assignment to const or proc
            error(12);
        }

        //Get next token
        getToken();

        //If token is not becomes
        if (token != becomessym) {

            //error: := missing in statement
            error(3);
        }

        //Get next token
        getToken();

        //parse expression
        expression();

        gen(sto, symbolLevel(identifier), symbolAddress(identifier));


    }

    //Else if token is call
    else if (token == callsym) {

        //Get next token
        getToken();

        //If token is not an identifier
        if (token != identsym) {

            //error: missing identifier
            error(14);
        }

        //Get next token
        getToken();
    }

    //If token is begin
    else if (token == beginsym) {

        //Get next token
        getToken();

        //parse statement
        statement();

        //While token is semi colon
        while (token == semicolonsym) {

            //Get next token
            getToken();

            //parse statement
            statement();

        }

        //If token is not end
        if (token != endsym) {

            //error: must be closed with end
            error(9);


        }

             //Get next token
            getToken();

    }

    //If token is if
    else if (token == ifsym) {

        //If next token
        getToken();

        //parse condition
        condition();

        //If token is not then
        if (token != thensym) {

            //error: condition must be followed by then
            error(16);

        }

        //Get next token
        getToken();

        //parse statement
        statement();
    }

    //If token is while
    else if (token == whilesym) {

        //Get next token
        getToken();

        //Parse condition
        condition();

        //If token is not do
        if (token != dosym) {

            //error: while condition must be followed by do
            error(18);
        }

        //Get next token
        getToken();

        //Parse statement
        statement();
        //gen(jmp, symbolLevel(identifier), symbolAddress(identifier));
    }
    

}

void condition() {

    //If token is odd
    if (token == oddsym) {

        //Get next token
        getToken();

        //Parse expression
        expression();

        //Gen odd, 6 for M odd
        gen(opr, 0, 6);
    }

    //Otherwise
    else {

        //Parse expression
        expression();

        //If token is not a relation operator
        int relCheck = isRelationalOperator();

        if (!relCheck) {

            //error: relational operator missing in conditional statement
            error(20);
        }

        int relationalOperator = token;

        //Get next token
        getToken();

        //Parse expression
        expression();

        if (relationalOperator == geqsym) {

            //Gen greater/equal (13 = M)
            gen(opr, 0, 13);

        }

        else if (relationalOperator == gtrsym) {

             //Gen greater than (12 = M)
            gen(opr, 0, 12);

        }

        else if (relationalOperator == leqsym) {

            //Gen less/equal (11 = M)
            gen(opr, 0, 11);

        }

        else if (relationalOperator == lessym) {

            //Gen less than (10 = M)
            gen(opr, 0, 10);

        }

        else if (relationalOperator == neqsym) {

            //Gen neq (9 = M)
            gen(opr, 0, 9);

        }

        else if (relationalOperator == eqlsym) {

            //Gen eql (8 = M)
            gen(opr, 0 , 8);
        }
    }

}

//expression
void expression() {

    int tokenOperator = 0;

    if(token == plussym || token == minussym) {

        tokenOperator = token;

        getToken();
    }

    term();

    if (tokenOperator == minussym) {

        //Gen neg (1 = M)
        gen(opr, 0, 1);
    }

    while(token == plussym || token == minussym) {

        tokenOperator = token;

        getToken();

        term();

        if (tokenOperator == plussym) {

            //Gen add (2 = M)
            gen(opr, 0, 2);
        }

        else {

            //Gen sub (3 = M)
            gen(opr, 0, 3);
        }

    }
}

void term() {

    int tokenOperator = 0;

    factor();

    while (token == multsym || token == slashsym) {

        tokenOperator = token;

        getToken();

        factor();

        if (tokenOperator == slashsym) {

            //Gen div (5 = M)
            gen(opr, 0, 5);
        }

        else {

            //Gen mul (4 = M)
            gen(opr, 0, 4);
        }
    }

}

void factor() {

    if (token == identsym) {

        int i;

        //printf("Statement identifier: %s\n", identifier);
        //find symbol
        i = find(identifier);

        //printf("Result of find %i", i);

        if (i == 0) {

            //Undeclared
            error(11);
        }

        int k;

        //Check identifier symbol type
        k = symbolType(identifier);

        //If identifier is varsym
        if (k == 2) {

            gen(lod, symbolLevel(identifier), symbolAddress(identifier));
        }

        //If identifier is const
        else if (k == 1) {

            gen(lit, 0, number);
        }

        else {

            //TODO: figure out this error
            error(1);
        }

        getToken();
    }

    else if (token == numbersym) {

        getToken();
        gen(lit, 0, token); //token could also be replaced by numbersym
        getToken();
    }

    else if (token == lparentsym) {

        getToken();

        expression();

        if (token != rparentsym) {

            //error: left parenthesis has not been closed
            error(22);
        }

        getToken();
    }

    else {

        //error: identifier, ( or number expect
        error(11);
    }

}
/////////////////////////////////////

int isRelationalOperator() {

    if (token == geqsym) {

        return 1;
    }

    else if (token == gtrsym) {

        return 1;
    }

    else if (token == leqsym) {

        return 1;
    }

    else if (token == lessym) {

        return 1;
    }

    else if (token == neqsym) {

        return 1;
    }

    else if (token == eqlsym) {

        return 1;
    }

    else return 0;

}

int scanTokens() {

        FILE * lexemes = fopen("lexemelist.txt", "r");

        if(lexemes == NULL) {

                printf("Error: No lexeme list file!\n");
        }

        //Iterated char
        char c;

        //Array for a single token
        char singleToken[100];

        char * sToken = singleToken;

        //Array counter
        int singleTokenCounter = 0;

        int tokenCounter = 0;

        //Iterate over lexeme list
        while (fscanf(lexemes, "%c", &c) != EOF) {

            //If we have whitespace, this is the end of the token
            if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c =='\r') {

                //Terminating char
                singleToken[singleTokenCounter] = '\0';

                //Print the single token - TODO: compile flag
                printf("%s ", sToken);

                //Copy the single token into the array of tokens
                strcpy(tokens[tokenCounter], sToken);

                //Increment index
                tokenCounter++;

                //Reset the single token array for the next token
                memset(&singleToken[0], 0, sizeof(singleToken));
                singleTokenCounter = 0;

            }

            else {

                   //Store next char of token
                   singleToken[singleTokenCounter] = c;

                   //Increment array counter
                   singleTokenCounter++;

            }

        }




        program();

        outputCode();

        outputSymbolTable();

        fclose(writeCode);
        fclose(lexemes);

        return 0;


}


int main()
{

    //Call assignment 2 scanner
    int failedToScan = scannermach();

    int maxTableSize = MAX_SYMBOL_TABLE_SIZE;

    symbolTable = (symbol*)malloc(sizeof(symbol)*(maxTableSize));

    //Init symbol table

    int i = 0;
    symbolTableIndex = 0;

    for (i = 0; i < maxTableSize; i++) {

        symbolTable[i].kind = 0;
        symbolTable[i].value = 0;
        symbolTable[i].level = 0;
        symbolTable[i].address = 0;
    }

    //If scanner
    if (!failedToScan) {

        scanTokens();

    }

    else {

        //TODO: Remove
        printf("\nCompiler Driver: Scanner failed and should have output error.");
    }

    if (!c_error) {

        printf("\nNo errors, program is syntactically correct.");
    }



    return 0;
}
