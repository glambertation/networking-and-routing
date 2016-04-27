#include "sys.h"
#include "usart.h"	 
extern unsigned short  USART_ERR_NOMESSAGE;
extern char _usart_recv_packet1[200] ;
extern char _usart_recv_packet2[200] ;
extern int len_packet;
extern int usart_flag1;
extern int usart_flag2;
////////////////////////////////////////////////////////////////////////////////// 	 
//Èç¹ûÊ¹ÓÃucos,Ôò°üÀ¨ÏÂÃæµÄÍ·ÎÄ¼þ¼´¿É.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos Ê¹ÓÃ	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEK STM32¿ª·¢°å
//´®¿Ú1³õÊ¼»¯		   
//ÕýµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//ÐÞ¸ÄÈÕÆÚ:2012/8/18
//°æ±¾£ºV1.5
//°æÈ¨ËùÓÐ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3ÐÞ¸ÄËµÃ÷ 
//Ö§³ÖÊÊÓ¦²»Í¬ÆµÂÊÏÂµÄ´®¿Ú²¨ÌØÂÊÉèÖÃ.
//¼ÓÈëÁË¶ÔprintfµÄÖ§³Ö
//Ôö¼ÓÁË´®¿Ú½ÓÊÕÃüÁî¹¦ÄÜ.
//ÐÞÕýÁËprintfµÚÒ»¸ö×Ö·û¶ªÊ§µÄbug
//V1.4ÐÞ¸ÄËµÃ÷
//1,ÐÞ¸Ä´®¿Ú³õÊ¼»¯IOµÄbug
//2,ÐÞ¸ÄÁËUSART_RX_STA,Ê¹µÃ´®¿Ú×î´ó½ÓÊÕ×Ö½ÚÊýÎª2µÄ14´Î·½
//3,Ôö¼ÓÁËUSART_REC_LEN,ÓÃÓÚ¶¨Òå´®¿Ú×î´óÔÊÐí½ÓÊÕµÄ×Ö½ÚÊý(²»´óÓÚ2µÄ14´Î·½)
//4,ÐÞ¸ÄÁËEN_USART1_RXµÄÊ¹ÄÜ·½Ê½
//V1.5ÐÞ¸ÄËµÃ÷
//1,Ôö¼ÓÁË¶ÔUCOSIIµÄÖ§³Ö
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//¼ÓÈëÒÔÏÂ´úÂë,Ö§³Öprintfº¯Êý,¶ø²»ÐèÒªÑ¡Ôñuse MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//±ê×¼¿âÐèÒªµÄÖ§³Öº¯Êý                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//¶¨Òå_sys_exit()ÒÔ±ÜÃâÊ¹ÓÃ°ëÖ÷»úÄ£Ê½    
_sys_exit(int x) 
{ 
	x = x; 
} 
//ÖØ¶¨Òåfputcº¯Êý 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//Ñ­»··¢ËÍ,Ö±µ½·¢ËÍÍê±Ï   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*Ê¹ÓÃmicroLibµÄ·½·¨*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //Èç¹ûÊ¹ÄÜÁË½ÓÊÕ
//´®¿Ú1ÖÐ¶Ï·þÎñ³ÌÐò
//×¢Òâ,¶ÁÈ¡USARTx->SRÄÜ±ÜÃâÄªÃûÆäÃîµÄ´íÎó   	
u8 USART_RX_BUF[USART_REC_LEN];     //½ÓÊÕ»º³å,×î´óUSART_REC_LEN¸ö×Ö½Ú.
//½ÓÊÕ×´Ì¬
//bit15£¬	½ÓÊÕÍê³É±êÖ¾
//bit14£¬	½ÓÊÕµ½0x0d
//bit13~0£¬	½ÓÊÕµ½µÄÓÐÐ§×Ö½ÚÊýÄ¿
u16 USART_RX_STA=0;       //½ÓÊÕ×´Ì¬±ê¼Ç	  

