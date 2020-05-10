#ifndef _WRITER_H
#define _WRITER_H

#include "delay.h"
#include "sys.h"
#include "usart.h"

void X_axis_add(int l);
void Y_axis_add(int l);
void Z_axis_add(int l);

//void X_axis_sub(int l);
//void Y_axis_sub(int l);
//void Z_axis_sub(int l);

void round_draw(int r);
#endif

