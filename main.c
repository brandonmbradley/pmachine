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

// //BASE function
// //This is from the HW document given
// //It just finds the base L levels down
// //Added an extra parameter of stack
// //Now it takes in the parameters l (L in the instruction format)
// //base, and stack
// int base(int l, int base, int stack[]) {

//     //find base L levels down
//     int b1;
//     b1 = base;

//     while (l > 0) {
//         b1 = stack[b1+1];
//         l--;
//     }
//     return b1;
// }

int main()
{

}
