#include<stdio.h>
#include<winsock2.h>

#include<time.h>
#include <string.h>
#include<stdlib.h>
#include <string.h>
#include <process.h>
#include "message_struct.h"
#include "global_var.h"
#pragma comment(lib,"ws2_32.lib")




void main(){

	struct A
	{
		int a;
		char b;
		int c;
		char d[];
	};
	struct A aa = { 2, 'k', 4, "hello" };

	char  buf[200] = { 0 };


	//memcpy(buf, &aa, sizeof(aa));

	sprintf_s(buf, 200, " all: %d%c%d%s\n", aa.a, aa.b, aa.c, aa.d);

	printf_s("Output:\n%s\ncharacter count =\n", buf);


	//all_init();
	_send_pingreq();
	//_recieve_pingreq();
	printf("hello\n");
	recv_process();

	routetable();
	//int lens = atoi(_current_out_packet);
	//int lenss = atoi(_out_packet);
	//printf("%d  and ", lens);




	//printf_s("Output:%scharacter count =\n", buff);
	//printf("%d  and buff ", sizeof(buff));
	//sprintf_s(buff, lens, " %u\n", PINGREQ);
	//printf_s("Output:%scharacter count =\n", buff);

	//printf("%s", _current_out_packet>>(lens-4));

	//printf("%d  and new buff ", sizeof(buff));

	//printf("ww%cww", _current_out_packet[2]);
	//printf("qqww%swwqq",_out_packet);
	//printf("%doo", lens);
	//printf("aa%d\n", lenss);
	//printf("end\n");

	printf("how many numbers\n");

	rt_init();
	insert_rt_next_doublenew(head, 1);
	insert_rt_next_doublenew(head, 2);
	insert_rt_next_doublenew(head, 3);
	insert_rt_next_doublenew(head, 4);
	insert_rt_next_doublenew(head, 5);
	insert_rt_next_doublenew(head, 6);
	insert_rt_next_doublenew(head, 7);

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


	printf("tocken!!!!!!!!!!!");
	char string1[] =
		"A string\tof ,,tokens and some  more tokens";

	char seps[] = ",";
	char seps1[] = "\t";
	char *token1 = NULL;

	char *next_token1 = NULL;


	printf("Tokens:\n");

	// Establish string and get the first token:
	token1 = strtok_s(string1, seps, &next_token1);
	printf("tocken1: %s\n", token1);
	token1 = strtok_s(token1, seps1, &next_token1);
	printf("tocken3: %s\n", token1);
	// While there are tokens in "string1" or "string2"
	while (token1 != NULL)
	{

		printf("tocken2:  %s\n", token1);
		token1 = strtok_s(NULL, seps1, &next_token1);


	}


	printf("tocken!!!!!!!!!!!\n\n\n");
	printf("new!!!!!!!!!!!\n");

	char we[] = { 'p', '2', '3' };
	int cc = atoi(we);
	char *me = we;
	printf("%c\n", *me);
	me++;
	printf("%c\n", *me);
	me++;
	printf("%c\n", *me);
	printf("%d\n", cc);

	printf("new!!!!!!!!!!!\n");




	getchar();
}








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

	unsigned short packet = htons(command);
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


