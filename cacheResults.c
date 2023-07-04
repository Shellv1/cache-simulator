#include "main.h"

/*
FUNCTION:   PrintData(1)
    1:      [obj]       'Data' struct
PURPOSE:    Print data from simulation
*/
void PrintData(Data **oData) {

    int i;

    // Cache Input Parameters
    printf("[-----------------------------------------]\n");
    printf("[= = = = Cache Input Parameters    = = = =]\n");

    if ((*oData)->sTraceFiles)
        for (i=0; (*oData)->sTraceFiles[i] != NULL; i++)
            printf("| Trace File %d:             %s\n", i+1, (*oData)->sTraceFiles[i]);

    if ((*oData)->iCacheSize) {
        printf("| Cache Size:               ");
        PrintBytes((*oData)->iCacheSize);
    }

    if ((*oData)->iBlockSize)
        printf("| Block Size:               %d Bytes\n", (*oData)->iBlockSize);

    if ((*oData)->iAssociativity)
        printf("| Associativity:            %d\n", (*oData)->iAssociativity);

    if ((*oData)->cPolicy)
        switch ((*oData)->cPolicy) {
            case 'R': printf("| Replacement Policy:       Random\n"); break;
            case 'N': printf("| Replacement Policy:       Round Robin\n"); break;
        }

    if ((*oData)->iPhysicalMemory) {
        printf("| Physical Memory:          ");
        PrintBytes((*oData)->iPhysicalMemory);
    }

    // Cache Calculated Values
    printf("|\n[= = = = Cache Calculated Values   = = = =]\n");

    if ((*oData)->iNumBlocks)
        printf("| Total Blocks:             %d\n", (*oData)->iNumBlocks);

    if ((*oData)->iTagBits)
        printf("| Tag Size:                 %d Bits\n", (*oData)->iTagBits);

    if ((*oData)->iIndexBits)
        printf("| Index Size:               %d Bits\n", (*oData)->iIndexBits);

    if ((*oData)->iNumRows)
        printf("| Total Rows:               %d\n", (*oData)->iNumRows);

    if ((*oData)->iOverhead) {
        printf("| Overhead Size:            ");
        PrintBytes((*oData)->iOverhead);
    }
    if ((*oData)->iMemorySize) {
        printf("| Memory Size:              ");
        PrintBytes((*oData)->iMemorySize);
    }
    if ((*oData)->dCost)
        printf("| Cost:                     $%.2f\n", (*oData)->dCost);

    // Cache Simulation Results
    printf("|\n[= = = = Cache Simulation Results  = = = =]\n");
    if ((*oData)->iAccesses)
        printf("| Total Cache Accesses:     %d\n", (*oData)->iAccesses);
    
    if ((*oData)->iHits)
        printf("| Cache Hits:               %d\n", (*oData)->iHits);

    if ((*oData)->iCompulsoryMisses && (*oData)->iConflictMisses) {
        printf("| Cache Misses:             %d\n", (*oData)->iCompulsoryMisses + (*oData)->iConflictMisses);
        printf("|   Compulsory Misses:        %d\n", (*oData)->iCompulsoryMisses);
        printf("|   Conflict Misses:          %d\n", (*oData)->iConflictMisses);
    }

    // Cache Hit and Miss Rates
    printf("|\n[= = = = Cache Hit and Miss Rates  = = = =]\n");
    if ((*oData)->dHitRate)
        printf("| Hit Rate:                 %.2f%%\n", (*oData)->dHitRate);
    
    if ((*oData)->dMissRate)
        printf("| Miss Rate:                %.2f%%\n", (*oData)->dMissRate);

    if ((*oData)->dCPI)
        printf("| CPI:                      %.2f%%\n", (*oData)->dCPI);

    // Waste
    printf("|\n[= = = = Waste                     = = = =]\n");
    if ((*oData)->iUnusedSpace)
        printf("| Unused Cache Space:       %d\n", (*oData)->iUnusedSpace);

    if ((*oData)->iUnusedBlocks)
        printf("| Unused Cache Blocks:      %d\n", (*oData)->iUnusedBlocks);

    printf("|\n[-----------------------------------------]\n\n");
}

/*
FUNCTION:   PrintBytes(1)
    1:      [int]       Number of bytes
PURPOSE:    Print an amount of bytes in KB, MB, or GB
*/
void PrintBytes(int iBytes) {
    switch ((int)(log(iBytes) / log(1024))) {
        case 0: printf("%d Bytes\n", iBytes); break;
        case 1: printf("%d KB\n",    iBytes / 1024); break;
        case 2: printf("%d MB\n",    iBytes / 1024 / 1024); break;
        case 3: printf("%d GB\n",    iBytes / 1024 / 1024 / 1024); break;
        default: break;
    }
}