#include <stdio.h>
#include "tree.cpp"
#include "Dump_t.cpp"

int main()
{
    Node_t* v1 = NewNode(NULL, "Связан_с_8_лицеем", LEFT);
    Node_t* v2 = NewNode(v1, "Препод", RIGHT);
    Node_t* v3 = NewNode(v1, "Препод", LEFT);
    Node_t* v4 = NewNode(v2, "Митяй_Козлов", RIGHT);
    Node_t* v5 = NewNode(v2, "Хлiбнiков", LEFT);
    Node_t* v6 = NewNode(v3, "Спущинкин", RIGHT);
    Node_t* v7 = NewNode(v3, "Путин", LEFT);


    FPrint(v1, "AkinatorInfo.txt");

    Node_t* v = ReadTree("AkinatorInfo.txt");

    //Print(v);
    Node_t* root = v;

    while (v && (v->right || v->left))
    {
        printf("Ваш персонаж %s?\n", v->data);
        int c = getchar();
        if (c == '+')
        {
            v = v->right;
        }
        else
        {
            v = v->left;
        }
        while (c != '\n') c = getchar();

    }
    
    if (v) printf("Ответ: %s\n", v->data);
    else   printf("Не угадал :(\n");

    FPrint(root, "AkinatorInfo.txt");
    TreeDumpPng(root, "tree.png");
    
    TreeFree(root);
    

    return 0;
}
