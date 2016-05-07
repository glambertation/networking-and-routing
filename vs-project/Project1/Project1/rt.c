#include "rt.h"

char track_rt[300] = { 0 };
int TRACE_FOUND_MID = 0;

/*
node *will_after_found_id;
extern unsigned short  FOUND_MID;
int send_my_rt(char * my_child_rt);
int read_my_child_rt(char * packet);
int build_my_child_rt(char *packet);
node * preordertraverse(node * tree, node *id);
void rt_init();
void insert_rt_next_doublenew(node * head, int one);
void insert_rt_next_doublenew_delete(node * tree, int delete_id);
*/


//make my own rt into my_rt[], then _send_simple_command(MY_RT);


//make my own rt into my_rt[], then _send_simple_command(MY_RT);
int send_my_rt(char * my_child_rt){
	char my_rt[300] = { 0 };//Êý×é³õÊ¼»¯¿ÉÒÔ²»È·¶¨´óÐ¡Âð£¿
	node * tmp_head;
	char *my_rt_point;
	char *my_child_rt_point;
	int my_child_rt_num;


	tmp_head = malloc(sizeof(struct list));
	my_child_rt_num = 0;
	my_rt_point = my_rt;
	my_child_rt_point = my_child_rt;

	sprintf_s(my_rt,300, "%u,%u#%u", head->father->mid, head->mid, head->mid);

	tmp_head = head;
	tmp_head = tmp_head->child;


	while (tmp_head != NULL) // add child
	{	

		sprintf_s(my_rt, 300,"%s,%u", my_rt, tmp_head->mid);
		
		tmp_head = tmp_head->next;
	}

	sprintf_s(my_rt,300, "%s#", my_rt);


	if (MY_CHILD_HAS_NODE){  //MY_CHILD_HAS_NODE set in  
		my_rt_point = strcat(my_rt_point, my_child_rt_point); // add child-child's child  
		//and the point my_rt_point point to the begining 
	}
	printf("ok!\n");
	printf("%s", my_rt_point);
	printf("ok!\n");
//	_send_simple_command(MY_RT, 102, 101);// 

	//todo
	/*
	_send_simple_command(MY_RT,my_rt_point);//
	*/

}


/*
when got child_rt, to build own rt:
1. read_my_child_rt(char * packet)  //cut use #
2. build_my_child_rt(token1);

*/

/*
int send_my_rt(char * my_child_rt){
	char my_rt[] = { 0 };//数组初始化可以不确定大小吗？
	my_rt[0] = head->father->mid;
	my_rt[1] = head->mid;
	my_rt[2] = "#";  //add father-me and over


	my_rt[3] = head->mid;  //add me
	node * tmp_head = (node *)malloc(sizeof(struct list));
	tmp_head = head;
	int my_rt_num = 4;
	tmp_head = tmp_head->child;


	while (tmp_head != NULL) // add child
	{
		my_rt[my_rt_num] = tmp_head->mid;
		my_rt_num++;

		tmp_head = tmp_head->next;
	}
	my_rt[my_rt_num] = '#';//over me-child


	int my_child_rt_num = 0;
	char *my_rt_point = my_rt;
	char *my_child_rt_point = my_child_rt;


	if (MY_CHILD_HAS_NODE){  //MY_CHILD_HAS_NODE set in  
		my_rt_point = strcpy_s(my_rt_point, my_rt_num, my_child_rt_point); // add child-child's child  
		//and the point my_rt_point point to the begining 
	}

	//_send_simple_command(MY_RT);// 

	//todo
	
//	_send_simple_command(MY_RT,my_rt_point);//
   

}
*/

/*
when got child_rt, to build own rt:
1. read_my_child_rt(char * packet)  //cut use #
2. build_my_child_rt(token1);

*/

