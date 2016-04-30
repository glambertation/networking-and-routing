#include "rt.h"

int recv_process(){

	char seps[] = " ,\t\n";
	char *token1 = NULL;

	char *next_token1 = NULL;


	printf("Tokens:\n");

	// Establish string and get the first token:
	token1 = strtok_s(_current_out_packet, seps, &next_token1);
	printf(" oo%soo", token1);
	int tokenx1 = atoi(token1);
	recmpkt.command = tokenx1;
	token1 = strtok_s(NULL, seps, &next_token1);
	int tokenx2 = atoi(token1);
	recmpkt.mid = tokenx2;
	printf(" %d\n", recmpkt.mid);

	// While there are tokens in "string1" or "string2"
	while (token1 != NULL)
	{
		// Get next token:

		printf(" %s\n", token1);
		token1 = strtok_s(NULL, seps, &next_token1);

	}

	unsigned short rc;
	if (recmpkt.command == PINGREQ){
		routetable();
		rc = ping_ack();

	}

	if (recmpkt.command == PINGRESP){
		//routetable_mult();
		rc = 0;


	}
	return rc;


}

int ping_ack(){

	unsigned short rc = _send_simple_command(PINGRESP);
	mpkt.did = rt.forward_mid;
	if (rc == MQTT_ERR_SUCCESS){
		unsigned short _ping_t = time(0);
	}
	return rc;

}




int routetable(){
	rt.mid = mpkt.mid;
	rt.forward_mid = recmpkt.mid;
	rt.layer = 1;
	rt.metric = 1;
	return 0;

}
//couple with ping——ack
unsigned short _send_pingreq(){
	//self._easy_log(MQTT_LOG_DEBUG, "Sending PINGREQ")
	unsigned short rc = _send_simple_command(PUBLISH);
	printf("%d", 11);
	if (rc == MQTT_ERR_SUCCESS){
		unsigned short _ping_t = time(0);
	}
	return rc;
}
unsigned short _send_simple_command(command){
	//For DISCONNECT, PINGREQ and PINGRESP
	//unsigned short remaining_length = 0;

	//unsigned short packet = htons(command);
	unsigned short packet =0;
	printf("%d", 12);
	printf("%d", packet);
	//packet = struct.pack('!BB', command, remaining_length);
	//unsigned short packet = command;
	return _packet_queue(command, packet, 0, 0);
}

unsigned short _packet_queue(command, packet, mid, qos){

	mpkt.command = command;
	mpkt.mid = mid;
	mpkt.did = 0;
	mpkt.packet = packet;
	mpkt.qos = qos;
	mpkt.pos = 0;
	mpkt.to_process = sizeof(packet);


	//self._out_packet_mutex.acquire();
	sprintf_s(_out_packet, 20, "%u,%u,%u,%u,%u,%u,%u", mpkt.command, mpkt.mid, mpkt.did, mpkt.packet, mpkt.qos, mpkt.pos, mpkt.to_process);
	printf("%s\n", _out_packet);
	//	_out_packet.append(mpkt);  //插入队列
	//if self._current_out_packet_mutex.acquire(False){
	//if (_current_out_packet == 0 && sizeof(_out_packet) > 0)
	if (sizeof(_out_packet) > 0){
		for (int i = 0; i < sizeof(_out_packet); i++){
			_current_out_packet[i] = _out_packet[i];//把packet最后一位弹出给current-out-packet
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
	printf("%d\n", 13);
	printf("%s", _current_out_packet);
	return MQTT_ERR_SUCCESS;
}


