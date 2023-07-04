#include "main.h"

void CacheSimulation(Data **oData) {

    /* EXAMPLE INSTRUCTIONS
        EIP (04): 7c809767 83 60 34 00 and dword [eax+0x34],0x0
        dstM: 00000000 -------- srcM: 7ffdfe2c 901e8b00

        EIP (07): 7c80976b 8b 84 88 10 0e 00 00 mov eax,[eax+ecx*4+0xe10]
        dstM: 7ffdf034 00000000 srcM: 7ffdfe2c 901e8b00
    */

    //int iLength[2] = {0};
    //char sAddress[6][8] = {'\0'};

    CreateCache();

    // for (s = READ LINE, i=0; s != EOF; s = READ LINE, i++)
        // if i % 3 == 0:
            // Get characters at [5,6], store as iLength[1]
            // Get characters at [10, 17], store as sAddress[1]
        // if i % 3 == 1:
            // Get characters at [6,13], store as sAddress[3]
            // Get characters at [30,37], store as sAddress[5]
        // if i % 3 == 2:
            // Handle instruction if necessary
            //iLength[0] = iLength[1];
            // for (j=0; j<6; j+=2)
                // for (k=0; k<8; k++)
                    // sAddress[j][k] = sAddress[j+1][k+1];

}

void CreateCache() {}

void SimulationAnalysis(Data **oData) {

    // [Hit Rate]               = [Cache Hits] / [Total Cache Accesses]
    (*oData)->dHitRate          = (*oData)->iHits / (*oData)->iAccesses;
    // [Miss Rate]              = 1 - [Hit Rate]
    (*oData)->dMissRate         = 1 - (*oData)->dHitRate;
    // [Cycles per Instruction] = [Total Cycles] / [Total Instructions]
    (*oData)->dCPI              = 0.0;
    // [Unused Cache Space]     = ([Total Blocks] - [Compulsory Misses]) * ([Block Size] + [Overhead])
    (*oData)->iUnusedSpace      = ((*oData)->iNumBlocks - (*oData)->iCompulsoryMisses) *
                                  ((*oData)->iBlockSize - (*oData)->iOverhead) /
                                  1024;
    // [Unused Cache Blocks]    = [Total Blocks] - []
    (*oData)->iUnusedBlocks     = NULL;
}

void FreeCache() {}