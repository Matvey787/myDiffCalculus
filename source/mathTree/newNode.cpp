#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <mathTree.h>

// Function get node_l and node_r. Then new head (node) is formed from node_l and node_r (node_l go to head left daughter, node_r go to head right daughter). 

node_t* newNode(types type, const char* variable, double number, node_t* node_l, node_t* node_r){
    node_t* varNewNode = (node_t*)calloc(1, sizeof(node_t));
    varNewNode->type = type;
    varNewNode->number = number;
    strcpy(varNewNode->variable, variable);
    varNewNode->left = node_l;
    varNewNode->right = node_r;
    return varNewNode;
}