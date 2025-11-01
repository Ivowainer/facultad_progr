typedef struct _BTNode
{
    void *data;
    struct _BTNode *left;
    struct _BTNode *right;
} BTNode;

typedef BTNode *BTree;

typedef enum
{
    BTREE_RECORRIDO_IN,
    BTREE_RECORRIDO_PRE,
    BTREE_RECORRIDO_PRE_ITERATIVE,
    BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef void *(CopyFunc)(void *);
typedef void (*VisitorFunc)(void *);
typedef int (*CompFunc)(void *data1, void *data2);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);

BTree btree_create();
BTree btree_join(void *data, BTree left, BTree right, CopyFunc copy);
void btree_map(BTree tree, BTreeOrdenDeRecorrido map, VisitorFunc visit);

int btree_nodes(BTree tree);
int btree_search(BTree tree, void *data, CompFunc func);

BTree btree_copy(BTree tree, CopyFunc copy);

int btree_height(BTree tree);
int btree_nodes_depth(BTree tree, int depth);
int btree_depth(BTree tree, void *data, CompFunc comp);
int btree_sum(BTree tree);

// 4. a
void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteExtra visit, void *extra);

// 5. a
void btree_visit_nodes_depth(BTree tree, VisitorFunc visit, int depth);
void btree_bfs(BTree tree, VisitorFunc visit);
void btree_bfs_iterative(BTree tree, VisitorFunc visit);