typedef enum _TLlistStatus {
  OK=0,
  ERR=1,
} TStatus;

typedef struct _TNode TNode;
typedef TNode * TLlist;

TStatus llistInsert(TLlist *list, unsigned int value);
TStatus llistDestroy(TLlist *list);
void llistPrint(TLlist p);
void testPool();
