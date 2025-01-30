#include <time.h>
#include "dialog.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

char* getInputString() {
    int capacity = 10;  // Начальная емкость буфера
    int length = 0;     // Текущая длина строки
    char* buffer = malloc(capacity * sizeof(char));

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (length >= capacity - 1) {
            capacity *= 2;  // Увеличение емкости буфера в два раза
            char* resizedBuffer = realloc(buffer, capacity * sizeof(char));

            buffer = resizedBuffer;
        }

        buffer[length] = c;
        length++;
    }

    if (length == 0) {
        free(buffer);
        return NULL;
    }

    char* resizedBuffer = realloc(buffer, (length + 1) * sizeof(char));

    resizedBuffer[length] = '\0';

    return resizedBuffer;
}

int dialog(const char *msgs[], int N) {
    char *errmsg = "";
    int rc = 0;
    int i, n;

    do {
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";

        for (i = 0; i < N; ++i) {
            puts(msgs[i]);
        }
        puts("Make your choice: --> ");

        n = scanf("%i", &rc);
        if (n == 0) {
            rc = 0;
        }
    } while (rc < 0 || rc >= N);
    return rc;
}

int D_load(Node_t **root) {
    char filename[100];

    printf("Enter the filename: ");
    scanf("%s", filename);

    int result = load(filename, root);

    if (result == 0) {
        printf("Data successfully loaded into the tree.\n");
    } else if (result == 3) {
        printf("File not found.\n");
    } else if (result == 4) {
        printf("Invalid file format.\n");
    }

    return 0;
}

int D_Add(Node_t** node) {
    clearInputBuffer();
    printf("Enter the key: ");
    char* keyStr = getInputString();

    printf("Enter the value: ");
    char* valueStr = getInputString();

    if (keyStr == NULL || valueStr == NULL) {
        printf("Error: Empty key or value.\n");
        return 0;
    }

    *node = insert(*node, keyStr, valueStr);
    printf("Node added.\n");
    return 0;
}

int D_Delete(Node_t **root) {

    clearInputBuffer();
    printf("Enter the key value: ");
    char *key = getInputString();

    if (key == NULL) {
        printf("key len error. Key len must be greater than zero.\n");
        return 0;
    }

    int result;

    *root = deleteNode(*root, key, &result);

    if (result == 0) {
        printf("Node with key \"%s\" deleted successfully.\n", key);
    } else if (result == 1) {
        printf("Node with the specified key \"%s\" not found.\n", key);
    }

    free(key);
    return 0;
}

int D_Find(Node_t **root) {
    int index;

    clearInputBuffer();
    printf("Enter the key: ");
    char *key = getInputString();

    if (key == NULL) {
        printf("key len error. Key len must be greater than zero.\n");
        return 0;
    }

    printf("Enter the value position starting with 1: ");
    scanf("%d", &index);

    if (index <= 0) {
        free(key);
        printf("Index error.\n");
        return 0;
    }

    int result;
    NodeValue_t* foundNode = findNode(*root, key, index, &result);

    if (result == 0 && foundNode != NULL) {
        printf("Found value: %s\n", (foundNode->value));
    } else if (result == 1) {
        printf("Element with the specified key not found.\n");
    } else if (result == 2) {
        printf("Invalid index.\n");
    }
    free(key);
    return 0;
}

int D_SpecialFind(Node_t **root) {

    clearInputBuffer();
    printf("Enter the maximum allowable key: ");
    char *maxKey = getInputString();
    if (maxKey == NULL) {
        printf("Max key len error. Max key len must be greater than zero.\n");
        return 0;
    }

    int index;

    printf("Enter the value position starting with 1: ");
    scanf("%d", &index);

    if (index <= 0) {
        free(maxKey);
        printf("Index error.\n");
        return 0;
    }


    int result;
    NodeValue_t* foundNode = findMaxKeyElement(*root, maxKey,index, &result);

    if (result == 0 && foundNode != NULL) {
        printf("Found value: %s\n", (foundNode->value));
    } else if (result == 1) {
        printf("Element with the maximum key value not found.\n");
    } else if (result == 2) {
        printf("Invalid index.\n");
    }

    free(maxKey);
    return 0;
}

int D_Show(Node_t **root) {

    clearInputBuffer();
    printf("Enter the left boundary of the interval: ");
    char *leftKeyValue = getInputString();

    printf("Enter the right boundary of the interval: ");
    char *rightKeyValue = getInputString();

    if (leftKeyValue == NULL || rightKeyValue == NULL) {
        free(leftKeyValue);
        free(rightKeyValue);
        printf("The length of the interval boundary must be greater than 0.");
        return 0;
    }

    printReverseValues(*root, leftKeyValue, rightKeyValue);

    printf("\n");

    free(leftKeyValue);
    free(rightKeyValue);
    return 0;
}

int D_PrintTree(Node_t **root) {
    if (root == NULL) {
        printf("Tree is empty");
        return 0;
    }

    printTree(*root, 0);
    return 0;
}

char* generateRandomString() {
    const char charset[] = "abcdefghTUVWXYZ";
    int length = rand() % 6;
    char* randomString = malloc((length + 1) * sizeof(char));

    for (int i = 0; i < length; i++) {
        int index = rand() % (sizeof(charset) - 1);
        randomString[i] = charset[index];
    }

    randomString[length] = '\0';
    return randomString;
}


int D_Timing() {
    Node_t *root = NULL;
    int errorCode;
    int numberOfTests = 10, cnt = 10000, numberOfElemForTests = 10000;
    clock_t first, last;
    srand(time(NULL));


    while (numberOfTests > 0) {
        for (int i = 0; i < cnt; i++){
            root = insert(root, generateRandomString(), generateRandomString());
        }

        printf("Timing#%d. Number of elements = %d\n    ", (10 - numberOfTests) + 1,cnt);

        //test time of insert
        first = clock();
        for (int i = 0; i < numberOfElemForTests; i++){
            root = insert(root, generateRandomString(), generateRandomString());
        }
        last = clock();
        printf("Time of insert %d elements: %.10fs\n    ", numberOfElemForTests, (double) (last - first) / CLOCKS_PER_SEC);

        //test time of delete
        first = clock();
        for (int i = 0; i < numberOfElemForTests; i++){
            char *randomString = generateRandomString();
            root = deleteNode(root, randomString, &errorCode);
            free(randomString);
        }
        last = clock();
        printf("Time of delete %d elements: %.10fs\n    ", numberOfElemForTests, (double) (last - first) / CLOCKS_PER_SEC);

//      test of find node
        first = clock();
        for (int i = 0; i < numberOfElemForTests; i++){
            char *randomString = generateRandomString();
            findNode(root, randomString, 1, &errorCode);
            free(randomString);
        }
        last = clock();
        printf("Time of find %d elements: %.10fs\n    ", numberOfElemForTests, (double) (last - first) / CLOCKS_PER_SEC);

        //test of specific find node
        first = clock();
        for (int i = 0; i < numberOfElemForTests; i++){
            char *randomString = generateRandomString();
            findMaxKeyElement(root, randomString,1, &errorCode);
            free(randomString);
        }
        last = clock();
        printf("Time of specific find %d elements: %.10fs\n", numberOfElemForTests, (double) (last - first) / CLOCKS_PER_SEC);

        numberOfTests-= 1;
        cnt += (int) (cnt * 0.1);
        clearTree(&root);
    }

    return 0;
}