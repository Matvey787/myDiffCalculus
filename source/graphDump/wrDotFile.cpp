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
    case ND_DIV:
    case ND_MUL:
    case ND_ADD:
    case ND_SUB:
    case ND_POW:
    case ND_SIN:
    case ND_COS:
    case ND_LOG:
        fprintf(*wFile, "node%p [ shape=record, color = %s rank = %lu, label= \"{ %p | %s | {<n%p_l> left | <n%p_r> right}} \" ];\n", 
                          node, getColor(node->type), rank, node, convertTypeToStr(node->type), node, node);
        break;
    case ND_NUM:
        fprintf(*wFile, "node%p [ shape=record, color = %s rank = %lu, label= \"{ %p | %s | %lg | {<n%p_l> left | <n%p_r> right}} \" ];\n", 
                          node, getColor(node->type), rank, node, convertTypeToStr(node->type), node->number, node, node);
        break;
    case ND_VAR:
        fprintf(*wFile, "node%p [ shape=record, color = %s rank = %lu, label= \"{ %p | %s | %s | {<n%p_l> left | <n%p_r> right}} \" ];\n", 
                          node, getColor(node->type), rank, node, convertTypeToStr(node->type), node->variable, node, node);
        break;
    case ND_RCIB:
    case ND_LCIB:
    case ND_EOT:
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
    case ND_ADD:
    case ND_SUB:
    case ND_DIV:
    case ND_MUL:
    case ND_POW:
    case ND_SIN:
    case ND_COS:
    case ND_LOG:
        return "red";
        break;
    case ND_NUM:
    case ND_VAR:
        return "blue";
        break;
    case ND_RCIB:
    case ND_LCIB:
    case ND_EOT:
        return "yellow";
        break;
    default:
        return "blue";
        break;
    }
}

static const char* convertTypeToStr(types type)
{
    switch (type)
    {
    case ND_ADD:
        return "+";
        break;
    case ND_SUB:
        return "-";
        break;
    case ND_MUL:
        return "*";
        break;
    case ND_DIV:
        return "/";\
        break; 
    case ND_NUM:
        return "number";
        break;
    case ND_POW:
        return "^";
        break;
    case ND_SIN:
        return "sin";
        break;
    case ND_COS:
        return "cos";
        break;
    case ND_LOG:
        return "log";
        break;
    case ND_VAR:
        return "variable";
        break;
    case ND_LCIB:
    case ND_RCIB:
    case ND_EOT:
    default:
        break;
    }
    return "error";
}

