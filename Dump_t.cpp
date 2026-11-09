#include <stdio.h>
#include <stdlib.h>
#include "tree.cpp"



void dump_node(const Node_t* node, FILE* out)
{
    if (!node) return;

    fprintf(out,
        "    n%p [shape=Mrecord, label=\"{ " TREE_FMT " | %p | L=%p R=%p }\"];\n",
        (const void*)node, node->data,
        (const void*)node,
        (const void*)node->left,
        (const void*)node->right);

    if (node->left) {
        fprintf(out, "    n%p -> n%p [color=\"#f70202\", label=\"NO\"];\n",
                (const void*)node, (const void*)node->left);
        dump_node(node->left, out);
    }
    if (node->right) {
        fprintf(out, "    n%p -> n%p [color=\"#0ef702\", label=\"YES\"];\n",
                (const void*)node, (const void*)node->right);
        dump_node(node->right, out);
    }
}

void TreeDumpPng(const Node_t* root, const char* png_path)
{
    char dot_path[512];
    snprintf(dot_path, sizeof dot_path, "%s.dot", png_path);

    FILE* f = fopen(dot_path, "w");
    if (!f) { perror("fopen"); return; }

    fprintf(f, "digraph BST {\n");
    fprintf(f, "    node [shape=Mrecord, fontname=\"Consolas\", fontsize=10];\n");
    if (root) dump_node(root, f);
    fprintf(f, "}\n");
    fclose(f);

    char cmd[1024];
    snprintf(cmd, sizeof cmd, "dot -Tpng \"%s\" -o \"%s\"", dot_path, png_path);

    int rc = system(cmd);
    if (rc != 0)
        fprintf(stderr, "[dump] dot failed (rc=%d). graphviz в PATH?\n", rc);
}
