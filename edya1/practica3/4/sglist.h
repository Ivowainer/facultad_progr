typedef struct _SGNode
{
    void *data;
    struct _SGNode *next;
} SGNode;

typedef struct
{
    SGNode *first;
    SGNode *last;
} SGList;

typedef void *(*CopyFunc)(void *);
typedef void (*VisitorFunc)(void *);

SGList *list_create();
void list_add_end(SGList *list, void *data, CopyFunc copy);
void list_map(SGList *list, VisitorFunc visitor);