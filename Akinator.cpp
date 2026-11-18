#include <stdio.h>
#include "tree.cpp"
#include "Dump_t.cpp"
#include "Stack.cpp"

#define MAXLEN 128
#define MAXSIZE 100

int Akinator(const char* filename, const char* png)
{
    Tree* tree = TreeCtor();
    tree->root = ReadTree(filename);

    Node_t* v = tree->root;
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
        char name[MAXLEN] = {};
        scanf("%127s", name);

        printf("Чем %s отличается от %s: он ", name, v->data);
        char quest[MAXLEN] = {};
        getchar();
        fgets(quest, sizeof(quest), stdin);

        char cur[MAXLEN] = {};
        strcpy(cur, v->data);

        DeleteLeaf(v);

        bool Question = true;
        char* q_text = quest;
        if(strncmp(quest, "не ", strlen("не ")) == 0)
        {
            Question = false;
            q_text = quest + strlen("не ");
        }


        Node_t* parent = v->parent;
        Node_t* q = NewNode(parent, q_text, dir);
        
        NewNode(q, cur,  Question ? LEFT : RIGHT);
        NewNode(q, name, Question ? RIGHT : LEFT);

    }

    FPrint(tree->root, filename);
    TreeDumpPng(tree->root, png);
    
    TreeDtor(tree);
    

    return 0;

}

Node_t* Search(Node_t* node, Elem_t elem)
{
    if (!node) return NULL;
    if (strcmp(node->data, elem) == 0) return node;

    Node_t* found = Search(node->left, elem);
    if (found) return found;

    return Search(node->right, elem);
}

int Path(const char* filename, const char* name)
{
    Tree* tree = TreeCtor();
    tree->root = ReadTree(filename);

    Node_t* v = Search(tree->root, name);

    if (!v)
    {
        printf("%s was not found", name);
        TreeDtor(tree);
        return 1;
    }

    printf(TREE_FMT ": ", name);

    stack path = {};
    InitStack(&path, MAXSIZE);

    int len = 0;

    while (v->parent)
    {
        if (v->parent->left == v) 
        {
            char buf[MAXLEN] = "не ";
            strcat(buf, v->parent->data);
            StackPush(&path, strdup(buf));
        }

        else StackPush(&path, strdup(v->parent->data));
       
        
        v = v->parent;
        len++;
    }
    //STACK_DUMP(path);

    while (len > 0)
    {
        printf(TREE_FMT, StackPop(&path));
        if (len > 1) printf("->");
        len--;
    }

    return 0;

}

int Compare(const char* filename, const char* name1, const char* name2)
{
    Tree* tree = TreeCtor();
    tree->root = ReadTree(filename);
    if (!tree->root) { TreeDtor(tree); return 1; }

    if (!Search(tree->root, name1)) { printf("%s not found\n", name1); TreeDtor(tree); return 1; }
    if (!Search(tree->root, name2)) { printf("%s not found\n", name2); TreeDtor(tree); return 1; }

    
    Node_t* cur = tree->root;
    while (cur)
    {
        if (Search(cur->left,  name1) && Search(cur->left,  name2)) { cur = cur->left;  continue; }
        if (Search(cur->right, name1) && Search(cur->right, name2)) { cur = cur->right; continue; }

        break;
    }

    printf("Чем %s отличается от %s?\n", name1, name2);

    
    if (Search(cur->left,  name1))
    {
        printf("%s не %s", name1, cur->data);
    }

    else printf("%s %s", name1, cur->data);
    
    TreeDtor(tree);
    return 0;
}