#ifndef __MIHASH_H__
#define __MIHASH_H__

typedef void *(*CopyFunction)(void *data);

typedef int (*CompFunction)(void *data1, void *data2);

typedef void (*DestroyFunction)(void *data);
/** Libera la memoria alocada para el data */
typedef unsigned (*HashFunction)(void *data);
/** Retorna un entero sin signo para el data */

typedef struct _HashTable *HashTable;

#define OCCUPIED 1
#define FREE 0

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct
{
    char *data;
    int state;
    // void* data
    /* GList data; */
} HashBox;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _HashTable
{
    HashBox *elems;
    unsigned numElems;
    unsigned capacity;
    CopyFunction copy;
    CompFunction comp;
    DestroyFunction destr;
    HashFunction hash;
};

/*
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
HashTable hashtable_create(unsigned capacity, CopyFunction copy,
                           CompFunction comp, DestroyFunction destroy,
                           HashFunction hash);

/*
 * Retorna el numero de elementos de la tabla.
 */
int hashtable_nelems(HashTable table);

/*
 * Retorna la capacidad de la tabla.
 */
int hashtable_capacity(HashTable table);

/*
 * Destruye la tabla.
 */
void hashtable_destroy(HashTable table);

/**
 * Inserta un data en la tabla, o lo reemplaza si ya se encontraba.
 * key % capacity
 */
void hashtable_insert(HashTable table, void *key, void *data);

/**
 * Retorna el data de la tabla que coincida con el data dado, o NULL si el data
 * buscado no se encuentra en la tabla.
 */
void *hashtable_search(HashTable table, void *key);

/**
 * Elimina el data de la tabla que coincida con el data dado.
 */
void hashtable_eliminate(HashTable table, int key);

HashTable hashtable_redim(HashTable table);

double hash_charge_factor(HashTable table);

void *copy(void *data);
int comp(void *data1, void *data2);
void destr(void *data);
unsigned simple_hash(void *data);

#endif /* __MIHASH_H__ */