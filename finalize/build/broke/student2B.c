#include <stdio.h>
#include <stdlib.h>
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


int ack;
struct pkt* responsePacket;

/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/
/*
 * The routines you will write are detailed below. As noted above,
 * such procedures in real-life would be part of the operating system,
 * and would be called by other procedures in the operating system.
 * All these routines are in layer 4.
 */

void B_output(struct msg message){

}

void B_timerinterrupt(){

};

/*
 * B_input(packet),where packet is a structure of type pkt. This routine 
 * will be called whenever a packet sent from the A-side (i.e., as a result 
 * of a tolayer3() being done by a A-side procedure) arrives at the B-side. 
 * packet is the (possibly corrupted) packet sent from the A-side.
 */
void B_input(struct pkt packet) {

    // Sequence # and Corruption Check
    if(packet.seqnum == ack && packet.checksum == checksum(packet)){

        // Respond with the correct ack immediately
        responsePacket->acknum = ack;
        responsePacket->checksum = checksum(*responsePacket);
        tolayer3(BEntity, *responsePacket);

        // Pass message up to layer5
        struct msg* message = malloc(sizeof(struct msg));
        bufferPass(packet.payload, message->data);
        tolayer5(BEntity, *message);
        ack = swap(ack);
        free(message);
    } else {

        // Respond with nack (previous ack) to trigger retransmission
        responsePacket->acknum = swap(ack);
        responsePacket->checksum = checksum(*responsePacket);
        tolayer3(BEntity, *responsePacket);
    }
}
/* 
 * The following routine will be called once (only) before any other   
 * entity B routines are called. You can use it to do any initialization 
 */
void B_init() {
    ack = 0;
    responsePacket = malloc(sizeof(struct pkt));
}

