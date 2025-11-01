#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./hash.h"

HashTable hashtable_create(unsigned capacity, CopyFunction copy, CompFunction comp, DestroyFunction destr, HashFunction hash)
{
    HashTable table = malloc(sizeof(struct _HashTable));

    table->elems = malloc(sizeof(HashBox) * capacity);

    for (int i = 0; i < capacity; i++)
    {

        table->elems[i].data = malloc(20 * sizeof(char));
        table->elems[i].state = FREE;
    }

    table->numElems = 0;
    table->comp = comp;
    table->copy = copy;
    table->destr = destr;
    table->hash = hash;
    table->capacity = capacity;
    return table;
}

int hashtable_nelemsm(HashTable table)
{
    return table->numElems;
}

int hashtable_capacity(HashTable table)
{
    return table->capacity;
}

void hashtable_destroy(HashTable table)
{

    for (unsigned int idx = 0; idx < table->capacity; idx++)
    {
        if (table->elems[idx].state == OCCUPIED)
            (table->destr(table->elems[idx].data));
    }

    free(table->elems);
    free(table);
}

void hashtable_insert(HashTable table, void *key, void *data)
{
    unsigned idx = table->hash(key) % table->capacity;

    table->numElems++;
    table->elems[idx].data = table->copy(data);
    table->elems[idx].state = OCCUPIED;
    return;
}

void *hashtable_search(HashTable table, void *key)
{
    // unsigned idx= table->hash(data) % table->capacity;
    unsigned idx = table->hash(key) % table->capacity;
    void *search = NULL;
    if (table->elems[idx].state == FREE)
    {
        search = NULL;
    }
    else
    {
        search = table->elems[idx].data;
    }
    return search;
}

void hashtable_eliminate(HashTable table, int key)
{
    unsigned idx = key % table->capacity;

    if (table->elems[idx].state == FREE)
    {
        return;
    }
    else
    {
        table->elems[idx].state = FREE;
        int len = strlen(table->elems[idx].data);
        for (int i = 0; i < len; i++)
        {
            table->elems[idx].data[i] = ' ';
        }
    }
}

void *copy(void *data)
{
    return data;
}

int comp(void *data1, void *data2)
{
    return (strcmp((char *)data1, (char *)data2));
}

void destr(void *data)
{
    free(data);
}

unsigned simple_hash(void *data)
{
    char *str = (char *)data;
    unsigned hash = 0;
    unsigned prime = 31; // Constante para mejorar la distribución
    while (*str)
    {
        hash = hash * prime + (unsigned char)(*str);
        str++;
    }
    return hash;
}