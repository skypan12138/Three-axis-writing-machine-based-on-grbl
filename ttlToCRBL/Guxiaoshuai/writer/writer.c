#include"writer.h"



void X_axis_add(int l)
{
//	 printf("G91\r\n");
	 printf("G01 X%d F260\r\n",l);
}

void Y_axis_add(int l)
{
	printf("G01 Y%d F260\r\n",l);
}
void Z_axis_add(int l)
{
	printf("G01 Z%d F260\r\n",l);
}

//void X_axis_sub(int l)
//{
//	printf("G01 X-1 F260\r\n");
//}
//void Y_axis_sub(int l)
//{
//	printf("G01 Y-3 F260\r\n");
//}
//void Z_axis_sub(int l)
//{
//	printf("G01 Z-1 F260\r\n");
//}
//						
void round_draw(int r)
{
	printf("G02 X0 Y0 I%d J%d F260\r\n",r,r);
}
