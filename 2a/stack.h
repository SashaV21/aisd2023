
typedef struct StackArr {
    int size;
    int top;
    int * array;
} StackArr;

StackArr * CreateStack(int size);

int Get(StackArr * stack);

int Push(StackArr * stack, int elem);

void StackDelete(StackArr * stack);

int Pop(StackArr * stack);
