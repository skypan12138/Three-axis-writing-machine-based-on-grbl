#include "iic.h"
#include "delay.h"
/*********************************************
函数功能 初始化IIC
*********************************************/
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	IIC_SCL=1;
	IIC_SDA=1;
}

/**********************************************
函数功能 SDA输出
****************************************/
void SDA_Out(void)
{
	GPIO_InitTypeDef GPIO_InitStructer;
    GPIO_InitStructer.GPIO_Pin= GPIO_Pin_7;
    GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructer.GPIO_Mode=GPIO_Mode_Out_PP; //推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructer);
}
/*******************************
函数功能 SDA输入
***************************************/

void SDA_In(void)
{
	GPIO_InitTypeDef GPIO_InitStructer;
    GPIO_InitStructer.GPIO_Pin= GPIO_Pin_7;
    GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructer.GPIO_Mode=GPIO_Mode_IPU; //上拉输入
    GPIO_Init(GPIOB, &GPIO_InitStructer);
}

/*******************************************
函数功能 发出IIC开始信号
****************************************/
void IIC_Start(void)
{
	SDA_Out();     
	IIC_SDA=1;	//  SDA拉高，为下降沿做准备	  
	IIC_SCL=1; 	// SCL高电平
	delay_us(4);
 	IIC_SDA=0; // 产生一个下降沿，即发出开始信号
	delay_us(4);
	IIC_SCL=0; //拉低SCL，为数据修改做准备
}

/********************************************
函数功能 发出IIC结束信号
******************************************/
void IIC_Stop(void)
{
	SDA_Out();
	IIC_SCL = 0;
	IIC_SDA = 0; // 拉低SDA，为上升沿做准备
	delay_us(5);
	IIC_SCL = 1;
	IIC_SDA = 1; // 产生一个上升沿，即发出结束信号
	delay_us(5);
}

/*****************************************
函数功能 产生应答信号
**********************************************/
void IIC_Ask(void)
{
	IIC_SCL=0;
	SDA_Out();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}

/****************************************
函数功能 不产生应答信号
****************************************/
void IIC_Nask(void)
{
	IIC_SCL=0;
	SDA_Out();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}

/**************************************
函数功能 读取应答信号,返回1表示应答，并发送结束信号，否则返回0
***********************************/
u8 Wait_Ask(void)
{
	u8 ucErrTime=0;
	SDA_In();       
	IIC_SDA=1;
	delay_us(1);	   
	IIC_SCL=1;
	delay_us(1);	 
	while(READ_SDA) // SDA被拉低则表明应答
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0; 
}

/****************************************
函数功能 发送一个字节
***********************************/
void  Send_Byte(u8 ByteData)
{
	u8 i;   
	SDA_Out(); 	    
    IIC_SCL=0;//拉低时钟为数据传输做准备
    for(i=0;i<8;i++)
    {              
        IIC_SDA=(ByteData&0x80)>>7; // 高位在前，低位在后
        ByteData<<=1; 	  
		delay_us(2);   
		IIC_SCL=1; // 拉高SCL，开始传输
		delay_us(2); 
		IIC_SCL=0;	//拉低时钟为下次数据传输做准备
		delay_us(2);
    }	 
}

/*****************************************
函数功能 读一个字节
*************************************/
u8 Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_In();
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_Nask();//发送nACK
    else
        IIC_Ask(); //发送ACK   
    return receive;
}



