
#include<winsock2.h>

#include<time.h>
#include <string.h>
#include<stdlib.h>
#include <string.h>
#include <process.h>

#include "rt.h"
#pragma comment(lib,"ws2_32.lib")

void pre(node * tree);


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
unsigned short	PINGREQ = 0xC0;//1100 0000 transfer to 192 in decimal unit
unsigned short	PINGRESP = 0xD0;
unsigned short	DISCONNECT = 0xE0;

unsigned short  MQTT_ERR_SUCCESS = 0;
unsigned short  MY_CHILD_HAS_NODE = 0;
unsigned short  MY_RT = 0xf0; //send myself route table
unsigned short  CHILD_RT_ERR = 1;
unsigned short  FOUND_MID = 0;


char _out_packet[20] = { 0 };
char _current_out_packet[20] = { 0 };



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
	insert_rt_next_doublenew(head, 8);

	//printf("head_mid->%d\n", head->mid);
	
	//	insert_rt_next_doublenew_delete(5);
	
	insert_rt_next_doublenew_delete(head,5);
	//insert_rt_next_doublenew_delete(head,16);
	/*
	head = head->child;
	printf("%d\n", head);
	while (head != NULL)
	{
		printf("my mid is :  ");
		printf("%d\n", head->mid);
		printf("my father mid is :");
		printf("%d\n", head->father->mid);


		head = head->next;
	}
	printf("\n");

	*/
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

	int ipo = 198;
	
	
	printf("new0!!!!!!!!!!!\n%d\n", ipo);
	printf("tree::%d\n", head->mid);
	unsigned short q = 2;
	unsigned short qw = 103;
	unsigned short qwe = 104;
	unsigned short qwer = 105;
	char rr[20] = { 0 };
	sprintf_s(rr,20, "%u,%u,%u,%u#", q,qw,qwe,qwer);
	node *father;
	father = malloc(sizeof(struct list));
	node_init(father);
	
	father->child = head;
	head->father = father;
	father->mid = 100;
	father->father = NULL;
	MY_CHILD_HAS_NODE = 1;
	send_my_rt(rr);

	read_my_child_rt(rr);
	pre(head);
	tracking_rt(head,104 );
	printf("new!!!!!!!!!!!\n");
	printf("%s", track_rt);
	getchar();
}

void pre(node * tree){




	//printf("tree_mid->%d\n", tree->mid);




	if (tree == NULL)
		return;
	printf("tree::%d---father::%d\n", tree->mid, tree->father->mid);


	pre(tree->child);
	pre(tree->next);



}




