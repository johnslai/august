#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include "llist.h"

bool testInsert0()
{
  TNode * p = NULL;
  printf("%s\n", __FUNCTION__);
  p = llistInsert(p, 10);
  assert(p);
  assert(p->value == 10);
  assert(p->next == NULL);
  llistPrint(p);
  return true;
}

bool testInsert1()
{
  TNode * p = NULL;
  printf("%s\n", __FUNCTION__);
  p = llistInsert(p, 10);
  p = llistInsert(p, 5);
  assert(p->value ==5);
  assert(p->next->value==10);
  llistPrint(p);
  return true;
}

bool testInsert2()
{
  TNode * p = NULL;
  printf("%s\n", __FUNCTION__);
  p = llistInsert(p, 10);
  p = llistInsert(p, 4);
  p = llistInsert(p, 5);
  assert(p->value ==4);
  assert(p->next->value ==5);
  assert(p->next->next->value ==10);
  llistPrint(p);
  return true;
}

bool testInsert3()
{
  TNode * p = NULL;
  printf("%s\n", __FUNCTION__);
  p = llistInsert(p, 4);
  p = llistInsert(p, 5);
  assert(p->value ==4);
  assert(p->next->value ==5);
  llistPrint(p);
  return true;
}

bool testx()
{
  return false;
}

int main()
{
  testInsert0();
  testInsert1();
  testInsert2();
  testInsert3();
}
