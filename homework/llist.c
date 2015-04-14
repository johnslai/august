#include <stdio.h>
#include "llist.h"

const int iPoolSize = 128;
typedef struct {
  unsigned int numAvail;
  unsigned int nextAvail;
  TNode pool[iPoolSize];
  unsigned char dirty[iPoolSize];
} TNodePool;
static TNodePool pool;

TLlist getNode()
{
  static int isFirst = 1;
  TNode * node;
  TNodePool * p = &pool;
  if (isFirst) {
    // initialize
    p->numAvail = iPoolSize;
    p->nextAvail = 0;
    isFirst = 0;
  }
  if (p->numAvail == 0) {
    printf("no more nodes available\n");
    return NULL;
  }
  // node to be returned
  unsigned int nextAvail = p->nextAvail;
  node = p->pool + nextAvail;
  p->dirty[nextAvail] = 1;
  p->numAvail--;
  // search for next available, could be done in background
  p->nextAvail++;

  return node;
}

TLlist llistInsert(TLlist list, unsigned int value)
{
  TLlist p = list;
  // create new node and store value
  TLlist new = getNode();
  if (!new) return list; // todo: return error
  new->value = value;

  if (!p || p->value >= value) {
    // case 0: empty list -> create list
    // case 1: insert at head
    new->next = p;
    p = new;
    return p;
  }
  // traverse list
  while (p) {
    if (!p->next || p->next->value >= value) {
      // case 2: (normal case) insert between p and p->next
      // case 3: (terminal case) reached end of list
      new->next = p->next;
      p->next = new;
      return list;
    }
    p = p->next;
  }
  // something is wrong, should not reach here
  return NULL;
}

void llistPrint(TLlist p)
{
  int i=0;
  while(p) {
    printf("%u ", p->value);
    if (p->next) printf("-> ");
    if (i++ %8 ==7 ) printf("\n");
    p= p->next;
  }
  printf("\n");
}

