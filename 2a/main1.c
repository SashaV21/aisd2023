#include <stdlib.h>
#include <stdio.h>
#include "readline/readline.h"
#include "stack_list.h"
#include "calc.h"
#include "string.h"
#include "general.h"


int main() {
    printf("Chose type:\n1.list\n2.stack\n");
    int typeparser = 2;
    scanf("%d", &typeparser);
    if (typeparser == 2) {
        printf("Enter an expression: \n");
        char * string = readline("");
        while(string){
	        printf("Your result: \n");
	        string_parser(string); 
	        free(string);
	        printf("Enter an expression: \n");
	        string = readline("");
	    }
	    free(string);
    }
    if (typeparser == 1) {
        char *str = readline("ENTER STRING -->");
        while(str){
            Stack * stack = init();
            if(!calc(stack, str))
                printf("WRONG INPUT. TRY AGAIN!\n");
            free(str);
            str = readline("ENTER STRING -->");
            delete(stack);
        }
        printf("PROGRAMM WAS FINISHED\n");
        free(str);
    }
    return 0;
}
