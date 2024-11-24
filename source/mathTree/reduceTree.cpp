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

void reduceTree(node_t* daughter, node_t* parent, char side){
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
    else if (daughter->type == MUL &&( abs(daughter->left->number - 1) < c_compareZero || abs(daughter->right->number - 1) < c_compareZero))
    {
        
        if (abs(daughter->left->number - 1) < c_compareZero)
        {
            if (side == 'r')
                parent->right = copyNode(daughter->right);
            else
                parent->left = copyNode(daughter->right);
        } 
        else if (abs(daughter->right->number - 1) < c_compareZero)
        {
            if (side == 'r')
                parent->right = copyNode(daughter->left);
            else
                parent->left = copyNode(daughter->left);
        }
        if (parent != nullptr)
        {
            delTree(daughter);
        }
    }
    else if ((daughter->left != nullptr && daughter->right != nullptr) &&
             (daughter->left->type == NUM && daughter->right->type == NUM))
    {
        if (daughter->type == ADD)
            daughter->number = daughter->left->number + daughter->right->number;

        else if (daughter->type == SUB)
            daughter->number = daughter->left->number - daughter->right->number;

        else if (daughter->type == MUL)
            daughter->number = daughter->left->number * daughter->right->number;

        else if (daughter->type == DIV)
            daughter->number = daughter->left->number / daughter->right->number;

        daughter->type = NUM;
        delTree(daughter->left);
        delTree(daughter->right);
        daughter->left = nullptr;
        daughter->right = nullptr;
    }
    /* if (parent != nullptr){
        writeDotFile(parent, "mathExp.dot");
        writePngFile("mathExp.dot", "png_files/");
    } */
}