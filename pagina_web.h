/* ȚĂLINĂ Laura-Florina - 314CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/utils.h"

#ifndef _WEB_PAGE_
#define _WEB_PAGE_

typedef struct{
	char url[21];
	unsigned int num_res;
	Resource *resources;
} TWeb_page;

/* Functie care initializeaza un element de tip TWebPage,
folosindu-se de functia "get_page_resources" */
TWeb_page *InitPage();

#endif /* _WEB_PAGE_ */