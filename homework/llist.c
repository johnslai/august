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
  if (!new) return list;
  new->value = value;

  if (!p) {
    // case 0: create list
    list = new;
    return list;
  }
  TLlist prev = NULL;
  while (p) {
    if (p->value >= value) {
      if (!prev) {
        // case 1: insert at head
        list = new;
        new->next = p;
      } else {
        // case 2: (normal case) insert between prev and p
        prev->next = new;
        new->next = p;
      }
      return list;
    }

    prev = p;
    p = p->next;
  }
  // case 3: (terminal case) reached end of list
  prev->next = new;
  new->next = p;
  return list;
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

