#ifndef TREE_FUNC_H
#define TREE_FUNC_H


typedef struct NodeValue {
    char *value;
    struct NodeValue *next;
} NodeValue_t;

typedef struct Node {
    char *key;
    unsigned int height;
    NodeValue_t *values;
    struct Node *left, *right;
} Node_t;

Node_t *create_node(char *key, char *value);
void clearTree(Node_t** tree);
Node_t *insert(Node_t *tree, char *key, char *value);
Node_t* deleteNode(Node_t* root, const char *key, int *errorCode);
void printReverseValues(Node_t* root, const char* leftValue, const char* rightValue);
NodeValue_t* findNode(Node_t* root, const char* key, int index, int* result);
NodeValue_t * findMaxKeyElement(Node_t* root, const char* maxKey, int position, int *result);
void printTree(Node_t *root, int level);

#endif
