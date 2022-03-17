/* ȚĂLINĂ Laura-Florina - 314CB */
#include "coada_f.h"

void* InitQ(size_t d) {
	AQ c;
	c = malloc(sizeof(TCoada));
	if (!c) {
		return NULL;
	}
	c->dime = d;
	c->ic = NULL;
	c->sc = NULL;
	return (void*)c;
}

int IntrQ(void *c, void *ae) {
	AC aux = malloc(sizeof(TCel));
	if (!aux) {
		return 0;
	}
	aux->info = malloc((DIME(c)));
	if (!aux->info) {
		return 0;
	}
	memcpy(aux->info, ae, DIME(c));
	if (!VIDA(c)) {
		aux->urm = NULL;
		((AQ)c)->sc->urm = aux;
		((AQ)c)->sc = aux;
	} else {
		aux->urm = NULL;
		((AQ)c)->ic = aux;
		((AQ)c)->sc = aux;
	}
	return 1;
}

int ExtrQ(void *c, void *ae) {
	AC aux =  calloc(1, sizeof(TCel));
	if (!aux) {
		return 0;
	}
	aux = ((AQ)c)->ic;
	((AQ)c)->ic = aux->urm;
	memcpy(ae, aux->info, DIME(c));
	free(aux->info);
	free(aux);
	/* cazul in care se face extragere dintr-o coada cu un singur element */
	if (((AQ)c)->ic == NULL) {
		((AQ)c)->sc = NULL;
	}
	return 1;
}

int VidaQ(void *c) {
	if (VIDA((AQ)c)) {
		return 1;
	}
	return 0;
}

int ConcatQ(void *d, void *s) {
	if (VIDA(d)) {
		((AQ)d)->ic = ((AQ)s)->ic;
		((AQ)d)->sc = ((AQ)s)->sc;
		((AQ)s)->ic = ((AQ)s)->sc = NULL;
	}
	if (VIDA(s)) {
		return -1; /* sursa e vida */
	}
	if (!VIDA(s) && !VIDA(d)) {
		((AQ)d)->sc->urm = ((AQ)s)->ic;
		((AQ)d)->sc = ((AQ)s)->sc;
		((AQ)s)->ic = ((AQ)s)->sc = NULL;
	}
	return 1;
}