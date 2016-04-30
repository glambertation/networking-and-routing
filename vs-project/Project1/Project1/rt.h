#include<stdio.h>


#include "message_struct.h"
#include "global_var.h"



extern unsigned short	CONNECT;
extern unsigned short	CONNACK;
extern unsigned short	PUBLISH ;
extern unsigned short	PUBACK;
extern unsigned short	PUBREC;
extern unsigned short	PUBREL;
extern unsigned short	PUBCOMP;
extern unsigned short	SUBSCRIBE;
extern unsigned short	SUBACK;
extern unsigned short	UNSUBSCRIBE ;
extern unsigned short	UNSUBACK;
extern unsigned short	PINGREQ;//1100 0000 transfer to 192 in decimal unit
extern unsigned short	PINGRESP;
extern unsigned short	DISCONNECT;

extern unsigned short  MQTT_ERR_SUCCESS;
extern unsigned short  MY_CHILD_HAS_NODE ;
extern unsigned short  MY_RT  ; //send myself route table
extern unsigned short  CHILD_RT_ERR ;



extern char _out_packet[20];
extern char _current_out_packet[20];


node * preordertraverse(node * tree, node *id);


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
