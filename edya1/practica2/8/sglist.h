typedef struct _SGNode
{
    void *dato;
    struct _SGNode *next;
} SGNode;

typedef struct SGList
{
    SGNode *head;
    SGNode *tail;
} SGList;

typedef void *(*CopyFunc)(void *);
typedef void (*VisitorFunc)(void *);
typedef void (*DestroyFunc)(SGNode *);
typedef int (*CompFunc)(void *, void *);

SGList *sglist_crear();
void add_first_list(SGList *list, void *dato, CopyFunc copy);
void add_last_list(SGList *list, void *dato, CopyFunc copy);

void sglist_destruir(SGList *list, DestroyFunc destroy);

void sglist_insertar(SGList *list, void *dato, CopyFunc copy, CompFunc comp);

void recorrer_list(SGList *list, VisitorFunc visitor);