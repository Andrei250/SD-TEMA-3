#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXIM (1 << 30)

typedef struct Queue {
	struct Queue *next;
	int i, j;
	int pas;
} Queue;

//Pentru fiecare pozitie am retinut ce mutare urmeaza sa fie.
//De exemplu pentru pozitia de inceput urmeaza mutarea 1 care genereaza
//mai multe noduri care au fiecare mutarea 2.
//Ideea algoritmului este e a baga in coada nodurile care nu au o valoare
//mai mare decat valoare curenta + 1. Daca acele noduri au valoare mai mare
//inseamna ca deja s-a mai trecut pe acolo si ca nu mai este nevoie sa
//se continue in acea parte. Astfel algoritmul este optimizat pentru a nu
//face pasi inutili care sa il ingreuneze.
void BFS(int Mat[][101], int Places[], int N, int M, int K, int s, int e)
{
	Queue *Q = (Queue *) malloc(sizeof(Queue));
	Queue *End = Q;

	Q->next = NULL;
	Q->i = s;
	Q->j = e;
	Q->pas = 1;
	short dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};


	while (Q) {
		Queue *copie = Q;

		Q = Q->next;

		//sar peste acest pas daca este un nod terminal
		if (copie->pas > K) {
			free(copie);
			continue;
		}

		int pas = copie->pas;
		int i = copie->i + dx[Places[pas]];
		int j = copie->j + dy[Places[pas]];

		free(copie);

		//bag in matrice toate nodurile pana la acel nod prin care s-a mai
		//trecut deja
		while (i >= 1 && j >= 1 && i <= N && j <= M &&
			Mat[i][j] != -1 && pas <= K && pas + 1 > Mat[i][j]) {

			Queue *node = (Queue *) malloc(sizeof(Queue));

			node->i = i;
			node->j = j;
			node->pas = pas + 1;
			node->next = NULL;
			Mat[i][j] = pas + 1;

			if (Q == NULL) {
				Q = node;
				End = Q;
			} else {
				End->next = node;
				End = End->next;
			}

			i = i + dx[Places[pas]];
			j = j + dy[Places[pas]];
		}
	}

	int counter = 0;

	//numar nodurile terminale care au valoarea K + 1
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			if (Mat[i][j] == K + 1)
				counter++;

	FILE *fid2 = fopen("labirint.out", "w");

	fprintf(fid2, "%d\n", counter);
	fclose(fid2);
}

int main(void)
{
	int N, M, K, startD, stopD;
	int Matrix[101][101];
	FILE *fid = fopen("labirint.in", "r");

	fscanf(fid, "%d %d %d", &N, &M, &K);

	//Am citit matricea
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			fscanf(fid, "%d", &Matrix[i][j]);

			if (Matrix[i][j] == 2) {
				startD = i;
				stopD = j;
				Matrix[i][j] = 0;
			} else if (Matrix[i][j] == 1)
				Matrix[i][j] = -1;
		}
	}

	int Places[K + 1];

	//Citesc directiile in care merge
	for (int i = 1; i <= K; ++i)
		fscanf(fid, "%d", &Places[i]);

	fclose(fid);

	//rezolv taskul cu un algoritm de tip BFS
	BFS(Matrix, Places, N, M, K, startD, stopD);

	return 0;
}

