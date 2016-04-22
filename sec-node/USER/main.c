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
unsigned short _packet_queue(unsigned short command, unsigned short packet, unsigned short mid, unsigned short did);
unsigned short _send_simple_command(unsigned short command , unsigned short mid, unsigned short did);
int USART_rec();
int recv_process_outside();
int recv_process(char *message);
int ping_ack(unsigned short did);
int _send_pub(unsigned short did);
int _send_sub(unsigned short did);

void rt_init();
void insert_rt_next_doublenew();
void insert_rt_next_doublenew_delete(int mid);
int searching_node(int mid);


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
unsigned short  USART_ERR_NOMESSAGE;
int rc;
int already_in_net=0;

char _out_packet[20] = { 0 };
char _current_out_packet[20] = { 0 };//µ±?°
char _usart_recv_packet[200] = { 0 };

struct messagestuff
{
	unsigned short  command;
	unsigned short  mid;
	unsigned short  did;
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



int searching_node(int mid){// searching node only at its child level,
	
	int yc = 1;
	printf("one");
	temp_next = head;
	temp_next=temp_next->child;
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
	return yc;





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
		printf("insert mid is: %d",temp_next->mid);
		printf("insert father node is: %d",temp_next->father->mid);
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


	//u8 USART_RX_BUF[USART_REC_LEN];//?ук??o3?,Ч?'уUSART_REC_LEN??Ч??ъ.

	//bit15??	?ук?нк3й±к??
	//bit14??	?ук?µ?0x0d
	//bit13~0??	?ук?µ?µ?уDD§Ч??ъкy??

	if (USART_RX_STA & 0x8000)//bit15??	?ук?нк3й±к?? ?ук?нкб?????т??ук?нкб?
	{
		len = USART_RX_STA & 0x3FFF;////?ук?Ч?·?3¤?и'у13-0
		for (t = 0; t<len; t++)
		{
			USART1->DR = USART_RX_BUF[t];
			_usart_recv_packet[t]=USART_RX_BUF[t];
			while ((USART1->SR & 0X40) == 0);//?-?··??н,?±µ?·??ннк±?   
		}
		printf("\r\n\r\n");//??DD
		USART_RX_STA = 0;//?ук?Ч'м?±к?? ±?3??ук?Ч'м? ??б?Ч?±??ук?
		rc = USART_ERR_SUCCESS;
	}
	else
	{
		int  rc = USART_ERR_NOMESSAGE;

	}
	return rc;
}

unsigned short _recieve_pingreq(){
	if (USART_ERR_NOMESSAGE){
		printf("begin\n %s \nend",_usart_recv_packet);
				recv_process_outside();
		USART_ERR_NOMESSAGE=0;
		
		
		
	}
	else if (USART_rec() == USART_ERR_NOMESSAGE){
		printf("not rec message");
	}
	else{
		printf("else situation");
	}

}

int recv_process_outside(){

	char seps[] = ";";
	char *token1 = NULL;

	// Establish string and get the first token:
	token1 = strtok(_usart_recv_packet, seps);
	printf("fisrt!!!!!!!!! %s\n", token1);
		printf("second!!!!!!!!! %s\n", token1);
  recv_process(token1);
 // printf("fisrt %s\n", token1);
	// While there are tokens in "string1" or "string2"
	while (token1 != NULL)
	{
		// Get next token:

		//printf(" %s\n", token1);
		printf("^^^^^^^^ %s^^^^^^^^\n", token1);
		token1 = strtok(NULL, seps);
		printf("^^^^^^^^ %s^^^^^^^^\n", token1);
		recv_process(token1 );

	}
	 memset(_usart_recv_packet, 0, sizeof(_usart_recv_packet));
	return rc;

}




int recv_process(char *message){

	char seps[] = " ,\t\n";
	char *token1 = NULL;

	char *next_token1 = NULL;
	int tokenx1 = 0;
	int tokenx2 = 0;
	int tokenx3 = 0;

	printf("Tokens:\n");
	printf("message %S\n",message);

	// Establish string and get the first token:
	token1 = strtok(message, seps);
	printf(" oo%soo", token1);


	tokenx1 = atoi(token1);
	recmpkt.command = tokenx1;
	printf("command: %d\n", recmpkt.command);
	token1 = strtok(NULL, seps);
	tokenx2 = atoi(token1);
	recmpkt.mid = tokenx2;
	printf("mid: %d\n", recmpkt.mid);
	token1 = strtok(NULL, seps);
	tokenx3 = atoi(token1);
	recmpkt.did = tokenx3;
	printf("did: %d\n", recmpkt.did);

	// While there are tokens in "string1" or "string2"
	while (token1 != NULL)
	{
		// Get next token:

		printf(" %s\n", token1);
		token1 = strtok(NULL, seps);

	}


	if (recmpkt.command == PINGREQ && (recmpkt.did==102||recmpkt.did==1111)){
		printf("PINGREQ");
		if(already_in_net==0){
			rc = ping_ack(recmpkt.mid);
			already_in_net=1;
		}
		

	}
	if (recmpkt.command == PINGRESP && (recmpkt.did==102||recmpkt.did==1111)){
		printf("PINGRESP");
		insert_rt_next_doublenew(recmpkt.mid);
	//	rc = _send_pub();// ask it to be master-child node
	//	printf("ask it to be master-child node");

	}
	if (recmpkt.command == PUBLISH ){
		printf("PUBLISH");
	//	printf("child ping!!!!!!!!!!!!");
		//if get pub,search rt to find out;
		if(recmpkt.did==102){
				_send_sub(recmpkt.mid);
		}
		else{
				if(searching_node(recmpkt.did)){
					_send_pub(recmpkt.did);
					
				}

		}
		// _send_pingreq();
		//printf("child ping!!!!!!!!!!!!");
		

	}
	
	return rc;


}

int _send_sub(unsigned short did){
	unsigned short rc = _send_simple_command(PINGRESP,102,did);
  
	rc = 0;
	return rc;

}


int _send_pub(unsigned short did){
	unsigned short rc = _send_simple_command(PUBLISH,102,did);
  
	rc = 0;
	return rc;

}


int ping_ack(unsigned short did){
	unsigned short rc = _send_simple_command(PINGRESP,102,did);
  
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
	unsigned short rc = _send_simple_command(PINGREQ,101,1111);
	//if (rc == MQTT_ERR_SUCCESS){
	//unsigned short _ping_t = time(0);
	//}
	
	delay_ms(30000);
	delay_ms(30000);
	delay_ms(30000);
	delay_ms(30000);
	delay_ms(30000);
	delay_ms(30000);
	delay_ms(30000);
	delay_ms(30000);
	delay_ms(30000);
	delay_ms(30000);
	delay_ms(30000);
	rc = 0;
	return rc;
}
unsigned short _send_simple_command(unsigned short command , unsigned short mid, unsigned short did){
	//For DISCONNECT, PINGREQ and PINGRESP
	//unsigned short remaining_length = 0;

	unsigned short packet = command;
	//printf("%d", 12);
	//packet = struct.pack('!BB', command, remaining_length);
	//unsigned short packet = command;
	return _packet_queue(command, packet, mid, did);
}

unsigned short _packet_queue(unsigned short command, unsigned short packet, unsigned short mid, unsigned short did){
	int i = 0;

	mpkt.command = command;
	mpkt.mid = mid;
	mpkt.packet = packet;
	mpkt.did = did;
	mpkt.pos = 0;
	mpkt.to_process = sizeof(packet);


	//self._out_packet_mutex.acquire();
	sprintf(_out_packet, "  %u%u%u%u%u%u  ", mpkt.command,  mpkt.mid, mpkt.did, mpkt.packet, mpkt.pos, mpkt.to_process);
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
//ALIENTEK????STM32?a·?°?кµ?й1
//?ь?нµ?кµ?й  
//??к??§3??owww.openedv.com
//1??YкDD?тнµ?Чу????уD?T1???
int main(void)
{
	delay_init();	    	 //?ук±oЇкy3?к??Ї	  
	LED_Init();		  	//3?к??Їу?LEDб??уµ?у2?t?у?ъ
	uart_init(9600);
  rt_init();

	while (1)
	{
		LED0 = 0;
		LED1 = 0;
		delay_ms(300);	 //?ук±300ms
		LED0 = 1;
		LED1 = 0;
		// _send_pingreq();
		_recieve_pingreq();



		
	//	insert_rt_next_doublenew(1);
	//	insert_rt_next_doublenew(2);
		

		//	insert_rt_next_doublenew_delete(5);

		//head = head->child;//transfer to the first child node and then printf head-next-mid
		//searching_node(15);
		//insert_rt_next_doublenew_delete(5);
		//insert_rt_next_doublenew_delete(16);
		/*
		while (head != NULL)
		{
			printf("my mid is :  ");
			printf("%d\n", head->mid);
			printf("my father mid is :");
			printf("%d\n", head->father->mid);


			head = head->next;
		}
		*/
		printf("\n");

		//delay_ms(30000);	//?ук±300ms
	}
}
