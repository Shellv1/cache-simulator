#include "main.h"

/*
FUNCTION:   main(1, 2)
    1:      [int]       Number of command-line arguments
    2:      [&char**]   Command-line arguments
*/
int main(int argc, char* argv[]) {

    Data* oData = CreateData(argc, &argv);

    CacheCalculations(&oData);

    PrintData(&oData);

    FreeData(&oData);

    return 0;
}

/*
FUNCTION:   CreateData(1, 2)
    1:      [int]       Number of command-line arguments
    2:      [&char**]   Command-line arguments
PURPOSE:    Dynamically allocate space for specified file names.
*/
Data* CreateData(int argc, char ***argv) {

    int i;

    Data* oData = (Data*)malloc(sizeof(Data));
    oData->sTraceFiles = (char**)malloc(sizeof(char*));

    for (i=1; i < argc; i+=2) {
        switch ((*argv)[i][1]) {
            case 'f': GetFileNames((*argv)[i+1], &oData);
            case 's': oData->iCacheSize = atoi((*argv)[i+1]) * 1024;
            case 'b': oData->iBlockSize = atoi((*argv)[i+1]);
            case 'a': oData->iAssociativity = atoi((*argv)[i+1]);
            case 'r': oData->cPolicy = (*argv)[i+1][1];
            case 'p': oData->iPhysicalMemory = atoi((*argv)[i+1]) * 1024;
        }
    }

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
FUNCTION:   PrintData(1)
    1:      [obj]       'Data' struct
PURPOSE:    Print data from simulation
*/
void PrintData(Data **oData) {

    int i;
    
    if ((*oData)->sTraceFiles)
        for (i=0; (*oData)->sTraceFiles[i] != NULL; i++)
            printf("Trace File %d:             %s\n", i+1, (*oData)->sTraceFiles[i]);

    if ((*oData)->iCacheSize) {
        printf("Cache Size:               ");
        PrintBytes((*oData)->iCacheSize);
    }

    if ((*oData)->iBlockSize)
        printf("Block Size:               %d Bytes\n", (*oData)->iBlockSize);

    if ((*oData)->iAssociativity)
        printf("Associativity:            %d\n", (*oData)->iAssociativity);

    if ((*oData)->cPolicy)
        switch ((*oData)->cPolicy) {
            case 'R': printf("Replacement Policy:       Random\n"); break;
            case 'N': printf("Replacement Policy:       Round Robin\n"); break;
        }

    if ((*oData)->iPhysicalMemory) {
        printf("Physical Memory:          ");
        PrintBytes((*oData)->iPhysicalMemory);
    }

    if ((*oData)->iNumBlocks)
        printf("Total Blocks:             %d\n", (*oData)->iNumBlocks);

    if ((*oData)->iTagSize)
        printf("Tag Size:                 %d Bytes\n", (*oData)->iTagSize);

    if ((*oData)->iIndexSize)
        printf("Index Size:               %d Bits\n", (*oData)->iIndexSize);

    if ((*oData)->iRows)
        printf("Total Rows:               %d\n", (*oData)->iRows);

    if ((*oData)->iOverhead) {
        printf("Overhead Size:            ");
        PrintBytes((*oData)->iOverhead);
    }
    if ((*oData)->iMemorySize) {
        printf("Memory Size:              ");
        PrintBytes((*oData)->iMemorySize);
    }

    printf("\n");
}

/*
FUNCTION:   PrintBytes(1)
    1:      [int]       Number of bytes
PURPOSE:    Print an amount of bytes in KB, MB, or GB
*/
void PrintBytes(int iBytes) {
    switch ((int)(log(iBytes) / log(1024))) {
        case 0: printf("%d Bytes\n", iBytes); break;
        case 1: printf("%d KB\n", iBytes / 1024); break;
        case 2: printf("%d MB\n", iBytes / 1024 / 1024); break;
        case 3: printf("%d GB\n", iBytes / 1024 / 1024 / 1024); break;
        default: break;
    }
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