#include <stdio.h>
#include "tree.cpp"

int main()
{
    Node_t* v1 = NewNode(NULL, 50, LEFT);
    Node_t* v2 = NewNode(v1, 20, LEFT);
    Node_t* v3 = NewNode(v1, 60, RIGHT);

    Print(v1);
    
    DeleteLeaf(v2);
    DeleteLeaf(v3);
    free(v1);
    return 0;
}
