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
int isRelationalOperator();
int tokens[100];
int getTokenCounter = -1;
int c_error = 0;
int pointLL = 0;
int compileFlag = 0;


//Lexeme List function
//Passes in output file for output printing and the current LL

void displayLexemeList(LexemeList *lists, FILE *fileout) {

    int i;

    //If there is a LL
    if (lists != NULL) {

        //Print the size
        printf("Size: %ld\n", lists->size);

        //FOR LOOP: From i equals 0 to the size of the list
        for (i = 0; i < lists->size; i++) {

            //Print out the list through each index i
            printf("%d ", lists->list[i]);

            //If the current value at index i happens to be an identifier
            //Increase i
            if (lists->list[i] == identsym) {
                i++;

                //If i is less than the size of the list, print
                if (i < lists->size)
                    printf("%s ", lists->symbols[lists->list[i]]);
            }
        }
    }

}

//Get next Token
void getToken() {

    getTokenCounter++;
    token = tokens[getTokenCounter];
    //return token;
}

//Fetches the ID
char *getID(int i) {
    return LL->symbols[i];
}

//Fetches the size of the table
int getTableSize() {
    return (int)(LL->numID * 2 + 1);
}

int hashFunc(char* ID) {
    int val = 0;
    int index = 0;
    int size;
    size = getTableSize();

    while(ID[index] != '\0') {
        //hash function
        val = val + ((int)ID[index] % size);

        //increase index for while loop
        index++;
    }
    return val;
}

int makeSymbolTable() {

    int i = 0;
    //insert symbol *symtab into ass3.h
    symbol * symtab = NULL;

    //Allocate some memory for table
    symtab = (symbol*)malloc(sizeof(symbol)*(2*LL->numID + 1));

    //If there is noting in the table then print error
    if(symtab == NULL) {
        printf("Error: Symbol Table is null.");
        return 1;
    }

    int max = getTableSize();

    //Zero the array out for kind variable
    for(i = 0; i < max; i++) {
        symtab[i].kind = 0;
    }

    return 0;
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
        getToken();
        if(token != semicolonsym) {
            error(5);
        }
        getToken();
        block();
        if(token != semicolonsym) {
            error(5);
        }
        getToken();
    } //end 3
    statement();
} //end 4

void statement() {

    //If token is an identifier
    if (token == identsym) {

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
    }

}

void condition() {

    //If token is odd
    if (token == oddsym) {

        //Get next token
        getToken();

        //Parse expression
        expression();
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

        //Get next token
        getToken();

        //Parse expression
        expression();
    }

}

//expression
void expression() {

    if(token == plussym || token == minussym) {
        getToken();
    }
        term();
        while(token == plussym || token == minussym) {
            getToken();
            term();
        } //edn 1
} //end 2




void term() {

    factor();

    while (token == multsym || token == slashsym) {

        getToken();

        factor();
    }

}

void factor() {

    if (token == identsym) {

        getToken();
    }

    else if (token == numbersym) {

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

                printf("Error: No lexeme list file!");
        }

        //Iterated char
        char c;

        //Array for a single token
        char singleToken[100];

        //Array counter
        int singleTokenCounter = 0;

        int tokenCounter = 0;

        //Iterate over input
        while (fscanf(lexemes, "%c", &c) != EOF) {

            //If we have whitespace, this is the end of the token
            if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c =='\r') {

		singleToken[singleTokenCounter] = '\0';

                //Print the single token
                printf("%s ", &singleToken);

                //Convert token to numerical token
                int digit = 0;
                sscanf(singleToken, "%d", &digit);

                //Ignore the non token types
                if (digit >= 1 && digit <= 33) {

                    //Store in token array
                    tokens[tokenCounter] = digit;

                    //Increment
                    tokenCounter++;
                }

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

        return 0;
}

//Display the symbol table list
void displaySymList(LexemeList *temp, FILE *fileout) {
	int i;
	for(int i = 0; i < temp->size; i++) {
        
        //print the reserved word
		printf("%s", isReservedWord(temp->list[i]));

        //if it is an identifier then add to the index and print the symbol
		if(temp->list[i] == identsym) {

			i++;
			printf("%s", temp->symbols[temp->list[i]]);
		}
		else if(temp->list[i] == numbersym) {
		    //if its a number then add to index and print the number in the list
			i++;
			printf("%d", temp->list[i]);


		}
	}
}

int main()
{
    //Call assignment 2 scanner
    int failedToScan = scannermach();

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
