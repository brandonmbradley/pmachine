//Assignment 2 c file


//Returns whether checked word is reserved
int isReservedWord(char * wordCheck) {

    int i = 0;

    if (strcmp(wordCheck, "const" ) == 0) {

        return constsym;
    }

    else if (strcmp(wordCheck, "var" ) == 0) {

        return varsym;
    }

    else if (strcmp(wordCheck, "procedure" ) == 0) {

        return procsym;
    }

    else if (strcmp(wordCheck, "call" ) == 0) {

        return callsym;

    }

    else if (strcmp(wordCheck, "begin" ) == 0) {

        return beginsym;
    }

    else if (strcmp(wordCheck, "end" ) == 0) {

        return endsym;
    }

    else if (strcmp(wordCheck, "if" ) == 0) {

        return ifsym;
    }

    else if (strcmp(wordCheck, "then" ) == 0) {

        return thensym;
    }

    else if (strcmp(wordCheck, "else" ) == 0) {

        return elsesym;
    }

    else if (strcmp(wordCheck, "while" ) == 0) {

        return whilesym;
    }

    else if (strcmp(wordCheck, "do" ) == 0) {

        return dosym;
    }

    else if (strcmp(wordCheck, "read" ) == 0) {

        return readsym;
    }

    else if (strcmp(wordCheck, "write" ) == 0) {

        return writesym;
    }

    else if (strcmp(wordCheck, "odd" ) == 0) {

        return oddsym;
    }

    else return -1;
}

