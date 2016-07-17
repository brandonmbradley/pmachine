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

void getToken() {
    token = LL->list[pointLL++];
}


int main()
{

}
