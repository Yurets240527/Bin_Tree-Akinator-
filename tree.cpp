#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef int Elem_t;
#define TREE_FMT "%d"

#define LEFT false
#define RIGHT true


struct Node_t
{
    Elem_t data;

    Node_t* left;
    Node_t* right;
    
    Node_t* parent;
};

struct Buffer
{
    char* buf;
    size_t size;
};

Node_t* NewNode(Node_t* parent, Elem_t value, bool direction);

void DeleteLeaf(Node_t* node);

void Print(const Node_t* node);

void FPrint(const Node_t* node, const char* filename);


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

void TreeFree(Node_t* node)
{
    if (!node) return;
    TreeFree(node->left);
    TreeFree(node->right);
    free(node);
}

void Print(const Node_t* node)
{
    if (!node) { printf("()"); return; }

    printf("( ");
    printf(TREE_FMT " ", node->data);

    if (node->left)  Print(node->left );
    if (node->right) Print(node->right);

    printf(")");

}

void fprint_rec(const Node_t* node, FILE* fp)
{
    if (!node) { fprintf(fp, "()"); return; }

    fprintf(fp, "( ");
    fprintf(fp, TREE_FMT " ", node->data);
    fprint_rec(node->left,  fp);
    fprintf(fp, " ");
    fprint_rec(node->right, fp);
    fprintf(fp, " )");
}

void FPrint(const Node_t* node, const char* filename)
{
    FILE* fp = fopen(filename, "w");
    if (!fp) { perror("fopen"); return; }
    fprint_rec(node, fp);
    fclose(fp);
}

int ReadTree(const char* filename, Node_t root)
{
    FILE* fp = fopen(filename, "r");
    assert(fp);
    
}

int ReadFile(const char* filename, Buffer* preorder)
{
    if (!preorder) return 1;

    int fd = open(filename, O_RDONLY);
    if (fd < 0) { fprintf(stderr, "open\n"); return 1; }

    struct stat st;
    if (fstat(fd, &st) != 0) { fprintf(stderr, "fstat\n"); close(fd); return 1; }

    size_t sz = (size_t)st.st_size;

    preorder->buf = (char*) calloc(sz + 1, sizeof(char));
    if (!preorder->buf) { close(fd); return 1; }

    preorder->size = read(fd, preorder->buf, sz);
    if (preorder->size < 0) { fprintf(stderr, "read"); free(preorder->buf); close(fd); return 1; }

    preorder->buf[preorder->size] = '\0';

    close(fd);

    return 0;
}

const char* Skip(const char* p)
{
    while (*p && (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')) p++;
    return p;
}

static Node_t* MakeNode(Elem_t val)
{
    Node_t* n = (Node_t*) calloc(1, sizeof(Node_t));
    if (!n) { fprintf(stderr, "calloc\n"); abort(); }
    n->data = val;
    return n;
}

Node_t* ParseSubtree(const char** p, Node_t* parent, bool* ok)
{
    *ok = false;
    *p = Skip(*p);

    if (**p != '(') return NULL;
    (*p)++;

    *p = Skip(*p);
    if (**p == ')') { (*p)++; *ok = true; return NULL; }

    Elem_t val = 0;
    int n = 0;
    if (sscanf(*p, TREE_FMT "%n", &val, &n) != 1) return NULL;
    *p += n;

    Node_t* node = MakeNode((Elem_t)val);
    node->parent = parent;

    bool lok = false;
    bool rok = false;
    node->left  = ParseSubtree(p, node, &lok);
    if (!lok) { TreeFree(node); return NULL; }

    node->right = ParseSubtree(p, node, &rok);
    if (!rok) { TreeFree(node); return NULL; }

    *p = Skip(*p);
    if (**p != ')') { TreeFree(node); return NULL; }
    (*p)++;

    *ok = true;
    return node;
}

Node_t* ReadTree(const char* filename)
{
    Buffer preorder = {};
    if (ReadFile(filename, &preorder) != 0) return NULL;

    const char* p = preorder.buf;
    bool ok = false;
    Node_t* root = ParseSubtree(&p, NULL, &ok);

    free(preorder.buf);

    if (!ok) { TreeFree(root); return NULL; }
    
    return root;
}


#endif