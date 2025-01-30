#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int *vector;
    struct Node *left, *right, *center;
} Node;

#define X 0
#define Y 1
#define Z 2


const int start_vector[3] = {3, 4, 5}
const int matr_A[3][3] = {{1, -2, 2}, {2, -1, 2}, {2, -2, 3}}
const int matr_B[3][3] = {{1, 2, 2}, {2, 1, 2}, {2, 2, 3}}
const int matr_C[3][3] = {{-1, 2, 2}, {-2, 1, 2}, {-2, 2, 3}}

Node *get_node(){
    Node* root = malloc(sizeof(Node));
    root->left = root->right = root->center = NULL;
    root->vector = calloc(3, sizeof(int));
    return root;
} 

int *mult(int *base, const int matr[3][3]){
    int *new = calloc(3, sizeof(int));
     new[X] = base[X] * matr[0][0] + base[Y] * matr[0][1] + base[Z] * matr[0][2];
     new[Y] = base[X] * matr[1][0] + base[Y] * matr[1][1] + base[Z] * matr[1][2];
     new[Z] = base[X] * matr[2][0] + base[Y] * matr[2][1] + base[Z] * matr[2][2];



    return new;
}


Node *biult(Node *root, int height, int iteration){
    if(!root){
        root = get_node();
        root->vector[X] = 3;
        root->vector[Y] = 4;
        root->vector[Z] = 5;
        return root;
    }
    if(iteration < height){
        int *vector_for_left = mult(root->vector, matr_A);
        Node *left = get_node();
        left->vector = vector_for_left;
        built(root->left, height, iteration + 1);

        int *vector_for_centr = mult(root->vector, matr_B);
        Node *centr = get_node();
        centr->vector = vector_for_centr;
        built(root->center, height, iteration + 1);

        int *vector_for_right = mult(root->vector, matr_C);
        Node *right = get_node();
        right->vector = vector_for_right;
        built(root->right, height, iteration + 1);
    }
    return root;
}









