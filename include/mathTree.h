#ifndef TREE
#define TREE

#include "errors.h"

enum types {
    ADD=1,
    SUB=2,
    DIV=3,
    MUL=4,
    NUM=5,
    VAR=6
};

struct node_t
{
    types type;
    char variable[20];
    double number;
    node_t* left;
    node_t* right;
};

void createTree(char** buffer, node_t* node);
error delTree(node_t* node);

//void printLeafDef(const node_t* node, const char* leafName, def_t* defParts, size_t i_dP);

#endif