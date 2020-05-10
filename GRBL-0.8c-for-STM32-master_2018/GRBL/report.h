/*
  report.h - reporting and messaging methods
  Part of Grbl

  The MIT License (MIT)

  GRBL(tm) - Embedded CNC g-code interpreter and motion-controller
  Copyright (c) 2012 Sungeun K. Jeon

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifndef report_h
#define report_h


// Define Grbl status codes.
#define STATUS_OK 0
#define STATUS_BAD_NUMBER_FORMAT 1//异常的数字格式
#define STATUS_EXPECTED_COMMAND_LETTER 2//预期的指令字符状态
#define STATUS_UNSUPPORTED_STATEMENT 3//不支持的声明
#define STATUS_ARC_RADIUS_ERROR 4//圆弧半径错误
#define STATUS_MODAL_GROUP_VIOLATION 5//模态组违反
#define STATUS_INVALID_STATEMENT 6//无效声明
#define STATUS_SETTING_DISABLED 7//设置无效
#define STATUS_SETTING_VALUE_NEG 8//否定的设定值
#define STATUS_SETTING_STEP_PULSE_MIN 9//设定最小的脉冲步数
#define STATUS_SETTING_READ_FAIL 10//查看失败
#define STATUS_IDLE_ERROR 11
#define STATUS_ALARM_LOCK 12//时钟锁定
#define STATUS_OVERFLOW 13

// 定义Grbl报警代码。小于0以区分报警错误和状态错误。
#define ALARM_HARD_LIMIT -1//限制器
#define ALARM_ABORT_CYCLE -2

// 定义Grbl反馈消息代码。
#define MESSAGE_CRITICAL_EVENT 1//紧急事件
#define MESSAGE_ALARM_LOCK 2//警报锁定
#define MESSAGE_ALARM_UNLOCK 3
#define MESSAGE_ENABLED 4
#define MESSAGE_DISABLED 5

// 打印系统状态信息。
void report_status_message(uint8_t status_code);

//打印系统报警信息。
void report_alarm_message(int8_t alarm_code);

//打印各种反馈信息。
void report_feedback_message(uint8_t message_code);

//打印初始消息
void report_init_message(void);

// 打印Grbl帮助和当前全局设置
void report_grbl_help(void);

//打印Grbl全局设置
void report_grbl_settings(void);

//打印实时状态报告
void report_realtime_status(void);

// 打印Grbl持续坐标参数
void report_gcode_parameters(void);

// 打印当前的g-code解析器模式状态
void report_gcode_modes(void);

// 打印启动线
void report_startup_line(uint8_t n, char *line);

#endif
