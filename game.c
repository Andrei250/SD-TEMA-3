#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 400000

// typedef struct child {
// struct child *next;
// struct node *nod;
// } child;

// typedef struct node {
// char **tablajoc;
// char color;
// int row;
// int column;
// struct child *children;
// } node;

typedef struct Node_2 {
	int valoare;
	// char nr_copii[10];
	// struct parent *parinte;
	struct copil *cop;
} Node_2;

// typedef struct parent {
// 	struct parent *next;
// 	struct Node_2 *nod;
// } Parent;

typedef struct copil {
	struct copil *next;
	struct Node_2 *nod;
} copil;

// void citire(char *nume_fisier, node *root, int *rows, int *columns,
// 	char *color1)
// {	
// 	int i;
// 	FILE *f;
// 	f = fopen(nume_fisier, "r");
// 	fscanf(f, "%d %d %c\n", rows, columns, color1);
// 	root->color = *color1;
// 	root->row = *rows;
// 	root->column = *columns;
// 	root->tablajoc = malloc(sizeof(char*) * (*rows));
// 	char buffer[*columns * 2 + 1];
// 	for (i = 1; i <= *rows; i++) {
// 		fgets(buffer, *columns * 2 + 1, f);
// 		if (buffer[strlen(buffer) - 1] == '\n')
// 			buffer[strlen(buffer) - 1] = '\0';
// 		root->tablajoc[i - 1] = strdup(buffer);
// 	}
// 	fclose(f);
// 	root->children = NULL;
// }

// void push_back(node *nodp, int p, int q)
// {
// 	int i, j;
// 	child *var;
// 	var = (child *)malloc(sizeof(child));
// 	var->nod = NULL;
// 	var->nod = (node *)malloc(sizeof(node));
// 	var->nod->row = nodp->row;
// 	var->nod->column = nodp->column;
// 	var->nod->children = NULL;
// 	var->nod->tablajoc = malloc(nodp->row * sizeof(char *));
// 	for (i = 0; i < nodp->row; i++)
// 		var->nod->tablajoc[i] = malloc(sizeof(char *) * nodp->column * 2);
// 	for (i = 0; i < nodp->row; i++)
// 		for (j = 0; j < nodp->column * 2; j++)
// 			var->nod->tablajoc[i][j] = nodp->tablajoc[i][j];
// 	var->nod->tablajoc[p][q] = nodp->color;
// 	if (nodp->color == 'R')
// 		var->nod->color = 'B';
// 	else
// 		var->nod->color = 'R';
// 	if (nodp->children == NULL) {
// 		nodp->children = var;
// 		var->next = NULL;
// 	}
// 	else {
// 		child *temp;
// 		temp = nodp->children;
// 		while (temp->next != NULL)
// 			temp = temp->next;
// 		temp->next = var;
// 		var->next = NULL;
// 	}
// }

