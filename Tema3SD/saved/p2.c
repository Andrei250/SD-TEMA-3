#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXIM (1 << 30)

typedef struct Queue {
	struct Queue *next;
	int current;
} Queue;

typedef struct Muchie {
	int node, value;
	struct Muchie *next;
} Muchie;

typedef struct final {
	int from;
	int value;
} final;

//Algoritmul lui Dijkstra pe acelasi principiu ca BFS
//Queue implementat dinamic
//Am bagat initial in coada toti reprezentantii
// La fiecare pas verific daca nodul a fost vizat sau nu
// Daca nu a fost vizat dar un alt reprezentant se afla mai aptoape
// modific valoarea din nodul respectiv si reprezentantul sau
void BFS(FILE *fid, final Vals[], int N, int K, Muchie * Graph[])
{
	Queue *Q = NULL;
	Queue *END = Q;

	for (int i = 0; i < K; ++i) {
		int nr;

		fscanf(fid, "%d", &nr);
		Vals[nr].value = 0;
		Vals[nr].from = nr;
		Queue *nod = malloc(sizeof(Queue));

		nod->current = nr;
		nod->next = NULL;

		if (Q == NULL) {
			Q = nod;
			END = Q;
		} else {
			END->next = nod;
			END = END->next;
		}
	}

	while (Q) {
		Queue *nod = Q;

		Q = Q->next;
		int current = nod->current;

		Muchie *copie = Graph[current];

		free(nod);

		while (copie) {
			int to = copie->node;
			int cost = copie->value;

			copie = copie->next;

			// daca nu a fost vizat sau daca are o valoare mai buna
			if (Vals[current].value + cost < Vals[to].value) {
				Vals[to].value = Vals[current].value + cost;
				Vals[to].from = Vals[current].from;
				Queue *nod = malloc(sizeof(Queue));

				nod->current = to;
				nod->next = NULL;

				if (Q == NULL) {
					Q = nod;
					END = Q;
				} else {
					END->next = nod;
					END = END->next;
				}
			} else if (Vals[current].value + cost == Vals[to].value &&
					Vals[to].from > Vals[current].from) {
				//Daca are aceeasi valoare, dar este un reprezentant
				//cu index mai mic
				Vals[to].from = Vals[current].from;
				Queue *nod = malloc(sizeof(Queue));

				nod->current = to;
				nod->next = NULL;

				if (Q == NULL) {
					Q = nod;
					END = Q;
				} else {
					END->next = nod;
					END = END->next;
				}
			}
		}
	}
}

int main(void)
{
	FILE *fid = fopen("reprezentanti.in", "r");
	char string[50];

	//citesc N, M si K
	fgets(string, 50, fid);
	string[strlen(string) - 1] = '\0';
	char *p = strtok(string, " ");
	int N = atoi(p);

	p = strtok(NULL, " ");
	int M = atoi(p);

	p = strtok(NULL, " ");
	int K = atoi(p);

	Muchie *Graph[N + 2];
	final Noduri[N + 2];

	for (int i = 1; i <= N; ++i) {
		Noduri[i].value = MAXIM;
		Graph[i] = NULL;
	}

	//citesc muchiile si formez graful orientat
	for (int i = 0; i < M; ++i) {
		fgets(string, 50, fid);

		if (string[strlen(string) - 1] == '\n')
			string[strlen(string) - 1] = '\0';

		int  from, to, cost;

		p = strtok(string, " ");
		from = atoi(p);
		p = strtok(NULL, " ");
		to = atoi(p);
		p = strtok(NULL, " ");
		cost = atoi(p);

		Muchie *nod = (Muchie *) malloc(sizeof(Muchie));

		nod->value = cost;
		nod->node = to;

		if (Graph[from] == NULL) {
			Graph[from] = nod;
			nod->next = NULL;
		} else {
			nod->next = Graph[from];
			Graph[from] = nod;
		}

		Muchie *nod1 = (Muchie *) malloc(sizeof(Muchie));

		nod1->value = cost;
		nod1->node = from;

		if (Graph[to] == NULL) {
			Graph[to] = nod1;
			nod1->next = NULL;
		} else {
			nod1->next = Graph[to];
			Graph[to] = nod1;
		}
	}

	//faci Dijkstra O(N^2)
	BFS(fid, Noduri, N, K, Graph);
	fclose(fid);
	fid = fopen("reprezentanti.out", "w");

	//Daca in nodul respectiv nu s-a ajuns afisez -1
	//altfel afisez reprezentantul si valoarea
	for (int i = 1; i <= N; ++i)
		if (Noduri[i].value != MAXIM)
			fprintf(fid, "%d %d\n", Noduri[i].from, Noduri[i].value);
		else
			fprintf(fid, "-1\n");

	for (int i = 1 ; i <= N; ++i) {
		while (Graph[i]) {
			Muchie *copy = Graph[i];

			Graph[i] = Graph[i]->next;
			free(copy);
		}
	}

	fclose(fid);

	return 0;
}

