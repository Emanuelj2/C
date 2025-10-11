#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_DATA_SIZE 256
#define TIMEOUT_VALUE 3

//packet structuer
typedef struct 
{
    int seq_num;    //sequence number
    char data[MAX_DATA_SIZE];
    int checksum;
}Packet;

//ACK packet
typedef struct 
{
    int ack_num;    //Note: ack number (1 or 0)
    int checksum;
}AckPacket;

//sender states
typedef enum 
{
    WAIT_CALL_0,
    WAIT_ACK_0,
    WAIT_CALL_1,
    WAIT_ACK_1
}SenderState;

//reciever states
typedef enum 
{
    WAIT_0,
    WAIT_1
}ReceiverState;

//Event type for simulation
typedef enum 
{
    SEND_DATA,
    RECEIVE_ACK,
    TIMEOUT_EVENT,
    PACKET_LOST,
    PACKET_CORRUPTED
}EventType;

//timer structure
typedef struct 
{
    bool active;
    int start_time;
    int timeout_value;
}Timer;

// Statistics
typedef struct {
    int packets_sent;
    int retransmissions;
    int timeouts;
    int corrupted_packets;
    int lost_packets;
    int acks_received;
}Statistics ;

Statistics stats = {0};

//calculate simple checksum
int calculate_checksum(const char *data, int len)
{
    int sum = 0;
    for(int i = 0; i < len; i++){
        sum += (unsigned char)data[i];
    }
    return sum;
}

//calc checksum for packet
int packet_checksum(Packet *pkt)
{
    int sum = pkt->seq_num;
    sum += calculate_checksum(pkt->data, strlen(pkt->data));
    return sum;
}

//canclulate the checksum for ACK packet
int ack_checksum(AckPacket *ack)
{
    return ack->ack_num + 100; // Add constant to distinguish from seq_num
}

// Check if packet is corrupted
bool is_corrupted_packet(Packet *pkt)
{
    return pkt->checksum != packet_checksum(pkt);
}

//check if ack is corrupt
bool is_corrupted_ack(AckPacket *ack)
{
    return ack->checksum != ack_checksum(ack);
}

//create a data packet
Packet make_packet(int seq_num, const char *data)
{
    Packet pkt;
    pkt.seq_num = seq_num;
    strncpy(pkt.data, data, MAX_DATA_SIZE - 1);
    pkt.data[MAX_DATA_SIZE - 1] = '\0';
    pkt.checksum = packet_checksum(&pkt);
    return pkt;
}

//create ack packet
AckPacket make_ack(int ack_num)
{
    AckPacket ack;
    ack.ack_num = ack_num;
    ack.checksum = ack_checksum(&ack);
    return ack;
}

//timer functions
void start_timer(Timer *timer, int current_time)
{
    timer->active = true;
    timer->start_time = current_time;
    timer->timeout_value = TIMEOUT_VALUE;
    printf("  [TIMER] Started (timeout=%d)\n", TIMEOUT_VALUE);
}

void stop_timer(Timer *timer)
{
    timer->active = false;
    printf("  [TIMER] Stopped\n");
}

bool timer_expired(Timer *timer, int current_time)
{
    if(!timer->active)
    {
        return false;
    }
    return (current_time - timer->start_time) >= timer->timeout_value;
}


// Simulate unreliable channel
void udt_send(Packet *pkt, bool *lost, bool *corrupt, int time)
{
    printf("  [TIME %d] → Sending packet [seq=%d, data='%s', checksum=%d]\n", 
           time, pkt->seq_num, pkt->data, pkt->checksum);

    stats.packets_sent++;

    if(*lost){
        printf("    Packet LOST during transmission!\n");
        stats.lost_packets++;
        return;
    }

    if(*corrupt){
        pkt->checksum += 1; //corrupt the checksum
        printf("    Packet CORRUPTED during transmission!\n");
        stats.corrupted_packets++;
    }
}

// Simulate ACK transmission
void send_ack(AckPacket *ack, bool *lost, bool *corrupt, int time) {
    printf("  [TIME %d] ← Sending ACK [ack_num=%d, checksum=%d]\n", 
           time, ack->ack_num, ack->checksum);
    
    if (*lost) {
        printf("    ACK LOST during transmission!\n");
        stats.lost_packets++;
        return;
    }
    
    if (*corrupt) {
        ack->checksum += 1;
        printf("    ACK CORRUPTED during transmission!\n");
        stats.corrupted_packets++;
    }
}