// void creare_tree(node *nodp)
// {
// 	int i, j, k, q;
// 	for (i = 0; i < nodp->row; i++) {
// 		q = 1;
// 		j = 0;
// 		k = 0;
// 		while (j < nodp->column * 2) {
// 			if (j + 2 < nodp->column * 2 &&
// 				nodp->tablajoc[i][j] == nodp->tablajoc[i][j + 2] &&
// 				nodp->tablajoc[i][j] != '-' && nodp->tablajoc[i][j] != ' ')
// 				k++;
// 		 else if (j + 2 < nodp->column * 2 &&
// 		 	nodp->tablajoc[i][j] != nodp->tablajoc[i][j + 2])
// 			 k = 0;
// 			if (k == 3) {
// 				q = 0;
// 				break;
// 			}
// 			j++;
// 		}
// 		if (q == 0) {
// 			nodp->children = NULL;
// 			break;
// 		}
// 	}
// 	if (q == 1)
// 		for (j = 0; j < nodp->column * 2; j = j + 2) {
// 			i = 0;
// 			k = 0;
// 			while (i < nodp->row) {
// 				if (i + 1 < nodp->row &&
// 					nodp->tablajoc[i][j] == nodp->tablajoc[i + 1][j] &&
// 					nodp->tablajoc[i][j] != '-' &&
// 					nodp->tablajoc[i][j] != ' ')
// 					k++;
// 			  else if (i + 1 < nodp->row &&
// 			  	nodp->tablajoc[i][j] != nodp->tablajoc[i + 1][j])
// 					k = 0;
// 				if (k == 3) {
// 					q = 0;
// 					break;
// 				}
// 				i++;
// 			}
// 			if (q == 0) {
// 				nodp->children = NULL;
// 				break;
// 			}
// 		}
// 	if (q == 1) {
// 		for (i = 0; i < nodp->row; i++) {
// 			for (j = 0; j < nodp->column * 2; j = j + 2) {
// 				if (i + 1 < nodp->row && i + 2 < nodp->row &&
// 					i + 3 < nodp->row && j + 2 < nodp->column * 2 &&
// 					j + 4 < nodp->column * 2 && j + 6 < nodp->column * 2) {
// 						if (nodp->tablajoc[i][j] ==
// 							nodp->tablajoc[i + 1][j + 2] &&
// 							nodp->tablajoc[i + 1][j + 2] ==
// 							nodp->tablajoc[i + 2][j + 4] &&
// 							nodp->tablajoc[i + 2][j + 4] ==
// 							nodp->tablajoc[i + 3][j + 6] &&
// 							nodp->tablajoc[i][j] != '-' &&
// 							nodp->tablajoc[i][j] != ' ') {
// 						q = 0;
// 						break;
// 					}
// 				}
// 			}
// 			if (q == 0) {
// 				nodp->children = NULL;
// 				break;
// 			}
// 		}
// 	}
// 	if (q == 1) {
// 		for (i = 0; i < nodp->row; i++) {
// 			for (j = 0; j < nodp->column * 2; j = j + 2) {
// 				if (i + 1 < nodp->row && i + 2 < nodp->row &&
// 					i + 3 < nodp->row && j - 2 >= 0 &&
// 					j - 4 >= 0 && j - 6 >= 0) {
// 						if (nodp->tablajoc[i][j] ==
// 						nodp->tablajoc[i + 1][j - 2] &&
// 						nodp->tablajoc[i + 1][j - 2] ==
// 						nodp->tablajoc[i + 2][j - 4] &&
// 						nodp->tablajoc[i + 2][j - 4] ==
// 						nodp->tablajoc[i + 3][j - 6] &&
// 						nodp->tablajoc[i][j] != '-' &&
// 						nodp->tablajoc[i][j] != ' ') {
// 						q = 0;
// 						break;
// 					}
// 				}
// 			}
// 			if (q == 0) {
// 				nodp->children = NULL;
// 				break;
// 			}
// 		}
// 	}
// 	if (q == 1) {
// 		for (j = 0; j < nodp->column * 2; j = j + 2) {
// 			for (i = nodp->row - 1; i >= 0; i--) {
// 				if (nodp->tablajoc[i][j] == '-') {
// 					push_back(nodp, i, j);
// 					break;	
// 				}
// 			}
// 		}
// 	}
// 	child *copie;
// 	copie = nodp->children;
// 	while (copie) {
// 		creare_tree(copie->nod);
// 		copie = copie->next;
// 	}
// }

// void print(FILE *f, int n)
// {
// 	int i;
// 	for (i = 0; i < n; i++)
// 		fprintf(f, "\t");
// }

// void print_tree(FILE *f, node *parinte, int n)
// {
// 	int i, j;
// 	for (i = 0; i < parinte->row; i++) {
// 		for (j = 0; j < parinte->column * 2 - 1; j++)
// 			fprintf(f, "%c", parinte->tablajoc[i][j]);
// 		fprintf(f, "\n");
// 		if (i != parinte->row - 1)
// 			print(f, n);
// 	}
// 	child * copil = parinte->children;
// 	fprintf(f, "\n");
// 	n++;
// 	if (parinte->children == NULL)
// 		n--;
// 	else
// 		while (copil) {
// 			print(f, n);
// 			print_tree(f, copil->nod, n);
// 			copil = copil->next;
// 		}
// }

