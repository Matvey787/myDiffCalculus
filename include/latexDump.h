#ifndef LATEXDUMP
#define LATEXDUMP

#include <stdio.h>
#include "mathTree.h"

void wrLatexFile(node_t* node, const char* fileName);
void rewLatexFile(node_t* node, const char* fileName);

#endif // LATEXDUMP