#include "OLEDout.h"
#include "oled.h"
#include "sys.h"
u8 w =0;
void Start_out() 
{		OLED_Clear();
		for(w=0;w<4;w++)
	{		
		OLED_ShowHz(16+16*w,0,w,1,2); 
	}
	for(w=0;w<5;w++)
	{
	
		OLED_ShowHz(16+16*w,24,w,1,3); 
	}
		OLED_Refresh_Gram();					
}

void Key_Xu()
{
	OLED_Clear();
	for(w=0;w<6;w++)
	{
		OLED_ShowHz(16+16*w,24,w,1,4); 
		
	}
	OLED_Refresh_Gram();	
}
void Key_Xd()
{
	OLED_Clear();
	for(w=0;w<6;w++)
	{
		OLED_ShowHz(16+16*w,24,w,1,5);
}
	OLED_Refresh_Gram();	
}
void Key_Yu()
{
	OLED_Clear();
	for(w=0;w<6;w++)
	{
		OLED_ShowHz(16+16*w,24,w,1,6); 
		
	}
	OLED_Refresh_Gram();	
}
void Key_Yd()
{
	OLED_Clear();
	for(w=0;w<6;w++)
	{
		OLED_ShowHz(16+16*w,24,w,1,7);
}
	OLED_Refresh_Gram();	
}
void Key_Zu()
{
	OLED_Clear();
	for(w=0;w<6;w++)
	{
		OLED_ShowHz(16+16*w,24,w,1,8); 
		
	}
	OLED_Refresh_Gram();	
}
void Key_Zd()
{
	OLED_Clear();
	for(w=0;w<6;w++)
	{
		OLED_ShowHz(16+16*w,24,w,1,9);
}
	OLED_Refresh_Gram();	
}
void Key_Ci()
{
	OLED_Clear();
	for(w=0;w<6;w++)
	{
		OLED_ShowHz(16+16*w,24,w,1,10);
}
	OLED_Refresh_Gram();	
}
