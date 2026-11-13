#include <stdio.h>
#include "tree.cpp"
#include "Dump_t.cpp"

int main()
{
    /*Node_t* v1 = NewNode(NULL, "препод", RIGHT);
    Node_t* v2 = NewNode(v1, "Овчос", RIGHT);
    Node_t* v3 = NewNode(v1, "ментор", LEFT);
    Node_t* v4 = NewNode(v3, "Костян", RIGHT);
    Node_t* v5 = NewNode(v3, "Виталя_Симонов", LEFT);


    FPrint(v1, "MIPT_Akinator.txt");*/

    Node_t* v = ReadTree("MIPT_Akinator.txt");

    //Print(v);
    Node_t* root = v;
    bool dir = LEFT;

    while (v && (v->right || v->left))
    {
        printf("Ваш персонаж %s?\n", v->data);
        int c = getchar();
        if (c == '+')
        {
            v = v->right;
            dir = RIGHT;
        }
        else
        {
            v = v->left;
            dir = LEFT;
        }
        while (c != '\n') c = getchar();

    }
    
    if (v) printf("Кажется, я знаю кто это: %s?\n", v->data);
    

    int c = getchar();
    if (c != '+')
    {
        printf("Кто это был?\n");
        char name[128] = {};
        scanf("%127s", name);

        printf("Чем %s отличается от %s: он ", name, v->data);
        char quest[128] = {};
        getchar();
        fgets(quest, sizeof(quest), stdin);

        char cur[128] = {};
        strcpy(cur, v->data);

        DeleteLeaf(v);

        bool Question = true;
        char* q_text = quest;
        if(strncmp(quest, "не ", strlen("не ")) == 0)
        {
            Question = false;
            q_text = quest + strlen("не ");
        }

        //printf("%s\n%s\n", name, q_text);

        Node_t* parent = v->parent;
        Node_t* q = NewNode(parent, q_text, dir);
        
        NewNode(q, cur,  Question ? LEFT : RIGHT);
        NewNode(q, name, Question ? RIGHT : LEFT);

        //if (!Question) printf("yaitsa\n");
    }

    FPrint(root, "MIPT_Akinator.txt");
    TreeDumpPng(root, "tree.png");
    
    TreeFree(root);
    

    return 0;
}
