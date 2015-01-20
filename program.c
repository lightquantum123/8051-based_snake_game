/*
 * program.c
 *
 *  Created on: 2014年7月16日
 *      Author: Marvin 蒋子缘
 */
/*头文件*/
#include <STC12C5A60S2.h> 
#include <stdlib.h>
#include <intrins.h>
#include "dlinkedlist.h"
#include "snake.h"    
#define uint unsigned int
#define uchar unsigned char
#define _Nop() _nop_()

/*端口定义*/
sbit D_port = P0^7;
sbit C_port = P0^6;
sbit B_port = P0^5;
sbit A_port = P0^4;
sbit G_port = P0^3;
sbit DI_port = P0^2;
sbit CLK_port = P0^1;
sbit Latch_port = P0^0;
sbit P10=P1^0;
sbit P20=P2^0;
sbit P21=P2^1;
sbit P22=P2^2;
sbit P23=P2^3;
sbit P24=P2^4;
sbit P25=P2^5;

unsigned char xdata malloc_mempool [0x200];

static uchar infrared0=0;
static uchar infrared=0;
static uchar photoSR0=0;
static uchar photoSR=0;
static uchar upButton0=1;
static uchar upButton=1;
static uchar downButton0=1;
static uchar downButton=1;
static uchar leftButton0=1;
static uchar leftButton=1;
static uchar rightButton0=1;
static uchar rightButton=1;
/*-------------------------------------------------------
    点阵LED第几行显示数据
   其中daH为数据高8位，daL为数据低8位，han为第几行显示
--------------------------------------------------------*/
void data_Send(uchar daH,uchar daL,uchar line)
{//发送至led显示屏的函数	
	uchar i;
	Latch_port = 0;  /*HC595锁定输出,避免数据传输过程中，屏数据变化从而显示闪烁*/
	CLK_port = 0;
	for(i=0;i<8;i++){
		if((daH&0x80)==0) DI_port = 1;	/*阴码*/
		else DI_port = 0;
		CLK_port = 1;
		CLK_port = 0;
		daH <<= 1;
		}
	for(i=0;i<8;i++){
		if((daL&0x80)==0) DI_port = 1;
		else DI_port = 0;
		CLK_port = 1;
		CLK_port = 0;
		daL <<= 1;
		}
	G_port = 1; /*关屏显示，原理为使HC138输出全为1，从而三极管截止，点阵不显示*/
	switch (line){
		case 0: 
			A_port = 0;	B_port = 0;	C_port = 0;	D_port = 0;
			break;
		case 1:
			A_port = 1;	B_port = 0;	C_port = 0;	D_port = 0;
			break;
		case 2:
			A_port = 0;	B_port = 1;	C_port = 0;	D_port = 0;
			break;
		case 3: 
			A_port = 1;	B_port = 1;	C_port = 0;	D_port = 0;
			break;
		case 4: 
			A_port = 0;	B_port = 0;	C_port = 1;	D_port = 0;
			break;
		case 5: 
			A_port = 1;	B_port = 0;	C_port = 1;	D_port = 0;
			break;
		case 6: 
			A_port = 0;	B_port = 1;	C_port = 1;	D_port = 0;
			break;
		case 7: 
			A_port = 1;	B_port = 1;	C_port = 1;	D_port = 0;
			break;
		case 8: 
			A_port = 0;	B_port = 0;	C_port = 0;	D_port = 1;
			break;
		case 9: 
			A_port = 1;	B_port = 0;	C_port = 0;	D_port = 1;
			break;
		case 10: 
			A_port = 0;	B_port = 1;	C_port = 0;	D_port = 1;
			break;
		case 11: 
			A_port = 1;	B_port = 1;	C_port = 0;	D_port = 1;
			break;
		case 12: 
			A_port = 0;	B_port = 0;	C_port = 1;	D_port = 1;
			break;
		case 13: 
			A_port = 1;	B_port = 0;	C_port = 1;	D_port = 1;
			break;
		case 14: 
			A_port = 0;	B_port = 1;	C_port = 1;	D_port = 1;
			break;
		case 15: 
			A_port = 1;	B_port = 1;	C_port = 1;	D_port = 1;
			break;
		}
	Latch_port = 1; /*允许HC595数据输出到Q1-Q8端口*/
	G_port = 0; /*HC138输出有效，打开显示*/
	Latch_port = 0;	/*锁定HC595数据输出*/

}

void testLED()
{
  uint i=0;
  uchar j=0;
  for(j=0;j<16;++j)
  for(i=0;i<2000;++i)
  {
   	 data_Send(0xff,0xff,j);
  }
  G_port = 1;
}

void testReverseLED()
{
  uint i=0;
  uchar j=0;
  for(j=15;j>=0;--j)
  for(i=0;i<2000;++i)
  {
   	 data_Send(0xff,0xff,j);
  }
  G_port = 1;
}

