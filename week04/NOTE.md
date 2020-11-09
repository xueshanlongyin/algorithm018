学习笔记
#include "stdafx.h"
#include"stdio.h"
#include"malloc.h"
#define NULL 0
#define OK  0
#define ERR 1
/*
结点*p的存储位置既存放在其前趋结点*(p—>prior)的直接后继指针域中，
也存放 在它的后继结点*(p—>next)的直接前趋指针域中
操作双向链表时一定要记住原来的前后关系一定要改变
与单链表的插入和删除操作不同的是,在双链表中插入和删除必须同时修改两个方向上的指针*/
typedef struct dlistnode
{
      int data;
      struct dlistnode *prior;
      struct dlistnode *next;
      
}dlinklist;

//typedef dlistnode * dlinklist;
dlinklist *head;

void PrintListData(dlinklist *head);
int ListLength(dlinklist* head);

/* 产生空的双向循环链表*/
dlinklist * InitList( )
{ 
	dlinklist *pHead = NULL;

	pHead = (dlinklist *)malloc(sizeof(dlinklist));
    
	/**/
	if(NULL == pHead)
	{
		printf("Init List Error \n");

		return NULL;

	}

    /* 头结点的两个指针域均指向NULL,头结点中存放数据 */
	pHead->next  = NULL;
    pHead->data  = 0; /*头结点的数据*/
	pHead->prior = NULL;

	return pHead;

}


/*从双向链表的头插入(前插)，且节点的值为x*/
dlinklist * insertbeforeHead(dlinklist *pHead, int x)
{
	 dlinklist *pNew = NULL;
    
	 pNew = (dlinklist*)malloc(sizeof(dlinklist));

	 if (NULL == pNew)
	 {
		 return NULL;
	 }
	 pNew->data = x;

	 if (NULL == pHead)/*初次插入*/
	 {
		 
		 pNew->next = NULL;
		 pNew->prior  = NULL;
		 pHead = pNew;
		 printf("\r\n Init insert link");
	 }
	 else
	 {
		 pNew->next = pHead;
		 pHead->prior   = pNew;
		 
		 /*链表头变为新的节点(前插)*/
		 pHead = pNew;
	 }

	 return (pHead);

}



/*从双向链表的尾插入，且节点的值为x,返回头指针*/
dlinklist * insertbeforeTail(dlinklist *pHead, int x)
{
	 dlinklist *pNew = NULL;
     dlinklist *p    = NULL;

	 pNew = (dlinklist*)malloc(sizeof(dlinklist));

	 if (NULL == pNew)
	 {
		 return NULL;
	 }

	 pNew->data = x;
     
     /*初次插入*/
	 if (NULL == pHead)
	 {

		 pNew->next = NULL;
		 pNew->prior  = NULL;
		 pHead = pNew;

		 return pHead;
	 }

	 
	 p = pHead;

	 while(p->next != NULL )
	 {
          p = p->next;
	 }
	 
	 p->next = pNew;
	 pNew->next = NULL;
	 pNew->prior = p;

	 return pHead;

}

/* 在双向链表中返回第i个元素的位置指针(算法2.18、2.19要调用的函数) */
dlinklist * GetElemP(dlinklist *pHead,int i) 
{ 
	int j = 1;
    
	dlinklist * p = pHead;

	/*空链表表*/
	if (NULL == pHead)
	{
		printf("the list is empty \n");
		return NULL;
	}
    
	/*指定的结点位置非法*/
	if ((i > ListLength(pHead)) || (i < 0))
	{
		printf("GetElemP invalid para %d \n",i+1);
		return NULL;
	}
    
	/*i = 0时，返回头结点*/
	if (0 == i)
	{
		 printf("return first node \n");
         return pHead;
	}

	/*查找第(i-1)个节点*/
	while ((p->next != NULL) && (j != i))
	{
		p = p->next;
		j++;
	}

	return p;
}

/*从双向链表的第i个结点之前插入一个新的结点，且节点的值为x,返回头指针*/
dlinklist * insertbeforep(dlinklist *pHead, int i, int x)
{
	 dlinklist *pNew = NULL;
     dlinklist *p    = NULL;

     /*查找到第i个结点之前的结点*/
	 p = GetElemP(pHead,i-1);

	 if (NULL == p)
	 {
         printf("\r\n position  error\r\n");
         return NULL;
	 }

	 pNew = (dlinklist*)malloc(sizeof(dlinklist));

	 if (NULL == pNew)
	 {
		 printf("malloc memory failed\n");
		 return NULL;
	 }

	 pNew->data = x;
     

	 /*在头结点之前插入*/
	 if (0 == (i-1))
	 {
		
		 pHead->prior = pNew;
		 pNew->next  = pHead;
		 pNew->prior = NULL;
		 
		 /*链表头变为新的节点(前插)*/
		 pHead = pNew;
         
	 }
	 else
	 {
		 pNew->prior    = p;
		 pNew->next     = p->next;
		 p->next->prior = pNew;
		 p->next        = pNew; 
		 
	 }

	 return (pHead);
}

