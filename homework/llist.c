#include <stdio.h>
#include <assert.h>
#include "llist.h"
// compile time parameter for configuring node pool size
const int iPoolSize = 4;

struct _TNode {
  unsigned long value;
  struct _TNode * next;
  // internal fields for pool management
  unsigned char used: 1; // checked if already allocated
};

typedef struct {
  unsigned int numAvail;
  unsigned int nextAvail;
  TNode pool[iPoolSize];
} TNodePool;
static TNodePool pool;

static void poolPrint(TNodePool * p)
{
  printf("pool address:\n");
  for (int i=0; i< iPoolSize; i++) 
    printf("%p\n", p->pool+i);
}

// initialize a pool
static void poolInit(TNodePool * p)
{
  // initialize
  p->numAvail = iPoolSize;
  p->nextAvail = 0;
  //poolPrint(p);
}

static unsigned int searchNextAvail(TNodePool * p)
{
  int i = p->nextAvail;
  if (!p->numAvail) return i; // pool full, just return something
  while (p->pool[i].used) {
    i=(i+1)%iPoolSize;
    assert(i != p->nextAvail); // infinite loop detected
  }
  return i;
}

static TLlist newNode()
{
  static int isFirst = 1;
  TLlist node;
  TNodePool * p = &pool;
  if (isFirst) {
    poolInit(p);
    isFirst = 0;
  }
  if (p->numAvail == 0) {
    printf("no more nodes available\n");
    return NULL;
  }
  // search for next available node
  p->nextAvail = searchNextAvail(p);
  // node to be returned
  node = p->pool + p->nextAvail;
  node->used = 1;
  p->numAvail--;

  return node;
}

static void freeNode(TLlist node)
{
  if (node && node->used) {
    int i;
    node->used = 0;
    pool.numAvail++;
  }
}

TStatus llistInsert(TLlist *list, unsigned long value)
{
  TLlist p = *list;
  // create new node and store value
  TLlist new = newNode();
  if (!new) return ERR;
  new->value = value;

  if (!p || p->value >= value) {
    // case 0: empty list -> create list
    // case 1: insert at head
    new->next = p;
    p = new;
    *list = p;
    return OK;
  }
  // traverse list
  while (p) {
    if (!p->next || p->next->value >= value) {
      // case 2: (normal case) insert between p and p->next
      // case 3: (terminal case) reached end of list
      new->next = p->next;
      p->next = new;
      // *list does not change
      return OK;
    }
    p = p->next;
  }
  // something is wrong, should not reach here
  return ERR;
}

TStatus llistDestroy(TLlist *list)
{
  TLlist p = *list;
  while (p) {
    TLlist q = p;
    freeNode(q);
    p=p->next;
  }
  *list = NULL;
  return OK;
}

void llistPrint(TLlist p)
{
  int i=0;
  while(p) {
    printf("%lu ", p->value);
    if (p->next) printf("-> ");
    if (i++ %8 ==7 ) printf("\n");
    p= p->next;
  }
  printf("\n");
}

void testPool()
{
  printf("%s\n", __FUNCTION__);
  assert(pool.nextAvail == 0);
  TNode * a = newNode();
  assert(pool.nextAvail == 0);
  TNode * b = newNode();
  assert(pool.nextAvail == 1);
  freeNode(b);
  TNode * c = newNode();
  assert(pool.nextAvail == 1);
  freeNode(a);
  TNode * d = newNode();
  assert(pool.nextAvail == 2);
  TNode * e = newNode();
  assert(pool.nextAvail == 3);
  TNode * f = newNode();
  assert(pool.nextAvail == 0);
  freeNode(d);
  TNode * g = newNode();
  assert(pool.nextAvail == 2);
  freeNode(b); freeNode(c); freeNode(e); freeNode(f); freeNode(g);
}
