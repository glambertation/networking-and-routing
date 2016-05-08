

struct messagestuff
{
	unsigned short  command;
	unsigned short  mid;
	unsigned short  did;
	unsigned short  qos;
	unsigned short  pos;
	unsigned short  to_process;
	char	        packet[200];

};
struct messagestuff recmpkt;
struct messagestuff mpkt;

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
node *point_found_mid;