int read_my_child_rt(char * packet){   //use # to cut and build_my_child_rt to biuld whole node
	char seps[] = "#";
	char *token1 = NULL, *pNext = NULL;
	printf("one!!!!!!!!!!!\n\n");
	// Establish string and get the first token:
	token1 = strtok_s(packet, seps, &pNext);
	build_my_child_rt(token1);
	printf("two!!!!!!!!!!!\n\n");
	while (token1 != NULL)
	{

		token1 = strtok_s(NULL, seps, &pNext);
		printf("there!!!!!!!!!!!\n\n");
		if (token1 != NULL){
			build_my_child_rt(token1);
			printf("four!!!!!!!!!!!\n\n");
		}
		

	}
	printf("new0!!!!!!!!!!!\n\n");
}





int build_my_child_rt(char *packet){ //packet cannot have some string or else, only ok for num packet[]={'1','22','678'}
	char seps[] = ",";
	char *token1 = NULL;
	char *pnext = NULL;
	char *pnext1 = NULL;
	printf("five!!!!!!!!!!!\n\n");
	printf("five!!!!!!!!!!!\n%s\n",packet);




	token1 = strtok_s(packet, seps, &pnext);





	if (atoi(token1) == 101){
		printf("six!!!!!!!!!!!\n\n");
		printf("six!!!!!!!!!!!\n%s\n",token1);
		while (token1!= NULL)
		{
			printf("seven!!!!!!!!!!!\n\n");
			
			token1 = strtok_s(NULL, seps, &pnext);
			printf("token1!!!!!!!!!!!\n%s\n",token1);
			if (token1 != NULL){
				insert_rt_next_doublenew(head, atoi(token1));
			}
			  //insert from packet:should packet->child then insert
			

		}
		printf("eight!!!!!!!!!!!\n\n");
	}

	else if (atoi(token1) != 101){

		node *try_found_id = (node *)malloc(sizeof(struct list));
		node *found_id = (node *)malloc(sizeof(struct list));
		
		try_found_id->mid = atoi(token1);
		preordertraverse(head, try_found_id);
		found_id = will_after_found_id;

		preordertraverse(head, try_found_id);
		printf("new000!!!!!!!!!!!%d\n", FOUND_MID);
		printf("new0found_id!!!!!!!!!!!%d\n", found_id->mid);
		if (FOUND_MID){// must return a point to tmp_id

			/*
			add something to change the point to tmp_id
			void move_piont_to_build_rt(){node *head, node *tmp_id_point}
			*/

			while (token1 != NULL)
			{
				
				token1 = strtok_s(NULL, seps, &pnext);
				if (token1 != NULL){
					insert_rt_next_doublenew(found_id, atoi(token1));
					printf("six--token1!!!!!!!!!!!\n%s\n", token1);
				}


			}
		}

		else {
			CHILD_RT_ERR = 1;
		}


	}




}


//searvh preoder

node * preordertraverse(node * tree, node *id){
	

	if (tree != NULL){
		if (tree->mid != 0){

			printf("tree_mid->%d\n", tree->mid);

			if (tree->mid == id->mid){
				FOUND_MID = 1;
				will_after_found_id = malloc(sizeof(struct list));
				will_after_found_id = tree;
				//printf("after_found_id->%d\n", will_after_found_id->mid);
				//printf("after_found_id->next%d\n", will_after_found_id->next->mid);
				//printf("after_found_id%d\n", will_after_found_id);
				//printf("FOUND_MID:%d\n", FOUND_MID);
				return 	will_after_found_id ;

			}


		}


	}
	if (tree == NULL)
		return ;
	printf("tree::%d\n", tree->mid);
	preordertraverse(tree->child, id);
	preordertraverse(tree->next, id);


}



//as we got node * preordertraverse(node * tree, int mid)
//which return the point of mid 


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



void node_init(node * node_to_init){

	node_to_init = malloc(sizeof(struct list));
	node_to_init->mid = NULL;
	node_to_init->next = NULL;
	node_to_init->father = NULL;
	node_to_init->prior = NULL;
	node_to_init->child = NULL;




}

