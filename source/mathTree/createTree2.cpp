#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#include "mathTree.h"

#include <stdlib.h>

static node_t* getG(char** exp);
static node_t* getE(char** exp);
static node_t* getT(char** exp);
static node_t* getP(char** exp);
static node_t* N_or_V(char** exp);
static node_t* getN(char** exp);
static node_t* getV(char** exp);
static node_t* getSin(char** exp);
static node_t* getCos(char** exp);
static node_t* getLog(char** exp);

static void syntaxError();

static node_t* getG(char** exp)
{
    printf("get G %c\n", **exp);
    node_t* val = getE(exp);

    if (**exp != '$')
        syntaxError();
    
    return val;   
}

static node_t* getE(char** exp)
{
    printf("get E %c\n", **exp);
    node_t* val = getT(exp);
    while (**exp == '+' || **exp == '-')
    {
        char op = **exp;
        (*exp)++;
        node_t* val2 = getT(exp);
        if (op == '+')
            val = newNode(ND_ADD, "no var", NAN, val, val2);
        else
            val = newNode(ND_SUB, "no var", NAN, val, val2);
    }
    return val;
}

static node_t* getT(char** exp)
{
    printf("get T %c\n", **exp);
    node_t* val = getP(exp);
    while (**exp == '*' || **exp == '/')
    {
        char op = **exp;
        (*exp)++;
        node_t* val2 = getP(exp);
        if (op == '*')
            val = newNode(ND_MUL, "no var", NAN, val, val2);
        else
            val = newNode(ND_DIV, "no var", NAN, val, val2);
    }
    return val;
}

static node_t* getP(char** exp)
{
    printf("get P %c\n", **exp);

    if (**exp == '(')
    {
        (*exp)++;
        node_t* val = getE(exp);
        if (**exp != ')')
            syntaxError();
        (*exp)++;
        return val;
    }
    else
    {
        //return N_or_V(exp);
        return getSin(exp);
    }
}

static node_t* getSin(char** exp)
{
    char* old_ptr = *exp;
    if (**exp == 's')
        (*exp)++;
    else
    {
        *exp = old_ptr;
        return getCos(exp);
    }
    if (**exp == 'i')
        (*exp)++;
    else
    {
        *exp = old_ptr;
        return getCos(exp);
    }

    if (**exp == 'n')
    {
        (*exp)++;
        return newNode(ND_SIN, "no var", NAN, getP(exp), nullptr);
    }
    else
    {
        *exp = old_ptr;
        return getCos(exp);
    }   
}

static node_t* getCos(char** exp)
{
    char* old_ptr = *exp;
    if (**exp == 'c')
        (*exp)++;
    else
    {
        *exp = old_ptr;
        return getLog(exp);
    }
    if (**exp == 'o')
        (*exp)++;
    else
    {
        *exp = old_ptr;
        return getLog(exp);
    }

    if (**exp == 's')
    {
        (*exp)++;
        return newNode(ND_COS, "no var", NAN, getP(exp), nullptr);
    }
    else
    {
        *exp = old_ptr;
        return getLog(exp);
    }   
}

static node_t* getLog(char** exp)
{
    char* old_ptr = *exp;
    if (**exp == 'l')
        (*exp)++;
    else
    {
        *exp = old_ptr;
        return N_or_V(exp);
    }
    if (**exp == 'o')
        (*exp)++;
    else
    {
        *exp = old_ptr;
        return N_or_V(exp);
    }

    if (**exp == 'g')
    {
        (*exp)++;
        node_t* base = N_or_V(exp);
        node_t* arg = getP(exp);
        printf("-------%lg\n", base->number);
        return newNode(ND_LOG, "no var", NAN, arg, base);
    }
    else
    {
        *exp = old_ptr;
        return N_or_V(exp);
    }  
}

static node_t* N_or_V(char** exp)
{
    if (isdigit(**exp))
        return getN(exp);
    else
        return getV(exp);
}

static node_t* getN(char** exp)
{
    printf("get N %c\n", **exp);
    int val = 0;
    char* old_ptr = *exp;
    while (('0' <= **exp) && (**exp <= '9'))
    {
        printf("get N %c\n", **exp);
        val = val*10 + (**exp - '0');
        (*exp)++;
        printf("get N %c\n", **exp);
    }
    if (old_ptr == *exp)
        syntaxError();

    return newNode(ND_NUM, "no var", val, nullptr, nullptr);
}

static node_t* getV(char** exp)
{
    printf("get V %c\n", **exp);
    char* old_ptr = *exp;
    if (**exp == 'x')
    {
        (*exp)++;
    }
    if (old_ptr == *exp)
        syntaxError();

    return newNode(ND_VAR, "x", NAN, nullptr, nullptr);
}

static void syntaxError()
{
    printf("error!\n");int
    exit(1);
}

node_t* crTree_by_recursiveDescent(char** buffer){
    assert(buffer != nullptr);
    assert(*buffer != nullptr);
    return getG(buffer);
}
