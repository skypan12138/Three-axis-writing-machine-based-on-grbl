#ifndef OLEDOUT_H
#define	OLEDOUT_H

void Start_out(void); //系统启动后发送字符

void Key_Xu(void); //X轴正向移动发送字符

void Key_Xd(void); // X轴负向移动发送字符

void Key_Yu(void);	//Y轴正向移动发送字符

void Key_Yd(void); //Y轴负向移动发送字符

void Key_Zu(void); // Z轴正向移动发送子

void Key_Zd(void);	//Z轴负向移动发送字符

void Key_Ci(void);	// 画圆时发送的字符
#endif

