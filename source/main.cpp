#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "readFile.h"
#include "mathTree.h"
#include "constants.h"
//#include "runAkinator.h"
//#include "newNodes.h"
#include "graphDump.h"
#include "latexDump.h"
#include "calcDiff.h"
#include "reduceTree.h"
// rm -rf png_files

const char* c_default_directory_for_saving_pictures = "png_files/";

int main(int argc, char *argv[]){
    char directory[c_length_of_strs] = {0};
    
    if (argc > 1)
    {
        sprintf(directory, "%s/", argv[1]);
    }
    else 
    {
        sprintf(directory, "%s/", c_default_directory_for_saving_pictures);
        system("mkdir -p png_files");
    }

    char* buffer = nullptr;
    size_t numOfSmbls = 0;
    size_t numOfStrs = 0;
    if (readFile(&buffer, "mathExp.json", &numOfSmbls, &numOfStrs) != NO_ERRORS){
        return 1;
    }

    char* ptrStartBuff = buffer;

    node_t* mathTree = (node_t*)calloc(1, sizeof(node_t));
    createTree(&(buffer), mathTree);


    writeDotFile(mathTree, "mathExp.dot");
    writePngFile("mathExp.dot", directory);
    wrLatexFile(mathTree, "document.tex");

    //node_t* array[20]= {0};
    mathTree = getDiff(mathTree);
    writeDotFile(mathTree, "mathExp.dot");
    writePngFile("mathExp.dot", directory);
    rewLatexFile(mathTree, "document.tex");
    
    reduceTree(mathTree, nullptr, 'c');
    
    writeDotFile(mathTree, "mathExp.dot");
    writePngFile("mathExp.dot", directory);
    rewLatexFile(mathTree, "document.tex");

    delTree(mathTree);
    //delTree(array[0]);
    free(ptrStartBuff);
}