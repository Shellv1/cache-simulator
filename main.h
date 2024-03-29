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
    int iTagBits;
    int iIndexBits;
    int iNumRows;
    int iOverhead;
    int iMemorySize;
    int iAccesses;
    int iHits;
    int iCompulsoryMisses;
    int iConflictMisses;
    int iUnusedSpace;
    int iUnusedBlocks;
    
    double dCost;
    double dHitRate;
    double dMissRate;
    double dCPI;
} Data;

// Function Prototypes - main.c
Data* CreateData(int, char***);
void GetFileNames(char*, Data**);
void FreeData(Data**);

// Function Prototypes - cacheSimulation.c
void CacheSimulation(Data**);
void CreateCache();
void SimulationAnalysis(Data**);
void FreeCache();

// Function Prototypes - cacheResults.c
void PrintData(Data**);
void PrintBytes(int);