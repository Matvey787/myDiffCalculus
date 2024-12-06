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

#define _newNode(name, l_subtr, r_subtr) newNode(ND_##name, "no var", NAN, l_subtr, r_subtr)
#define _newNode2(name, num) newNode(ND_##name, "no var", num, nullptr, nullptr)

static node_t* calcDiff(node_t* node)
{
    switch (node->type)
    {
    case ND_NUM:
        return _newNode2(NUM, 0);

    case ND_VAR:
        return _newNode2(NUM, 1);

    case ND_ADD:
        return _newNode(ADD, calcDiff(node->left), calcDiff(node->right));

    case ND_SUB:
    {
        node_t* dL = calcDiff(node->left);
        node_t* dR = calcDiff(node->right);
        return _newNode(SUB, dL, dR);
    }
    case ND_POW:
        if (node->left->type == ND_NUM)
        {
            if (node->right->type == ND_NUM)
                return newNode(ND_NUM, "no var", 0, nullptr, nullptr);
            
            ////printf("pow worked\n");
            node_t* cL = copySubtree(node->left);
            node_t* cR = copySubtree(node->right);
            node_t* dR = calcDiff(node->right);
            return _newNode(MUL, _newNode(MUL, cR, _newNode(LOG, cL, _newNode2(NUM, c_exp))), dR);
        }
        else
        {   
            //printf("pow worked\n");
            node_t* cL = copySubtree(node->left);
            node_t* cR1 = copySubtree(node->right);
            node_t* cR2 = copySubtree(node->right);
            node_t* dL = calcDiff(node->left);
            cR1->number -= 1;
            return _newNode(MUL, _newNode(MUL, cR2, _newNode(POW, cL, cR1)), dL);
        }
            
    case ND_MUL:
    {
        node_t* dL = calcDiff(node->left);
        node_t* dR = calcDiff(node->right);
        node_t* cL = copySubtree(node->left);
        node_t* cR = copySubtree(node->right);
        return _newNode(ADD, _newNode(MUL, dL, cR), _newNode(MUL, cL, dR));
    }
    case ND_DIV:
    {
        node_t* cL = copySubtree(node->left);
        node_t* cR1 = copySubtree(node->right);
        node_t* cR2 = copySubtree(node->right);
        node_t* cR3 = copySubtree(node->right);
        node_t* dL = calcDiff(node->left);
        node_t* dR = calcDiff(node->right);
        return _newNode(DIV, _newNode(SUB, _newNode(MUL, dL, cR1), _newNode(MUL, cL, dR)),
                                           _newNode(MUL, cR2, cR3));
    }

    case ND_SIN:
    {
        if (node->left != nullptr)
        {
            node_t* cL = copySubtree(node->left);
            node_t* dL = calcDiff(node->left);
            return _newNode(MUL, _newNode(COS, cL, nullptr), dL);
        }
        break;
    }
    case ND_COS:
    {
        if (node->left != nullptr)
        {
            node_t* cL = copySubtree(node->left);
            node_t* dL = calcDiff(node->left);
            node_t* minus_one = (node_t*)calloc(1, sizeof(node_t));
            *minus_one = {ND_NUM, "no var", -1, nullptr, nullptr};
            return _newNode(MUL, _newNode(MUL, minus_one, _newNode(SIN, cL, nullptr)), dL);
        }
        break;
    }
    case ND_LOG:
    {
        if (node->left != nullptr && node->right != nullptr)
        {
            node_t* cL = copySubtree(node->left);
            node_t* cR = copySubtree(node->right);
            node_t* dL = calcDiff(node->left);
            return _newNode(MUL, _newNode(DIV, newNode(ND_NUM, "no var", 1, nullptr, nullptr), _newNode(MUL, cL, _newNode(LOG, cR, newNode(ND_NUM, "no var", c_exp, nullptr, nullptr)))), dL);
        }
        break;   
    }
    case ND_RCIB:
    case ND_LCIB:
    case ND_EOT:
    default:
        break;
    }
    return nullptr;
}
