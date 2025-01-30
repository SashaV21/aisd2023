#include "dialog.h"

const char *msgs[] = {"0.Quit", "1.LoadTreeFromFile","2.Add", "3.Find", "4.SpecialFind", "5.Delete", "6.Show", "7.Timing", "8.PrintTree"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
int (*fptr[])(Node_t **) = {NULL,D_load, D_Add, D_Find, D_SpecialFind, D_Delete, D_Show, D_Timing, D_PrintTree};


int main(){

    Node_t *root = NULL;

    int rc = 0;
    while ((rc = dialog(msgs, NMsgs))){
        if (fptr[rc](&root)){
            break;
        }
    }
    printf("That's all. Bye!\n");
    clearTree(&root);
    return 0;
}