/* 删除带头结点的双链循环线性表L的第i个元素,i的合法值为1≤i≤表长+1 ,返回头结点*/
 dlinklist * ListDelete(dlinklist* head,int i) 
 { 

    dlinklist* p = NULL;
    dlinklist* r = NULL;

   /*删除头节点*/
	if (0 == (i-1))
	{

        r = head->next;
		free(head);
		head = r;
		return head;

	}

    /*找到第i-1个节点*/
    p = GetElemP(head,i-1);
    
    /*如果为空或i 大于链表的总长度*/
    /*i必须满足1≦i≦ (链表总长度)*/
    if ((NULL == p)  || (NULL== p->next))
    {
       return head;
    }

    /* r就是第i个节点*/

    r = p->next;

	p->next = r->next;

	/*防止删除链表最后一个结点导致r->next->prior 为空*/
	if (r->next != NULL)
	{
        r->next->prior = p;
	}

    free( r ) ; /*释放内存*/

	return head;

 }


/* 初始条件：L已存在。操作结果：将L重置为空表 ,但是链表头结点还是保存的 */
int  ClearList(dlinklist* pHead) 
{ 
	dlinklist *q = NULL;
	dlinklist *p = pHead->next; /* p指向第一个结点 */

    while (p != NULL ) /* p没到表头 */
	{
		q = p->next;
		free(p);
		p = q;
	}
	
	/* 头结点的两个指针域均指向空指针*/
	pHead->next = NULL;
	pHead->prior = NULL; 
	
	return OK;
}

/* 操作结果：销毁双向循环链表L */
int DestroyList(dlinklist **pHead)
{ 
	dlinklist *p  = NULL;

	while((*pHead) != NULL) /* p没到表头 */
	{
		p = (*pHead)->next;

		free(*pHead);

        *pHead = NULL;

		(*pHead) = p;
	}
	
	return OK;
}


/* 初始条件：L已存在。操作结果：返回L中数据元素个数 */
int ListLength(dlinklist* head)
{ 
	int i = 0;

	/* p指向第一个结点 */
	dlinklist *p = head; 
    
	while ( p != NULL) 
	{
		i++;
		p = p->next;
	}

	return i;
}

/*删除指定的双向链表的指定节点,并返回头指针*/
dlinklist*  deletenode(dlinklist *head,dlinklist *p)
{
    if (NULL == p)
    {
        return head;
    }
    
	/*如果删除的是头结点*/
	if (p == head)
	{
        head = p->next;
		return head;

	}

	/*防止P为前向结点为空*/
	if (p->prior != NULL)
	{
		p->prior->next = p->next;
	}
    
	/*防止P为后续结点为空*/
	if (p->next != NULL)
	{
		p->next->prior = p->prior;
	}

    free(p);

	return head;
}

/*删除链表中结点的数值为num结点,返回头指针*/
dlinklist *DelNodeForData(dlinklist *head,long num)  
{
     dlinklist *p1,*p2;

    if ( NULL == head)
    {
        printf("\r\n The List Null! \n");
        return head;
    }

    p1 = head;
    
    while ((num != p1->data) && (p1->next != NULL))
    {
        p2 = p1;

        p1 = p1->next;

    }
    
	/*查找到指定数值的节点*/
    if (num == p1->data)
    {
        if (p1 == head) 
        {
           head = p1->next;
		   return head;
        }
        
		p2->next = p1->next;

		/*防止删除的结点的为空*/
		if (p1->next != NULL)
		{
            p1->next->prior = p2;
		}

		free(p1);
        
    }
    else 
    {
        printf("\r\n %d not been fonnd! \n",num);
    }

    return(head);
    
}


/*创建双向链表的节点*/
/*
dlinklist * create(int Val)
{
	dlinklist *p;
    int i;
   
	p =(dlinklist *)malloc(sizeof(dlinklist));

    if (NULL == p)
	{
		printf("\r\n create list failed \n");
        return NULL;
	}

	p->data = Val;
	p->prior = NULL;
	p->next  = NULL;

	return p;

}
*/


/*打印数据*/
void PrintListData(dlinklist *head)
{
    dlinklist *p = NULL;

	p = head;
 
	while( p != NULL)
	{
		printf("\r\n %d\n",p->data);
		p = p->next;
		
	}
     
}
