/*
 * dilinkedlist.c
 *
 *  Created on: 2014��7��16��
 *      Author: Marvin ����Ե
 */
#include <stdlib.h>
#include "dlinkedlist.h"
//�������
pdbNode createNode(unsigned char m,unsigned char n)
{
pdbNode pnode = (pdbNode)malloc(sizeof(DbNode));
pnode->x = m;
pnode->y = n;
pnode->left = pnode->right = pnode;    //�����½��ʱ������ǰ���ͺ��ָ�붼ָ������

return pnode;
}

//=========================================================================
//��������
pdbNode createList() //����������ͷ������� ����ͷ��㲻��Ϊ������������ݵĽ�㣩
{
pdbNode pnode = (pdbNode)malloc(sizeof(DbNode));
pnode->x = 255;
pnode->y = 255;
pnode->left = pnode->right = pnode;

return pnode;
}

//�����½��,�����ڱ�ͷ����; ���ر�ͷ���
pdbNode insertNode(pdbNode h,pdbNode pnode) // ����1������ı�ͷ��㣬����2��Ҫ����Ľ�㣨�������Ϊdata��
{
pdbNode ptmp = h->right;

// �����һָ�����
h->right = pnode;
pnode->right = ptmp;

// ���ҵ���ָ�����
ptmp->left = pnode;
pnode->left = h;

return h;
}

pdbNode removeNode(pdbNode h)//�ӱ�β�Ƴ��ڵ�
{
pdbNode ptmp = h->left;
h->left=ptmp->left;
ptmp->left->right=h;
ptmp->left=ptmp->right=ptmp;
return ptmp;
}

//����Ƿ��к͵�һ���ڵ�����һ���Ľڵ㣬���򷵻�1�����򷵻�0
unsigned char searchCollision(pdbNode h) // ����1������ı�ͷ���
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



