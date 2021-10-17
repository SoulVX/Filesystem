#include <stdlib.h>
#include <string.h>

#include "list.h"

void creaza_l(lista *lista,  int dim_elem,  fct_stergere fct_s)
{
	lista->lungime = 0;
	lista->dim_elem = dim_elem;
	lista->p_nod_cap = NULL;
	lista->fct_s = fct_s;
}

void sterge_l(lista *lista)
{
	nod *p_nod_curent;

	while (lista->p_nod_cap != NULL) {
		p_nod_curent = lista->p_nod_cap;
		lista->p_nod_cap = p_nod_curent->next;
		if (lista->fct_s)
			lista->fct_s(p_nod_curent->data);
		free(p_nod_curent->data);
		free(p_nod_curent);
	}
	free(lista);
}

nod *adg_la_pos(lista *l, int poz,  void *data)
{
	nod *p_nod_nou = malloc(sizeof(nod));

	p_nod_nou->data = malloc(l->dim_elem);
	memcpy(p_nod_nou->data,  data,  l->dim_elem);
	free(data);

	if (poz == 1) {
		p_nod_nou->next = l->p_nod_cap;
		l->p_nod_cap = p_nod_nou;
	} else {
		nod *it = l->p_nod_cap;

		int poz_it = 1;

		while (poz_it != poz-1) {
			poz_it++;
			it = it->next;
		}
		p_nod_nou->next = it->next;
		it->next = p_nod_nou;
	}
	l->lungime++;
	return p_nod_nou;
}

void stg_la_pos(lista *l, int poz)
{
	nod *tmp;

	if (poz == 1) {
		tmp = l->p_nod_cap;
		l->p_nod_cap = l->p_nod_cap->next;
		free(tmp->data);
		free(tmp);
	} else {
		nod *it = l->p_nod_cap;
		int poz_it = 1;

		while (poz_it != poz-1) {
			poz_it++;
			it = it->next;
		}
		tmp = it->next;
		it->next = it->next->next;
		free(tmp->data);
		free(tmp);
	}
	l->lungime--;
}