int scannermach() {
    
    identifierCount = 0;

    numberCount = 0;

    //Scanning word flag
    scanningWord = 0;

    //Scanning digit flag
    scanningDigit = 0;

    //Scanning comment flag
    scanningComment = 0;

    //Divide or comment flag
    scanningDivideOrComment = 0;

    //Ending comment flag
    endingComment = 0;

    //Multiply or comment flag
    scanningMultiplyOrComment = 0;

    //Skip closing comment flag
    skipEndComment = 0;

    //Becomesym flag
    becomes = 0;

    //Less equal flag
    lesseq = 0;

    //Greater equal flag
    greateq = 0;

    //Error flag
    m_error = 0;

    //Init input/output files
     FILE * readCode = fopen("input6.txt", "r");
     FILE * outputLexemeTable = fopen("lexemetable.txt", "w");
     FILE * outputLexemeList = fopen("lexemelist.txt", "w");
     FILE * outputCleanInput = fopen("cleaninput.txt", "w");

     //If read file error, output and exit
     if (readCode == NULL) {

        printf("Error: Could not open input file!\n");
        exit(1);

     }

     //Header for lexeme table
     fprintf(outputLexemeTable, "lexeme\t\ttoken type");

     //Iterated char
     char c;

     //Iterate over input
     while ((fscanf(readCode, "%c", &c) != EOF) && !m_error) {

        //Right parenthesis
        if (c == '(' && !scanningComment) {

            fprintf(outputLexemeTable, "\n(\t\t%i", lparentsym);
            fprintf(outputLexemeList, "%i ", lparentsym);
        }

        //Left parenthesis
        if (c == ')' && !scanningComment) {

            fprintf(outputLexemeTable, "\n)\t\t%i", rparentsym);
            fprintf(outputLexemeList, "%i ", rparentsym);
        }

        //Colon
        if (c == ':' && !scanningComment) {

            becomes = 1;
        }

        //Single =
        if (c == '=' && !becomes && !lesseq && !greateq && !scanningComment) {

            //there was no :/<> in front of eq
            fprintf(outputLexemeTable, "\n=\t\t%i", eqlsym);
            fprintf(outputLexemeList, "%i ", eqlsym);
        }

        //Becomesym
        if (c == '=' && becomes && !scanningComment) {

            fprintf(outputLexemeTable, "\n:=\t\t%i", becomessym);
            fprintf(outputLexemeList, "%i ", becomessym);
            becomes = 0;
        }

        //Lessym
        if (c != '=' && c != '>' && lesseq && !scanningComment) {

            lesseq = 0;
            fprintf(outputLexemeTable, "\n<\t\t%i", lessym);
            fprintf(outputLexemeList, "%i ", lessym);
        }

        //Gtrsym
        if (c != '=' && greateq && !scanningComment) {

            greateq = 0;
            fprintf(outputLexemeTable, "\n>\t\t%i", gtrsym);
            fprintf(outputLexemeList, "%i ", gtrsym);
        }

        //Flag for lessym completion
        if (c == '<' && !scanningComment && !scanningComment) {

            lesseq = 1;
        }

        //Leqsym
        if (c == '=' && lesseq && !scanningComment) {

            lesseq = 0;
            fprintf(outputLexemeTable, "\n<=\t\t%i", leqsym);
            fprintf(outputLexemeList, "%i ", leqsym);
        }

        //Flag for gtrsym completion
        if (c == '>' && !scanningComment) {

            greateq = 1;
        }

        //Neqsym
        if (c == '>' && lesseq && !scanningComment) {

            lesseq = 0;
            greateq = 0;
            fprintf(outputLexemeTable, "\n<>\t\t%i", neqsym);
            fprintf(outputLexemeList, "%i ", neqsym);
        }

        //Geqsym
        if (c == '=' && greateq && !scanningComment) {

            greateq = 0;
            fprintf(outputLexemeTable, "\n>=\t\t%i", geqsym);
            fprintf(outputLexemeList, "%i ", geqsym);
        }

        //Continuity decision checks, is this a divide or beginning of comment
        if (scanningDivideOrComment) {

            //If current char is not an asterisk, the last was actually a divide and not comment
            if (c != '*') {

                //this was a divide
                fprintf(outputCleanInput, "/");
                fprintf(outputLexemeTable, "\n/\t\t%i", slashsym);
                fprintf(outputLexemeList, "%i ", slashsym);
                scanningComment = 0;
                scanningDivideOrComment = 0;
            }

        }

        //Unsupported symbols throw error
        if (c == '$' || c == '#' || c == '&' || c == '!' || c == '~' || c == '`' || c == '?') {

            m_error = 1;
        }

        //All forms of whitespace are ignored
        if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c =='\r') {

            //Whitespace
            //Don't care
        }

        //End of statement and not in a comment
        else if ((c == ' ' || c == ';' || c == ',' || c == '+' || c == '-' || c == '.' || c == ':') && !scanningComment) {

            //End of word
            if (scanningWord) {

                //Reset flag
                scanningWord = 0;

                //Copy word into checking array
                char wordCheck[identifierCount];
                memset(&wordCheck[0], 0, sizeof(wordCheck));
                memcpy(wordCheck, m_identifier, sizeof(m_identifier));

                //Check if this word is a reserve word
                int check = isReservedWord(wordCheck);

                //This word is a reserve word
                if (check != -1) {

                    fprintf(outputLexemeTable, "\n%s\t\t%i", m_identifier, check);
                    fprintf(outputLexemeList, "%i ", check);
                }

                //This word is not a reserve word
                else {

                    fprintf(outputLexemeTable, "\n%s\t\t%i", m_identifier, identsym);
                    fprintf(outputLexemeList, "%i %s ",identsym, wordCheck);

                }

                    //Output tokens
                    if (c == ',') {

                        fprintf(outputLexemeTable, "\n,\t\t%i", commasym);
                        fprintf(outputLexemeList, "%i ",commasym);
                    }

                    if (c == ';') {

                        fprintf(outputLexemeTable, "\n;\t\t%i", semicolonsym);
                        fprintf(outputLexemeList, "%i ", semicolonsym);
                    }

                    if (c == '+') {

                        fprintf(outputLexemeTable, "\n+\t\t%i", plussym);
                        fprintf(outputLexemeList, "%i ", plussym);
                    }

                    if (c == '-') {

                        fprintf(outputLexemeTable, "\n-\t\t%i", minussym);
                        fprintf(outputLexemeList, "%i ", minussym);
                    }

                    if (c == '.') {

                        fprintf(outputLexemeTable, "\n.\t\t%i", periodsym);
                        fprintf(outputLexemeList, "%i ", periodsym);

                    }

                //Clear identifier array
                memset(&m_identifier[0], 0, sizeof(m_identifier));

            }

            //Check if statement was a digit
            else if (scanningDigit) {

                    //Reset flag
                    scanningDigit = 0;

                    //Copy into array
                    char number[numberCount];
                    memset(&number[0], 0, sizeof(number));
                    memcpy(number, m_number, sizeof(m_number));

                    //Convert array to digit
                    int digit = 0;
                    sscanf(m_number, "%d", &digit);

                    //Output digit
                    fprintf(outputLexemeTable, "\n%i\t\t%i", digit, numbersym);
                    fprintf(outputLexemeList, "%i %i ", numbersym, digit);

                    //Output tokens
                    if (c == ',') {

                        fprintf(outputLexemeTable, "\n,\t\t%i", commasym);
                        fprintf(outputLexemeList, "%i ", commasym);
                    }

                    if (c == ';') {

                        fprintf(outputLexemeTable, "\n;\t\t%i", semicolonsym);
                        fprintf(outputLexemeList, "%i ", semicolonsym);
                    }

                    if (c == '+') {

                        fprintf(outputLexemeTable, "\n+\t\t%i", plussym);
                        fprintf(outputLexemeList, "%i ", plussym);
                    }

                    if (c == '-') {

                        fprintf(outputLexemeTable, "\n-\t\t%i", minussym);
                        fprintf(outputLexemeList, "%i ", minussym);
                    }

                    if (c == '.') {

                        fprintf(outputLexemeTable, "\n.\t\t%i", periodsym);
                        fprintf(outputLexemeList, "%i ", periodsym);

                    }

                    //Clear the array
                    memset(&m_number[0], 0, sizeof(m_number));

            }

            //We were not scanning a word or digit
            else {

                    //Output symbols
                    if (c == ',') {

                        fprintf(outputLexemeTable, "\n,\t\t%i", commasym);
                        fprintf(outputLexemeList, "%i ", commasym);
                    }

                    if (c == ';') {

                        fprintf(outputLexemeTable, "\n;\t\t%i", semicolonsym);
                        fprintf(outputLexemeList, "%i ", semicolonsym);
                    }

                    if (c == '+') {

                        fprintf(outputLexemeTable, "\n+\t\t%i", plussym);
                        fprintf(outputLexemeList, "%i ", plussym);
                    }

                    if (c == '-') {

                        fprintf(outputLexemeTable, "\n-\t\t%i", minussym);
                        fprintf(outputLexemeList, "%i ", minussym);
                    }

                    if (c == '.') {

                        fprintf(outputLexemeTable, "\n.\t\t%i", periodsym);
                        fprintf(outputLexemeList, "%i ", periodsym);

                    }
            }

        }

        //Scanned a digit and we are not in a comment or word
        else if (c >= 48 && c <= 57 && !scanningComment && !scanningWord) {

            //Continuation of a number
            if (scanningDigit) {

                //Sanity check for bounds
                if (numberCount == 5) {

                    //Error
                    m_error = 1;
                }

                //Add to previous digit
                else {

                m_number[numberCount] = c;
                numberCount++;

                }

            }

            //Begin scanning digit
            else {

                //Set flags
                scanningDigit = 1;
                numberCount = 0;

                //Store digit
                m_number[numberCount] = c;

                //Increment
                numberCount++;
            }

        }

        //Scanning a word and have received a digit
        else if (c >= 48 && c <= 57 && !scanningComment && scanningWord) {

            //Sanity check for bounds
            if (identifierCount == 11) {

                m_error = 1;
            }

            //Add digit to word
            else {

            m_identifier[identifierCount] = c;

            //Increment
            identifierCount++;

            }
        }

        //Scanned a letter and are not in a comment or digit
        else if (((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) && !scanningComment && !scanningDigit) {

            //Continuation of a word
            if (scanningWord) {

                //Sanity check for bounds
                if (identifierCount == 11) {

                    //Error
                    m_error = 1;
                }

                //Add letter to word
                else {

                    m_identifier[identifierCount] = c;

                    //Increment
                    identifierCount++;

                }
            }

            //Beginning a word
            else {

                //Set flags
                scanningWord = 1;
                identifierCount = 0;

                //Add letter to word
                m_identifier[identifierCount] = c;

                //Increment
                identifierCount++;
            }


        }

        //Scanning a digit and have received a letter
        else if (((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) && !scanningComment && scanningDigit) {

                //Error letter before a digit
                m_error = 1;
        }

        //Scanned a slash and not in a comment
        else if (c == '/' && !endingComment) {

            //If this is a slash that does not end a comment, and one not in the middle of a comment
            if (!endingComment && !scanningComment) {

                //Next iteration determines if this is a divide or the beginning of a comment
                scanningDivideOrComment = 1;

            }

        }

        //Scanned a slash and we are currently in a comment, and flagged to end the comment
        else if (c == '/' && endingComment && scanningComment) {

                //Reset flags
                scanningComment = 0;
                endingComment = 0;
                skipEndComment = 1;
        }

        //Scanned an asterisk
        else if (c == '*') {

            //If we are scanning a comment, set flag to end it
            if (scanningComment) {

                endingComment = 1;
            }

            //If we are flagged to determine whether this is a comment, this is now a comment
            else if (scanningDivideOrComment) {

                //Set flags
                scanningComment = 1;
                scanningDivideOrComment = 0;

            }

            //We found an asterisk that was not preceded by a slash
            else {

                //Output tokens
                fprintf(outputLexemeTable, "\n*\t\t%i", multsym);
                fprintf(outputLexemeList, "%i ", multsym);

            }

        }

        //We are not scanning or determining a comment, output clean input
        if (!scanningComment && !scanningDivideOrComment && !scanningDivideOrComment && !skipEndComment) {

            fprintf(outputCleanInput, "%c", c);

        }

        //Skip end of comment output for clean input, reset flag
        if (skipEndComment) {

            skipEndComment = 0;
        }

     }

     //We have reached end of file, but were scanning a word
     if (scanningWord) {

            //Copy word into checking array
            char wordCheck[identifierCount];
            memset(&wordCheck[0], 0, sizeof(wordCheck));
            memcpy(wordCheck, m_identifier, sizeof(m_identifier));

            //Check if word is a reserved word
            int check = isReservedWord(wordCheck);

            //Word was a reserved word, output tokens
            if (check != -1) {

                fprintf(outputLexemeTable, "\n%s\t\t%i", m_identifier, check);
                fprintf(outputLexemeList, "%i ", check);
            }

            //Word was a variable
            else {

                fprintf(outputLexemeTable, "\n%s\t\t%i", m_identifier, identsym);
                fprintf(outputLexemeList, "%i %s ",identsym, wordCheck);

            }
     }

     //We have reached end of file, but were scanning a digit
     if (scanningDigit) {

            //Copy into array
            char number[numberCount];
            memset(&number[0], 0, sizeof(number));
            memcpy(number, m_number, sizeof(m_number));

            //Convert to int
            int digit= 0;
            sscanf(m_number, "%d", &digit);

            //Output tokens
            fprintf(outputLexemeTable, "\n%i\t\t%i", digit, numbersym);
            fprintf(outputLexemeList, "%i %i ", numbersym, digit);

     }

     //Output error message
     if (m_error) {

        printf("pScanner was aborted early due to lexical error.");
     }
     
     fclose(readCode);
     fclose(outputLexemeTable);
     fclose(outputLexemeList);
     fclose(outputCleanInput);

     return 0;
}
