#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ElementType int

typedef struct qnode
{
    ElementType elem;
    struct qnode *next;
} Qnode;

typedef struct Queue
{
    Qnode *head;
    Qnode *tail;
    int count;
} Queue;

void queue_init(Queue *s);
bool queue_find(Queue *s, ElementType *elem);
void queue_add(Queue *s, ElementType *elem); //add tail item to queue
ElementType queue_remove(Queue *s);          //remove head item from queue
int queue_count(Queue *s);                   //return items in queue
void queue_free(Queue *s);                   //free the queue

void queue_init(Queue *s)
{
    s->head = s->tail = NULL;
    s->count = 0;
}

bool queue_find(Queue *s, ElementType *elem)
{
    Qnode *node;
    node = s->head;
    while (node != NULL)
    {
        if (memcmp(&(node->elem), elem, sizeof(ElementType)) == 0)
        {
            return true;
        }
        node = node->next;
    }
    return false;
}

void queue_add(Queue *s, ElementType *elem)
{
    Qnode *node; //new node
    if (queue_find(s, elem))
    {
        return;
    }
    if (s->head == NULL)
    {
        node = s->head = s->tail = (Qnode *)malloc(sizeof(Qnode));
        memcpy(&(node->elem), elem, sizeof(ElementType));
        node->next = NULL;
    }
    else
    {
        node = (Qnode *)malloc(sizeof(Qnode));
        memcpy(&(node->elem), elem, sizeof(ElementType));
        node->next = NULL;
        s->tail->next = node;
        s->tail = node;
    }
    s->count++;
}

ElementType queue_remove(Queue *s)
{
    ElementType res;
    Qnode *node;
    if (s->head != NULL)
    {
        node = s->head;
        memcpy(&res, &(node->elem), sizeof(ElementType));
        s->head = s->head->next;
        s->count--;
        free(node);
    }
    return res;
}

int queue_count(Queue *s)
{
    return s->count;
}

void queue_print(Queue *s)
{
    Qnode *node = s->head;
    while(node != NULL) {
        printf("%d ", node->elem);
        node = node->next;
    }
    printf("\n");
}

void queue_free(Queue *s)
{
    while (queue_count(s))
    {
        printf("%d ", queue_remove(s));
    }
    printf("\n");
}

int main()
{
    Queue *s = (Queue *)malloc(sizeof(Queue));
    queue_init(s);
    for (int i = 0; i < 10; i++)
    {
        ElementType elem = i + 100;
        queue_add(s, &elem);
    }
    queue_print(s);
    queue_free(s);
    if(s->count == 0) {
        printf("free sucess\n");
    }
}