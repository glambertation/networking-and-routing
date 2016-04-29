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





