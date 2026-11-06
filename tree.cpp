#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Elem_t;

#define LEFT false
#define RIGHT true

struct Node_t
{
    Elem_t data;

    Node_t* left;
    Node_t* right;
    
    Node_t* parent;
};

Node_t* NewNode(Node_t* parent, Elem_t value, bool direction);

void DeleteLeaf(Node_t* node);

void Print(const Node_t* node);


Node_t* NewNode(Node_t* parent, Elem_t value, bool direction)
{
    Node_t* node = (Node_t*) calloc(1, sizeof(Node_t));
    if (!node)
    {
        fprintf(stderr, "Calloc\n");
        abort();
    }

    node->data   = value;
    node->parent = parent;

    node->left  = NULL;
    node->right = NULL;
    
    if (parent)
    {
        if (direction == LEFT) parent->left = node;

        else parent->right = node;

    }

    return node;
}

void DeleteLeaf(Node_t* node)
{
    if (!node) return;
    if (node->left || node->right) return;

    if (node->parent) {
        if (node->parent->left  == node) node->parent->left  = NULL;
        if (node->parent->right == node) node->parent->right = NULL;
    }
    free(node);
}

void Print(const Node_t* node)
{
    assert(node);

    printf("( ");
    printf("%d ", node->data);

    if (node->left)  Print(node->left );
    if (node->right) Print(node->right);

    printf(")");

}