void sender_rdt30(const char *messages[], int num_messages, bool data_lost[], bool data_corrupt[], bool ack_lost[], bool ack_corrupt[])
{
    SenderState state = WAIT_CALL_0;
    Packet current_packet;
    Timer timer = {false, 0, TIMEOUT_VALUE};
    int msg_index = 0;
    int time = 0;
    int max_iterations = 100; //just in case :)
    int iteration = 0;

    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║           SENDER RDT 3.0 SIMULATION           ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");

    while (msg_index < num_messages && iteration < max_iterations) {
        iteration++;
        
        switch (state) {
            case WAIT_CALL_0:
                printf("\n[STATE: WAIT_CALL_0] (Message %d/%d)\n", msg_index + 1, num_messages);
                current_packet = make_packet(0, messages[msg_index]);
                udt_send(&current_packet, &data_lost[msg_index], &data_corrupt[msg_index], time);
                start_timer(&timer, time);
                state = WAIT_ACK_0;
                time++;
                break;
                
            case WAIT_ACK_0:
                printf("\n[STATE: WAIT_ACK_0]\n");
                
                // Check for timeout
                if (timer_expired(&timer, time)) {
                    printf("  [TIME %d]  TIMEOUT! Resending packet 0\n", time);
                    stats.timeouts++;
                    stats.retransmissions++;
                    bool no_loss = false, no_corrupt = false;
                    udt_send(&current_packet, &no_loss, &no_corrupt, time);
                    start_timer(&timer, time);
                    time++;
                    break;
                }
                
                // Simulate receiving ACK
                if (!data_lost[msg_index]) {
                    AckPacket ack = make_ack(0);
                    send_ack(&ack, &ack_lost[msg_index], &ack_corrupt[msg_index], time);
                    
                    if (!ack_lost[msg_index]) {
                        if (is_corrupted_ack(&ack)) {
                            printf("    Corrupted ACK received, waiting...\n");
                        } else if (ack.ack_num == 0) {
                            printf("    ACK 0 received correctly\n");
                            stop_timer(&timer);
                            stats.acks_received++;
                            msg_index++;
                            state = WAIT_CALL_1;
                        } else {
                            printf("    Duplicate ACK 1 received, waiting...\n");
                        }
                    }
                }
                
                time++;
                break;
                
            case WAIT_CALL_1:
                if (msg_index >= num_messages) break;
                
                printf("\n[STATE: WAIT_CALL_1] (Message %d/%d)\n", msg_index + 1, num_messages);
                current_packet = make_packet(1, messages[msg_index]);
                udt_send(&current_packet, &data_lost[msg_index], &data_corrupt[msg_index], time);
                start_timer(&timer, time);
                state = WAIT_ACK_1;
                time++;
                break;
                
            case WAIT_ACK_1:
                printf("\n[STATE: WAIT_ACK_1]\n");
                
                // Check for timeout
                if (timer_expired(&timer, time)) {
                    printf("  [TIME %d]  TIMEOUT! Resending packet 1\n", time);
                    stats.timeouts++;
                    stats.retransmissions++;
                    bool no_loss = false, no_corrupt = false;
                    udt_send(&current_packet, &no_loss, &no_corrupt, time);
                    start_timer(&timer, time);
                    time++;
                    break;
                }
                
                // Simulate receiving ACK
                if (!data_lost[msg_index]) {
                    AckPacket ack = make_ack(1);
                    send_ack(&ack, &ack_lost[msg_index], &ack_corrupt[msg_index], time);
                    
                    if (!ack_lost[msg_index]) {
                        if (is_corrupted_ack(&ack)) {
                            printf("    Corrupted ACK received, waiting...\n");
                        } else if (ack.ack_num == 1) {
                            printf("    ✓ ACK 1 received correctly\n");
                            stop_timer(&timer);
                            stats.acks_received++;
                            msg_index++;
                            state = WAIT_CALL_0;
                        } else {
                            printf("    Duplicate ACK 0 received, waiting...\n");
                        }
                    }
                }
                
                time++;
                break;
        }
    }
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║              TRANSMISSION COMPLETE             ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
}

