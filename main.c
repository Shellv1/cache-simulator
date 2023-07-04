#include "main.h"

/*
FUNCTION:   main(1, 2)
    1:      [int]       Number of command-line arguments
    2:      [&char**]   Command-line arguments
*/
int main(int argc, char* argv[]) {

    Data* oData = CreateData(argc, &argv);

    CacheSimulation(&oData);

    PrintData(&oData);

    FreeData(&oData);

    return 0;
}

/*
FUNCTION:   CreateData(1, 2)
    1:      [int]       Number of command-line arguments
    2:      [&char**]   Command-line arguments
PURPOSE:    Dynamically allocate space for specified file names and
            calculate cache information.
*/
Data* CreateData(int argc, char ***argv) {

    int i;

    Data* oData        = (Data*)malloc(sizeof(Data));
    oData->sTraceFiles = (char**)malloc(sizeof(char*));

    for (i=1; i < argc; i+=2) {
        switch ((*argv)[i][1]) {
            case 'f': GetFileNames((*argv)[i+1], &oData);
            case 's': oData->iCacheSize      = atoi((*argv)[i+1]) * 1024;
            case 'b': oData->iBlockSize      = atoi((*argv)[i+1]);
            case 'a': oData->iAssociativity  = atoi((*argv)[i+1]);
            case 'r': oData->cPolicy         = (*argv)[i+1][1];
            case 'p': oData->iPhysicalMemory = atoi((*argv)[i+1]) * 1024;
        }
    }

    // [Number of Blocks] = [Cache Size] / [Block Size]
    oData->iNumBlocks  = oData->iCacheSize / oData->iBlockSize;
    // [Number of Rows]   = [Number of Blocks] / [Associativity]
    oData->iNumRows    = oData->iNumBlocks / oData->iAssociativity;
    // [Index Bits]       = [log_2 of Number of Rows]
    oData->iIndexBits  = log2(oData->iNumRows);
    // [Tag Bits]         = [32 Bit Bus] - [5 Bits Offset] - [Index Bits]
    oData->iTagBits    = 27 - oData->iIndexBits;
    // [Overhead]         = [Tag Size] + [Index Size]
    oData->iOverhead   = pow(2, oData->iTagBits) + pow(2, oData->iIndexBits);
    // [Memory Size]      = [Cache Size] + [Overhead]
    oData->iMemorySize = oData->iCacheSize + oData->iOverhead;
    // [Cost]             = [Implementation Memory Size (in KB)] * [$0.15 per KB]
    oData->dCost       = (double)(oData->iMemorySize / 1024) * 0.15;

    return oData;
}

/*
FUNCTION:   GetFileNames(1, 2)
    1:      [char**]    File name
    2:      [obj]       'Data' struct
PURPOSE:    Dynamically allocate space for specified file names.
*/
void GetFileNames(char* sFileName, Data **oData) {

    int i, j;

    // Get length of array
    for (i=0; (*oData)->sTraceFiles[i] != NULL; i++) continue;

    // Allocate space for file index + null index
    (*oData)->sTraceFiles = (char**)realloc((*oData)->sTraceFiles, (i+2) * sizeof(char*));
    (*oData)->sTraceFiles[i+1] = NULL;
    // Allocate space for length of file name + null character
    (*oData)->sTraceFiles[i] = (char*)realloc((*oData)->sTraceFiles[i], 1 + strlen(sFileName));
    // Copy contents of file name into list of file names
    for (j=0; j < strlen(sFileName); j++)
        (*oData)->sTraceFiles[i][j] = sFileName[j];
    (*oData)->sTraceFiles[i][j+1] = '\0';
}

/*
FUNCTION:   FreeData(1)
    1:      [obj]       'Data' struct
PURPOSE:    Free allocated memory for 'Data' struct
*/
void FreeData(Data **oData) {

    int i;

    for (i=0; (*oData)->sTraceFiles[i] != NULL; i++)
        free((*oData)->sTraceFiles[i]);

    free(*oData);
}