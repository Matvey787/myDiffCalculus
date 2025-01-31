#include <stdio.h>
#include <string.h>
#include "mathTree.h"
#include "latexDump.h"
#include <assert.h>

static void wrTreeToFile(node_t* node, FILE* wFile);

void wrLatexFile(node_t* node, const char* fileName){
    FILE* wFile = fopen(fileName, "w");
    assert(wFile != NULL);
    printf("111111111111111111111111111111111 latex file\n");
    fprintf(wFile, "\\documentclass[12pt]{article}\n\\begin{document}\n");
    fprintf(wFile, "Exp: \n");
    fprintf(wFile, "\\begin{center}\n$ ");
    wrTreeToFile(node, wFile);
    fprintf(wFile, " $\n\\end{center}\n");
    fprintf(wFile, "\\end{document}\n");

    fclose(wFile);
}

void rewLatexFile(node_t* node, const char* fileName){
    FILE* wFile = fopen(fileName, "r+");
    fseek(wFile, -1*((int)strlen("\\end{center}")+3), SEEK_END);
    fprintf(wFile, "Ochev: \n");
    fprintf(wFile, "\\begin{center}\n$ ");
    wrTreeToFile(node, wFile);
    fprintf(wFile, " $\n\\end{center}\n");
    fprintf(wFile, "\\end{document}\n");

    fclose(wFile);
}

static void wrTreeToFile(node_t* node, FILE* wFile){
    printf("222222222222222222222222222222222222 latex file\n");
    switch (node->type)
    {
    case ND_ADD:
        fprintf(wFile, "(");
        wrTreeToFile(node->left, wFile);
        fprintf(wFile, " + ");
        wrTreeToFile(node->right, wFile);
        fprintf(wFile, ")");
        break;
    case ND_SUB:
        fprintf(wFile, "(");
        wrTreeToFile(node->left, wFile);
        fprintf(wFile, " - ");
        wrTreeToFile(node->right, wFile);
        fprintf(wFile, ")");
        break;
    case ND_DIV:
        fprintf(wFile, "\\frac{");
        wrTreeToFile(node->left, wFile);
        fprintf(wFile, "}{");
        wrTreeToFile(node->right, wFile);
        fprintf(wFile, "}");
        break;
    case ND_MUL:
        //fprintf(wFile, "(");
        wrTreeToFile(node->left, wFile);
        fprintf(wFile, " \\cdot ");
        wrTreeToFile(node->right, wFile);
        //fprintf(wFile, ")");
        break;
    case ND_POW:
        fprintf(wFile, "{");
        wrTreeToFile(node->left, wFile);
        fprintf(wFile, "}^{");
        wrTreeToFile(node->right, wFile);
        fprintf(wFile, "}");
        // fprintf(wFile, ")");
        break;

    case ND_SIN:
        fprintf(wFile, "sin\\left(");
        wrTreeToFile(node->left, wFile);
        fprintf(wFile, "\\right)");
        // fprintf(wFile, ")");
        break;
    
    case ND_LOG:
        fprintf(wFile, "\\log_{");
        wrTreeToFile(node->right, wFile);
        fprintf(wFile, "} \\left(");
        wrTreeToFile(node->left, wFile);
        fprintf(wFile, "\\right)");
        break;

    case ND_COS:
        fprintf(wFile, "cos\\left(");
        wrTreeToFile(node->left, wFile);
        fprintf(wFile, "\\right)");
        // fprintf(wFile, ")");
        break;

    case ND_NUM:
        fprintf(wFile, "%lg", node->data.num);
        break;
    case ND_VAR:
        fprintf(wFile, "%s", node->data.var->str);
        break;
    case ND_SQRT:
    case ND_LCUB:
    case ND_RCUB:
    case ND_IF:
    case ND_EQ:
    case ND_FOR:
    case ND_SEP:
    case ND_POADD: 
    case ND_ISEQ:
    case ND_NISEQ: 
    case ND_LS:
    case ND_AB:
    case ND_LSE:
    case ND_ABE:
    case ND_ENDFOR:
    case ND_PR:
    case ND_FUN:
    case ND_RET:
    case ND_FUNCALL:
    case ND_GET:
    case ND_GETDIFF:
    case ND_RCIB:
    case ND_LCIB:
    case ND_EOT:
    default:
        break;
    }
}