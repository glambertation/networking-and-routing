#include "rt.h"


int send_my_rt(char * my_child_rt){
	char my_rt[] = { 0 };//数组初始化可以不确定大小吗？
	my_rt[0] = head->father->mid;
	my_rt[1] = head->mid;
	my_rt[2] = "#";
	my_rt[3] = head->mid;
	node * tmp_head = (node *)malloc(sizeof(struct list));
	tmp_head = head;
	int my_rt_num = 4;
	tmp_head = tmp_head->child;
	while (tmp_head != NULL)
	{
		my_rt[my_rt_num] = tmp_head->mid;
		my_rt_num++;

		tmp_head = tmp_head->next;
	}
	int my_child_rt_num = 0;
	char *my_rt_point = my_rt;
	char *my_child_rt_point = my_child_rt;


	if (MY_CHILD_HAS_NODE){

		my_rt_point = strcpy_s(my_rt_point, my_rt_num, my_child_rt_point);

	}

	_send_simple_command(MY_RT);



}

int read_my_child_rt(char * packet){   //use # to cut and build_my_child_rt to biuld whole node
	char seps[] = "#";
	char *token1 = NULL, *pNext = NULL;

	// Establish string and get the first token:
	token1 = strtok_s(packet, seps, pNext);
	build_my_child_rt(token1);

	while (token1 != NULL)
	{

		token1 = strtok_s(NULL, seps, pNext);

		build_my_child_rt(token1);

	}
}
int build_my_child_rt(char *packet){ //packet cannot have some string or else, only ok for num packet[]={'1','22','678'}

	if (atoi(*packet) == 102){
		packet++;
		while (*packet != NULL)
		{
			int tmp_id;
			tmp_id = atoi(*packet);
			insert_rt_next_doublenew(packet, tmp_id);
			packet++;

		}
	}

	if (*packet != 102){
		int tmp_id;
		tmp_id = atoi(*packet);
		if (FOUND_MID){// must return a point to tmp_id
			node *after_found_id = (node *)malloc(sizeof(struct list));
			after_found_id = preordertraverse(head, tmp_id);

			/*
			add something to change the point to tmp_id
			void move_piont_to_build_rt(){node *head, node *tmp_id_point}
			*/
			packet++;
			while (*packet != NULL)
			{
				int tmp_id;
				tmp_id = atoi(*packet);
				insert_rt_next_doublenew(after_found_id, tmp_id);//inset from the after_found_id
				packet++;

			}
		}

		else {
			CHILD_RT_ERR = 1;
		}


	}

}




void preordertraverse(node * tree, int mid){
	if (tree->mid == mid){
		FOUND_MID = 1;
		node *point_found_mid = tree;
		return point_found_mid;

	}

	if (tree == NULL)
		return;
	printf("%d", tree->mid);
	preordertraverse(tree->child, mid);
	preordertraverse(tree->next, mid);


}
void move_piont_to_build_rt(node *head, node *tmp_id_point){
	head = tmp_id_point;

}

int searching_node(int mid){// searching node only at its child level,
	printf("one");
	temp_next = head;
	int yc = 1;
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

	head = malloc(sizeof(struct list));
	head->mid = 101;
	head->next = NULL;
	head->father = NULL;
	head->prior = NULL;
	head->child = NULL;



	temp_next = malloc(sizeof(struct list));
	temp_next = head;
	temp_child = malloc(sizeof(struct list));
	temp_child = head;

}
void insert_rt_next(){
	if (temp_next != 0){
		while (temp_next->next != 0){
			temp_next = temp_next->next;
		}
	}
	temp_next->next = malloc(sizeof(struct list));
	temp_next = temp_next->next;
	temp_next->mid = 4;
	temp_next->next = NULL;

}


void insert_rt_next_doublenew(node * head, int one){

	node * temp_insert = (node *)malloc(sizeof(struct list));//middle one

	if (head->child == 0){      //如果子节点为空

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
/*
void insert_rt_next_doublenew(int one){

node * temp_insert = (node *)malloc(sizeof(struct list));//middle one

if (temp_next != 0){
while (temp_next->next != 0){
temp_next = temp_next->next;
}
}
//temp_next->next = malloc(sizeof(struct list));
//temp_next = temp_next->next;
//temp_next->mid = 4;
//temp_next->next = NULL;

temp_next->next = temp_insert;
temp_insert->prior = temp_next;
temp_insert->mid = one;
temp_insert->next = NULL;
temp_insert->father = temp_next->father;//same father node
temp_next = temp_insert;



}

*/
void insert_rt_next_doublenew_delete(int mid){//deletenode
	printf("one");
	int ic = 1;
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


