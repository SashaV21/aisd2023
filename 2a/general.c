#include <stdlib.h>
#include <stdio.h>
#include "readline/readline.h"

#include "stack.h"

#define SUCCESS 1
#define FAILURE 0
#define DELIM " \t"



int size_of_steque(char* str) {
    int size = 1;
    while(*str != '\0') {
        if (*str == ' ') {
            size++;
        }
        str++;
    }
    return size;
}

int string_parser(char* str) {
    int stack_size = size_of_steque(str);
    StackArr  * stack = CreateStack(stack_size);
    int size = 0;

    char * tempstr = strtok(str, DELIM);
    while (tempstr != NULL) {
        if (strlen(tempstr) == 1 && (*tempstr == '+' || *tempstr == '-' || *tempstr == '*' || *tempstr == '/')) {
            if (size > 1) {
                int a = Get(stack);
                Pop(stack);
                int b = Get(stack);
                Pop(stack);
                int c;
                if (*tempstr == '+') {
                    c = a + b;
                }
                if (*tempstr == '*') {
                    c = a * b;
                }

                if (*tempstr == '/') {
                    if(a == 0){
                        printf("Expression cannot be calculated\n");
                        StackDelete(stack);
                        return FAILURE;
                    }
                    c = b / a;
                }
                if (*tempstr == '-') {
                    c = b - a;
                }
                Push(stack, c);

                size--;
            }
            else {
                StackDelete(stack);
                printf("WRONG\n");
                return FAILURE;
            }
        }

        else if (strlen(tempstr) > 0) {
            int is_true = 1;
			int str_len = strlen(tempstr);

            for (int i = 0; i < str_len; ++i) {
                if (*(tempstr + i) < '0' || *(tempstr + i) > '9') {
                    is_true = 0;
                }
            }

            if (is_true) {
                Push(stack, atoi(tempstr));
                size++;
            }
            else {
                StackDelete(stack);
                printf("WRONG\n");
                return FAILURE;
            }
        }
        tempstr = strtok(NULL, DELIM);
    }
    if (size == 1) {
        printf("%d\n", Get(stack));
    }
    else if (size == 0){
        printf("Stack is empty\n");
    }
    else {
        printf("The string was entered incorrectly!\n");
    }
    StackDelete(stack);
    return 0;
}
