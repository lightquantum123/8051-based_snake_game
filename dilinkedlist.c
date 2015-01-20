/*
 * dilinkedlist.c
 *
 *  Created on: 2014年7月16日
 *      Author: Marvin 蒋子缘
 */
#include <stdlib.h>
#include "dlinkedlist.h"
//创建结点
pdbNode createNode(unsigned char m,unsigned char n)
{
pdbNode pnode = (pdbNode)malloc(sizeof(DbNode));
pnode->x = m;
pnode->y = n;
pnode->left = pnode->right = pnode;    //创建新结点时，让其前驱和后继指针都指向自身

return pnode;
}

//=========================================================================
//创建链表
pdbNode createList() //参数给出表头结点数据 （表头结点不作为存放有意义数据的结点）
{
pdbNode pnode = (pdbNode)malloc(sizeof(DbNode));
pnode->x = 255;
pnode->y = 255;
pnode->left = pnode->right = pnode;

return pnode;
}

//插入新结点,总是在表头插入; 返回表头结点
pdbNode insertNode(pdbNode h,pdbNode pnode) // 参数1是链表的表头结点，参数2是要插入的结点（结点数据为data）
{
pdbNode ptmp = h->right;

// 从左到右恢复链接
h->right = pnode;
pnode->right = ptmp;

// 从右到左恢复链接
ptmp->left = pnode;
pnode->left = h;

return h;
}

pdbNode removeNode(pdbNode h)//从表尾移除节点
{
pdbNode ptmp = h->left;
h->left=ptmp->left;
ptmp->left->right=h;
ptmp->left=ptmp->right=ptmp;
return ptmp;
}

//检查是否有和第一个节点数据一样的节点，有则返回1，否则返回0
unsigned char searchCollision(pdbNode h) // 参数1是链表的表头结点
{
pdbNode pnode0 = h->right;
pdbNode pnode = h->right->right;
while (pnode!= h)
{
if((pnode->x==pnode0->x)&&(pnode->y==pnode0->y))break;
pnode = pnode->right;
}

if (pnode == h) return 0;
else
return 1;
}

//delete all nodes
pdbNode deleteList(pdbNode h)
{
pdbNode pnode=h->right;
pdbNode ptmp=h->right;
while(pnode!=h)
{
ptmp=pnode;
pnode=pnode->right;
free(ptmp);
}
h->right=h->left=h;
return h;
}



