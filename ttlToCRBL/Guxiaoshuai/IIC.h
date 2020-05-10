#ifndef IIC_H
#define IIC_H
#include "sys.h"

// IO操作
#define IIC_SCL PBout(6) // 宏定义时钟总线于PB6
#define IIC_SDA PBout(7) // 宏定义数据总线于PB7
#define READ_SDA PBin(7) //宏定义输入数据总线于PB7


// 操作函数
void IIC_Init(void); // 初始化IIC
void IIC_Start(void); // 开始信号函数
void IIC_Stop(void); // 结束信号函数
void IIC_Ask(void); // 发送应答信号
void IIC_Nask(void); // 不发送应答信号
void Send_Byte(u8 ByteData); //发送一个字节
u8 Read_Byte(unsigned char ack); // 读字节
u8 Wait_Ask(void); //读应答信号
void SDA_Out(void); // SDA输出
void SDA_In(void); // SDA输入
#endif

