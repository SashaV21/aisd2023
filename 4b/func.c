#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int height(Node_t *tree) {
    return tree ? tree->height : 0;
}

void fix_height(Node_t *tree) {
    unsigned int hl = height(tree->left);
    unsigned int hr = height(tree->right);
    tree->height = (hl > hr ? hl : hr) + 1;
}

Node_t *rotate_left(Node_t *root) {
    Node_t *right = root->right;
    root->right = right->left;
    right->left = root;
    fix_height(root);
    fix_height(right);
    return right;
}

Node_t *rotate_right(Node_t *root) {
    Node_t *left = root->left;
    root->left = left->right;
    left->right = root;
    fix_height(root);
    fix_height(left);
    return left;
}

int balance_factor(Node_t *tree) {
    return height(tree->right) - height(tree->left);
}

Node_t *balance(Node_t *tree) {
    fix_height(tree);
    if (balance_factor(tree) == 2) {
        if (balance_factor(tree->right) < 0) {
            tree->right = rotate_right(tree->right);
        }
        return rotate_left(tree);
    } else if (balance_factor(tree) == -2) {
        if (balance_factor(tree->left) > 0) {
            tree->left = rotate_left(tree->left);
        }
        return rotate_right(tree);
    }
    return tree;
}

NodeValue_t *create_node_value(char *value) {
    NodeValue_t *new_node_value = (NodeValue_t *)malloc(sizeof(NodeValue_t));
    new_node_value->value = value;
    new_node_value->next = NULL;
    return new_node_value;
}

void insert_node_value(Node_t *node, char *value) {
    NodeValue_t *new_node_value = create_node_value(value);
    if (node->values == NULL) {
        node->values = new_node_value;
    } else {
        NodeValue_t *current = node->values;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node_value;
    }
}

Node_t *create_node(char *key, char *value) {
    Node_t *new_node = (Node_t *)malloc(sizeof(Node_t));
    new_node->key = key;
    new_node->height = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->values = NULL;
    insert_node_value(new_node, value);
    return new_node;
}

Node_t *insert(Node_t *tree, char *key, char *value) {
    if (!tree) {
        return create_node(key, value);
    }
    int cmp = strcmp(key, tree->key);
    if (cmp == 0) {
        insert_node_value(tree, value);
        free(key);
    } else if (cmp < 0) {
        tree->left = insert(tree->left, key, value);
    } else {
        tree->right = insert(tree->right, key, value);
    }
    return balance(tree);
}

Node_t* deleteNode(Node_t* root, const char* key, int* errorCode) {
    if (root == NULL) {
        *errorCode = 1; // Значение не найдено
        return NULL;
    }

    int cmp = strcmp(key, root->key);

    if (cmp < 0) {
        root->left = deleteNode(root->left, key, errorCode);
    } else if (cmp > 0) {
        root->right = deleteNode(root->right, key, errorCode);
    } else {
        // Найден узел с заданным ключом
        if (root->values->next != NULL) {
            // У узла есть несколько значений, удаляем последнее из них
            NodeValue_t* oldValue = root->values;
            root->values = oldValue->next;

            free(oldValue->value);
            free(oldValue);
            *errorCode = 0;
        } else {
            // Узел без потомков или с одним потомком
            if (root->left == NULL) {
                Node_t* temp = root->right;
                free(root->key);
                free(root->values->value);
                free(root->values);
                free(root);
                *errorCode = 0; // Успешно
                return temp;
            } else if (root->right == NULL) {
                Node_t* temp = root->left;
                free(root->key);
                free(root->values->value);
                free(root->values);
                free(root);
                *errorCode = 0; // Успешно
                return temp;
            }

            // Узел с двумя потомками
            Node_t* successor = root->right;
            while (successor->left != NULL) {
                successor = successor->left;
            }

            free(root->values->value);
            free(root->values);
            free(root->key);
            root->key = strdup(successor->key);
            root->values = create_node_value(strdup(successor->values->value));

            root->right = deleteNode(root->right, successor->key, errorCode);
        }
    }

    return balance(root);
}

