/*
Alana Arjune
Brandon Bradley
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ass1.h"


//Instruction Fetch
//First step of two step instruction execution
void instructionFetch() {

	//Fetch instruction from code memory store using program counter
	IR = &codeMemStore[PC];

	//Increment program counter
    PC = PC + 1;
}

//Return corresponding op code string
const char * instructionStrOP(int opCode) {

    if (opCode == 0) {

      static char strOp0[] = "SIO";

      return strOp0;
    }

    if (opCode == 1) {

      static char strOp[] = "LIT";

      return strOp;
    }

    else if (opCode == 2) {

      static char strOp2[] = "OPR";

      return strOp2;
    }

    else if (opCode == 3) {

      static char strOp3[] = "LOD";

      return strOp3;
    }

    else if (opCode == 4) {

      static char strOp4[] = "STO";

      return strOp4;
    }

    else if (opCode == 5) {

      static char strOp5[] = "CAL";

      return strOp5;
    }

    else if (opCode == 6) {

      static char strOp6[] = "INC";

      return strOp6;
    }

    else if (opCode == 7) {

      static char strOp7[] = "JMP";

      return strOp7;
    }

    else if (opCode == 8) {

      static char strOp8[] = "JPC";

      return strOp8;
    }

    else if (opCode == 9) {

      static char strOp9[] = "SIO";

      return strOp9;
    }

    else if (opCode == 10) {

      static char strOp10[] = "SIO";

      return strOp10;
    }

    else if (opCode == 11) {

      static char strOp11[] = "SIO";

      return strOp11;
    }

    else {

        static char strOpNull[] = "NULL";
        return strOpNull;
    }

}

//Execute Instruction
void instructionExecute() {

    //LIT 0, M
    if (IR->op == 1) {

        SP = SP + 1;
        m_nstack[SP] = IR->m;

    }

    //OPR 0,#
    else if (IR->op == 2) {

        //RET
        if (IR->m == 0) {

            lexicographical = lexicographical - 1;
            SP = BP - 1;
            PC = m_nstack[SP + 4];
            BP = m_nstack[SP + 3];

        }

        //NEG
        else if (IR->m == 1) {

            m_nstack[SP] = -m_nstack[SP];
        }

        //ADD
        else if (IR->m == 2) {

            SP = SP - 1;
            m_nstack[SP] = m_nstack[SP] + m_nstack[SP + 1];

        }

        //SUB
        else if (IR->m == 3) {

            SP = SP - 1;
            m_nstack[SP] = m_nstack[SP] - m_nstack[SP + 1];

        }

        //MUL
        else if (IR->m == 4) {

            SP = SP - 1;
            m_nstack[SP] = m_nstack[SP] * m_nstack[SP + 1];

        }

        //DIV
        else if (IR->m == 5) {

            SP = SP - 1;
            m_nstack[SP] = m_nstack[SP] / m_nstack[SP + 1];
        }

        //ODD
        else if (IR->m == 6) {

            m_nstack[SP] = m_nstack[SP] % 2;
        }

        //MOD
        else if (IR->m == 7) {

            SP = SP - 1;
            m_nstack[SP] = m_nstack[SP] % m_nstack[SP + 1];

        }

        //EQL
        else if (IR->m == 8) {

            SP = SP - 1;
            m_nstack[SP] = m_nstack[SP] == m_nstack[SP + 1];
        }

        //NEQ
        else if (IR->m == 9) {

            SP = SP - 1;
            m_nstack[SP] = m_nstack[SP] != m_nstack[SP + 1];
        }

        //LSS
        else if (IR->m == 10) {

            SP = SP - 1;
            m_nstack[SP] = m_nstack[SP] < m_nstack[SP + 1];

        }

        //LEQ
        else if (IR->m == 11) {

            SP = SP - 1;
            m_nstack[SP] = m_nstack[SP] <= m_nstack[SP + 1];
        }

        //GTR
        else if (IR->m == 12) {

            SP = SP - 1;
            m_nstack[SP] = m_nstack[SP] > m_nstack[SP + 1];
        }

        //GEQ
        else if (IR->m == 13) {

            SP = SP - 1;
            m_nstack[SP] = m_nstack[SP] >= m_nstack[SP + 1];

        }

    }

    //LOD L, M
    else if (IR->op == 3) {

        SP = SP + 1;
        m_nstack[SP] = m_nstack[base(IR->l, BP) + IR->m];
    }

    //STO L, M
    else if (IR->op == 4) {

        m_nstack[base(IR->l, BP) + IR->m] = m_nstack[SP];
        SP = SP - 1;
    }

    //CAL L, M
    else if (IR->op == 5) {

        //Space to return value
        m_nstack[SP + 1] = 0;

        //Static Link
        m_nstack[SP + 2] = base(IR->l, BP);

        //Dynamic Link
        m_nstack[SP + 3] = BP;

        //Return address
        m_nstack[SP + 4] = PC;

        BP = SP + 1;

        PC = IR->m;

        //Generate new activation record
        lexicographicalLevel[lexicographical] = SP;
        lexicographical = lexicographical + 1;

    }

    //INC 0, M
    else if (IR->op == 6) {

        SP = SP + IR->m;

    }

    //JMP 0, M
    else if (IR->op == 7) {

        PC = IR->m;
    }

    //JPC 0, M
    else if (IR->op == 8) {

        if (m_nstack[SP] == 0) {

            PC = IR->m;
        }

        SP = SP - 1;
    }

    //SIO, 0, 1
    else if (IR->op == 9 && IR->m == 1) {

      //Write the top stack element to the screen
      printf("\nTOP OF STACK: %i\n\n", m_nstack[SP]);
      SP = SP - 1;
    }

    //SIO 0, 2
    else if (IR->op = 10 && IR->m == 2) {

        SP = SP + 1;
        //Read in input from the user and store it at the top of stack
        printf("Input the number to store: ");
        scanf("%i", &m_nstack[SP]);
        printf("\n");

    }

    else if (IR->op == 11 && IR->m == 3) {

        //halt
        halt = 1;

    }
}

//From assignment instructions
int base(l, base) { // l stand for L in the instruction format

    int b1; //find base L levels down
    b1 = base;

    while (l > 0) {

    b1 = m_nstack[b1 + 1];
    l--;
}

    return b1;
}

void outputStackTrace(FILE * outputTrace) {

    //Get corresponding OP code string
    const char * str = instructionStrOP(IR->op);

    //If not halt, print all required data and stack
    if (!halt) {

    //Output required data
    printf("%i\t%s\t%i\t%i\t%i\t%i\t%i\t", IR->lineNum, str, IR->l, IR->m, PC, BP, SP);
    fprintf(outputTrace, "%i\t%s\t%i\t%i\t%i\t%i\t%i\t", IR->lineNum, str, IR->l, IR->m, PC, BP, SP);

    //Init vars
    int count = 0;
    int i = 0;
    int lexicographicalSeparator = 0;

    //Iterate, i starts at one as first in stack is never printed to stack pointer
    for (i = 1; i <= SP; i++) {

        //Output lexicographical separation of Activation Records
        if (lexicographicalLevel[lexicographicalSeparator] > 0 && lexicographicalLevel[lexicographicalSeparator] < i) {

            printf("| ");
            fprintf(outputTrace, "| ");
            lexicographicalSeparator = lexicographicalSeparator + 1;
        }

        //Output the value
        printf("%i ", m_nstack[i]);
        fprintf(outputTrace, "%i ", m_nstack[i]);
    }

    //Output for legibility after iteration
    printf("\n");
    fprintf(outputTrace, "\n");

    }

    //If halt
    else {

        //Output required data except PC, BP, SP and stack
        printf("%i\t%s\t%i\t%i\t", IR->lineNum, str, IR->l, IR->m);
        fprintf(outputTrace, "%i\t%s\t%i\t%i", IR->lineNum, str, IR->l, IR->m);

        //Output successful halt
        printf("\nSuccessfully halted.");
        fprintf(outputTrace, "\nSuccessfully halted.");

    }

}

void startVirtualMachine () {

    lexicographical = 0;
    halt = 0;

    SP = 0;
    BP = 1;
    PC = 0;

     //Initial stack store values
     m_nstack[1] = 0;
     m_nstack[2] = 0;
     m_nstack[3] = 0;

     //Initial lexicographical level values
     lexicographicalLevel[0] = 0;
     lexicographicalLevel[1] = 0;
     lexicographicalLevel[2] = 0;
     lexicographicalLevel[3] = 0;

    //Init input/output files
     FILE * readCode = fopen("mcode.txt", "r");
     FILE * outputTrace = fopen("stacktrace.txt", "w");

     //If read file error, output and exit
     if (readCode == NULL) {

        printf("Error: Could not open input file!\n");
        exit(1);

     }

     //Var for counting lines
     int count = 0;

     //Output code memory store header
     printf("Line\tOP\tL\tM\n");
     fprintf(outputTrace, "Line\tOP\tL\tM\n");

     //Read each line and store in struct code memory store array
     while (fscanf(readCode, "%i %i %i", &codeMemStore[count].op, &codeMemStore[count].l, &codeMemStore[count].m) != EOF) {

        //Store line number for output
        codeMemStore[count].lineNum = count;

        //Output struct code memory store
        printf("%i\t%i\t%i\t%i \n",count, codeMemStore[count].op, codeMemStore[count].l, codeMemStore[count].m );
        fprintf(outputTrace, "%i\t%i\t%i\t%i \n",count, codeMemStore[count].op, codeMemStore[count].l, codeMemStore[count].m );

        //Increment
        count++;

    }

    //Only output terminal header once
    int outputTerminalHeader = 1;

    //While halt not called
    while (!halt) {

        //Fetch the next instruction
        instructionFetch();

        //If program counter has reached number of lines in code memory store
        if (PC == count) {

            //Halt
            halt = 1;
        }

        //Execute the next instruction
        instructionExecute();

        //If output header is 1, output the header
        if (outputTerminalHeader == 1) {

            //Output headers
            printf("\n\t\t\t\tPC\tBP\tSP\tStack\t\n");
            fprintf(outputTrace, "\n\t\t\t\tPC\tBP\tSP\tStack\t\n");
            printf("Initial values\t\t\t0\t1\t0\n");
            fprintf(outputTrace, "Initial values\t\t\t0\t1\t0\n");

            //Reset flag
            outputTerminalHeader = 0;

        }

        //Output trace on each iteration
        outputStackTrace(outputTrace);

    }

}



