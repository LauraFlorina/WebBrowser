/* ȚĂLINĂ Laura-Florina - 314CB */
#include "pagina_web.h"
#include "utils/utils.h"

TWeb_page *InitPage(char *url) {
	TWeb_page *page = calloc(1, sizeof(TWeb_page));
	if (!page) {
		return NULL;
	}
	strcpy(page->url, url);
	int nr_resurse = 0;
	/* Se extrag resursele paginii */
	page->resources = get_page_resources(url, &nr_resurse);
	page->num_res = nr_resurse;
	return page;
}
