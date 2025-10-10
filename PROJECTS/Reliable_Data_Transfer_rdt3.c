#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_DATA_SIZE 256
#define TIMEOUT_VALUE 3

//packet structuer
typedef struct Packet
{
    int sqe_num;    //sequence number
    char data[MAX_DATA_SIZE];
    int checksum;
};

//ACK packet
typedef struct AckPacket
{
    int ack_num;    //Note: ack number (1 or 0)
    int checksum;
};

//sender states
typedef enum SenderState
{
    WAIT_CALL_0,
    WAIT_ACK_0,
    WAIT_CALL_1,
    WAIT_ACK_0
};

//reciever states
typedef enum ReceiverState
{
    WAIT_0,
    WAIT_1
};

//Event type for simulation
typedef enum EventType
{
    SEND_DATA,
    RECEIVE_ACK,
    TIMEOUT_EVENT,
    PACKET_LOST,
    PACKET_CORRUPTED
};

//timer structure
typedef struct Timer
{
    bool active;
    int start_time;
    int timeout_value;
};

// Statistics
typedef struct Statistics{
    int packets_sent;
    int retransmissions;
    int timeouts;
    int corrupted_packets;
    int lost_packets;
    int acks_received;
} ;