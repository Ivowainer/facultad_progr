typedef struct _GNode
{
    void *dato;
    struct _GNode *next;
} GNode;

typedef struct
{
    GNode *first;
    GNode *last;
} GList;

typedef void *(*CopyFunc)(void *dato);
typedef void (*VisitorFunc)(void *dato);
typedef int (*Predicado)(void *dato);

GList *create_list(void *dato, CopyFunc copy);
void add_list_first(GList *list, void *dato, CopyFunc copy);
void add_list_last(GList *list, void *dato, CopyFunc copy);
void recorrer_list(GList *list, VisitorFunc visitor);

GList *glist_filtrar(GList *list, CopyFunc copy, Predicado predicado);