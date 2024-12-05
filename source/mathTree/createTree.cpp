#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#include "mathTree.h"

types chooseType(char symbol);
size_t getNumberSize(double number);

size_t getNumberSize(double number)
{
    char str[100];
    snprintf(str, 100, "%lg", number);

    return strlen(str);
}

void createTree(char** buffer, node_t* node){
    assert(buffer != nullptr);
    assert(*buffer != nullptr);
    assert(node != nullptr);

    double number = 0;

    while (isspace(**buffer)) *buffer += 1;

    if (**buffer == '(')
    {
        *buffer += 1;

        if (!isdigit(**buffer) && !isalpha(**buffer))
        {
            node->left = (node_t*)calloc(1, sizeof(node_t));
            createTree(buffer, node->left);
            if (**buffer == '\n')
                return;

            while (isspace(**buffer)) *buffer += 1;

            node->type = chooseType(**buffer);
            node->number = NAN;
            strcpy(node->variable, "no var");
            *buffer += 1;
            
            node->right = (node_t*)calloc(1, sizeof(node_t));
            createTree(buffer, node->right);
            if (**buffer == '\n')
                return;
            while (isspace(**buffer)) *buffer += 1;
        }

    }
    if (isdigit(**buffer)) {
        node->type = NUM;
        sscanf(*buffer, "%lg", &number);
        node->number = number;
        strcpy(node->variable, "no var");
        node->left = nullptr;
        node->right = nullptr;
        *buffer += getNumberSize(number);
    } 
    else if (isalpha(**buffer)) 
    {
        node->type = VAR;
        node->variable[0] = **buffer;
        node->variable[1] = '\0';
        node->number = NAN;
        node->left = nullptr;
        node->right = nullptr;
        *buffer += 1;
    }
    
    if (**buffer == ')')
    {
        *buffer += 1;
        return;
    }

    if (**buffer == '\n')
        return;
}

types chooseType(char symbol){
    if (symbol == '+')
    {
        return ADD;
    }
    if (symbol == '-')
    {
        return SUB;
    }
    if (symbol == '*')
    {
        return MUL;
    }
    if (symbol == '/')
    {
        return DIV;
    }
    if (symbol == '^')
    {
        return POW;
    }
    return NUM;
}