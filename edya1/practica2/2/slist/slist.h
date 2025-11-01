typedef struct _SNode
{
    int dato;
    struct _SNode *sig;
} SNode;

typedef int (*compare_function)(int, int);
typedef int (*compare_function2)(int, int);

void slist_add(SNode **node, int dato);
void slist_imprimir(SNode *list1);

// Ejs
int slist_longitud(SNode *node);
void slist_concatenar(SNode **list1, SNode *list2);
void slist_insertar(SNode **list, int dato, int posicion);
void slist_eliminar(SNode **list, int dato);
int slist_contiene(SNode *list, int dato);
int slist_indice(SNode *list, int dato);
SNode *slist_intersecar(SNode *list1, SNode *list2);
SNode *slist_intersecar_custom(SNode *list1, SNode *list2, compare_function);
void slist_ordenar(SNode *list, compare_function2 func);
SNode *slist_intercalar(SNode *list1, SNode *list2);
void slist_add_final(SNode **list, int dato);