/*
 * dlinkedlist.h
 *
 *  Created on: 2014年7月16日
 *      Author: Marvin 蒋子缘
 */
#ifndef DLINKEDLIST_H_
#define DLINKEDLIST_H_
typedef struct tagDbNode
{
unsigned char x;
unsigned char y;
struct tagDbNode * left;
struct tagDbNode * right;
} DbNode, * pdbNode;

pdbNode createNode(unsigned char m,unsigned char n);
pdbNode createList();
pdbNode insertNode(pdbNode h,pdbNode pnode);
pdbNode removeNode(pdbNode h);
unsigned char searchCollision(pdbNode h);
pdbNode deleteList(pdbNode h);
#endif 
