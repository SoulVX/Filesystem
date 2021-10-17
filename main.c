#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "file.h"

void citeste_input(char *input)
{
	fgets(input, 100, stdin);
	char *pos = strchr(input,  '\n');
	*pos = '\0';
}

int main(void)
{

	char *input,  *copy,  *token;

	input = malloc(100*sizeof(char)); copy = malloc(100*sizeof(char));
	folder *folder_curent, *folder_radacina;

	char nume[100], content[100], a1[100], a2[100];

	citeste_input(input);

	while (strcmp(input, "create fs") != 0)
		citeste_input(input);

	folder_radacina = mkdir(NULL, "/");
	folder_curent = folder_radacina;

	while (strcmp(input, "delete fs") != 0) {

		citeste_input(input);
		strcpy(copy, input);

		token = strtok(copy,  " ");

		if (strcmp(token, "touch") == 0) {

			token = strtok(NULL,  " ");
			strcpy(nume, token);

			token = strtok(NULL,  " ");
			if (token == NULL) {
				touch(folder_curent, nume, NULL);
			} else {
				strcpy(content, token);
				touch(folder_curent, nume, content);
			}

		}

		else if (strcmp(token, "ls") == 0) {

			ls(folder_curent);

		}

		else if (strcmp(token, "mkdir") == 0) {

			token = strtok(NULL,  " ");
			strcpy(nume, token);

			mkdir(folder_curent, nume);

		}

		else if (strcmp(token, "pwd") == 0) {

			pwd(folder_curent);

		}

		else if (strcmp(token, "cd") == 0) {

			token = strtok(NULL,  " ");
			strcpy(nume, token);

			folder_curent = cd(folder_curent, nume);

		}

		else if (strcmp(token, "tree") == 0) {

			tree(folder_curent, 0);

		}

		else if (strcmp(token, "rm") == 0) {

			token = strtok(NULL,  " ");
			strcpy(nume, token);

			rm(folder_curent, nume);

		}

		else if (strcmp(token, "rmdir") == 0) {

			token = strtok(NULL,  " ");
			strcpy(nume, token);

			rmdir(folder_curent, nume);

		}

		else if (strcmp(token, "find") == 0) {

			token = strtok(NULL,  " ");
			strcpy(nume, token);

			token = strtok(NULL,  " ");
			strcpy(content, token);

			token = strtok(NULL,  " ");
			strcpy(a1, token);

			token = strtok(NULL,  " ");
			strcpy(a2, token);

			int a, b, c;

			a = atoi(nume);
			b = atoi(content);
			c = atoi(a1);

			find(folder_curent, a, b, c, a2, 0);

			printf("\n");

		}

	}

	free(input); free(copy);
	sterge_l(folder_radacina->fisiere);
	sterge_l(folder_radacina->foldere);
	free(folder_radacina->nume);
	free(folder_radacina);
}
