#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>//atoi
//#include "WinSock2.h"

//#include <time.h>
#include <string.h>
#include "usart.h"
#include "malloc.h"
#pragma comment(lib,"ws2_32.lib")
unsigned short _send_pingreq();
unsigned short _recieve_pingreq();
unsigned short _packet_queue(unsigned short command, unsigned short packet, unsigned short mid, unsigned short qos);
unsigned short _send_simple_command(unsigned short command);
int USART_rec();
int recv_process();
int ping_ack();

void rt_init();
void insert_rt_next_doublenew();
void insert_rt_next_doublenew_delete(int mid);
void searching_node(int mid);


unsigned short	CONNECT = 0x10;
unsigned short	CONNACK = 0x20;
unsigned short	PUBLISH = 0x30;
unsigned short	PUBACK = 0x40;
unsigned short	PUBREC = 0x50;
unsigned short	PUBREL = 0x60;
unsigned short	PUBCOMP = 0x70;
unsigned short	SUBSCRIBE = 0x80;
unsigned short	SUBACK = 0x90;
unsigned short	UNSUBSCRIBE = 0xA0;
unsigned short	UNSUBACK = 0xB0;
unsigned short	PINGREQ = 0xC0;
unsigned short	PINGRESP = 0xD0;
unsigned short	DISCONNECT = 0xE0;

unsigned short  MQTT_ERR_SUCCESS = 0;
unsigned short  USART_ERR_SUCCESS = 1;
unsigned short  USART_ERR_NOMESSAGE = 2;
int rc;

char _out_packet[20] = { 0 };
char _current_out_packet[20] = { 0 };//µ±?°

struct messagestuff
{
	unsigned short  command;
	unsigned short  mid;
	unsigned short  qos;
	unsigned short  pos;
	unsigned short  to_process;
	unsigned short	packet;
}recmpkt, mpkt;

struct routestuff
{

	unsigned short  mid;
	unsigned short  forward_mid;
	unsigned short  layer;
	unsigned short  metric;
}rt;

typedef struct list
{
	int mid;
	struct list *child;//child
	struct list *next;//college
	struct list *prior;//college
	struct list *father;//college
}node;
node *head;
node *temp_next;
node *temp_child;
node *temp_prior;
node *temp_father;



void searching_node(int mid){// searching node only at its child level,
	int yc = 1;
	printf("one");
	temp_next = head;

	//head = head->child;
	//node * temp_delete = (node *)malloc(sizeof(struct list));//middle one
	while (temp_next->mid != mid){
		printf("two");
		if (temp_next != 0){
			printf("there");
			if (temp_next->next != 0){
				printf("four\n");
				temp_next = temp_next->next;

			}
			else{
				printf("out of storage node and cannot find it out \n");
				printf("the lost mid is : %d-------fail!!! \n", mid);
				yc = 0;
				break;
			}
		}
	}
	if (yc == 1){
		printf("get mid:  %d--------success!!\n", temp_next->mid);
		printf("its father is :  %d\n", temp_next->father->mid);

	}

	//temp_next->next = malloc(sizeof(struct list));
	//temp_next = temp_next->next;
	//temp_next->mid = 4;
	//temp_next->next = NULL;
	printf("five");





}


void rt_init(){

	//head = malloc(sizeof(struct list));
	head = mymalloc(0, sizeof(struct list));
	head->mid = 101;
	head->next = NULL;
	head->father = NULL;
	head->prior = NULL;
	head->child = NULL;



	//temp_next = malloc(sizeof(struct list));
	temp_next = mymalloc(0, sizeof(struct list));
	temp_next = head;
	//temp_child = malloc(sizeof(struct list));
	temp_child = mymalloc(0, sizeof(struct list));
	temp_child = head;

}


