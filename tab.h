/* ȚĂLINĂ Laura-Florina - 314CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pagina_web.h"
#include "stiva/stiva_f.h"

#ifndef _TAB_
#define _TAB_

typedef struct celula_tab{
	TWeb_page *current_page;
	ASt back_stack;
	ASt forward_stack;
	struct celula_tab *urm;
} TTab, *ATab;

/* Se initializeaza un element de tip TTab.
Se returneaza : NULL - eroare de alocare,
un pointer la un element de tip TTab - succes. */ 
TTab *InitTab();

/* Scoate o pagina web din stiva de back, aceasta devenind
pagina curenta.
Returneaza -2 - nu exista elemente in stiva de back,
1 - succes. */
int Back(TTab *tab);

/* Scoate o pagina web din stiva de forward, aceasta
devening pagina curenta.
Returneaza: -2 - nu exista elemente in stiva de forward,
1 - succes. */ 
int Forward(TTab *tab);

/* Afiseaza resursele paginii curente.
Returneaza: -2 - nu exista o pagina deschisa in tab,
1- succes. */
int AfiseazaResurse(TTab *tab, FILE *fp);

#endif /* _TAB_ */