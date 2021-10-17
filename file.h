#include "list.h"
#ifndef __FILE_H__
#define __FILE_H__

typedef struct folder {
	char *nume;
	lista *fisiere;
	lista *foldere;
	struct folder *parinte;
} folder;

typedef struct fisier {
	char *nume;
	int dim;
	char *data;
	folder *folder;
} fisier;

void print_spaces(int nr);
void dezaloca_fis(void *f);
void dezaloca_fld(void *f);
void ins_ord_fis(lista *l, fisier *f);
void ins_ord_fld(lista *l, folder *f);
fisier *creaza_fis(folder *folder_curent, char *filename, char *content);
folder *creaza_fld(folder *fd_parinte, char *nume);

folder *mkdir(folder *folder_curent, char *nume);
fisier *touch(folder *folder_curent, char *filename, char *content);
void ls(folder *f);
void pwd(folder *f);
folder *cd(folder *f, char *nume_fd_nou);
void tree(folder *f, int nr);
void rm(folder *f, char *nume_fis);
void rmdir(folder *f, char *nume_fld);
void find(folder *f, int ad_max, int min, int max, char *subcnt, int ad_cur);

#endif
