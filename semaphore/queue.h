#ifndef __QUEUE_H__
#define __QUEUE_H__

#define QMAX 128

struct queue {
  int tail, head;
  int list[QMAX];
};

void que_init(struct queue *que)
{
  que->head = 0;
  que->tail = 0;
}

int next_pos(int pos)
{
  if (pos == QMAX-1)
    return 0;
  return pos+1;
}

int que_empty(struct queue *que)
{
  if (que->head == que->tail)
    return 1;
  return 0;
}

int que_peek(struct queue *que)
{
  if (que_empty(que))
    return -1;

  return que->list[next_pos(que->head)];
}

int dequeue(struct queue *que)
{
  if (que_empty(que))
    return -1;

  que->head = next_pos(que->head);
  return que->list[que->head];
}

void enqueue(struct queue *que, int data)
{
  if (next_pos(que->tail) == que->head)
    return;

  que->tail = next_pos(que->tail);
  que->list[que->tail] = data;
}

#endif