// void delete_tree(node *nodp)  
// {
// 	int i;
//     while (nodp->children != NULL) {
//     	child *copie;
// 		copie = nodp->children;
//     	delete_tree(nodp->children->nod); 
//     	nodp->children = nodp->children->next;
//     	free(copie);
// 	}
// 	for (i = 0; i < nodp->row; i++)
// 		free(nodp->tablajoc[i]);
// 	free(nodp->tablajoc);
//     free(nodp); 
// } 

void citire2(char *nume_fisier, char ***mat, int *h) {
	int i;
	FILE *f;
	f = fopen(nume_fisier, "r");
	fscanf(f, "%d\n", h);
	*mat = malloc ((*h + 2) * sizeof (char*)); 
	for (i = 0; i < *h; i++) {
		char buffer[MAX];
		fgets (buffer, MAX, f);
		buffer[strlen (buffer) - 1] = '\0';
		(*mat)[i] = strdup (buffer);
	}
}

void push_back2(copil *inceput, Node_2 *node)
{
	if (inceput->nod == NULL) {
		inceput->nod = (Node_2 *)malloc(sizeof(Node_2));
		inceput->nod = node;
		inceput->next = NULL;
	}
	else {
		copil *temp;
		temp = inceput;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = (copil *)malloc(sizeof(copil));
		temp->next->nod = (Node_2 *)malloc(sizeof(Node_2));
		temp->next->nod = node;
		temp->next->next = NULL;
	} 
}

int maxim(copil *cap)
{
	copil *temp;
	temp = cap;
	// int min = cap->nod->valoare;
	int max = cap->nod->valoare;
	// if (h % 2 == 0) {
	while (temp != NULL) {
		if (temp->nod->valoare > max)
			max = temp->nod->valoare;
		temp = temp->next;
	}
	return max;
	// }
}

int minim(copil *cap)
{
	copil *temp;
	temp = cap;
	int min = cap->nod->valoare;
	while (temp != NULL) {
		if (temp->nod->valoare < min)
			min = temp->nod->valoare;
		temp = temp->next;
	}
	return min;
}

// void minimax(char **mat, int h, Node_2 *nou2) {
// 	int p;
// 	int copie = h;
// 	for (p = 1; p < h; p++) {
// 		int i = 0;
// 		int nr1 = 0;
// 		int nr2 = 0;
// 		char *string1[MAX];
// 		char **mat1;
// 		int index;
// 		mat1 = (char **)malloc ((h + 2) * sizeof (char *));
// 		for (index = 0; index < h; index++)
// 			mat1[index] = strdup(mat[index]);
// 		// for (index = 0; index < h; index++) {
// 		// 	printf("%s", mat1[index]);
// 		// 	printf("\n");
// 		// }
// 		string1[0] = strdup(strtok(mat1[h - 2], " "));
// 		while (string1[i] != NULL) {
// 			i++;
// 			string1[i] = (strtok(NULL, " "));
// 		}
// 		nr1 = i;
// 		// printf("%d ", nr1);
// 		int j = 0;
// 		char *string2[MAX];
// 		string2[0] = strdup(strtok(mat1[h - 1], " "));
// 		while (string2[j] != NULL) {
// 			j++;
// 			string2[j] = strtok(NULL, " ");
// 		}
// 		nr2 = j;
// 		// printf("%d ", nr2);
// 		j = 0;
// 		for (i = 0; i < nr1; i++) {
// 			Node_2 *node;
// 			node = (Node_2 *)malloc(sizeof(Node_2));
// 			if (string1[i][0] == '[') {
// 				node->cop = NULL;
// 				char *a = strtok(string1[i], "[]");
// 				int m;
// 				m = atoi(a);
// 				node->valoare = m;
// 				// printf("%d %d ", node->valoare, h);
// 			}
// 			else {
// 				char *b = strtok(string1[i], "()");
// 				int c = atoi(b);
// 				int k = 0;
// 				copil *temp;
// 				temp = (copil *)malloc(sizeof(copil));
// 				temp->nod = (Node_2 *)malloc(sizeof(Node_2));
// 				char *d = strtok(string2[j], "[]");

