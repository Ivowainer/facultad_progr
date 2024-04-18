typedef struct _DNode
{
    int dato;
    struct _DNode *next;
    struct _DNode *prev;
} DNode;

typedef struct
{
    DNode *first;
    DNode *last;
} DList;

typedef enum
{
    DLIST_RECORRIDO_HACIA_ADELANTE, // 0
    DLIST_RECORRIDO_HACIA_ATRAS     // 1
} DListOrdenDeRecorrido;

DList *create_list(int dato);
void add_final(DList *list, int dato);
void add_start(DList *list, int dato);
void recorrer_list(DListOrdenDeRecorrido orden, DList *list, int (*FuncVisitante)(int *));
void print_list(DList *list);