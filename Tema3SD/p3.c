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
	int node;
	struct Muchie *next;
} Muchie;

typedef struct final {
	int *from;
	int capacity, value, untilNow;
} final;

void check(int *V, final Back[], int current, int start)
{
	V[current]++;

	if (current == start)
		return;

	for (int i = 0; i < Back[current].untilNow; ++i)
		check(V, Back, Back[current].from[i], start);
}

//BFS in care am facut drumul minim si am retinut pentru fiecare nod
// din ce parinti ar putea veni drumul minim in caz ca sunt mai multe.
//Apoi am folosit un vector de aparitii ca sa verific ce noduri
//se afla pe toate drumurile minime.
//Astfel de la final spre inceput am luat in calcul toate nodurile pana
//la primul nod care avea mai mult de 1 parinte, deoarece aceste noduri
//se aflau pe toate drumurile minime.
//Apoi am numarat de cate ori apare fiecare nod in celalalte drumuri,
//iar urmatoarele noduri luate in calcul au fost cele care apar de atatea
//ori de cate ori apare si nodul initial.
void BFS(FILE *fid2, int N, int start, int stop, Muchie * Graph[])
{
	Queue *Q = (Queue *)malloc(sizeof(Queue));

	Q->current = start;
	Q->next = NULL;
	Queue *END = Q;
	int *Values = calloc(N + 1, sizeof(int));
	final GoBack[N + 1];

	for (int i = 1; i <= N; ++i) {
		GoBack[i].value = MAXIM;
		GoBack[i].capacity = 50;
		GoBack[i].from = (int *) malloc(sizeof(int) * 50);
		GoBack[i].untilNow = 0;
	}

	GoBack[start].value = 0;

	//Creez drumurile minime si listele de parinti
	while (Q) {
		Queue *nod = Q;

		Q = Q->next;
		int current = nod->current;
		Muchie *copie = Graph[current];

		free(nod);

		while (copie) {
			int to = copie->node;

			copie = copie->next;

			if (GoBack[current].value + 1 < GoBack[to].value) {
				GoBack[to].value = GoBack[current].value + 1;
				GoBack[to].untilNow = 1;
				GoBack[to].from[0] = current;
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
			} else if (GoBack[current].value + 1 == GoBack[to].value) {
				GoBack[to].untilNow++;

				if (GoBack[to].untilNow == GoBack[to].capacity) {
					GoBack[to].capacity *= 2;
					GoBack[to].from = realloc(GoBack[to].from,
										sizeof(int) * GoBack[to].capacity);
				}
				GoBack[to].from[GoBack[to].untilNow - 1] = current;
			}

		}
	}

	//Daca nu se ajunge la final nu exista drum
	if (GoBack[stop].value == MAXIM) {
		fprintf(fid2, "0\n");
		free(Values);

		for (int i = 1; i <= N; ++i)
			free(GoBack[i].from);
		return;
	}

	int ans[N + 1], w = 0;

	ans[w++] = stop;

	//toate nodurile pana la primul care are mai mult
	//de 1 parinte sunt bagati in sir
	while (GoBack[stop].untilNow == 1 && stop != start) {
		stop = GoBack[stop].from[0];
		ans[w++] = stop;
	}

	//aflu de cate ori apare fiecare nod din cele ramase
	//in toate drumurile
	check(Values, GoBack, stop, start);

	//nodurile cu valoarea egala cu nodul start sunt bagate in sir
	int value = Values[start];

	for (int i = 1; i <= N && start != stop; ++i)
		if (Values[i] == value)
			ans[w++] = i;

	//le sortez
	for (int i = 0; i < w - 1; ++i)
		for (int j = i + 1; j < w; ++j)
			if (ans[i] > ans[j]) {
				int temp = ans[i];

				ans[i] = ans[j];
				ans[j] = temp;
			}

	fprintf(fid2, "%d ", w);

	for (int i = 0; i < w; ++i)
		fprintf(fid2, "%d ", ans[i]);

	fprintf(fid2, "\n");
	free(Values);
	for (int i = 1; i <= N; ++i)
		free(GoBack[i].from);
}

int main(void)
{
	FILE *fid = fopen("drumuri.in", "r");
	char string[50];

	//Am citit N, M, Q
	fgets(string, 50, fid);
	string[strlen(string) - 1] = '\0';
	char *p = strtok(string, " ");
	int N = atoi(p);

	p = strtok(NULL, " ");
	int M = atoi(p);

	p = strtok(NULL, " ");
	int Q = atoi(p);

	Muchie *Graph[N + 1];

	for (int i = 1; i <= N; ++i)
		Graph[i] = NULL;

	//Am citit muchiile si le-am lus in lista
	for (int i = 0; i < M; ++i) {
		fgets(string, 50, fid);

		if (string[strlen(string) - 1] == '\n')
			string[strlen(string) - 1] = '\0';

		int  from, to;

		p = strtok(string, " ");
		from = atoi(p);
		p = strtok(NULL, " ");
		to = atoi(p);

		Muchie *nod = (Muchie *) malloc(sizeof(Muchie));

		nod->node = to;

		if (Graph[from] == NULL) {
			Graph[from] = nod;
			nod->next = NULL;
		} else {
			nod->next = Graph[from];
			Graph[from] = nod;
		}

		Muchie *nod1 = (Muchie *) malloc(sizeof(Muchie));

		nod1->node = from;

		if (Graph[to] == NULL) {
			Graph[to] = nod1;
			nod1->next = NULL;
		} else {
			nod1->next = Graph[to];
			Graph[to] = nod1;
		}
	}

	FILE *fid2 = fopen("drumuri.out", "w");

	//pentru fiecare pereche de noduri am facut BFS
	for (int i = 0; i < Q; ++i) {
		int start, stop;

		fscanf(fid, "%d %d", &start, &stop);
		BFS(fid2, N, start, stop, Graph);
	}

	fclose(fid2);
	fclose(fid);

	for (int i = 1 ; i <= N; ++i) {
		while (Graph[i]) {
			Muchie *copy = Graph[i];

			Graph[i] = Graph[i]->next;
			free(copy);
		}
	}

	return 0;
}

