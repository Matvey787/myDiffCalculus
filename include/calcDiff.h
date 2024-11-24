#ifndef CALCDIFF
#define CALCDIFF

#include "mathTree.h"

node_t* newNode(types type, const char* variable, double number, node_t* node_l, node_t* node_r);
node_t* copyNode(node_t* node);
node_t* getDiff(node_t* operandTree);

#endif // CALCDIFF