// 				temp->nod->valoare = atoi(d);
// 				node->cop = temp;
// 				if (j == 0)
// 					j++;
// 				while (j < nr2 && k < c) {
// 					Node_2 *nou = malloc(sizeof(Node_2));
// 					nou->valoare = atoi(strtok(string2[j], "[]"));
// 					push_back2(temp, nou);
// 					if (j != c)
// 							j++;
// 					k++;
// 				}
// 				if (copie % 2 == 0)
// 					node->valoare = maxim(temp);
// 				else
// 					node->valoare = minim(temp);
// 				printf("%d ", node->valoare);
// 			}
// 			if (p == h - 1)
// 				nou2 = node;
// 		}
	
// 	char **mat2;
// 	copie--;
// 	mat2 = (char **)malloc((copie + 2) * sizeof (char *));
// 	int index1;
// 	for (index1 = 0; index1 < copie; index1++) {
// 		mat2[index1] = strdup(mat[index1]);
// 	}
// }
// }

void minimax(char **mat, int h, Node_2 *nou2)
{
	int nr2;
	int j = 0;
	int i;
	char *string[MAX];
	string[0] = strdup(strtok(mat[h - 1], " "));
	while (string[j] != NULL) {
		j++;
		string[j] = strtok(NULL, " ");
	}
	nr2 = j;
	j = 0;
	copil *lista;
	lista = (copil *)malloc(sizeof(copil));
	char *a = strtok(string[j], "[]");
	lista->nod = (Node_2 *)malloc(sizeof(Node_2));
	lista->nod->valoare = atoi(a);
	for (j = 1; j < nr2; j++) {
		Node_2 *node;
		node = (Node_2 *)malloc(sizeof(Node_2));
		char *a = strtok(string[j], "[]");
		node->valoare = atoi(a);
		push_back2(lista, node);
	}
	for (i = h - 2; i >= 0; i--) {
		char *string1[MAX], *w;
		w = (strtok(mat[i], " "));
		while (w) {
			j++;
			printf("%s\n", w);
			w = (strtok(NULL, " "));
			
		}
		copil *lista1;
		lista1 = (copil *)malloc(sizeof(copil));
		int nr1 = j;
		int p = 0;

		
		// for (j = 0; j < nr1; j++) {
		// 	// copil *lista1;
		// 	// lista1 = (copil *)malloc(sizeof(copil));
		// 	if (string1[j][0] == '[') {
		// 		Node_2 *node1;
		// 		node1 = (Node_2 *)malloc(sizeof(Node_2));
		// 		char *b = strtok(string1[j], "[]");
		// 		node1->valoare = atoi(b);
		// 		push_back2(lista1, node1);
		// 		node1->cop = NULL;
		// 	}
		// 	else {
		// 		int k = 0;
		// 		char *c = strtok(string1[j], "()");
		// 		Node_2 *node1;
		// 		node1 = (Node_2 *)malloc(sizeof(Node_2));
		// 		copil *lista2;
		// 		lista2 = (copil *)malloc(sizeof(copil));
		// 		while (k < atoi(c)) {
		// 			push_back2(lista2, lista->nod);
		// 			if (lista->next != NULL)
		// 				lista = lista->next;
		// 			k++;
		// 		}
		// 		node1->cop = lista2;
		// 		if (i % 2 == 0)
		// 			node1->valoare = maxim(lista2);
		// 		else
		// 			node1->valoare = minim(lista2);
		// 		push_back2(lista1, node1);

		// 	}
		// }
		lista = lista1;
		break;
	}
}

