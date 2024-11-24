#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "mathTree.h"

static error delBranches(node_t* node);

error delTree(node_t* node){
    assert(node != nullptr);
    if (node == nullptr)
        return NULLPTR_ERROR;

    delBranches(node);
    free(node);

    node = nullptr;
    return NO_ERRORS;
}

static error delBranches(node_t* node){
    assert(node != nullptr);

    error status = NO_ERRORS;

    if (node == nullptr)
        return NULLPTR_ERROR;

    if (node->left != nullptr)
        status = delBranches(node->left);
    
    if (node->right != nullptr)
        status = delBranches(node->right);

    if (status != NO_ERRORS)
        return status;

    if (node->left != nullptr)
    {
        free(node->left);
        node->left = nullptr;
    }
    
    if (node->right != nullptr)
    {
        free(node->right);
        node->right = nullptr;
    }
    return status;
}