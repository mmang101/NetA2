#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "project2.h"
 
/* ***************************************************************************
 ALTERNATING BIT AND GO-BACK-N NETWORK EMULATOR: VERSION 1.1  J.F.Kurose

   This code should be used for unidirectional or bidirectional
   data transfer protocols from A to B and B to A.
   Network properties:
   - one way network delay averages five time units (longer if there
     are other messages in the channel for GBN), but can be larger
   - packets can be corrupted (either the header or the data portion)
     or lost, according to user-defined probabilities
   - packets may be delivered out of order.

   Compile as gcc -g project2.c student2.c -o p2
**********************************************************************/

void bufferPass(const char* src, char* dst){
    for(int i = 0; i< MESSAGE_LENGTH; i++){
        dst[i] = src[i];
    }
}

unsigned short checksum(struct pkt packet){
    int i, checksum = 0;

    for(i = 0; i < MESSAGE_LENGTH; i++){

        checksum += (int)(packet.payload[i]) * i;

    }

    checksum += packet.acknum * 21;

    checksum += packet.seqnum * 22;

    return checksum;
}

int swap(int swappee){
    switch (swappee) {
        case 0:
            return  1;

        case 1:
            return 0;

        default:
            break;
    }
}