/* ȚĂLINĂ Laura-Florina - 314CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "browser.h"
#include "utils/utils.h"

TBrowser *InitBrowser() {
	TBrowser *browser = calloc(1, sizeof(TBrowser));
	if (!browser) {
		return NULL;
	}
	/* Initializare lista taburi. */
	browser->lista_taburi = InitTab();
	if (!browser->lista_taburi) {
		return NULL;
	}
	/* Initializare coada istoric. */
	browser->istoric = InitQ(sizeof(TWeb_page));
	if (!browser->istoric) {
		return NULL;
	}
	/* Initializare coada de prioritati. */
	browser->prioritati_down = InitQ(sizeof(Resource));
	if (!browser->prioritati_down) {
		return NULL;
	}
	/* Initializare coada descarcari finalizate. */
	browser->descarcari = InitQ(sizeof(Resource));
	if (!browser->descarcari) {
		return NULL;
	}
	browser->index_tab_curent = 0;
	browser->tab_curent = browser->lista_taburi;
	browser->bandwidth = 1024;
	return browser;
}

int AddTab(TBrowser *browser) {
	ATab new_tab = InitTab();
	if (!new_tab) {
		return -1; /* Eroare de alocare */
	}
	ATab p = browser->lista_taburi; /* pointer cu care se parcurge lista */
	ATab ant = NULL; /* pastreaza tabul anterior */
	int index = 0;
	for (; p != NULL; ant = p, p = p->urm) {
		index++;
	}
	ant->urm = new_tab;
	browser->index_tab_curent = index;
	browser->tab_curent = new_tab;
	return 1;
}

void DelTab(TBrowser *browser) {
	ATab p = browser->lista_taburi; /* pointer cu care se parcurge lista */
	ATab ant = NULL; /* pastreaza tabul anterior */
	int index = 0;
	for (; p->urm != NULL; ant = p, p = p->urm) {
		index++;
	}
	ant->urm = NULL;
	if (browser->index_tab_curent == index) {
		browser->index_tab_curent = index - 1;
		browser->tab_curent = ant;
	}
}

void ChangeTab(TBrowser *browser, int index) {
	ATab p = browser->lista_taburi;
	int i;
	for (i = 0; p != NULL; p = p->urm, i++) {
		if (i == index) {
			break;
		}
	}
	browser->index_tab_curent = index;
	browser->tab_curent = p;
}

void print_open_tabs(TBrowser *browser, FILE *fp) {
	ATab p = browser->lista_taburi; /* pointer cu care se parcurge lista */
	int index = 0;
	while ( p != NULL) {
		if (p->current_page) {
			fprintf(fp, "(%d: ", index);
			fprintf(fp, "%s)\n", p->current_page->url);
		} else {
			fprintf(fp, "(%d: empty)\n", index);
		}
		p = p->urm;
		index++;
	}
}

void DeschidePagina(TBrowser *browser, char *url) {
	TWeb_page *new_page = InitPage(url);
	IntrQ(browser->istoric, new_page);
	/* Cazul in care exista o pagina deschisa in tab-ul respectiv */
	if (browser->tab_curent->current_page != NULL) {
		Push(browser->tab_curent->back_stack, browser->tab_curent->current_page);
	}
	/* Se goleste stiva de forward. */
	ResetS(browser->tab_curent->forward_stack);
	browser->tab_curent->current_page = new_page;
	Wait(browser, 1);
}

int AfisareIstoric(TBrowser *browser, FILE *fp) {
	TWeb_page *aux_page = calloc(1, sizeof(TWeb_page));
	if (!aux_page) {
		return -1; /* Eroare de alocare */
	}
	/* Se initializeaza o coada auxiliara. */
	AQ coada_aux = InitQ(sizeof(TWeb_page));
	if (!coada_aux) {
		return -1;
	}
	while (!VidaQ(browser->istoric)) {
		ExtrQ(browser->istoric, aux_page);
		fprintf(fp, "%s\n", aux_page->url);
		IntrQ(coada_aux, aux_page);
	}
	int cod = ConcatQ(browser->istoric, coada_aux);
	if (cod == -2) {
		return -2; /* Sursa nu are elemente */
	}
	return 1;
}

int Sterge_Istoric(TBrowser *browser, int intrari) {
	int i;
	TWeb_page *aux_page = calloc(1, sizeof(TWeb_page));
	if (!aux_page) {
		return -1; /* Eroare de alocare */
	}
	if (intrari == 0) {
		while (!VidaQ(browser->istoric)) {
			ExtrQ(browser->istoric, aux_page);
		}
	} else {
		for (i = 0; i < intrari; i++) {
			if (!VidaQ(browser->istoric)){
				ExtrQ(browser->istoric, aux_page);
			}
		}
	}
	return 1;
}

