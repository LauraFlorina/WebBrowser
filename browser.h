/* ȚĂLINĂ Laura-Florina - 314CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tab.h"
#include "coada/coada_f.h"

#ifndef _BROWSER_
#define _BROWSER_

typedef struct{
	unsigned int index_tab_curent;
	ATab tab_curent;
	ATab lista_taburi; /* Lista taburi. */
	AQ istoric; /* Coada istoric global. */
	AQ prioritati_down; /* Coada prioritati. */
	AQ descarcari; /* Coada descarcari finalizate. */
	unsigned int bandwidth;
} TBrowser;

/* Initializare element te tip TBrowser.
Returneaza: NULL - esec, pointer catre un element de tip TBrowser - succes. */
TBrowser *InitBrowser();

/* Adauga un nou tab in browser.
Returneaza: -1 - eroare de alocare, 1 - succes. */
int AddTab(TBrowser *browser);

/* Sterge ultimul tab deschis. */
void DelTab(TBrowser *browser);

/* Schimba tabul curent cu o referinta la tabul de la indexul
primit ca parametru. */
void ChangeTab(TBrowser *browser, int index);

/* Afiseaza informatii despre taburile unui browser. */
void print_open_tabs(TBrowser *browser, FILE *fp);

/* Initializeaza o noua pagina avand url-ul primit ca parametru,
pe care o deschide in tabul curent. */
void DeschidePagina(TBrowser *browser, char *url);

/* Afiseaza istoricul browserului.
Returneaza: -1 - eroare de alocare, 1 - succes,
-2 - in cazul in care la incercarea de a concatena 2 cozi,
sursa este vida. */
int AfisareIstoric(TBrowser *browser, FILE *fp);

/* Sterge un numar de "intrari" din istoricul browserului.
Returneaza: -1 - eroare de alocare, 1 - succes. */
int Sterge_Istoric(TBrowser *browser, int intrari);

/* Preia resursa cu index-ul primit ca parametru, adaugand-o
in coada prioritatilor.
Returneaza: -1 - eroare de alocare, 1 - succes,
-2 - in tabul curent nu e deschisa nicio pagina. */
int DownloadResurse(TBrowser *browser, int index);

/* Afiseaza istoricul descarcarilor din browser.
Returneaza: -1 - eroare de alocare, 1 - succes. */
int Downloads(TBrowser *browser, FILE *fp);

/* Setare bandwitdth. */
void SetBand(TBrowser *browser, unsigned int bandwidth);

/* Comanda care permite avansarea descarcarilor.
Returneaza: -1 - eroare de alocare, 1 - succes. */
int Wait(TBrowser *browser, unsigned int sec);

#endif /* _BROWSER_ */