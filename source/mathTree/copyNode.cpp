#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <mathTree.h>

node_t* copyNode(node_t* node){
    assert(node != nullptr);
    node_t* varCopyNode = (node_t*)calloc(1, sizeof(node_t));
    assert(varCopyNode != nullptr);
    varCopyNode->type = node->type;
    varCopyNode->number = node->number;
    strcpy(varCopyNode->variable, node->variable);
    varCopyNode->left = node->left;
    varCopyNode->right = node->right;
    return varCopyNode;
    
}

// Function get node and returns a copy of the subtree starting from the one passed node.

node_t* copySubtree(node_t* node){
    assert(node != nullptr);
    node_t* varCopyNode = (node_t*)calloc(1, sizeof(node_t));
    assert(varCopyNode != nullptr);
    varCopyNode->type = node->type;
    varCopyNode->number = node->number;
    strcpy(varCopyNode->variable, node->variable);

    if (node->left != nullptr)
    {
        varCopyNode->left = copySubtree(node->left);
    }
    else
        varCopyNode->left = nullptr;

    if (node->right != nullptr)
    {
        varCopyNode->right = copySubtree(node->right);
    }  
    else
        varCopyNode->right = nullptr;
    return varCopyNode;
}