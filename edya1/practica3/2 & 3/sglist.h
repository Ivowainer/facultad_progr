typedef struct _SGNode
{
    void *dato;
    struct _SGNode *next;
} SGNode;

typedef struct
{
    SGNode *start;
    SGNode *last;
} SGList;

typedef SGList Stack;

typedef void (*VisitorFunc)(void *dato);
typedef void *(*CopyFunc)(void *dato);

Stack *stack_create();
void stack_push(Stack *stack, void *dato, CopyFunc func);
void stack_pop(Stack *stack);
void *stack_top(Stack *stack);

void stack_destroy(Stack *stack);
void stack_map(Stack *stack, VisitorFunc visitor);

// EJ 3
SGList *list_reverse(SGList *list, CopyFunc func);