void wordLED()
{ //显示字的函数，暂且不用管 
uchar code table[][32]={
{0x00,0x00,0x30,0x03,0x10,0x01,0x98,0x01,0x88,0x7F,0xCC,0x02,0x6C,0x02,0x0A,0x3E,
0x0A,0x02,0x08,0x02,0x08,0x02,0x08,0x7E,0x08,0x02,0x08,0x02,0x08,0x02,0x08,0x02},/*"作",0*/

{0x00,0x00,0x80,0x00,0x80,0x00,0xF8,0x37,0x80,0x18,0x80,0x0C,0xFE,0x7F,0x00,0x01,
0xC0,0x00,0xF0,0x1F,0x3C,0x10,0xF6,0x1F,0x30,0x10,0x30,0x10,0xF0,0x1F,0x30,0x10},/*"者",1*/

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x18,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x18,0x00,0x00,0x00,0x00,0x00},/*"：",2*/

{0x00,0x00,0x20,0x04,0xFE,0x7F,0x20,0x04,0x20,0x05,0x90,0x3F,0xD2,0x10,0x74,0x0B,
0x1C,0x06,0x90,0x13,0x58,0x7F,0x9C,0x10,0x16,0x11,0x12,0x11,0x10,0x1C,0x00,0x00},/*"蒋",3*/

{0x00,0x00,0x00,0x00,0xFC,0x3F,0x00,0x1C,0x00,0x06,0x80,0x01,0x80,0x01,0xFE,0x7F,
0xFE,0x1F,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0xE0,0x00,0x00,0x00},/*"子",4*/

{0x00,0x00,0x08,0x03,0x0C,0x1F,0x04,0x11,0xB4,0x1C,0x92,0x0B,0xEE,0x7F,0x28,0x02,
0x84,0x33,0xC6,0x1E,0x1E,0x1D,0xE0,0x2C,0x50,0x2B,0x9E,0x49,0x60,0x0E,0x00,0x02},/*"缘",5*/

};	 
	uint i;
	uchar j=0; /*读取对应的第几行数据*/
	uchar k=0; /*读取对应的第几个字数据*/
	uchar br=0;
	for(k=0;k<6;++k)
	{
	if(br==0)
	    for(i=0;i<2000;++i)
	    {	
		if(br==0)
	        for(j=0;j<16;++j)
			{  
			    if(infrared!=0)
                data_Send(table[k][j*2+1],table[k][j*2],j);
				else
				{
				br=1;
				break;
				}
			}
		else
		break;
      	}
	else
	break;
    }
G_port = 1;
}					   

void snakeLED()
{
//贪食蛇的函数
    uchar *table;
	uint i;
	uchar j=0; /*读取对应的第几行数据*/
	uchar br=0;
	uchar direction=0;
	uchar playing=1;
	testLED();
	initializeGame();
  while(playing&&infrared==0)
  {
	//decide direction
	if(upButton==0)
	playing=move(0);
	else if(downButton==0)
	playing=move(1);
	else if(leftButton==0)
	playing=move(2);
	else if(rightButton==0)
	playing=move(3);
	else 
	playing=move(currentDir());

	table=displayArray();
	for(i=0;i<1000;++i)
	{	
	for(j=0;j<16;++j)
	{  
      data_Send(table[j*2+1],table[j*2],j);
	}
	}
	free(table);
	table=NULL;
  }

	endGame();
G_port = 1;
}

void sense() interrupt 1 using 1
{
//检查红外接收器和各个按键，两次采样结果相同才被采纳。
infrared=infrared0&&P24;
photoSR=photoSR0&&P10;
upButton=P23||upButton0;
downButton=P22||downButton0;
leftButton=P21||leftButton0;
rightButton=P20||rightButton0;
infrared0=P24;
photoSR0=P10;
upButton0=P23;
downButton0=P22;
leftButton0=P21;
rightButton0=P20;
TH0=(65536-25000)/256; 
TL0=(65536-25000)%256;
}

void send() interrupt 3 using 2
{
//红外发射器信号
P25=!P25;
}

int main()
{ 
init_mempool (&malloc_mempool, sizeof(malloc_mempool));
//testLED();
//testReverse();
infrared0=0;
infrared=0;
photoSR0=0;
photoSR=0;
upButton0=1;
upButton=1;
downButton0=1;
downButton=1;
leftButton0=1;
leftButton=1;
rightButton0=1;
rightButton=1;

TMOD=0x21;      //设置定时器0位工作模式1（M1,M0位0，1）
TH0=(65536-50000)/256; 
TL0=(65536-50000)%256;
TH1=256-33; 
TL1=256-33;
ET1=1;
TR1=1;
EA=1;    //开总中断
ET0=1;   //开定时器0中断
TR0=1;   //启动定时器0
P24=1;
P10=1;
//testLED();
//testReverseLED();
while(1)
{
if(infrared!=0)
wordLED();
else
snakeLED();
}  
}