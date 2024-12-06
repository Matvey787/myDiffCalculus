#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mathTree.h"
#include "reduceTree.h"
#include "calcDiff.h"
#include "graphDump.h"
#include "constants.h"

static void bothOprtsNumbs(node_t* daughter);
static void oneOprtIsZero(node_t* daughter, node_t* parent, char side);
static void oneOprtIsOne(node_t* daughter, node_t* parent, char side);

void reduceTree(node_t* daughter, node_t* parent, char side){ // TODO split into functions
    if (daughter->type == ND_DIV || daughter->type == ND_MUL || daughter->type == ND_SUB || daughter->type == ND_ADD)
    {
        
        reduceTree(daughter->left, daughter, 'l');
        if (daughter->right != nullptr && daughter != nullptr)
            reduceTree(daughter->right, daughter, 'r');
    }
        
    if (daughter->type == ND_MUL && (abs(daughter->left->number) < c_compareZero || abs(daughter->right->number) < c_compareZero))
    {
        daughter->type = ND_NUM;
        daughter->number = 0;
        delTree(daughter->left);
        delTree(daughter->right);
        daughter->left = nullptr;
        daughter->right = nullptr;
    } 
    else if (daughter->type == ND_MUL && 
            (abs(daughter->left->number - 1) < c_compareZero || abs(daughter->right->number - 1) < c_compareZero) && 
            parent != nullptr)
    {   
        oneOprtIsOne(daughter, parent, side);
    }
    else if ((daughter->type == ND_ADD || daughter->type == ND_MUL || daughter->type == ND_SUB || daughter->type == ND_DIV || daughter->type == ND_POW) &&
            (daughter->left->type == ND_NUM && daughter->right->type == ND_NUM) && parent != nullptr)
    {
        bothOprtsNumbs(daughter);
    }
    else if (daughter->type == ND_MUL && daughter->left->type == ND_VAR && daughter->right->type == ND_VAR && 
            strcmp(daughter->left->variable, daughter->right->variable) == 0)
    {
        daughter->type = ND_POW;
        daughter->right->type = ND_NUM;
        strcpy(daughter->right->variable, "no var");
        daughter->right->number = 2;
    }
    else if (daughter->type == ND_POW && abs(daughter->right->number - 1) < c_compareZero && parent != nullptr)
    {
        if (side == 'r')
            parent->right = copySubtree(daughter->left);
        else
            parent->left = copySubtree(daughter->left);
        delTree(daughter);
    }
    else if ((daughter->type == ND_ADD || daughter->type == ND_SUB) && (abs(daughter->right->number) < c_compareZero ||
                                                                        abs(daughter->left->number) < c_compareZero     ) && parent != nullptr)
    {
        oneOprtIsZero(daughter, parent, side);
    }
}

// reduce tree if both of daughter subtrees is nummbers and daughter type is + - / *
static void bothOprtsNumbs(node_t* daughter)
{
    if (daughter->type == ND_ADD)
        daughter->number = daughter->left->number + daughter->right->number;

    else if (daughter->type == ND_SUB)
        daughter->number = daughter->left->number - daughter->right->number;

    else if (daughter->type == ND_MUL)
        daughter->number = daughter->left->number * daughter->right->number;

    else if (daughter->type == ND_DIV)
        daughter->number = daughter->left->number / daughter->right->number;

    else if (daughter->type == ND_POW)
        daughter->number = pow(daughter->left->number, daughter->right->number);

    daughter->type = ND_NUM;
    delTree(daughter->left);
    delTree(daughter->right);
    daughter->left = nullptr;
    daughter->right = nullptr;
}

// reduce tree if one of daughter subtrees is 0 and daughter type is + -
static void oneOprtIsZero(node_t* daughter, node_t* parent, char side)
{
    if (abs(daughter->right->number) < c_compareZero)
    {
        if (side == 'r')
            parent->right = copySubtree(daughter->left);
        else
            parent->left = copySubtree(daughter->left);
        delTree(daughter);
    }
    else
    {
        if (side == 'r')
            parent->right = copySubtree(daughter->right);
        else
            parent->left = copySubtree(daughter->right);
        delTree(daughter);
    }
}

// reduce tree if both of daughter subtrees is nummbers and daughter type is + - / *
static void oneOprtIsOne(node_t* daughter, node_t* parent, char side)
{
    if (abs(daughter->left->number - 1) < c_compareZero)
        {
            if (side == 'r')
                parent->right = copySubtree(daughter->right);
            else
                parent->left = copySubtree(daughter->right);
        } 
        else if (abs(daughter->right->number - 1) < c_compareZero)
        {
            if (side == 'r')
                parent->right = copySubtree(daughter->left);
            else
                parent->left = copySubtree(daughter->left);
        }
    delTree(daughter);
}