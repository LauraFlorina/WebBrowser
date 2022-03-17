/* ȚĂLINĂ Laura-Florina - 314CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _STIVA_
#define _STIVA_

typedef struct celula_stiva{
	struct celula_stiva *urm;
	void *info;
} TCelSt, *ACelSt;

typedef struct stiva{
	size_t dime;
	ACelSt vf; /* adresa celulei din varf */ 
} TStiva, *ASt;

/* Initializeaza o stiva cu elemente de dimensiune d. */
void* InitS(size_t d);

/* Introducere elementul ae, in stiva a.
Returneaza: 0 - eroare de alocare, 1 - succes. */
int Push(void *a, void *ae);

/* Extrage elementul din stiva s, la adresa elementului ae.
Returneaza: 0 - nu exista elemente de extras, 1 - succes. */
int Pop(void *s, void *ae);

/* Testeaza daca stiva s este vida.
Returneaza: 1 - vida, 0 - nevida. */
int VidaS(void *s);

/* Reseteaza stiva s, eliberand memoria */
void ResetS(void *s);

#endif /* _STIVA_ */
