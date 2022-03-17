/* ȚĂLINĂ Laura-Florina - 314CB */
#include "stiva_f.h"

void* InitS(size_t d) {
	ASt s;
	s = malloc(sizeof(TStiva));
	if (!s) {
		return NULL;
	}
	s->dime = d;
	s->vf = NULL;
	return (void*)s;
}

int Push(void *s, void *ae) {
	ACelSt aux = malloc(sizeof(TCelSt));
	if (!aux) {
		return 0;
	}
	aux->info = malloc(((TStiva*)s)->dime);
	if (!aux->info) {
		return 0;
	}
	memcpy(aux->info, ae, ((TStiva*)s)->dime);
	aux->urm = ((TStiva*)s)->vf;
	((TStiva*)s)->vf = aux;
	return 1;
}

int VidaS(void *s) {
	if (((TStiva*)s)->vf == NULL) {
		return 1;
	}
	return 0;
}

int Pop(void *s, void *ae) {
	if (((TStiva*)s)->vf == NULL) {
		return -1;
	}
	memcpy(ae, ((TStiva*)s)->vf->info, ((TStiva*)s)->dime);
	ACelSt aux = ((TStiva*)s)->vf;
	((TStiva*)s)->vf = aux->urm;
	free(aux->info);
	free(aux);
	return 1;
}

void ResetS(void *s) {
	ACelSt l = ((TStiva*)s)->vf;
	while (l) {
		ACelSt aux = l;
		l = l->urm;
		free(aux);
	}
	((TStiva*)s)->vf = NULL;
}