void insert_rt_next_doublenew(int one){

	node * temp_insert;
	//temp_insert = (node *)malloc(sizeof(struct list));//middle one
	temp_insert = mymalloc(0, sizeof(struct list));
	if (head->child == 0){      //???????

		temp_next->child = temp_insert;
		temp_insert->prior = temp_next;
		temp_insert->mid = one;
		temp_insert->next = NULL;
		temp_insert->father = head;//same father node
		temp_next = temp_insert;

	}
	else{
		if (temp_next != 0){
			while (temp_next->next != 0){
				temp_next = temp_next->next;
			}
			temp_next->next = temp_insert;
			temp_insert->prior = temp_next;
			temp_insert->mid = one;
			temp_insert->next = NULL;
			temp_insert->father = temp_next->father;//same father node
			temp_next = temp_insert;
		}
	}

	//temp_next->next = malloc(sizeof(struct list));
	//temp_next = temp_next->next;
	//temp_next->mid = 4;
	//temp_next->next = NULL;




}


void insert_rt_next_doublenew_delete(int mid){//deletenode
	int ic = 1;
	printf("one");

	temp_next = head;
	//node * temp_delete = (node *)malloc(sizeof(struct list));//middle one
	while (temp_next->mid != mid){
		printf("two");
		if (temp_next != 0){
			printf("there");
			if (temp_next->next != 0){
				printf("four\n");
				temp_next = temp_next->next;

			}
			else{
				printf("out of storage node and cannot delete it out \n");
				printf("the mid cannot delete is : %d-------fail!!! \n", mid);
				ic = 0;
				break;
			}
		}
	}

	//temp_next->next = malloc(sizeof(struct list));
	//temp_next = temp_next->next;
	//temp_next->mid = 4;
	//temp_next->next = NULL;
	printf("five\n");

	if (ic == 1){
		printf("delete node mid is :  %d----succes!!\n", temp_next->mid);
		temp_next->next->prior = temp_next->prior;
		temp_next->prior->next = temp_next->next;
	}



}



int USART_rec(){
	u16 t;
	u16 len;
	u16 times = 0;
	rc = 0;


	//u8 USART_RX_BUF[USART_REC_LEN];//?óê??o3?,×?'óUSART_REC_LEN??×??ú.

	//bit15??	?óê?íê3é±ê??
	//bit14??	?óê?µ?0x0d
	//bit13~0??	?óê?µ?µ?óDD§×??úêy??

	if (USART_RX_STA & 0x8000)//bit15??	?óê?íê3é±ê?? ?óê?íêá?????ò??óê?íêá?
	{
		len = USART_RX_STA & 0x3FFF;////?óê?×?·?3¤?è'ó13-0
		for (t = 0; t<len; t++)
		{
			USART1->DR = USART_RX_BUF[t];
			while ((USART1->SR & 0X40) == 0);//?-?··??í,?±µ?·??ííê±?   
		}
		printf("\r\n\r\n");//??DD
		USART_RX_STA = 0;//?óê?×'ì?±ê?? ±?3??óê?×'ì? ??á?×?±??óê?
		rc = USART_ERR_SUCCESS;
	}
	else
	{
		int  rc = USART_ERR_NOMESSAGE;

	}
	return rc;
}

unsigned short _recieve_pingreq(){
	if (USART_rec() == USART_ERR_SUCCESS){
		printf("rec message");
	}
	else if (USART_rec() == USART_ERR_NOMESSAGE){
		printf("not rec message");
	}
	else{
		printf("else situation");
	}

}


int recv_process(){

	char seps[] = " ,\t\n";
	char *token1 = NULL;

	char *next_token1 = NULL;
	int tokenx1 = 0;
	int tokenx2 = 0;

	printf("Tokens:\n");

	// Establish string and get the first token:
	token1 = strtok(_current_out_packet, seps);
	printf(" oo%soo", token1);

	tokenx1 = atoi(token1);
	recmpkt.command = tokenx1;
	token1 = strtok(NULL, seps);
	tokenx2 = atoi(token1);
	recmpkt.mid = tokenx2;
	printf(" %d\n", recmpkt.mid);

	// While there are tokens in "string1" or "string2"
	while (token1 != NULL)
	{
		// Get next token:

		printf(" %s\n", token1);
		token1 = strtok(NULL, seps);

	}


	if (recmpkt.command == PINGREQ){
		rc = ping_ack();

	}
	return rc;


}

