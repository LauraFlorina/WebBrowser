/* ȚĂLINĂ Laura-Florina - 314CB */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils/utils.h"
#include "browser.h"
#include "tab.h"
#include "coada/coada_f.h"
#include "stiva/stiva_f.h"
#include "pagina_web.h"

#define DIM_LINIE 256

int main(int arg_num, char **arg_val){
	TBrowser *browser = InitBrowser();
	int cod_returnat;
	/* Se deschid fisierele de in si out. */
	FILE *fp_read, *fp_write;
	fp_read = fopen(arg_val[1], "rt");
	if (fp_read == NULL) {
		return -2; /* */
	}
	fp_write = fopen(arg_val[2], "wt");
	if (fp_read == NULL) {
		return -2;
	}
	char *linie = calloc(DIM_LINIE, sizeof(char));
	if (!linie) {
		return -1;
	}
	/* Se parcurge fisierul de intrare linie cu linie. */
	while (fgets(linie, DIM_LINIE, fp_read)) {
		/* Se sparge comanda pe componente. */
		char *comanda = strtok(linie, " \n");
		if (!comanda) {
			return -1;
		}
		if (strcmp(comanda, "newtab") == 0) {
			cod_returnat = AddTab(browser);
			if (cod_returnat == -1) {
				return -1;
			}
		} else if (strcmp(comanda, "deltab") == 0) {
			DelTab(browser);
		} else if (strcmp(comanda, "change_tab") == 0) {
			/* Indexul este citit sub forma de char */
			char *index_char = strtok(NULL, " \n");
			if (!index_char) {
				return -1;
			}
			/* Se converteste index-ul la int */
			int index = atoi(index_char);
			ChangeTab(browser, index);
		} else if (strcmp(comanda, "print_open_tabs") == 0) {
			print_open_tabs(browser, fp_write);
		} else if (strcmp(comanda, "goto") == 0) {
			char *url = strtok(NULL, " \n");
			if (!url) {
				return -1;
			}
			DeschidePagina(browser, url);
		} else if (strcmp(comanda, "back") == 0) {
			cod_returnat = Back(browser->tab_curent);
			if (cod_returnat == -2) {
				fprintf(fp_write, "can't go back, no pages in stack\n");
			}
		} else if (strcmp(comanda, "forward") == 0) {
			cod_returnat = Forward(browser->tab_curent);
			if (cod_returnat == -2) {
				fprintf(fp_write, "can't go forward, no pages in stack\n");
			}
		} else if (strcmp(comanda, "history") == 0){
			cod_returnat = AfisareIstoric(browser, fp_write);
			if (cod_returnat == -1) {
				return -1;
			}
			if (cod_returnat == -2) {
				return -1;
			}
		} else if (strcmp(comanda, "del_history") == 0){
			/* Intrarile sunt citite sub forma de char */
			char *intrari_char = strtok(NULL, " \n");
			if (!intrari_char) {
				return -1;
			}
			/* Se convertesc intrarile la int */
			int intrari = atoi(intrari_char);
			cod_returnat = Sterge_Istoric(browser, intrari);
			if (cod_returnat == -1) {
				return -1;
			}
		} else if (strcmp(comanda, "list_dl") == 0) {
			cod_returnat = AfiseazaResurse(browser->tab_curent, fp_write);
		} else if (strcmp(comanda, "download") == 0) {
			char *index_resursa_char = strtok(NULL, " \n");
			if (index_resursa_char == NULL) {
				return -1;
			}
			cod_returnat = DownloadResurse(browser, atoi(index_resursa_char));
			if (cod_returnat == -1) {
				return -1;
			}
		} else if (strcmp(comanda, "downloads") == 0) {
			int cod_returnat = Downloads(browser, fp_write);
			if (cod_returnat == -1) {
				return -1;
			}
		} else if (strcmp(comanda, "set_band") == 0) {
			char *bandwidth = strtok(NULL, " \n");
			if (!bandwidth) {
				return -1;
			}
			SetBand(browser, atoi(bandwidth));
		} else if (strcmp(comanda, "wait") == 0) {
			char *sec = strtok(NULL, " \n");
			if (!sec) {
				return -1;
			}
			cod_returnat = Wait(browser, atoi(sec));
			if (cod_returnat == -1) {
				return -1;
			}
		}
	}
	fclose(fp_read);
	fclose(fp_write);
	return 0;
}