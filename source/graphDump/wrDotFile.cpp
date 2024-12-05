#include "graphDump.h"
#include <assert.h>

static void writeTreeToDotFile(node_t* node, FILE** wFile, size_t rank);

void writeDotFile(node_t* node, const char* fileName){
    assert(node != nullptr);
    assert(fileName != nullptr);
    
    FILE* wFile = fopen(fileName, "w");
    if (wFile == nullptr){
        printf("couldn't open file");
        return;
    }

    fprintf(wFile, "digraph\n{ \nrankdir=HR;\n");
    fprintf(wFile, "\n");

    writeTreeToDotFile(node, &wFile, 1);

    fprintf(wFile, "}\n");

    fclose(wFile);
}

static const char* getColor(types type);
static const char* convertTypeToStr(types type);

static void writeTreeToDotFile(node_t* node, FILE** wFile, size_t rank){
    assert(node != nullptr);
    assert(wFile != nullptr);

    switch (node->type)
    {
    case DIV:
    case MUL:
    case ADD:
    case SUB:
    case POW:
    case SIN:
    case COS:
    case LOG:
        fprintf(*wFile, "node%p [ shape=record, color = %s rank = %lu, label= \"{ %p | %s | {<n%p_l> left | <n%p_r> right}} \" ];\n", 
                          node, getColor(node->type), rank, node, convertTypeToStr(node->type), node, node);
        break;
    case NUM:
        fprintf(*wFile, "node%p [ shape=record, color = %s rank = %lu, label= \"{ %p | %s | %lg | {<n%p_l> left | <n%p_r> right}} \" ];\n", 
                          node, getColor(node->type), rank, node, convertTypeToStr(node->type), node->number, node, node);
        break;
    case VAR:
        fprintf(*wFile, "node%p [ shape=record, color = %s rank = %lu, label= \"{ %p | %s | %s | {<n%p_l> left | <n%p_r> right}} \" ];\n", 
                          node, getColor(node->type), rank, node, convertTypeToStr(node->type), node->variable, node, node);
        break;
    default:
        break;
    }

    
    if (node->left != nullptr)
    {
        writeTreeToDotFile(node->left, wFile, ++rank);
        fprintf(*wFile, "node%p:<n%p_l>:s -> node%p:n [ color = black; ]\n", node, node, node->left);
    }
    if (node->right != nullptr)
    {
        writeTreeToDotFile(node->right, wFile, ++rank);
        fprintf(*wFile, "node%p:<n%p_r>:s -> node%p:n [ color = black; ]\n", node, node, node->right);
    }
}

static const char* getColor(types type)
{
    switch (type)
    {
    case ADD:
    case SUB:
    case DIV:
    case MUL:
    case POW:
    case SIN:
    case COS:
    case LOG:
        return "red";
        break;
    case NUM:
    case VAR:
    default:
        return "blue";
        break;
    }
}

static const char* convertTypeToStr(types type)
{
    switch (type)
    {
    case ADD:
        return "+";
        break;
    case SUB:
        return "-";
        break;
    case MUL:
        return "*";
        break;
    case DIV:
        return "/";\
        break; 
    case NUM:
        return "number";
        break;
    case POW:
        return "^";
        break;
    case SIN:
        return "sin";
        break;
    case COS:
        return "cos";
        break;
    case LOG:
        return "log";
        break;
    case VAR:
        return "variable";
        break;
    default:
        break;
    }
    return "error";
}

