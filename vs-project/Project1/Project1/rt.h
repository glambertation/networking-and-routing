#include<stdio.h>
#include<winsock2.h>

#include<time.h>
#include <string.h>
#include<stdlib.h>
#include <string.h>
#include <process.h>
#include "message_struct.h"
#include "global_var.h"


unsigned short _send_pingreq();
unsigned short _recieve_pingreq();
unsigned short _packet_queue(command, packet, mid, qos);
unsigned short _send_simple_command(command);
int recv_process();


int ping_ack();
int routetable();
//int USART_rec();
void rt_init();
void insert_rt_next();

void insert_rt_next_doublenew();
void insert_rt_next_doublenew_delete(int mid);
int searching_node(int mid);
