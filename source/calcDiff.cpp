#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "mathTree.h"
#include "calcDiff.h"
#include "constants.h"

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

    case POW:
        if (node->left->type == NUM)
        {
            if (node->right->type == NUM)
                return newNode(NUM, "no var", 0, nullptr, nullptr);
            
            printf("pow worked\n");
            node_t* cL = copySubtree(node->left);
            node_t* cR = copySubtree(node->right);
            node_t* dR = calcDiff(node->right);
            return newNode(MUL, "no var", NAN, newNode(MUL, "no var", NAN, cR, newNode(LOG, "no var", NAN, cL, newNode(NUM, "no var", c_exp, nullptr, nullptr))), dR);
        }
        else
        {   
            printf("pow worked\n");
            node_t* cL = copySubtree(node->left);
            node_t* cR = copySubtree(node->right);
            node_t* dL = calcDiff(node->left);
            cR->number -= 1;
            return newNode(MUL, "no var", NAN, newNode(MUL, "no var", NAN, copySubtree(node->right), newNode(POW, "no var", NAN, cL, cR)), dL);
        }
            
    case MUL:
    {
        node_t* dL = calcDiff(node->left);
        node_t* dR = calcDiff(node->right);
        node_t* cL = copySubtree(node->left);
        node_t* cR = copySubtree(node->right);
        return newNode(ADD,"no var", NAN, newNode(MUL, "no var", NAN, dL, cR), newNode(MUL, "no var", NAN, cL, dR));
    }
    case DIV:
    {
        node_t* cL = copySubtree(node->left);
        node_t* cR = copySubtree(node->right);
        node_t* dL = calcDiff(node->left);
        node_t* dR = calcDiff(node->right);
        return newNode(DIV, "no var", NAN, newNode(SUB, "no var", NAN, newNode(MUL, "no var", NAN, dL, copySubtree(cR)), newNode(MUL,"no var", NAN, cL, dR)),
                                           newNode(MUL, "no var", NAN, copySubtree(cR), cR));
    }

    case SIN:
    {
        if (node->left != nullptr)
        {
            node_t* cL = copySubtree(node->left);
            node_t* dL = calcDiff(node->left);
            return newNode(MUL, "no var", NAN, newNode(COS, "no var", NAN, cL, nullptr), dL);
        }
        break;
    }
    case COS:
    {
        if (node->left != nullptr)
        {
            node_t* cL = copySubtree(node->left);
            node_t* dL = calcDiff(node->left);
            node_t* minus_one = (node_t*)calloc(1, sizeof(node_t));
            *minus_one = {NUM, "no var", -1, nullptr, nullptr};
            return newNode(MUL, "no var", NAN, newNode(MUL, "no var", NAN, minus_one, newNode(SIN, "no var", NAN, cL, nullptr)), dL);
        }
        break;
    }
    case LOG:
    {
        if (node->left != nullptr && node->right != nullptr)
        {
            node_t* cL = copySubtree(node->left);
            node_t* cR = copySubtree(node->right);
            node_t* dL = calcDiff(node->left);
            return newNode(MUL, "no var", NAN, newNode(DIV, "no var", NAN, newNode(NUM, "no var", 1, nullptr, nullptr), newNode(MUL, "no var", NAN, cL, newNode(LOG, "no var", NAN, cR, newNode(NUM, "no var", c_exp, nullptr, nullptr)))), dL);
        }
        break;   
    }
    default:
        break;
    }
    return nullptr;
}
