#include <stdio.h>
#include <stdlib.h>

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
    token = LL->list[pointLL++];
    //return token;
}

//Fetches the ID
char *getID(int i) {
    return LL->symbols[i];
}

//Fetches the size of the table
int getTablesize() {
    return (int)(LL->numID * 2 + 1);
}

int makeSymbolTable() {
    
    int i = 0;
    //insert symbol *symtab into ass3.h
    symtab = NULL;
    
    //Allocate some memory for table
    symtab = (symbol*)malloc(sizeof(symbol)*(2*LL->numID + 1));
    
    //If there is noting in the table then print error
    if(symtab == NULL) {
        printf("Error: Symbol Table is null.");
        return 1;
    }
    
    //Zero the array out for kind variable
    for(i = 0; i < getTableSize); i++) {
        symtab[i].kind = 0;
    }
    
    return 0;
}

void error(int errorNumber) {

    printf("*****Error number %d, ", errorNumber);
    switch (errorNumber) {
        case 1:
            printf("Use = instead of :=.\n");
            break;

        case 2:
            printf("= must be followed by a number.\n");
            break;

        case 3:
            printf("Identifier must be followed by =.\n");
            break;

        case 4:
            printf("const, int, procedure must be followed by identifier.\n");
            break;

        case 5:
            printf("Semicolon or comma missing.\n");
            break;

        case 6:
            printf("Incorrect symbol after procedure declaration.\n");
            break;

        case 7:
            printf("Statement expected.\n");
            break;

        case 8:
            printf("Incorrect symbol after statement part in block.\n");
            break;

        case 9:
            printf("Period expected.\n");
            break;

        case 10:
            printf("Semicolon between statements missing.\n");
            break;

        case 11:
            printf("Undeclared identifier.\n");
            break;

        case 12:
            printf("Assignment to constant or procedure is not allowed.\n");
            break;

        case 13:
            printf("Assignment operator expected.\n");
            break;

        case 14:
            printf("call must be followed by an identifier.\n");
            break;

        case 15:
            printf("Call of a constant or variable is meaningless.\n");
            break;

        case 16:
            printf("then expected.\n");
            break;

        case 17:
            printf("Semicolon or } expected.\n");
            break;

        case 18:
            printf("do expected.\n");
            break;

        case 19:
            printf("Incorrect symbol following statement.\n");
            break;

        case 20:
            printf("Relational operator expected.\n");
            break;

        case 21:
            printf("Expression must not contain a procedure identifier.\n");
            break;

        case 22:
            printf("Right parenthesis missing.\n");
            break;

        case 23:
            printf("The preceding factor cannot begin with this symbol.\n");
            break;

        case 24:
            printf("An expression cannot begin with this symbol.\n");
            break;

        case 25:
            printf("This number is too large.\n");
            break;

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
    
    if(token = constsym) {
        
        //Gotta do a do while loop
        do {
        getToken();
        if(token != identsym) {
            //error
            error(4);
        }
        getToken();
        if(token != eqsym) {
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

            //Get next token
            getToken();
        }

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
        if (!isRelationalOperator()) {

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

        //error: identifier, ( or number expected
    }

}


bool isRelationalOperator() {

    if (token == geqsym) {

        return true;
    }

    else if (token == gtrsym) {

        return true;
    }

    else if (token == leqsym) {

        return true;
    }

    else if (token == lessym) {

        return true;
    }

    else if (token == neqsym) {

        return true;
    }

    else if (token == eqlsym) {

        return true;
    }

    else return false;

}

int main()
{

}
