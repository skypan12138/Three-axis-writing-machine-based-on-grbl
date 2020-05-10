/*
系列。c -通过串口发送和接收字节的低级函数
Grbl的一部分
g-code解释器和运动控制器
*/

//#include <avr/interrupt.h>
//#include "serial.h"
//#include "config.h"
//#include "motion_control.h"
//#include "protocol.h"

#include "include.h"

uint8_t rx_buffer[RX_BUFFER_SIZE];
uint8_t rx_buffer_head = 0;
volatile uint8_t rx_buffer_tail = 0;

uint8_t tx_buffer[TX_BUFFER_SIZE];
uint8_t tx_buffer_head = 0;
volatile uint8_t tx_buffer_tail = 0;

#ifdef ENABLE_XONXOFF
  volatile uint8_t flow_ctrl = XON_SENT; // 流控制状态变量
  
  // 返回RX缓冲区中的字节数。这将替换要防止的典型字节计数器
  // 中断和主程序从写入到计数器的同时。
static uint8_t get_rx_buffer_count()
  {
    if (rx_buffer_head == rx_buffer_tail) { return(0); }
    if (rx_buffer_head < rx_buffer_tail) { return(rx_buffer_tail-rx_buffer_head); }
    return (RX_BUFFER_SIZE - (rx_buffer_head-rx_buffer_tail));
  }
#endif

void serial_init()
{
//==========================================
//  // Set baud rate
//  #if BAUD_RATE < 57600
//    uint16_t UBRR0_value = ((F_CPU / (8L * BAUD_RATE)) - 1)/2 ;
//    UCSR0A &= ~(1 << U2X0); // baud doubler off  - Only needed on Uno XXX
//  #else
//    uint16_t UBRR0_value = ((F_CPU / (4L * BAUD_RATE)) - 1)/2;
//    UCSR0A |= (1 << U2X0);  // baud doubler on for high baud rates, i.e. 115200
//  #endif
//  UBRR0H = UBRR0_value >> 8;					 //设置波特率
//  UBRR0L = UBRR0_value;
//            
//  // enable rx and tx
//  UCSR0B |= 1<<RXEN0;							 //使能IO作为收发
//  UCSR0B |= 1<<TXEN0;
//	
//  // enable interrupt on complete reception of a byte
//  UCSR0B |= 1<<RXCIE0;						 //接收结束中断使能

/*--------已在串口初始化函数中定义---------*/
//==========================================
	  
  // defaults to 8-bit, no parity, 1 stop bit
}

//写函数
void serial_write(uint8_t data) {
  // Calculate next head
  uint8_t next_head = tx_buffer_head + 1;
  if (next_head == TX_BUFFER_SIZE) { next_head = 0; }

  // Wait until there is space in the buffer
  while (next_head == tx_buffer_tail) { 
    if (sys.execute & EXEC_RESET) { return; } // Only check for abort to avoid an endless loop.
  }

  // Store data and advance head
  tx_buffer[tx_buffer_head] = data;
  tx_buffer_head = next_head;
 //========================================== 
  // Enable Data Register Empty Interrupt to make sure tx-streaming is running
//  UCSR0B |=  (1 << UDRIE0);		   //使能串口发送完成中断后会立刻进入发送完成中断!!!!!
	USART_ITConfig(USART1,USART_IT_TXE, ENABLE);//开启发送中断并立刻进入发送中断
  //========================================== 
}


//读函数
uint8_t serial_read()
{
  uint8_t tail = rx_buffer_tail; // 临时rx_buffer_tail
  uint8_t data ;
  if (rx_buffer_head == tail) {
    return SERIAL_NO_DATA;
  } else {
    data = rx_buffer[tail];
    tail++;
    if (tail == RX_BUFFER_SIZE) { tail = 0; }
    rx_buffer_tail = tail;
    
    #ifdef ENABLE_XONXOFF
      if ((get_rx_buffer_count() < RX_BUFFER_LOW) && flow_ctrl == XOFF_SENT) { 
        flow_ctrl = SEND_XON;
        UCSR0B |=  (1 << UDRIE0); // Force TX
      }
    #endif
    
    return data;
  }
}

//串口缓存区重置
void serial_reset_read_buffer() 
{
  rx_buffer_tail = rx_buffer_head;

  #ifdef ENABLE_XONXOFF
    flow_ctrl = XON_SENT;
  #endif
}

//中断使能函数
//==========================================
void USART1_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART1 , USART_IT_RXNE)!=RESET)//接收到数据
	{
		//-----------------【接收中断】
		//==========================================
		uint8_t data=USART1->DR;				   //接收
		uint8_t next_head;
		//==========================================
//ISR(SERIAL_RX)
//{
//  
//  	uint8_t data = UDR0;
//  	uint8_t next_head;
  // 直接从串行流中选择运行时命令字符。这些字符是
  // 没有传递到缓冲区，但是这些设置系统的状态标志位用于运行时执行。
  switch (data) {
    case CMD_STATUS_REPORT: sys.execute |= EXEC_STATUS_REPORT; break; // Set as true
    case CMD_CYCLE_START:   sys.execute |= EXEC_CYCLE_START; break; // Set as true
    case CMD_FEED_HOLD:     sys.execute |= EXEC_FEED_HOLD; break; // Set as true
    case CMD_RESET:         mc_reset(); break; // Call motion control reset routine.
    default: // 写字符到缓存区			
      next_head = rx_buffer_head + 1;
      if (next_head == RX_BUFFER_SIZE) { next_head = 0; }
    
      // Write data to buffer unless it is full.
      if (next_head != rx_buffer_tail) {
        rx_buffer[rx_buffer_head] = data;
        rx_buffer_head = next_head;    
        
//        #ifdef ENABLE_XONXOFF
//          if ((get_rx_buffer_count() >= RX_BUFFER_FULL) && flow_ctrl == XON_SENT) {
//            flow_ctrl = SEND_XOFF;
//            UCSR0B |=  (1 << UDRIE0); // Force TX
//          } 
//        #endif

      }
  }
//}
//--------------------------
	}
	if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET) 	//写数据寄存器空，可以写数据
	{
		//-----------------【BUFF空中断】
//		// Data Register Empty Interrupt handler
//		ISR(SERIAL_UDRE)
//		{
		  // Temporary tx_buffer_tail (to optimize for volatile)
		  uint8_t tail = tx_buffer_tail;
		  
		  #ifdef ENABLE_XONXOFF
		    if (flow_ctrl == SEND_XOFF) { 
		      UDR0 = XOFF_CHAR; 
		      flow_ctrl = XOFF_SENT; 
		    } else if (flow_ctrl == SEND_XON) { 
		      UDR0 = XON_CHAR; 
		      flow_ctrl = XON_SENT; 
		    } else
		  #endif
		  { 
		    // Send a byte from the buffer
		   //==========================================

		    USART1->DR= tx_buffer[tail];  //发送
		   //==========================================
		    // Update tail position
		    tail++;
		    if (tail == TX_BUFFER_SIZE) { tail = 0; }
		  
		    tx_buffer_tail = tail;
		  }
		  
		  // Turn off Data Register Empty Interrupt to stop tx-streaming if this concludes the transfer
		  if (tail == tx_buffer_head) {
		  //==========================================
//		   UCSR0B &= ~(1 << UDRIE0);						//如果输出到对首，关闭TXE中断
		   USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		   //==========================================
		  }
	}
}


//==========================================

