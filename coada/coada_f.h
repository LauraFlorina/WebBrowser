/* ȚĂLINĂ Laura-Florina - 314CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _COADA_
#define _COADA_

typedef struct celula_coada{
	struct celula_coada *urm;
	void *info;
} TCel, *AC;

typedef struct coada{
	size_t dime;
	AC ic, sc;
} TCoada, *AQ;

#define VIDA(c) (((TCoada*)(c))->ic == NULL && ((TCoada*)(c))->sc == NULL)
#define DIME(c) (((TCoada*)(c))->dime)

/* Initializeaza o coada, cu elemente de dimensiune d. */
void* InitQ(size_t d);

/* Introduce la sfarsitul cozii c, elementul ae.
Returneaza : 0 - eroare de alocare, 1 - succes. */
int IntrQ(void *c, void *ae);

/* Extrage primul element din coada c, la adresa ae.
Returneaza: 0 - eroare de alocare, 1 - succes. */
int ExtrQ(void *c, void *ae);

/* Testeaza daca coada este vida.
Returneaza: 1 - vida, 0 -nevida. */
int VidaQ(void *c);

/* Concateneaza elementele sursei la destinatie.
Returneaza: -1 - sursa e vida, 1 - succes. */
int ConcatQ(void *d, void *s);

#endif /* _COADA_ */