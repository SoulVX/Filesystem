#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

void print_spaces(int nr)
{
	for (int i = 1; i <=  nr; i++)
		printf("    ");
}

void dezaloca_fis(void *f)
{
	free(((fisier *) f)->nume);
	free(((fisier *) f)->data);
}

void dezaloca_fld(void *f)
{
	free(((folder *) f)->nume);
	sterge_l(((folder *) f)->foldere);
	sterge_l(((folder *) f)->fisiere);
}

void ins_ord_fld(lista *l,  folder *f)
{
	nod *iterator  =  l->p_nod_cap;
	int poz = 1;

	while (iterator) {
		if (strcmp(((folder *) iterator->data)->nume,  f->nume)  ==  0)
			return;
		if (strcmp(((folder *) iterator->data)->nume,  f->nume) > 0)
			break;
		iterator  =  iterator->next;
		poz++;
	}
	if (!iterator)
		adg_la_pos(l,  l->lungime+1,  f);
	else
		adg_la_pos(l,  poz,  f);
}

void ins_ord_fis(lista *l,  fisier *f)
{
	nod *iterator  =  l->p_nod_cap;
	int poz = 1;

	while (iterator) {
		if (strcmp(((fisier *) iterator->data)->nume,  f->nume) > 0)
			break;
		iterator  =  iterator->next;
		poz++;
	}
	if (!iterator)
		adg_la_pos(l,  l->lungime+1,  f);
	else
		adg_la_pos(l,  poz,  f);
}

fisier *creaza_fis(folder *folder_curent,  char *filename,  char *content)
{
	fisier *fis  =  malloc(sizeof(fisier));

	fis->nume  =  strdup(filename);
	if (content != NULL)
		fis->data  =  strdup(content);
	else
		fis->data  =  NULL;
	fis->folder  =  folder_curent;
	if (content != NULL)
		fis->dim = strlen(content);
	else
		fis->dim = 0;
	return fis;
}

folder *creaza_fld(folder *fd_parinte,  char *nume)
{

	folder *fd  =  malloc(sizeof(folder));

	fd->nume  =  strdup(nume);
	fd->parinte  =  fd_parinte;

	lista *fisiere  =  malloc(sizeof(lista));

	creaza_l(fisiere,  sizeof(fisier),  dezaloca_fis);
	fd->fisiere  =  fisiere;

	lista *foldere  =  malloc(sizeof(lista));

	creaza_l(foldere,  sizeof(folder),  dezaloca_fld);
	fd->foldere  =  foldere;

	return fd;
}

folder *mkdir(folder *folder_curent,  char *nume)
{
	folder *fd  =  creaza_fld(folder_curent, nume);

	if (folder_curent)
		ins_ord_fld(folder_curent->foldere, fd);

	return fd;
}

fisier *touch(folder *folder_curent,  char *filename,  char *content)
{
	fisier *fis  =  creaza_fis(folder_curent,  filename, content);

	ins_ord_fis(folder_curent->fisiere,  fis);
	return fis;
}

void ls(folder *f)
{
	nod *iterator1  =  f->fisiere->p_nod_cap;

	while (iterator1) {
		printf("%s ",  ((fisier *) iterator1->data)->nume);
		iterator1  =  iterator1->next;
	}
	nod *iterator2  =  f->foldere->p_nod_cap;

	while (iterator2) {
		printf("%s ",  ((folder *) iterator2->data)->nume);
		iterator2  =  iterator2->next;
	}
	printf("\n");
}

void pwd(folder *f)
{

	if (strcmp(f->nume, "/") == 0) {
		printf("/\n");
		return;
	}

	int l = 1;
	char cale[100][100];

	 strcpy(cale[0], f->nume);

	folder *iterator  =  f->parinte;

	while (iterator) {
		strcpy(cale[l++],  iterator->nume);
		iterator  =  iterator->parinte;
	}

	for (int i = l-2 ; i >=  0 ; i--)
		printf("/%s",  cale[i]);
	printf("\n");
}

folder *cd(folder *f,  char *nume_fd_nou)
{

	if (strcmp(nume_fd_nou, "..") == 0) {
		if (f->parinte)
			return f->parinte;
		else
			return f;
	}

	nod *iterator  =  f->foldere->p_nod_cap;

	while (iterator) {
		if (strcmp(((folder *)iterator->data)->nume, nume_fd_nou) == 0)
			return (((folder *) iterator->data));
		iterator  =  iterator->next;
	}
	printf("Cannot move to '%s': No such directory!\n", nume_fd_nou);
	return f;
}

void tree(folder *f,  int nr)
{
	print_spaces(nr);
	if (nr == 0) {
		if (strcmp(f->nume, "/")  ==  0)
			printf("%s\n",  f->nume);
		else
			printf("%s\n",  f->nume);
	} else
		printf("%s\n",  f->nume);
	nod *iterator  =  f->fisiere->p_nod_cap;

	while (iterator) {
		print_spaces(nr+1);
		printf("%s\n",  ((fisier *) iterator->data)->nume);
		iterator  =  iterator->next;
	}
	iterator  =  f->foldere->p_nod_cap;
	while (iterator) {
		tree((folder *) iterator->data,  nr+1);
		iterator  =  iterator->next;
	}
}

void rm(folder *f,  char *nume_fis)
{
	nod *iterator  =  f->fisiere->p_nod_cap;
	int poz = 1;

	while (iterator) {
		if (strcmp(((fisier *) iterator->data)->nume, nume_fis) == 0) {
			free(((fisier *) iterator->data)->nume);
			free(((fisier *) iterator->data)->data);
			stg_la_pos(f->fisiere,  poz);
			return;
		}
		iterator  =  iterator->next;
		poz++;
	}
	printf("Cannot remove '%s': No such file!\n", nume_fis);
}

void rmdir(folder *f,  char *nume_fld)
{
	nod *iterator  =  f->foldere->p_nod_cap;
	int poz = 1;

	while (iterator) {
		if (strcmp(((folder *) iterator->data)->nume, nume_fld) == 0) {
			free(((folder *) iterator->data)->nume);
			sterge_l(((folder *) iterator->data)->foldere);
			sterge_l(((folder *) iterator->data)->fisiere);
			stg_la_pos(f->foldere,  poz);
			return;
		}
		iterator  =  iterator->next;
		poz++;
	}
	printf("Cannot remove '%s': No such directory!\n", nume_fld);
}

void find(folder *f, int am, int m, int M, char *x,  int ac)
{
	if (ac <=  am) {
		nod *i  =  f->fisiere->p_nod_cap;
		char *D, *L; int z;

		while (i) {
			D = ((fisier *) i->data)->data;
			z = ((fisier *) i->data)->dim;
			L = ((fisier *) i->data)->nume;
			if (D !=  NULL) {
				if (strstr(D, x) != NULL && z <= M && z >= m)
					printf("%s ", L);
			}
			i  =  i->next;
		}
		if (ac < am) {
			nod *it  =  f->foldere->p_nod_cap;

			while (it) {
				find(((folder *)it->data), am, m, M, x, ac+1);
				it  =  it->next;
			}
		}
	}
}
