#ifndef __lista_H
#define __lista_H

typedef void (*fct_stergere)(void *);

typedef struct _nod {
	void *data;
	struct _nod *next;
} nod;

typedef struct {
	int lungime;
	int dim_elem;
	nod *p_nod_cap;
	fct_stergere fct_s;
} lista;

void creaza_l(lista *lista, int dim_elem, fct_stergere fct_s);
void sterge_l(lista *lista);
nod *adg_la_pos(lista *l, int poz, void *data);
void stg_la_pos(lista *l, int poz);

#endif
