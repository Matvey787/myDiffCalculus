#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//#include "readFile.h"
//#include "mathTree.h"
//#include "runAkinator.h"
//#include "newNodes.h"
// rm -rf png_files
#include "../../General/treeTransfer/treeTransfer.h"
#include "../include/mathTree.h"
#include "../include/constants.h"
#include "../include/calcDiff.h"
#include "../include/readFile.h"
#include "../../General/graphDump/graphDump.h"
#include "../../General/programTree/tree.h"

void delTable(nameTable_t* nameTable);

const char* c_default_directory_for_saving_pictures = "png_files/";
static size_t space_for_nameTable = 500;

int main(int argc, char *argv[]){
    char directory[c_length_of_strs] = {0};
    nameTable_t* nameTable = (nameTable_t*)calloc(space_for_nameTable, sizeof(nameTable_t));
    nameTable_t* startOfNameTable = nameTable;
    char mode = 0;
    if (argc > 2)
    {
        mode  = argv[1][0];
        snprintf(directory, c_length_of_strs, "%s/", argv[2]);
    }
    else 
    {
        mode = '2';
        sprintf(directory, "%s", c_default_directory_for_saving_pictures);
        char command[c_length_of_strs] = {0};
        sprintf(command, "mkdir -p %s", c_default_directory_for_saving_pictures);
        system(command); // FIXME
    }


    if (mode == '1')
    {
        node_t* mathTree = pullTree(&nameTable, "../progTree");
        writeDotFile(mathTree, "../dot_files/test.dot");
        writePngFile("../dot_files/test.dot", directory, "white");
        printf("tree getted in diff\n");
        getchar();
        mathTree = getDiff(mathTree);
        writeDotFile(mathTree, "../dot_files/test.dot");
        writePngFile("../dot_files/test.dot", directory, "white");
        printf("tree after diff\n");
        getchar();
        pushTree(mathTree, "../progTree");
        delTree(mathTree);
        delTable(startOfNameTable);
    } 
    else if (mode == '2')
    {


        // from old project for analize math expression (not work with new structure) !!!!
        // from old project for analize math expression (not work with new structure) !!!!
        // from old project for analize math expression (not work with new structure) !!!!
        // from old project for analize math expression (not work with new structure) !!!!



        /* char* buffer = nullptr;
        size_t numOfSmbls = 0;
        size_t numOfStrs = 0;
        if (readFile(&buffer, "mathExp.json", &numOfSmbls, &numOfStrs) != NO_ERRORS){
            return 1;
        }

        char* ptrStartBuff = buffer;

        node_t* mathTree = (node_t*)calloc(1, sizeof(node_t));

        if (mathTree == nullptr)
            printf("allocate memory fail\n");
            
        node_t* nodes = (node_t*)calloc(60, sizeof(node_t));
        if (nodes == nullptr)
            printf("allocate memory fail\n");

        if (*buffer++ == '$')
        {
            free(mathTree);
            if (*buffer == '$')
            {
                buffer++;
                mathTree = crTree_by_tokens(nodes, buffer);
            }
            else 
            {
                mathTree = crTree_by_recursiveDescent(&buffer); // create tree by recursive descent
            }
            free(nodes);
        }
        else
        {
            createTree(&(buffer), mathTree);
        } */


        /* writeDotFile(mathTree, "mathExp.dot");
        writePngFile("mathExp.dot", directory);
        wrLatexFile(mathTree, "document.tex"); */

        //node_t* array[20]= {0};
        
        /* writeDotFile(mathTree, "mathExp.dot");
        writePngFile("mathExp.dot", directory);
        rewLatexFile(mathTree, "document.tex"); */

        /* reduceTree(mathTree, nullptr, 'c');

        mathTree = getDiff(mathTree);
        writeDotFile(mathTree, "mathExp.dot");
        writePngFile("mathExp.dot", directory);
        rewLatexFile(mathTree, "document.tex");
        
        reduceTree(mathTree, nullptr, 'c');
        
        writeDotFile(mathTree, "mathExp.dot");
        writePngFile("mathExp.dot", directory);
        rewLatexFile(mathTree, "document.tex");

        reduceTree(mathTree, nullptr, 'c');

        writeDotFile(mathTree, "mathExp.dot");
        writePngFile("mathExp.dot", directory);
        rewLatexFile(mathTree, "document.tex"); */
    }
}

void delTable(nameTable_t* nameTable)
{
    assert(nameTable != nullptr);
    int i = 0;
    while (nameTable[i].str != nullptr)
    {
        free(nameTable[i].str);
        nameTable[i++].str = nullptr;
    }
    free(nameTable);
}