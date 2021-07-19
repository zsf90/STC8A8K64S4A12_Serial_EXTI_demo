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
#include "delay.h"
#include "led.h"

void led_toggle(uint32_t ms)
{
	DelayMs(ms);
	led = ~led;
}