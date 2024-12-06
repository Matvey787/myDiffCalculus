#include <stdio.h>
#include <string.h>
#include "mathTree.h"
#include "latexDump.h"

static void wrTreeToFile(node_t* node, FILE* wFile);

void wrLatexFile(node_t* node, const char* fileName){
    FILE* wFile = fopen(fileName, "w");
    fprintf(wFile, "\\documentclass[12pt]{article}\n\\begin{document}\n");
    fprintf(wFile, "Firstly: \n");
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
        fprintf(wFile, "%lg", node->number);
        break;
    case ND_VAR:
        fprintf(wFile, "%s", node->variable);
        break;
        
    case ND_RCIB:
    case ND_LCIB:
    case ND_EOT:
    default:
        break;
    }
}