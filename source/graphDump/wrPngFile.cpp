#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "graphDump.h"

int writePngFile(const char* dotFile, const char* directory){
    
    assert(dotFile != nullptr);
    static int numOfCall = 0;
    char command[100] = {0};
    sprintf(command, "dot %s -Tpng -o %spicture%d.png", dotFile, directory, numOfCall++);
    system(command);

    return numOfCall;
}