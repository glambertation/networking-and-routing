#include<stdio.h>
#include <string.h> //memset
#include <stdlib.h> //atoi
#include "delay.h"
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

//===============  usart  ======================
extern char _out_packet[20];
extern char _current_out_packet[20];
extern char _usart_recv_packet1[200] ;
extern char _usart_recv_packet2[200] ;

extern int already_in_net;
extern int len_packet;
extern int usart_flag1;
extern int usart_flag2;



//===============  rt  ======================
extern unsigned short  MQTT_ERR_SUCCESS;
extern unsigned short  MY_CHILD_HAS_NODE ;
extern unsigned short  MY_RT  ; //send myself route table
extern unsigned short  CHILD_RT_ERR ;


node *will_after_found_id;
extern unsigned short  FOUND_MID;

int send_my_rt(char * my_child_rt);
int read_my_child_rt(char * packet);
int build_my_child_rt(char *packet);
node * preordertraverse(node * tree, node *id);
void rt_init();
void insert_rt_next_doublenew(node * head, int one);
void insert_rt_next_doublenew_delete(node * tree, int delete_id);


//================= over ============================= //




//===============  recv-proccess  ======================


unsigned short _send_pingreq();
void _recieve_pingreq();
unsigned short _packet_queue(unsigned short command, unsigned short packet, unsigned short mid, unsigned short did);
unsigned short _send_simple_command(unsigned short command , unsigned short mid, unsigned short did);
int USART_rec();
int recv_process_outside();
int recv_process(char *message);
int ping_ack(unsigned short did);
int _send_pub(unsigned short did);
int _send_sub(unsigned short did);


extern unsigned short  MQTT_ERR_SUCCESS ;
extern unsigned short  USART_ERR_SUCCESS ;
extern unsigned short  USART_ERR_NOMESSAGE;
extern int rc;
extern int already_in_ne;
extern int len_packet;
extern int usart_flag1;
extern int usart_flag2;
extern int already_in_net;


//===============  message_struct  ======================



extern node *head;
extern node *temp_next;
extern node *temp_child;
extern node *temp_prior;
extern node *temp_father;
extern node *point_found_mid;
