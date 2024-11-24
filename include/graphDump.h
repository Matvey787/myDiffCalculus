#ifndef EDITFILES
#define EDITFILES

#include <stdio.h>
#include "mathTree.h"

int writePngFile(const char* dotFile, const char* directory);
void writeDotFile(node_t* node, const char* fileName);

#endif // EDITFILES