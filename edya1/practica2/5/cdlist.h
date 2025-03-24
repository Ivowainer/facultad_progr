typedef struct _DNode
{
    struct _DNode *next;
    struct _DNode *prev;
    int dato;
} DNode;

typedef struct
{
    DNode *first;
    DNode *last;
} DList;

DList *create_list(int dato);
void add_final(DList *list, int dato);
void add_start(DList *list, int dato);
void cdlist_recorrer(DList *list, void (*FuncVisitante)(int *));
void print_list(DList *list);