void printReverseValues(Node_t* root, const char* leftValue, const char* rightValue) {
    if (root == NULL) {
        return;
    }

    // Рекурсивно обходим левое поддерево
    printReverseValues(root->left, leftValue, rightValue);

    // Рекурсивно обходим правое поддерево
    printReverseValues(root->right, leftValue, rightValue);

    if (strcmp(root->key, leftValue) > 0 && strcmp(root->key, rightValue) < 0) {
        // Ключ находится в заданном интервале, выводим значения данного узла
        NodeValue_t* currValue = root->values;
        fprintf(stdout, "(%s: ", root->key);
        while (currValue != NULL) {
            if (currValue->next == NULL) {
                fprintf(stdout, "%s", currValue->value);
            } else {
                fprintf(stdout, "%s ", currValue->value);
            }
            currValue = currValue->next;
        }
        fprintf(stdout, ") ");
    }
}

NodeValue_t* findNode(Node_t* root, const char* key, int index, int* result) {
    if (root == NULL) {
        *result = 1; // ERROR_KEY_NOT_FOUND
        return NULL;
    }

    int cmp = strcmp(key, root->key);
    if (cmp == 0) {
        // Найден узел с заданным ключом

        NodeValue_t* currValue = root->values;
        int count = 1;

        if (currValue == NULL) {
            *result = 2; // ERROR_INVALID_INDEX
            return NULL;
        }

        while (currValue != NULL) {
            if (count == index) {
                // Найдено значение с указанным порядковым номером
                *result = 0; // SUCCESS
                return currValue;
            }

            currValue = currValue->next;
            count++;
        }

        // Порядковый номер превышает количество значений в узле
        *result = 2; // ERROR_INVALID_INDEX
        return NULL;
    }

    // Рекурсивный поиск в левом или правом поддереве
    if (cmp < 0) {
        return findNode(root->left, key, index, result);
    } else {
        return findNode(root->right, key, index, result);
    }
}

NodeValue_t * findMaxKeyElement(Node_t* root, const char* maxKey, int position, int *result) {
    if (root == NULL) {
        *result = 1; // ERROR_TREE_EMPTY
        return NULL;
    }
    while (root->right != NULL && strcmp(root->right->key, maxKey) <= 0) {
        root = root->right;
    }

    NodeValue_t* currValue = root->values;
    int count = 1;

    if (currValue == NULL) {
        *result = 2; // ERROR_INVALID_INDEX
        return NULL;
    }

    while (currValue != NULL) {
        if (count == position) {
            // Найдено значение с указанным порядковым номером
            *result = 0; // SUCCESS
            return currValue;
        }

        currValue = currValue->next;
        count++;
    }

    // Порядковый номер превышает количество значений в узле
    *result = 2; // ERROR_INVALID_INDEX
    return NULL;
}


//выводит дерево (слева находится корень)
void printTree(Node_t *root, int level){
    if (root == NULL){
        return;
    }

    printTree(root->right, level + 1);

    for (int i = 0; i < level; i++){
        printf("    ");
    }

    printf("%s\n", root->key);

    printTree(root->left, level + 1);
}

void clearTree(Node_t** tree) {
    if (*tree == NULL) {
        return;
    }

    clearTree(&((*tree)->left));
    clearTree(&((*tree)->right));

    // Освобождаем память, занятую списком значений
    NodeValue_t* current = (*tree)->values;
    while (current != NULL) {
        NodeValue_t* temp = current;
        current = current->next;
        free(temp->value);
        temp->value = NULL;
        free(temp);
        temp = NULL;
    }

    // Освобождаем память, занятую ключом
    free((*tree)->key);
    (*tree)->key = NULL;
    // Освобождаем память, занятую узлом
    free(*tree);

    *tree = NULL;
}