int ping_ack(){
	unsigned short rc = _send_simple_command(PINGRESP);

	rc = 0;
	return rc;

}

int routetable(){
	rt.mid = mpkt.mid;
	rt.forward_mid = recmpkt.mid;
	rt.layer = 1;
	rt.metric = 1;


}


unsigned short _send_pingreq(){
	//self._easy_log(MQTT_LOG_DEBUG, "Sending PINGREQ")
	unsigned short rc = _send_simple_command(PINGREQ);
	//if (rc == MQTT_ERR_SUCCESS){
	//unsigned short _ping_t = time(0);
	//}
	rc = 0;
	return rc;
}
unsigned short _send_simple_command(unsigned short command){
	//For DISCONNECT, PINGREQ and PINGRESP
	//unsigned short remaining_length = 0;

	unsigned short packet = command;
	//printf("%d", 12);
	//packet = struct.pack('!BB', command, remaining_length);
	//unsigned short packet = command;
	return _packet_queue(command, packet, 0, 0);
}

unsigned short _packet_queue(unsigned short command, unsigned short packet, unsigned short mid, unsigned short qos){
	int i = 0;

	mpkt.command = command;
	mpkt.mid = mid;
	mpkt.packet = packet;
	mpkt.qos = qos;
	mpkt.pos = 0;
	mpkt.to_process = sizeof(packet);


	//self._out_packet_mutex.acquire();
	sprintf(_out_packet, "  %u%u%u%u%u%u  ", mpkt.command, mpkt.packet, mpkt.mid, mpkt.qos, mpkt.pos, mpkt.to_process);
	//printf("%s\n", _out_packet);
	//	_out_packet.append(mpkt);  //????
	//if self._current_out_packet_mutex.acquire(False){
	//if (_current_out_packet == 0 && sizeof(_out_packet) > 0)
	if (sizeof(_out_packet) > 0){
		for (i = 0; i < sizeof(_out_packet); i++){
			_current_out_packet[i] = _out_packet[i];//?packet???????current-out-packet
		}
	}

	//	self._current_out_packet_mutex.release()
	//	}
	//self._out_packet_mutex.release()

	//Write a single byte to sockpairW (connected to sockpairR) to break
	//out of select() if in threaded mode.
	/*try:
	self._sockpairW.send(sockpair_data)
	except socket.error as err:
	if err.errno != EAGAIN:
	raise

	if not self._in_callback and self._thread is None:
	return self.loop_write()
	else:
	return MQTT_ERR_SUCCESS
	*/
	//printf("%d\n", 13);
	printf("%s", _current_out_packet);
	return MQTT_ERR_SUCCESS;
}
//ALIENTEK????STM32?a·?°?êµ?é1
//?ü?íµ?êµ?é  
//??ê??§3??owww.openedv.com
//1??YêDD?òíµ?×ó????óD?T1???
int main(void)
{
	delay_init();	    	 //?óê±o¯êy3?ê??¯	  
	LED_Init();		  	//3?ê??¯ó?LEDá??óµ?ó2?t?ó?ú
	uart_init(9600);


	while (1)
	{
		LED0 = 0;
		LED1 = 1;
		delay_ms(300);	 //?óê±300ms
		LED0 = 1;
		LED1 = 0;
		_send_pingreq();
		_recieve_pingreq();


		rt_init();
		insert_rt_next_doublenew(1);
		insert_rt_next_doublenew(2);
		insert_rt_next_doublenew(3);
		insert_rt_next_doublenew(4);
		insert_rt_next_doublenew(5);
		insert_rt_next_doublenew(6);
		insert_rt_next_doublenew(7);

		//	insert_rt_next_doublenew_delete(5);

		head = head->child;//transfer to the first child node and then printf head-next-mid
		searching_node(15);
		insert_rt_next_doublenew_delete(5);
		insert_rt_next_doublenew_delete(16);
		while (head != NULL)
		{
			printf("my mid is :  ");
			printf("%d\n", head->mid);
			printf("my father mid is :");
			printf("%d\n", head->father->mid);


			head = head->next;
		}
		printf("\n");

		delay_ms(300);	//?óê±300ms
	}
}

