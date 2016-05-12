#include <stdio.h>
#include <assert.h>

#include "message_struct.h"




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
extern unsigned short	SEND_RT;
extern unsigned short  SEND_MESSAGE;

//===============  usart  ======================
extern char _out_packet[20];
extern char _current_out_packet[20];


//===============  rt  ======================
extern unsigned short  MQTT_ERR_SUCCESS;
extern unsigned short  MY_CHILD_HAS_NODE ;
extern unsigned short  MY_RT  ; //send myself route table
extern unsigned short  CHILD_RT_ERR ;


node *will_after_found_id;
extern unsigned short  FOUND_MID;
int TRACE_FOUND_MID = 0;
char track_rt[300] = {0};

int send_my_rt(char * my_child_rt);
int read_my_child_rt(char * packet);
int build_my_child_rt(char *packet);
node * preordertraverse(node * tree, node *id);
void rt_init();
void insert_rt_next_doublenew(node * head, int one);
void insert_rt_next_doublenew_delete(node * tree, int delete_id);
void node_init(node * node_to_init);
void tracking_rt(node * tree, int  id);


//================= over ============================= //




//===============  recv-proccess  ======================

//extern node * will_after_found_id;  defined in rt.h
extern int rc;
extern int already_in_net;


void _recieve_pingreq();
int recv_process(char *message);
int _send_rt(unsigned short did, char * packet);
int _send_sub(unsigned short did);
int _send_pub(unsigned short did);
int ping_ack(unsigned short did);
unsigned short _send_pingreq();
unsigned short _send_simple_command(unsigned short command, unsigned short mid, unsigned short did, char *packet);
unsigned short _packet_queue(unsigned short command, char * packet, unsigned short mid, unsigned short did, unsigned short mid_id);