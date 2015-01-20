/*
 * dlinkedlist.h
 *
 *  Created on: 2014��7��16��
 *      Author: Marvin ����Ե
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