//³õÊ¼»¯IO ´®¿Ú1 
//bound:²¨ÌØÂÊ
void uart_init(u32 bound){
    //GPIO¶Ë¿ÚÉèÖÃ
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//Ê¹ÄÜUSART1£¬GPIOAÊ±ÖÓ
 	USART_DeInit(USART1);  //¸´Î»´®¿Ú1
	 //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//¸´ÓÃÍÆÍìÊä³ö
    GPIO_Init(GPIOA, &GPIO_InitStructure); //³õÊ¼»¯PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//¸¡¿ÕÊäÈë
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //³õÊ¼»¯PA10

   //Usart1 NVIC ÅäÖÃ

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//ÇÀÕ¼ÓÅÏÈ¼¶3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//×ÓÓÅÏÈ¼¶3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQÍ¨µÀÊ¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);	//¸ù¾ÝÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯VIC¼Ä´æÆ÷
  
   //USART ³õÊ¼»¯ÉèÖÃ

	USART_InitStructure.USART_BaudRate = bound;//Ò»°ãÉèÖÃÎª9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//×Ö³¤Îª8Î»Êý¾Ý¸ñÊ½
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//Ò»¸öÍ£Ö¹Î»
	USART_InitStructure.USART_Parity = USART_Parity_No;//ÎÞÆæÅ¼Ð£ÑéÎ»
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//ÎÞÓ²¼þÊý¾ÝÁ÷¿ØÖÆ
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//ÊÕ·¢Ä£Ê½

    USART_Init(USART1, &USART_InitStructure); //³õÊ¼»¯´®¿Ú
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//¿ªÆôÖÐ¶Ï
    USART_Cmd(USART1, ENABLE);                    //Ê¹ÄÜ´®¿Ú 

}

void USART1_IRQHandler(void)                	//´®¿Ú1ÖÐ¶Ï·þÎñ³ÌÐò
	{
	u8 Res;
		u16 len;
		u16 t;

#ifdef OS_TICKS_PER_SEC	 	//Èç¹ûÊ±ÖÓ½ÚÅÄÊý¶¨ÒåÁË,ËµÃ÷ÒªÊ¹ÓÃucosIIÁË.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //½ÓÊÕÖÐ¶Ï(½ÓÊÕµ½µÄÊý¾Ý±ØÐëÊÇ0x0d 0x0a½áÎ²)
		{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//¶ÁÈ¡½ÓÊÕµ½µÄÊý¾Ý
		
		if((USART_RX_STA&0x8000)==0)//½ÓÊÕÎ´Íê³É
			{
			if(USART_RX_STA&0x4000)//½ÓÊÕµ½ÁË0x0d
				{
				if(Res!=0x0a)USART_RX_STA=0;//½ÓÊÕ´íÎó,ÖØÐÂ¿ªÊ¼
				else USART_RX_STA|=0x8000;	//½ÓÊÕÍê³ÉÁË 
				}
			else //»¹Ã»ÊÕµ½0X0D
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//½ÓÊÕÊý¾Ý´íÎó,ÖØÐÂ¿ªÊ¼½ÓÊÕ	  
					}		 
				}
			}   
				if (USART_RX_STA & 0x8000)//bit15??	?óê?íê3é±ê?? ?óê?íêá?????ò??óê?íêá?
			{
					len = USART_RX_STA & 0x3FFF;////?óê?×?·?3¤?è'ó13-0
					printf("usart_flag1::%d   and usart_flag2:: %d\n",usart_flag1,usart_flag2);
				 // printf("_usart_recv_packet1::%s   and usart_flag2:: %s\n",_usart_recv_packet1,_usart_recv_packet2);
				 
					printf("USART_RX_BUF::%s \n",USART_RX_BUF);
					
							//USART1->DR = USART_RX_BUF[t];
					if( usart_flag1==0){
						USART_ERR_NOMESSAGE=0;
						for (t = 0; t<len; t++){
							_usart_recv_packet1[t]=USART_RX_BUF[t];
							while ((USART1->SR & 0X40) == 0);
						}
						usart_flag1=1;
					}
					else if (	 usart_flag2==0&&usart_flag1==1){
						USART_ERR_NOMESSAGE=0;
						for (t = 0; t<len; t++){
							_usart_recv_packet2[t]=USART_RX_BUF[t];
							while ((USART1->SR & 0X40) == 0);
						}
						usart_flag2=1;	
						
						}
					
					printf("over\n");
					
				USART_RX_STA=0;

		}
			 	// _usart_recv_packet_len=sizeof(_usart_recv_packet_current);
			 
     } 
#ifdef OS_TICKS_PER_SEC	 	//Èç¹ûÊ±ÖÓ½ÚÅÄÊý¶¨ÒåÁË,ËµÃ÷ÒªÊ¹ÓÃucosIIÁË.
	OSIntExit();  											 
#endif
} 
#endif	

