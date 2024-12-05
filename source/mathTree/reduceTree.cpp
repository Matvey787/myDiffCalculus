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


void reduceTree(node_t* daughter, node_t* parent, char side){ // TODO split into functions
    if (daughter->type == DIV || daughter->type == MUL || daughter->type == SUB || daughter->type == ADD)
    {
        
        reduceTree(daughter->left, daughter, 'l');
        if (daughter->right != nullptr && daughter != nullptr)
            reduceTree(daughter->right, daughter, 'r');
    }
        
    if (daughter->type == MUL && (abs(daughter->left->number) < c_compareZero || abs(daughter->right->number) < c_compareZero))
    {
        daughter->type = NUM;
        daughter->number = 0;
        delTree(daughter->left);
        delTree(daughter->right);
        daughter->left = nullptr;
        daughter->right = nullptr;
    } 
    else if (daughter->type == MUL &&( abs(daughter->left->number - 1) < c_compareZero || abs(daughter->right->number - 1) < c_compareZero) && parent != nullptr)
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
    else if ((daughter->type == ADD || daughter->type == MUL || daughter->type == SUB || daughter->type == DIV || daughter->type == POW) &&
            (daughter->left->type == NUM && daughter->right->type == NUM) && parent != nullptr)
    {
        bothOprtsNumbs(daughter);
    }
    else if (daughter->type == MUL && daughter->left->type == VAR && daughter->right->type == VAR && 
            strcmp(daughter->left->variable, daughter->right->variable) == 0)
    {
        daughter->type = POW;
        daughter->right->type = NUM;
        strcpy(daughter->right->variable, "no var");
        daughter->right->number = 2;
    }
    else if (daughter->type == POW && abs(daughter->right->number - 1) < c_compareZero && parent != nullptr)
    {
        if (side == 'r')
            parent->right = copySubtree(daughter->left);
        else
            parent->left = copySubtree(daughter->left);
        delTree(daughter);
    }
    else if (daughter->type == ADD && (abs(daughter->right->number) < c_compareZero || abs(daughter->left->number) < c_compareZero) && parent != nullptr)
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

    /* if (parent != nullptr){
        writeDotFile(parent, "mathExp.dot");
        writePngFile("mathExp.dot", "png_files/");
    } */
}

// reduce tree if both of daughter subtrees is nummbers and daughter type is + - / *
static void bothOprtsNumbs(node_t* daughter)
{
    if (daughter->type == ADD)
        daughter->number = daughter->left->number + daughter->right->number;

    else if (daughter->type == SUB)
        daughter->number = daughter->left->number - daughter->right->number;

    else if (daughter->type == MUL)
        daughter->number = daughter->left->number * daughter->right->number;

    else if (daughter->type == DIV)
        daughter->number = daughter->left->number / daughter->right->number;

    else if (daughter->type == POW)
        daughter->number = pow(daughter->left->number, daughter->right->number);

    daughter->type = NUM;
    delTree(daughter->left);
    delTree(daughter->right);
    daughter->left = nullptr;
    daughter->right = nullptr;
}