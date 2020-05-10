#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
 
#define KEY13  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13) // 读取各个按键的状态
#define KEY12  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
#define KEY11  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)
#define KEY10 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)
#define KEY14  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)
#define KEY15 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)
#define KEY9 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)

 

#define Yd 	4	 //相应按键的按键码
#define Yu	3	
#define Xd	2	
#define Xu  1	
#define Zd	6	
#define Zu  5	
#define Ci  7	

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif
