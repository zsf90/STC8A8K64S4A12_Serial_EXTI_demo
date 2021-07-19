#include "public.h"
#include "uart.h"
#include "led.h"
#include <STC8.h>
#include <string.h>
#include <stdio.h>


#define FOSC    24000000UL      // 系统工作频率
#define BAUDRATE   115200         // 串口波特率设定
#define BRT     (65536 - FOSC / BAUDRATE / 4)

bit busy = 0; // 忙碌标志
bit rx_over = 0;
uint8_t rx_cnt = 0;
uint8_t rx_index = 0;
char rx_buffer[16];
char rx_data[16];

/*
 * 串口1中断服务函数 
 * 
*/
void UartIsr() interrupt 4
{
    /* TI 为1，则为串口发送中断标志位 */
    if(TI)
    {
        TI = 0;     /* 清除发送中断标志位 */
        busy = 0;   /* 一个字节数据发送完成后，复位忙标志 */
    }
    
    /* 串口接收标志位 */
    if(RI)
    {
        /* 来到这里代表已经接收到了一个字节的数据，可以从SBUF取数据了 */
        char ch = SBUF;
        if(ch != '#')
        {
            rx_buffer[rx_cnt++] = ch; /* 把接收到的单个字节数据存储到 rx_buffer */
        }
        else
        {
            for(rx_index=0; rx_index<rx_cnt; rx_index++)
            {
                rx_data[rx_index] = rx_buffer[rx_index];
            }
            rx_over = 1;
            rx_cnt = 0;
        }
        RI = 0;
    }
}

/*
 * 串口初始化函数
*/
void UartInit(void)
{
	SCON = 0x50;		/* 8位数据,可变波特率 0101 0000 允许串口接收数据 */
    AUXR |= 0x15;       /* 0x15=0001 0101，用定时器2作为波特率发生器 */
	T2L = BRT;          /* 定时器2 重载值低字节 */
    T2H = BRT >> 8;     /* 定时器2 重载值低字节 */
    busy = 0;           /* 标志位初始化为 0 */
    ES = 1;             /* 使能串口中断 */
    EA = 1;             /* 使能总中断 */
}

/*
 * 发送一个字节数据到串口
*/
void UartSend(char dat)
{
    while(busy);    /* 如果 busy 为1，则一直循环 */
    busy = 1;       /* 置位忙标志 */
    SBUF = dat;     /* 把要发送的数据送给 SBUF */
}

/*
 * 发送字符串到串口
*/
void UartSendStr(char *p)
{
    while(*p)
    {
        UartSend(*p++);
    }
}

void UartReceiveHandle()
{
    /* 接收完成 */
    if(rx_over == 1)
    {
        if(strstr(rx_data, "LED_ON") != NULL)
        {
            led = 0;
        }
        
        if(strstr(rx_data, "LED_OFF") != NULL)
        {
            led = 1;
        }
        rx_over = 0; /* 清除接收完成标志位 */
    }
}

/* 重写putchar函数 */
char putchar(char c)
{
    UartSend(c);
    return c;
}