void print_minimax(Node_2 *parinte)
{
	// int i, j;
	// for (i = 0; i < parinte->row; i++) {
	// 	for (j = 0; j < parinte->column * 2 - 1; j++)
	// 		fprintf(f, "%c", parinte->tablajoc[i][j]);
	// 	fprintf(f, "\n");
	// 	if (i != parinte->row - 1)
	// 		print(f, n);
	// }
	copil * child2 = parinte->cop;
	// printf(f, "\n");
	// n++;
	if (parinte->cop == NULL)
	// 	n--;
		printf("%d ", parinte->valoare);
	else
		while (child2) {
			printf("%d", parinte->valoare);
			print_minimax(child2->nod);
			child2 = child2->next;
		}
}

int main(int argc, char *argv[])
{
	// node *nodp;
	// int rows, columns;
	// char color1;
	// nodp = (node *)malloc(sizeof(node));
	// citire (argv[2], nodp, &rows, &columns, &color1);
	// creare_tree(nodp);
	// FILE *f;
	// f = fopen(argv[3], "w");
	// print_tree(f, nodp, 0);
	// fclose(f);
	// delete_tree(nodp);
	int h;
	char **mat;
	citire2("test1.in", &mat, &h);

		// 	char **mat1;
		// int index;
		// 	mat1 = (char **)malloc ((h + 2) * sizeof (char *));
		// for (index = 0; index < h; index++)
		// 	mat1[index] = strdup(mat[index]);
		// for (index = 0; index < h; index++) {
		// 	printf("%s", mat1[index]);
		// 	printf("\n");
		// }
	// int i;
	// for (i = 0; i < h; i++) {
		// printf("%d", mat[2][0]);
	// 	printf("\n");
	// }
	// printf("%d", h);
	//char *string[20];
	//int a;
	// string[0] = strtok(mat[2], " ");
	// char *a;
	// a = strtok(string[0], "()");
	// printf("%s", a);
	// printf("%s", string[0]);
	// int i = 0;
	// int j;
	// int nr = 0;
	// char *string[MAX];
	// string[0] = strdup(strtok(mat[h - 2], " "));
	// while (string[i] != NULL) {
	// 	i++;
	// 	string[i] = strtok(NULL, " ");
	// }
	//nr = i;
	//for (j = 0; j < nr; j++)
		//printf("%c ", string[2][0]);
	// char *a;
	// a = strtok(string[2], "[]");
	// char b[10];
	// *b = 2;
	// int b;
	// b = atoi(a);

	// sprintf(b, "%d", 0);
	// printf("%s", b);
	Node_2 *nou2;
	nou2 = (Node_2 *)malloc(sizeof(Node_2));
	// nou2->valoare = 5;
	// Node_2 *nou3;
	// nou3 = (Node_2 *)malloc(sizeof(Node_2));
	// nou3->valoare = 7;
	// copil *hei;
	// hei = (copil *)malloc(sizeof(copil));
	// hei->nod = (Node_2 *)malloc(sizeof(Node_2));
	// hei->nod->valoare = 10;
	// hei->next = NULL;
	// Node_2 *nou4;
	// nou4 = (Node_2 *)malloc(sizeof(Node_2));
	// nou4->valoare = 12;
	// push_back2(hei, nou2);
	// printf("%d", hei->nod->valoare);
	// push_back2(hei, nou3);
	// push_back2(hei, nou4);
	minimax(mat, h, nou2);
	// print_minimax(nou2);
	// return 0;
	// int min = minim(hei);
	// int max = maxim(hei);
	// printf("%d %d", min, max);
	// copil *temp;
	// temp = hei;
	// while (temp != NULL) {
	// 	printf("%d ", temp->nod->valoare);
	// 	temp = temp->next;
	// }

}
