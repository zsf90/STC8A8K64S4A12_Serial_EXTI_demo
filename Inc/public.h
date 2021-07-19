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
#ifndef _PUBLIC_H
#define _PUBLIC_H
#include "stc8.h"

sbit led = P0^0;

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

#endif