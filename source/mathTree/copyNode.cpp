#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <mathTree.h>

// Function get node and returns a copy of the subtree starting from the one passed node.

node_t* copyNode(node_t* node){
    assert(node != nullptr);
    node_t* varCopyNode = (node_t*)calloc(1, sizeof(node_t));
    assert(varCopyNode != nullptr);
    varCopyNode->type = node->type;
    varCopyNode->number = node->number;
    strcpy(varCopyNode->variable, node->variable);

    if (node->left != nullptr)
    {
        varCopyNode->left = copyNode(node->left);
    }
    else
        varCopyNode->left = nullptr;

    if (node->right != nullptr)
    {
        varCopyNode->right = copyNode(node->right);
    }  
    else
        varCopyNode->right = nullptr;
    return varCopyNode;
}