/*******************************************************************************
 * STC8A8K63S412A 第一个程序                                                   *
 *******************************************************************************
 * 作者：		信念D力量													   *
 * 网站：		https://zsf90.github.io										   *
 * Git: 	   https://www.github.com/zsf90 								   *
 * 哔哩哔哩: 	https://space.bilibili.com/334715750						   *
 * 创建日期：	2021-7-13													   *
 * 更新日期：	2021-7-13													   *
 *******************************************************************************
 *******************************************************************************
*/

#include "public.h"
#include <intrins.h>
#include "stdio.h"
#include "led.h"
#include "key.h"
#include "uart.h"
#include "delay.h"


uint32_t num = 0;
float temp = 2.65f;

// 时钟初始化
void SystemClkInit()
{
	P_SW2 = 0x80;
	CKSEL = 0x00;   // 主时钟选择
	CLKDIV = 0x00;  // 
	P_SW2 = 0x00;
}

// GPIO 初始化函数
void GPIO_Init()
{
	/* 配置P0 */
	P0M0 = 0x01;
	P0M1 = 0x00;
    
    /* 串口1 GPIO 配置P3.1 配置为强推挽输出 */
    P3M0 = 0x02; /* 0000 0010 */
    P3M1 = 0x00;    
    
}


int main(void)
{
	SystemClkInit();    /* 系统时钟初始化 */
	GPIO_Init();	    /* GPIO初始化 */
	key_init();		    /* 按键初始化 */
    UartInit();         /* 串口初始化 */
    
	
	while(1)
	{
        UartReceiveHandle();
        
        if(key_up_over == 1)
        {
            num++;
            temp += 0.1;
            printf("num: %ld\r\n", num);
            printf("当前温度为: %.2f\r\n", temp);
            key_up_over = 0;
        }
        
        if(key_down_over == 1)
        {
            num--;
            temp -= 0.1;
            printf("num: %ld\r\n", num);
            printf("当前温度为: %.2f\r\n", temp);
            key_down_over = 0;
        }
	}
}
