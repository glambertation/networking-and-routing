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
#pragma comment(lib,"ws2_32.lib")
unsigned short _send_pingreq();
unsigned short _recieve_pingreq();
unsigned short _packet_queue(unsigned short command, unsigned short packet, unsigned short mid, unsigned short qos);
unsigned short _send_simple_command(unsigned short command);
int USART_rec();
int recv_process();
int ping_ack();

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

char _out_packet[20] = {0};
char _current_out_packet[20] = {0};//μ±?°

struct messagestuff
{
	unsigned short  command;
	unsigned short  mid;
	unsigned short  qos;
	unsigned short  pos;
	unsigned short  to_process;
	unsigned short	packet;
}recmpkt,mpkt;

struct routestuff
{
	
	unsigned short  mid;
	unsigned short  forward_mid;
	unsigned short  layer;
	unsigned short  metric;
}rt;



int USART_rec(){
	u16 t;
	u16 len;
	u16 times = 0;
	rc=0;


//u8 USART_RX_BUF[USART_REC_LEN];//?óê??o3?,×?′óUSART_REC_LEN??×??ú.

//bit15￡?	?óê?íê3é±ê??
//bit14￡?	?óê?μ?0x0d
//bit13~0￡?	?óê?μ?μ?óDD§×??úêy??

		if (USART_RX_STA & 0x8000)//bit15￡?	?óê?íê3é±ê?? ?óê?íêá?￡???ò??óê?íêá?
		{
			len = USART_RX_STA & 0x3FFF;////?óê?×?·?3¤?è′ó13-0
			for (t = 0; t<len; t++)
			{
				USART1->DR = USART_RX_BUF[t];
				while ((USART1->SR & 0X40) == 0);//?-?··￠?í,?±μ?·￠?ííê±?   
			}
		    printf("\r\n\r\n");//??DD
			USART_RX_STA = 0;//?óê?×′ì?±ê?? ±￡3??óê?×′ì? ??á?×?±??óê?
			rc = USART_ERR_SUCCESS ;
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
  int tokenx1=0;
	int tokenx2=0;

	printf("Tokens:\n");

	// Establish string and get the first token:
	token1 = strtok(_current_out_packet, seps);
	printf(" oo%soo", token1);
	
  tokenx1	= atoi(token1);
	recmpkt.command = tokenx1;
	token1 = strtok(NULL, seps);
	tokenx2 = atoi(token1);
	recmpkt.mid = tokenx2;
	printf(" %d\n",recmpkt.mid);

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

  rc=0;
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
	rc=0;
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
	sprintf(_out_packet, "  %u%u%u%u%u%u  ", mpkt.command, mpkt.packet, mpkt.mid,  mpkt.qos, mpkt.pos, mpkt.to_process);
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
//ALIENTEK???￠STM32?a·￠°?êμ?é1
//?ü?íμ?êμ?é  
//??ê??§3?￡owww.openedv.com
//1??YêDD?òíμ?×ó????óD?T1???
 int main(void)
 {	
	delay_init();	    	 //?óê±oˉêy3?ê??ˉ	  
	LED_Init();		  	//3?ê??ˉó?LEDá??óμ?ó2?t?ó?ú
	uart_init(9600);
	 
	 
	while(1)
	{
		LED0=0;
		LED1=1;
		delay_ms(300);	 //?óê±300ms
		LED0=1;
		LED1=0;
		_send_pingreq();		
	    _recieve_pingreq();
	

		delay_ms(300);	//?óê±300ms
	}
 }

