/*
 * snake.c
 *
 *  Created on: 2014年7月16日
 *      Author: Marvin 蒋子缘
 */
#include "dlinkedlist.h"
#include "snake.h"
#include<stdlib.h>

static unsigned char food[2]={1,1};
static pdbNode head=NULL;
void initializeGame()
{
//游戏初始化
food[0]=1;
food[1]=1;
head=createList();
insertNode(head,createNode(6,6));
insertNode(head,createNode(7,6));
}

void endGame()
{
free(deleteList(head));
}

unsigned char validateCoordinate(char x)
{
//修正坐标，使能从上边转至下边
if(x>=0)
{
return x%16;
}else
{
return x%16+16;
}
}

unsigned char currentDir()
{
//返回当前行进方向
//0 up，1 down ，2 left，3 right
pdbNode first=head->right;
pdbNode second=first->right;
char diffX=(char)(first->x)-second->x;
char diffY=(char)(first->y)-second->y;
if(diffY<0)
{
 if(diffY==-1)
  return 0;
 else
  return 1;
}
if(diffY>0)
{
 if(diffY==1)
  return 1;
 else
  return 0;
}
if(diffX<0)
{
 if(diffX==-1)
  return 2;
 else
  return 3;
}
if(diffX>0)
{
 if(diffX==1)
  return 3;
 else
  return 2;
}
}

unsigned char move(unsigned char dir)
{
//移动蛇的函数
unsigned char preDir=currentDir();
pdbNode first=head->right;
pdbNode second=first->right;
pdbNode temp=createNode(255,255);
insertNode(head,temp);
//0 up，1 down ，2 left，3 right
switch(dir)
{
case 0:
  if(preDir!=1)
  {
  temp->x=first->x;
  temp->y=validateCoordinate(-1+first->y);
  }else{
    temp->x=first->x;
    temp->y=validateCoordinate(first->y+1);
  }
break;
case 1:
  if(preDir!=0)
  {
  temp->x=first->x;
  temp->y=validateCoordinate(first->y+1);
  }else
  {
  temp->x=first->x;
  temp->y=validateCoordinate(-1+first->y);
  }
break;
case 2:
  if(preDir!=3)
  {
  temp->x=validateCoordinate(-1+first->x);
  temp->y=first->y;
  }else
  {
  temp->x=validateCoordinate(first->x+1);
  temp->y=first->y;
  }
break;
case 3:
  if(preDir!=2)
  {
  temp->x=validateCoordinate(first->x+1);
  temp->y=first->y;
  }else
  {
  temp->x=validateCoordinate(-1+first->x);
  temp->y=first->y;
  }
break;
}

//checking collision with the food. If not, delete the last node.
if(temp->x!=food[0]||temp->y!=food[1])
{
free(removeNode(head));
}else
{
	food[0]=rand()%16;
	food[1]=rand()%16;
}

//checking collision with itself to tell the main program if the game end.
if(searchCollision(head))
  return 0;
else
  return 1;
}

unsigned char* displayArray()
{
//返回可供显示的数组
pdbNode iterator=head->right;
unsigned char i=0;
unsigned char* display=NULL;
unsigned char m,n,temp;
display=(unsigned char*)malloc(32*sizeof(unsigned char));
for(i=0;i<32;++i)
{
  display[i]=0;
}

for(iterator=head->right;(iterator->x!=255);iterator=iterator->right)
{
  m=iterator->x;
  n=iterator->y;
  if(m<8)
  {
  temp=1;
  temp=temp<<m;
  display[n*2]=temp|display[n*2];
  //printf("%x",display[n*2]);
  }else
  {
  temp=1;
  temp=temp<<(m%8);
  display[n*2+1]=temp|display[n*2+1];
  //printf("%x",display[n*2+1]);
  }
}
  m=food[0];
  n=food[1];
  if(m<8)
  {
  temp=1;
  temp=temp<<m;
  display[n*2]=temp|display[n*2];
  }else
  {
  temp=1;
  temp=temp<<(m%8);
  display[n*2+1]=temp|display[n*2+1];
  }

return display;
}

