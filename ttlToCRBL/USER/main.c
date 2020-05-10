#include "stm32f10x.h"
#include "led.h"
#include	"sys.h"
#include "delay.h"
#include "iic.h"
#include "oled.h"
#include "key.h"
#include "usart.h"
#include "OLEDout.h"
#include "writer.h"
//**********************************¡¾Ö÷º¯Êı¡¿
int main(void)
{ 
	u8 key=0;	//ÓÃÓÚ½ÓÊÕ°´¼üÖµ
  
	delay_init();	//ÑÓÊ±º¯Êı³õÊ¼»¯
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //ÉèÖÃNVICÖĞ¶Ï·Ö×é2:2Î»ÇÀÕ¼ÓÅÏÈ¼¶£¬2Î»ÏìÓ¦ÓÅÏÈ¼¶
	led_init(); // LED³õÊ¼»¯£¬PA2µÄLED½ö¹©²âÊÔÊ¹ÓÃ£¬Óë³ÌĞòÎŞ¹Ø
//	M_Usart1_Init();
	//uart_init(9600);
	IIC_Init();   		//IIC³õÊ¼»¯
	OLED_Init();		//OLED³õÊ¼»¯ 
	KEY_Init();			// °´¼ü³õÊ¼»¯
	uart_init(9600);
	Start_out(); // Æô¶¯ºó£¬OLEDÏÔÊ¾Æô¶¯Íê±
  //X_axis_add(5);
	
	while(1) //ÎŞÏŞÉ¨Ãè°´¼ü
	{	
		key=KEY_Scan(0);	//µÃµ½¼üÖµ
	   	if(key)
		{						   
			switch(key)
			{				 
				case Xu:	
					led_shansuo();
					//PA2¿ÚLEDÉÁË¸£¬¹©²âÊÔÊ¹ÓÃ£¬×¢ÊÍ
				  X_axis_add(3);  //XÖáÕıÏò×ª¶¯Ò»²½¡
				  //delay_ms(300);
					Key_Xu(); //OLEDÏÔÊ¾´ËÊ±µÄ¶¯×÷£¬ÏÂÃæµÄKey_xx() º¯Êı¾ÍÊÇ´Ë×÷ÓÃ
					break;
				case Xd:	
					led_shansuo();
				  X_axis_add(-3);  //XÖá·´Ïò×ª¶¯Ò»²½
					//delay_ms(300);
				  Key_Xd();
					break;
				case Yu:	 
					led_shansuo();
				  Y_axis_add(3);   //YÖáÕıÏò
					//delay_ms(300);
				  Key_Yu();	
					break;
				case Yd:	
					led_shansuo();
				  Y_axis_add(-3);   //YÖá·´Ïò
					//delay_ms(300);
				  Key_Xu();;	
					break;
				case Zu:	
					led_shansuo();
				  Z_axis_add(3);     //ZÖáÕıÏò
					//delay_ms(300);
				  Key_Zu();	
					break;
				case Zd:	
					led_shansuo();
				  Z_axis_add(-3);      //ZÖá·´Ïò
				  //delay_ms(300);
					Key_Zd();	
					break;
				case Ci:	
					led_shansuo();
					//delay_ms(30);
				  round_draw(4);      //»­³öÒ»¸öËÄ²½³¤Îª°ë¾¶µÄÔ²
					//delay_ms(300);
				  Key_Ci();
					
					
					break;
			}
		}else delay_ms(10); 
	}
}
 
