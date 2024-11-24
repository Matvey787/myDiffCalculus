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
node_t* newNode(types type, const char* variable, double number, node_t* node_l, node_t* node_r);
node_t* copyNode(node_t* node);


#endif