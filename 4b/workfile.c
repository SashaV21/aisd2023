#include "workfile.h"
#include <stdio.h>
#include <stdlib.h>

int getLine(char** str, FILE* fp) {
    int len = 0;
    int capacity = 100;  // Начальная емкость строки
    *str = (char*)malloc(sizeof(char) * capacity);

    if (*str == NULL) {
        return 0;  // Не удалось выделить память
    }

    int get = fgetc(fp);
    if (get == EOF) {
        free(*str);
        return 0;
    }

    while (get != '\n' && (fp != stdin && get != EOF)) {
        (*str)[len] = (char)get;
        len += 1;

        if (len >= capacity) {
            capacity *= 2;  // Увеличение емкости строки вдвое
            char* temp = (char*)realloc(*str, sizeof(char) * capacity);
            if (temp == NULL) {
                free(*str);
                return 0;  // Не удалось перераспределить память
            }
            *str = temp;
        }
        get = fgetc(fp);
    }

    (*str)[len] = '\0';

    if (get == EOF && len == 0) {
        free(*str);
        return 0;
    }

    return 1;
}

int load(const char* filename, Node_t** tree) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 3; // ERROR_FILE_NOT_FOUND
    } else {
        clearTree(tree);
    }

    char* key = NULL;
    char* value = NULL;


    while (getLine(&key, file) != 0) {
        if (getLine(&value, file) == 0) {
            fclose(file);
            clearTree(tree);
            free(key);
            free(value);
            return 4; // ERROR_INVALID_FILE_FORMAT
        }
        *tree = insert(*tree, key, value);
    }

    fclose(file);
    return 0; // SUCCESS
}