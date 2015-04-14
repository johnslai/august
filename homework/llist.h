typedef enum _TLlistStatus {
  OK=0,
  ERR=1,
} TStatus;

typedef struct _TNode {
  unsigned int value;
  struct _TNode * next;
} TNode;

typedef TNode * TLlist;

// init function before using this linkList lib
TLlist llistInsert(TLlist list, unsigned int value);
void llistPrint(TLlist p);
