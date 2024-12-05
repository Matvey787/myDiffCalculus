#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#include "mathTree.h"

#include <stdlib.h>

node_t* getG(node_t** exp);
node_t* getE(node_t** exp);
node_t* getT(node_t** exp);
node_t* getP(node_t** exp);
node_t* N_or_V(node_t** exp);
node_t* getN(node_t** exp);
node_t* getV(node_t** exp);
node_t* getSin(node_t** exp);
node_t* getCos(node_t** exp);
node_t* getLog(node_t** exp);
node_t* getPOW(node_t** nodes);

static void syntaxError();

node_t* createTree3(node_t* nodes, char* buffer){
    double tmpNum = 0;
    char tmpStr[100] = {0};
    int i_nodes = 0;
    while (1)
    {
        printf("%c\n", *buffer);
        if (*buffer == '$')
        {
            //printf("%d\n", i_nodes);
            nodes[i_nodes++] = {EOT, "$", NAN, nullptr, nullptr};
            break;
        }
        if (sscanf(buffer, "%lg", &tmpNum) == 1)
        {
            nodes[i_nodes++] = {NUM, "no var", tmpNum, nullptr, nullptr};
            snprintf(tmpStr, 100, "%lg", tmpNum);
            printf("%d\n", strlen(tmpStr));
            buffer += strlen(tmpStr);
        }
        if (sscanf(buffer, "%[^1234567890(]", tmpStr) == 1)
        {
            if (strcmp(tmpStr, "sin") == 0)
            {
                nodes[i_nodes++] = {SIN, "no var", NAN, nullptr, nullptr};
                buffer += strlen(tmpStr);
            }
            else if (strcmp(tmpStr, "cos") == 0)
            {
                nodes[i_nodes++] = {COS, "no var", NAN, nullptr, nullptr};
                buffer += strlen(tmpStr);
            }

            else if (strcmp(tmpStr, "log") == 0)
            {
                nodes[i_nodes++] = {LOG, "no var", NAN, nullptr, nullptr};
                buffer += strlen(tmpStr);
            }
        }
        printf("-------%c\n", *buffer);
        if (*buffer == '(')
        {
            nodes[i_nodes++] = {LCIB, "no var", NAN, nullptr, nullptr};
            buffer += 1;
        }

        if (*buffer == ')')
        {
            nodes[i_nodes++] = {RCIB, "no var", NAN, nullptr, nullptr};
            buffer += 1;
        }
        if (*buffer == '+')
        {
            printf("++++++ %c\n", *buffer);
            nodes[i_nodes++] = {ADD, "no var", NAN, nullptr, nullptr};
            buffer += 1;
            printf("--voi;afniska-----%c\n", *(buffer - 1));
        }
        printf("--voi;BZD-----%c\n", *buffer);
        if (*buffer == '-')
        {
            nodes[i_nodes++] = {SUB, "no var", NAN, nullptr, nullptr};
            buffer += 1;
        }
        
        printf("-------%c\n", *buffer);

        if (*buffer == '/')
        {
            nodes[i_nodes++] = {DIV, "no var", NAN, nullptr, nullptr};
            buffer += 1;
        }
            
        if (*buffer == '*')
            {
                nodes[i_nodes++] = {MUL, "no var", NAN, nullptr, nullptr};
                buffer += 1;
            }
        printf("--|||||-----%c\n", *buffer);

        if (*buffer == 'x')
        {
            nodes[i_nodes++] = {VAR, "x", NAN, nullptr, nullptr};
            buffer += 1;
        }
        if (*buffer == '^')
        {
            nodes[i_nodes++] = {POW, "x", NAN, nullptr, nullptr};
            buffer += 1;
        }
        printf("-------%c\n", *buffer);
    }
    printf("-----------------%p: %d %p: %d %d\n",nodes, nodes[0].type, nodes+1, nodes[1].type, nodes[2].type);
    return getG(&nodes);
}

node_t* getG(node_t** nodes)
{
    node_t* subtree = getE(nodes);

    if ((*nodes)->type != EOT)
        syntaxError();
    printf("getG  %p\n", subtree);
    return subtree;   
}

node_t* getE(node_t** nodes)
{
    node_t* l_subtree = getT(nodes);
    printf("aiofioa' work\n");
    while ((*nodes)->type == ADD || (*nodes)->type == SUB)
    {
        printf("while work\n");
        types op = (*nodes)->type;
        (*nodes)++;
        node_t* r_subtree = getT(nodes);

        if (op == ADD)
        {
            printf("add work\n");
            l_subtree = newNode(ADD, "no var", NAN, l_subtree, r_subtree);
        }
        else
            l_subtree = newNode(SUB, "no var", NAN, l_subtree, r_subtree);
    }
    return l_subtree;
}

node_t* getT(node_t** nodes)
{
    node_t* l_subtree = getPOW(nodes);
    while ((*nodes)->type == MUL || (*nodes)->type == DIV)
    {
        types op = (*nodes)->type;
        (*nodes)++;
        node_t* r_subtree = getPOW(nodes);

        if (op == MUL)
            l_subtree = newNode(MUL, "no var", NAN, l_subtree, r_subtree);
        else
            l_subtree = newNode(DIV, "no var", NAN, l_subtree, r_subtree);
    }
    return l_subtree;
}

node_t* getPOW(node_t** nodes)
{
    node_t* l_subtree = getP(nodes);
    while ((*nodes)->type == POW)
    {
        types op = (*nodes)->type;
        (*nodes)++;
        node_t* r_subtree = getP(nodes);

        l_subtree = newNode(POW, "no var", NAN, l_subtree, r_subtree);
    }
    return l_subtree;
}

node_t* getP(node_t** nodes)
{

    if ((*nodes)->type == LCIB)
    {
        (*nodes)++;
        node_t* val = getE(nodes);
        if ((*nodes)->type != RCIB)
            syntaxError();
        (*nodes)++;
        return val;
    }
    else
    {
        //return N_or_V(nodes);
        return getSin(nodes);
    }
}

node_t* getSin(node_t** nodes)
{
    if ((*nodes)->type == SIN)
    {
        node_t* sin = *nodes;
        (*nodes)++;
        sin->left = getP(nodes);
        return copyNode(sin);
    }
    else
    {
        return getCos(nodes);
    }   
}

node_t* getCos(node_t** nodes)
{
    if ((*nodes)->type == COS)
    {
        node_t* cos = *nodes;
        (*nodes)++;
        cos->left = getP(nodes);
        return copyNode(cos);
    }
    else
    {
        return getLog(nodes);
    }   
}

node_t* getLog(node_t** nodes)
{

    if ((*nodes)->type == LOG)
    {
        node_t* log = *nodes;
        (*nodes)++;
        log->right = N_or_V(nodes);
        log->left = getP(nodes);
        return copyNode(log);
    }
    else
    {
        return N_or_V(nodes);
    }
}

node_t* N_or_V(node_t** nodes)
{
    if ((*nodes)->type == NUM)
        return getN(nodes);
    else if ((*nodes)->type == VAR)
        return getV(nodes);
    else
        return *nodes;
}

node_t* getN(node_t** nodes)
{
    printf("get N()-----> %d\n", (*nodes)->type);
    node_t* number = *nodes;
    (*nodes)++;
    return copyNode(number);
}

node_t* getV(node_t** nodes)
{

    node_t* var = *nodes;
    (*nodes)++;
    printf("variable: %d %c\n", var->type, var->variable);
    return copyNode(var);
}

static void syntaxError()
{
    printf("error!\n");int
    exit(1);
}
