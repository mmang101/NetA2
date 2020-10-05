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


int seq, busy, packets;
struct node* head;
struct node* tail;
struct pkt* inTransit;
const int TIMERLIFETIME = 1000000;

/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/
/*
 * The routines you will write are detailed below. As noted above,
 * such procedures in real-life would be part of the operating system,
 * and would be called by other procedures in the operating system.
 * All these routines are in layer 4.
 */

/*
 * A_output(message), where message is a structure of type msg, containing
 * data to be sent to the B-side. This routine will be called whenever the
 * upper layer at the sending side (A) has a messpacketage to send. It is the job
 * of your protocol to insure that the data in such a message is delivered
 * in-order, and correctly, to the receiving side upper layer.
 */
void A_output(struct msg message) {
    // Check if message can be sent immediately
    if(!busy){
        busy = 1;

        // Make packet
        inTransit->seqnum=seq; // Store packets sequence number
        inTransit->acknum=seq; // Store expected ack
        bufferPass(message.data,inTransit->payload);
        inTransit->checksum = checksum(*inTransit);

        // Send Packet, swap sequence
        tolayer3(AEntity, *inTransit);
        startTimer(AEntity, TIMERLIFETIME);
        seq = swap(seq);
    } else {
        
        // Store Message in buffer to be sent when ready
        packets++;
        struct node* bufferedNode = malloc(sizeof(struct node));
        struct msg* bufferedMessage = malloc(sizeof(struct msg));
        bufferPass(message.data,bufferedMessage->data);
        bufferedNode->payload = bufferedMessage;
        tail->tail = bufferedNode;
        tail = bufferedNode;
    }
}


/*
 * A_input(packet), where packet is a structure of type pkt. This routine
 * will be called whenever a packet sent from the B-side (i.e., as a result
 * of a tolayer3() being done by a B-side procedure) arrives at the A-side.
 * packet is the (possibly corrupted) packet sent from the B-side.
 */
void A_input(struct pkt packet) {

    // Check to see if incoming packet is not corrupt and correct ack
    if(packet.acknum == inTransit->acknum && packet.checksum == checksum(packet)){
        busy = 0; // No longer busy for a brief moment when receiving packets

        // Send another buffered message if any available
        if(packets--){
            busy = 1;

            // Make Packet
            head = head->tail;
            inTransit->seqnum=seq;
            inTransit->acknum=seq;
            bufferPass(head->payload->data,inTransit->payload);
            inTransit->checksum = checksum(*inTransit);

            // Send Packet, swap sequence
            tolayer3(AEntity, *inTransit);
            startTimer(AEntity, TIMERLIFETIME);
            seq = swap(seq);
        }
    } else {
        busy = 1;

        // Retransmit packet
        tolayer3(AEntity, *inTransit);
        startTimer(AEntity, TIMERLIFETIME);
    }
}

/*
 * A_timerinterrupt()  This routine will be called when A's timer expires
 * (thus generating a timer interrupt). You'll probably want to use this
 * routine to control the retransmission of packets. See starttimer()
 * and stoptimer() in the writeup for how the timer is started and stopped.
 */
void A_timerinterrupt() {
    busy = 1;
    // Timeout occured, retransmit packet
    tolayer3(AEntity, *inTransit);
    startTimer(AEntity, TIMERLIFETIME);
}

/* The following routine will be called once (only) before any other    */
/* entity A routines are called. You can use it to do any initialization */
void A_init() {
    //Initialiazation of releveant globals
    inTransit = malloc(sizeof(struct pkt));
    seq = 0;
    busy = 0;
    packets = 0;
    head = malloc(sizeof(struct node));
    tail = malloc(sizeof(struct node));
    head = tail;
}
