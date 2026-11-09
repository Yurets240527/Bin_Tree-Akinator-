#include <stdio.h>
#include "tree.cpp"
#include "Dump_t.cpp"

int main()
{
    /*Node_t* v1 = NewNode(NULL, 50, LEFT);
    Node_t* v2 = NewNode(v1, 67, RIGHT);
    Node_t* v3 = NewNode(v1, 20, LEFT);
    Node_t* v4 = NewNode(v3, 23, RIGHT);
    Node_t* v5 = NewNode(v3, 19, LEFT);


    Print(v1);
    FPrint(v1, "AkinatorInfo.txt");
    TreeDumpPng(v1, "tree.png");

    Buffer preorder = {};
    ReadFile("AkinatorInfo.txt", &preorder);
    printf("\n%s\n", preorder.buf);
    
    DeleteLeaf(v2);
    DeleteLeaf(v3);
    free(v1);*/

    Node_t* root = ReadTree("AkinatorInfo.txt");
    Print(root);
    TreeDumpPng(root, "tree.png");

    return 0;
}
