#ifndef __TIPOS_H__
#define __TIPOS_H__

typedef int (*FuncComp)(void *a, void *b);
typedef void (*FuncDestr)(void *a);
typedef void *(*FuncCopy)(void *a);
typedef void (*FuncVisit)(void *a);

#endif