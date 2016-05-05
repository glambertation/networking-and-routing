
struct messagestuff
{
	unsigned short  command;
	unsigned short  mid;
	unsigned short  did;
	unsigned short  qos;
	unsigned short  pos;
	unsigned short  to_process;
	unsigned short	packet;

};
extern struct messagestuff recmpkt;
extern struct messagestuff mpkt;


 typedef struct list
{
	int mid;
	struct list *child;//child
	struct list *next;//college
	struct list *prior;//college
	struct list *father;//college
}node;


extern node *head;
extern node *temp_next;
extern node *temp_child;
extern node *temp_prior;
extern node *temp_father;
extern node *point_found_mid;

