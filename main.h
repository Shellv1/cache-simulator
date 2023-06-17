// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // gcc -lm

// Structs
typedef struct Data {
    char** sTraceFiles;

    char cPolicy;

    int iCacheSize;
    int iBlockSize;
    int iAssociativity;
    int iPhysicalMemory;
    int iNumBlocks;
    int iTagSize;
    int iIndexSize;
    int iRows;
    int iOverhead;
    int iMemorySize;
} Data;

// Function Prototypes
Data* CreateData(int, char***);
void GetFileNames(char*, Data**);
void PrintData(Data**);
void PrintBytes(int);
void FreeData(Data**);

void CacheCalculations(Data**);