void insert_rt_next_doublenew(node * head_insert, int one){

	node * temp_insert = (node *)malloc(sizeof(struct list));//middle one
	node_init(temp_next);
	node_init(temp_insert);
	temp_next = head_insert;

	if (head_insert->child == 0){      //如果子节点为空

		temp_next->child = temp_insert;
		temp_insert->prior = temp_next;
		temp_insert->mid = one;
		temp_insert->next = NULL;
		temp_insert->child = NULL;
		temp_insert->father = head_insert;//same father node
		temp_next = temp_insert;

	}
	else{
		temp_next = temp_next->child;
		if (temp_next != 0){
			while (temp_next->next != 0){
				temp_next = temp_next->next;
			}
			temp_next->next = temp_insert;
			temp_insert->prior = temp_next;
			temp_insert->mid = one;
			temp_insert->next = NULL;
			temp_insert->child= NULL;
			temp_insert->father = temp_next->father;//same father node
			temp_next = temp_insert;
		}
	}






}


void insert_rt_next_doublenew_delete(node * tree ,int delete_id){//delete node
	FOUND_MID = 0;
	node *found_id = (node *)malloc(sizeof(struct list));
	//after_found_id = NULL;
	node *will_found_id = (node *)malloc(sizeof(struct list));
	//will_found_id = NULL;
	will_found_id->mid = delete_id;
	printf("deltet_head_mid->%d\n", tree->mid);
	preordertraverse(tree, will_found_id);
	printf("id\n");
	printf("id%d\n", will_after_found_id->mid);
	found_id = will_after_found_id;
	//printf("balal%d\n", preordertraverse(tree, will_found_id));
	printf("found_id->%d\n", found_id->next->mid);
	printf("FOUND_MID:%d\n", FOUND_MID);

	



	if (FOUND_MID == 1){
		
		found_id->next->prior = found_id->prior;
		printf("found_id->%d\n", found_id->next->prior->mid);
		found_id->prior->next = found_id->next;
		//found_id->father->child = NULL;  cause every child was point to father and if delete,it will affact
		if (found_id->child != NULL){
			found_id->child->father->next->prior = found_id->child->father->prior;
			found_id->child->father->prior->next = found_id->child->father->next;
			found_id->child = NULL;

		}
		
	}



}





void tracking_rt(node * tree , int  id)
{
	char temp_track[300] = { 0 };

	if (tree != NULL){
		if (tree->mid != 0){

			printf("tree_mid->%d\n", tree->mid);
			

			if (tree->mid == id){

				

				TRACE_FOUND_MID = 1;
				will_after_found_id = malloc(sizeof(struct list));
				will_after_found_id = tree;
				//printf("after_found_id->%d\n", will_after_found_id->mid);
				//printf("after_found_id->next%d\n", will_after_found_id->next->mid);
				//printf("after_found_id%d\n", will_after_found_id);
				//printf("FOUND_MID:%d\n", FOUND_MID);
				node_init(temp_father);
				temp_father = tree;
				printf("father::%d\n", temp_father->mid);
				sprintf_s(track_rt, 300, "%u",  tree->mid);
				strcpy(temp_track, track_rt);
				printf("temp_track::%s\n",temp_track);
				printf("trck::%s\n", track_rt);
		
				
				while (temp_father != NULL){
					printf("one father::%d\n", temp_father->mid);


					if (temp_father->father != NULL){

						temp_father = temp_father->father;
						sprintf_s(track_rt, 300, "%u,%s", temp_father->mid, temp_track);
						strcpy(temp_track, track_rt);
						printf("trck::%s\n", track_rt);

					}
					else {
						printf("four\n");
						break;
					}

				}
		
				return 	;

			}
			


		}


	}
	if (tree == NULL)
		return;
	printf("tree::%d\n", tree->mid);
	tracking_rt(tree->child, id);
	tracking_rt(tree->next, id);


}