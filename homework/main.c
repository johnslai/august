// main is the test program
#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include "llist.h"

struct _TNode {
  unsigned int value;
  struct _TNode * next;
};

void testInsert0()
{
  TLlist p = NULL;
  printf("%s\n", __FUNCTION__);
  if (ERR == llistInsert(&p, 5)) goto cleanup;
  assert(p);
  assert(p->value == 5);
  assert(p->next == NULL);
  llistPrint(p);
cleanup:
  llistDestroy(&p);
}

void testInsert1()
{
  TLlist p = NULL;
  printf("%s\n", __FUNCTION__);
  if (ERR == llistInsert(&p, 10)) goto cleanup;
  if (ERR == llistInsert(&p, 5)) goto cleanup;
  assert(p->value ==5);
  assert(p->next->value==10);
  llistPrint(p);
cleanup:
  llistDestroy(&p);
}

void testInsert2()
{
  TLlist p = NULL;
  printf("%s\n", __FUNCTION__);
  if (ERR == llistInsert(&p, 10)) goto cleanup;
  if (ERR == llistInsert(&p, 4)) goto cleanup;
  if (ERR == llistInsert(&p, 5)) goto cleanup;
  assert(p->value ==4);
  assert(p->next->value ==5);
  assert(p->next->next->value ==10);
  llistPrint(p);
cleanup:
  llistDestroy(&p);
}

void testInsert3()
{
  TLlist p = NULL;
  printf("%s\n", __FUNCTION__);
  if (ERR == llistInsert(&p, 4)) goto cleanup;
  if (ERR == llistInsert(&p, 5)) goto cleanup;
  assert(p->value ==4);
  assert(p->next->value ==5);
  llistPrint(p);
cleanup:
  llistDestroy(&p);
}

// a test template
void testx()
{
  TLlist p = NULL;
  printf("%s\n", __FUNCTION__);
  // setup

  // unit test
  if (ERR == llistInsert(&p, 5)) goto cleanup;

  // assert
  assert(p->value == 5);
  assert(p->next == NULL);

  // print
  llistPrint(p);
cleanup:
  llistDestroy(&p);
}

int main()
{
  testPool();
  testInsert0();
  testInsert1();
  testInsert2();
  testInsert3();
}
