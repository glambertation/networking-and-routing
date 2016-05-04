#include "rt.h"


void _recieve_pingreq(){
		if(USART_ERR_NOMESSAGE){
			printf("wrong situation");
		}
	//	printf("begin\n %s \nend",_usart_recv_packet);
		if (usart_flag1==1){
				recv_process( _usart_recv_packet1);
			 memset(_usart_recv_packet1, 0, sizeof(_usart_recv_packet1));
				printf("????%s ????\n",_usart_recv_packet1);
			usart_flag1=0;
			printf("case1\n");
		}
			
			
		//USART_ERR_NOMESSAGE=0;
		
		else if (usart_flag2==1){
				recv_process( _usart_recv_packet2);
				 memset(_usart_recv_packet2, 0, sizeof(_usart_recv_packet2));
			printf("!!!!%s !!!\n",_usart_recv_packet2);
					usart_flag2=0;
				printf("case2\n");
		}

	else{
		printf("else situation");
	}
	
	//printf("USART_ERR_NOMESSAGE: %d \n",USART_ERR_NOMESSAGE);
	//printf("usart_flag: %d \n usart_flag %d \n",usart_flag1,usart_flag2);

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


	if (recmpkt.command == PINGREQ && (recmpkt.did==102||recmpkt.did==1111)){//192
		printf("PINGREQ");
		if(already_in_net==0){
			rc = ping_ack(recmpkt.mid);
			already_in_net=1;
		}
		

	}
	if (recmpkt.command == PINGRESP && (recmpkt.did==102||recmpkt.did==1111)){  //208
		printf("PINGRESP");
		insert_rt_next_doublenew(head,recmpkt.mid);
	//	rc = _send_pub();// ask it to be master-child node
	//	printf("ask it to be master-child node");

	}
	if (recmpkt.command == PUBLISH ){  //48
		printf("PUBLISH");
	//	printf("child ping!!!!!!!!!!!!");
		//if get pub,search rt to find out;
		if(recmpkt.did==102){
				_send_sub(recmpkt.mid);
		}
		else{
			preordertraverse(head, recmpkt.did);
				if(FOUND_MID==1 ){
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