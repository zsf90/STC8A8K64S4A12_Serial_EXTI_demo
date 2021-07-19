/*******************************************************************************
 * 外部中断按键程序例子														   *
 *******************************************************************************
 * 作者：		信念D力量													   *
 * 网站：		https://zsf90.github.io										   *
 * Git: 		https://www.github.com/zsf90 								   *
 * 哔哩哔哩: 	https://space.bilibili.com/334715750						   *
 * 创建日期：	2021-7-13													   *
 * 更新日期：	2021-7-13													   *
 *******************************************************************************
 * INT0 -> P3.2																   *
 * INT1 -> P3.3																   *
 * INT2 -> P3.6																   *
 *******************************************************************************
*/
#include "public.h"
#include "key.h"
#include "delay.h"
#include "uart.h"
#include <stdio.h>

extern uint32_t num;


bit key_up_over = 0;   /* 按钮下降沿触发标志位 */
bit key_down_over = 0;   /* 按钮下降沿触发标志位 */

void key_init()
{
	EA = 1;		// 总中断使能
	EX0 = 1;	// 外部中断0使能
	IT0 = 1;	// 外部中断0下降沿触发
    EX1 = 1;
    IT1 = 1;
}

/*
外部中断服务程序
******************
interrupt 0	外部中断0
interrupt 1 定时器中断0
interrupt 2 外部中断1
interrupt 3 定时器中断1
interrupt 4 串口中断
*/
void isr_key_up(void) interrupt 0
{
    key_up_over = 1;
}

/*
外部中断服务程序
******************
interrupt 0	外部中断0
interrupt 1 定时器中断0
interrupt 2 外部中断1
interrupt 3 定时器中断1
interrupt 4 串口中断
*/
void isr_key_down(void) interrupt 2
{
    key_down_over = 1;
}