// RECEIVER FSM
void receiver_rdt30(Packet packets[], bool lost[], bool corrupt[], int num_packets) {
    ReceiverState state = WAIT_0;
    int expected_seq = 0;
    int last_ack_sent = 1; // Initially, we haven't ACKed anything
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║           RECEIVER RDT 3.0 SIMULATION          ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
    
    for (int i = 0; i < num_packets; i++) {
        if (lost[i]) {
            printf("\n[Packet %d] ✗ LOST - no packet received\n", i);
            continue;
        }
        
        Packet *pkt = &packets[i];
        if (corrupt[i]) {
            pkt->checksum += 1; // Corrupt it
        }
        
        switch (state) {
            case WAIT_0:
                printf("\n[STATE: WAIT_0] Expecting seq=0\n");
                printf("  Received packet [seq=%d, data='%s']\n", pkt->seq_num, pkt->data);
                
                if (is_corrupted_packet(pkt)) {
                    printf("  Packet corrupted! Sending duplicate ACK %d\n", last_ack_sent);
                    AckPacket ack = make_ack(last_ack_sent);
                    bool no_loss = false, no_corrupt = false;
                    send_ack(&ack, &no_loss, &no_corrupt, i);
                } else if (pkt->seq_num == 1) {
                    printf("  Wrong sequence (got 1, expected 0)! Duplicate packet detected\n");
                    printf("  Sending duplicate ACK 1\n");
                    AckPacket ack = make_ack(1);
                    bool no_loss = false, no_corrupt = false;
                    send_ack(&ack, &no_loss, &no_corrupt, i);
                } else {
                    printf("  ✓ Correct packet received! Delivering: '%s'\n", pkt->data);
                    AckPacket ack = make_ack(0);
                    bool no_loss = false, no_corrupt = false;
                    send_ack(&ack, &no_loss, &no_corrupt, i);
                    last_ack_sent = 0;
                    state = WAIT_1;
                }
                break;
                
            case WAIT_1:
                printf("\n[STATE: WAIT_1] Expecting seq=1\n");
                printf("  Received packet [seq=%d, data='%s']\n", pkt->seq_num, pkt->data);
                
                if (is_corrupted_packet(pkt)) {
                    printf("  Packet corrupted! Sending duplicate ACK %d\n", last_ack_sent);
                    AckPacket ack = make_ack(last_ack_sent);
                    bool no_loss = false, no_corrupt = false;
                    send_ack(&ack, &no_loss, &no_corrupt, i);
                } else if (pkt->seq_num == 0) {
                    printf("  Wrong sequence (got 0, expected 1)! Duplicate packet detected\n");
                    printf("  Sending duplicate ACK 0\n");
                    AckPacket ack = make_ack(0);
                    bool no_loss = false, no_corrupt = false;
                    send_ack(&ack, &no_loss, &no_corrupt, i);
                } else {
                    printf("   Correct packet received! Delivering: '%s'\n", pkt->data);
                    AckPacket ack = make_ack(1);
                    bool no_loss = false, no_corrupt = false;
                    send_ack(&ack, &no_loss, &no_corrupt, i);
                    last_ack_sent = 1;
                    state = WAIT_0;
                }
                break;
        }
    }
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║            RECEIVER PROCESSING DONE            ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
}

void print_statistics() {
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║              TRANSMISSION STATISTICS           ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    printf("  Total packets sent:     %d\n", stats.packets_sent);
    printf("  Retransmissions:        %d\n", stats.retransmissions);
    printf("  Timeouts:               %d\n", stats.timeouts);
    printf("  Packets lost:           %d\n", stats.lost_packets);
    printf("  Packets corrupted:      %d\n", stats.corrupted_packets);
    printf("  ACKs received:          %d\n", stats.acks_received);
    printf("  Efficiency:             %.1f%%\n", 
           100.0 * stats.acks_received / stats.packets_sent);
    printf("╚════════════════════════════════════════════════╝\n");
}

int main(){
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║  Reliable Data Transfer 3.0 (Stop-and-Wait)    ║\n");
    printf("║         With Loss, Corruption, & Timeout       ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    
    // Messages to send
    const char *messages[] = {
        "Hello",
        "World",
        "RDT",
        "3.0",
        "Works!"
    };
    int num_messages = 5;
    
    // Simulation scenarios (true = problem occurs)
    bool data_lost[]    = {false, true,  false, false, false}; // Lose 2nd packet
    bool data_corrupt[] = {false, false, true,  false, false}; // Corrupt 3rd packet
    bool ack_lost[]     = {false, false, false, true,  false}; // Lose 4th ACK
    bool ack_corrupt[]  = {false, false, false, false, false}; // No ACK corruption
    
    // Run sender simulation
    sender_rdt30(messages, num_messages, data_lost, data_corrupt, ack_lost, ack_corrupt);
    
    print_statistics();
    
    // Demonstrate receiver separately
    printf("\n\n");
    Packet test_packets[] = {
        make_packet(0, "First"),
        make_packet(1, "Second"),
        make_packet(0, "Third"),
        make_packet(1, "Fourth")
    };
    
    bool rcv_lost[]    = {false, false, false, false};
    bool rcv_corrupt[] = {false, true,  false, false}; // Corrupt 2nd packet
    
    receiver_rdt30(test_packets, rcv_lost, rcv_corrupt, 4);
    
    return 0;
}