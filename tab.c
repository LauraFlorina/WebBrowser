/* ȚĂLINĂ Laura-Florina - 314CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tab.h"
#include "utils/utils.h"

TTab *InitTab() {
	ATab tab = calloc(1, sizeof(TTab));
	if (!tab) {
		return NULL;
	}
	tab->current_page = NULL;
	tab->back_stack = InitS(sizeof(TWeb_page));
	tab->forward_stack = InitS(sizeof(TWeb_page));
	tab->urm = NULL;
	return tab;
}

int Back(TTab *tab) {
	if (tab->back_stack == NULL) {
		return -2; /* Nu exista elemente in stiva de back */
	}
	Push(tab->forward_stack, tab->current_page);
	Pop(tab->back_stack, tab->current_page);
	return 1;
}

int Forward(TTab *tab) {
	if(tab->forward_stack == NULL) {
		return -2; /* Nu exista elemente in stiva de forward */
	}
	Push(tab->back_stack, tab->current_page);
	Pop(tab->forward_stack, tab->current_page);
	return 1;
}

int AfiseazaResurse(TTab *tab, FILE *fp) {
	int i;
	if (tab->current_page == NULL) {
		return -2; /* Nu exista o pagina deschisa in tabul respectiv */ 
	}
	for (i = 0; i < tab->current_page->num_res; i++) {
		fprintf(fp, "[%d - ", i);
		fprintf(fp, "\"%s\"", tab->current_page->resources[i].name);
		fprintf(fp, " : %lu]\n", tab->current_page->resources[i].dimension);
	}
	return 1;
}