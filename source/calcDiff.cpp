#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "mathTree.h"
#include "calcDiff.h"

static node_t* calcDiff(node_t* node);

node_t* getDiff(node_t* operandTree){
    node_t* resultTree = calcDiff(operandTree);
    delTree(operandTree);
    return resultTree;
}

static node_t* calcDiff(node_t* node)
{
    switch (node->type)
    {
    case NUM:
        return newNode(NUM, "no var", 0, nullptr, nullptr);

    case VAR:
        return newNode(NUM, "no var", 1, nullptr, nullptr);

    case ADD:
        return newNode(ADD, "no var", NAN, calcDiff(node->left), calcDiff(node->right));

    case SUB:
        return newNode(SUB, "no var", NAN, calcDiff(node->left), calcDiff(node->right));

    case MUL:
    {
        node_t* dL = calcDiff(node->left);
        node_t* dR = calcDiff(node->right);
        node_t* cL = copyNode(node->left);
        node_t* cR = copyNode(node->right);
        return newNode(ADD,"no var", NAN, newNode(MUL, "no var", NAN, dL, cR), newNode(MUL, "no var", NAN, cL, dR));
    }
    case DIV:
    {
        node_t* cL = copyNode(node->left);
        node_t* cR = copyNode(node->right);
        node_t* dL = calcDiff(node->left);
        node_t* dR = calcDiff(node->right);
        return newNode(DIV, "no var", NAN, newNode(SUB, "no var", NAN, newNode(MUL, "no var", NAN, dL, copyNode(cR)), newNode(MUL,"no var", NAN, cL, dR)), newNode(MUL, "no var", NAN, copyNode(cR), cR));
    }

    default:
        break;
    }
}

node_t* newNode(types type, const char* variable, double number, node_t* node_l, node_t* node_r){
    node_t* varNewNode = (node_t*)calloc(1, sizeof(node_t));
    varNewNode->type = type;
    varNewNode->number = number;
    strcpy(varNewNode->variable, variable);
    varNewNode->left = node_l;
    varNewNode->right = node_r;
    return varNewNode;
}

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