int DownloadResurse(TBrowser *browser, int index) {
	if (browser->tab_curent->current_page == NULL) {
		return -2; /* In tabul curent nu e deschisa nicio pagina. */
	}
	Resource *resursa = calloc(1, sizeof(Resource));
	if (!resursa) {
		return -1;
	}
	resursa = &browser->tab_curent->current_page->resources[index];
	/* Odata copiata resursa, aceasta se introduce in coada de prioritati. */
	if (VidaQ(browser->prioritati_down)) {
		IntrQ(browser->prioritati_down, resursa);
	} else {
		Resource *extrasa = calloc(1, sizeof(Resource));
		if (!extrasa) {
			return -1;
		}
		unsigned long extrasa_ramas, resursa_ramas;
		AQ coada_aux = InitQ(sizeof(Resource));
		if (!coada_aux) {
			return -1;
		}
		/* Daca coada de prioritati nu este goala, atunci se extrage cate o
		resursa. */
		int introdus = 0;
		while (!VidaQ(browser->prioritati_down)) {
			ExtrQ(browser->prioritati_down, extrasa);
			extrasa_ramas = extrasa->dimension - extrasa->currently_downloaded;
			resursa_ramas = resursa->dimension - resursa->currently_downloaded;
			if ((extrasa_ramas >= resursa_ramas) && (introdus == 0)) {
				IntrQ(coada_aux, resursa);
				IntrQ(coada_aux, extrasa);
				introdus = 1;
			} else {
				IntrQ(coada_aux, extrasa);
			}
		}
		/* Daca resursa are prioritate mai mica fata de elementele din coada. */
		if (introdus == 0) {
			IntrQ(coada_aux, resursa);
		}
		/* Reconstruirea cozii de prioritati. */
		while (!VidaQ(coada_aux)) {
			ExtrQ(coada_aux, extrasa);
			IntrQ(browser->prioritati_down, extrasa);
		}
	}
	return 1;
}

int Downloads(TBrowser *browser, FILE *fp) {
	Resource *extrasa = calloc(1, sizeof(Resource));
	if (!extrasa) {
		return -1;
	}
	AQ coada_aux = InitQ(sizeof(Resource));
	if (!coada_aux) {
		return -1;
	}
	/* Afisarea resurselor aflate in coada de prioritati. */
	unsigned long extrasa_ramas;
	while (!VidaQ(browser->prioritati_down)) {
		ExtrQ(browser->prioritati_down, extrasa);
		fprintf(fp, "[\"%s\" : ", extrasa->name);
		extrasa_ramas = extrasa->dimension - extrasa->currently_downloaded;
		fprintf(fp, "%lu/%lu]\n", extrasa_ramas, extrasa->dimension);
		IntrQ(coada_aux, extrasa);
	}
	/* Reconstruirea cozii de prioritati. */
	while (!VidaQ(coada_aux)) {
		ExtrQ(coada_aux, extrasa);
		IntrQ(browser->prioritati_down, extrasa);
	}
	/* Afisarea resurselor complet descarcate. */
	while (!VidaQ(browser->descarcari)) {
		ExtrQ(browser->descarcari, extrasa);
		fprintf(fp, "[\"%s\" : completed]\n", extrasa->name);
		IntrQ(coada_aux, extrasa);
	}
	/* Reconstruirea cozii de descarcari finalizate. */
	while (!VidaQ(coada_aux)) {
		ExtrQ(coada_aux, extrasa);
		IntrQ(browser->descarcari, extrasa);
	}
	return 1;
}

void SetBand(TBrowser *browser, unsigned int bandwidth) {
	browser->bandwidth = bandwidth;
}

int Wait(TBrowser *browser, unsigned int sec) {
	unsigned long nr_bytes = (unsigned long)(sec * browser->bandwidth);
	Resource *extrasa = calloc(1, sizeof(Resource));
	if (!extrasa) {
		return -1;
	}
	/* Initializare coada auxiliara. */
	AQ coada_aux = InitQ(sizeof(Resource));
	if (!coada_aux) {
		return -1;
	}
	unsigned long ramasa; /* Dimensiunea ramasa de descarcat. */
	while(!VidaQ(browser->prioritati_down)) {
		ExtrQ(browser->prioritati_down, extrasa);
		if (nr_bytes > 0) {
			ramasa = extrasa->dimension - extrasa->currently_downloaded;
			if (nr_bytes < ramasa) {
				/* Cazul in care ne-au fost oferiti mai putini bytes decat avem
				nevoie pentru a descarca resursa. */
				extrasa->currently_downloaded += nr_bytes;
				nr_bytes = 0;
			} else if (nr_bytes == ramasa) {
				/* Cazul in care numarul de bytes este exact cel necesar
				descarcarii resursei. */
				extrasa->currently_downloaded = extrasa->dimension;
				nr_bytes = 0;
				IntrQ(browser->descarcari, extrasa);
				continue;
			} else {
				/* Cazul in care numarul de bytes este suficient pentru a
				descarca resursa, si pentru a avansa la urmatoarea resursa. */
				nr_bytes = nr_bytes - ramasa;
				extrasa->currently_downloaded = extrasa->dimension;
				IntrQ(browser->descarcari, extrasa);
				continue;
			}
		}
		IntrQ(coada_aux, extrasa);
	}
	/* Reconstruirea cozii de prioritati. */
	while (!VidaQ(coada_aux)) {
		ExtrQ(coada_aux, extrasa);
		IntrQ(browser->prioritati_down, extrasa);
	}
	return 1;
}