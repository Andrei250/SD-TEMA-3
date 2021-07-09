#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXIM (1 << 30)

typedef struct final {
	int value, cost1, cost2, Level, parent;
} final;

typedef struct Queue {
	int node;
	struct Queue *next;
} Queue;

//verific daca e ciclu
int checkForCycle(int from, int **Graph, int nod,
				int *visited, int *FStack, int N, int *number, int *top)
{

	visited[nod] = 1;
	FStack[nod] = 1;
	//Fstack este un vector care retine daca un nod se afla in
	//parcurgerea curenta DFS a grafului
	//daca un nod are legatura cu alt nod din parcurgerea curenta DFS
	//atunci formeaza ciclu si returnez 1
	//daca nu continui parcurgerea si de asemenea sortez
	//topologic graful

	for (int i = 1; i <= N; ++i)
		if (Graph[nod][i] && (i != nod)) {

			if (FStack[i])
				return 1;

			if (!visited[i]) {
				if (checkForCycle(nod, Graph, i, visited, FStack, N,
								&(*number), top))
					return 1;
			}
		}

	top[*number] = nod;
	*number = *number + 1;
	FStack[nod] = 0;
	return 0;
}

// LCA O(h) unde h e inaltimea arborelui partial BFS
//daca nodul 1 e pe un nivel mai mic schimb valorile
//pentru a calcula doar pentru nodul 1
int LCA(int node1, int node2, final *Vals)
{
	if (Vals[node1].Level < Vals[node2].Level) {
		int temp = node1;

		node1 = node2;
		node2 = temp;
	}

	//aduc nodurile pe acelasi nivel, deoarece daca sunt
	//pe niveluri diferite in arbore atunci stramosul comun
	//nu se afla intre ei
	while (node1 && Vals[node1].Level != Vals[node2].Level)
		node1 = Vals[node1].parent;

	//caut stramosul comun
	while (node1 && node1 != node2) {
		node1 = Vals[node1].parent;
		node2 = Vals[node2].parent;
	}

	return node1;
}

//formez costurile minime pentru fiecare nod
//astfel daca ajung dintr-un nod la alt nod care deja a fost
//parcurs verific daca pot modifica costul acestuia
//am parcurs un graf neorientat si am adunat in cost1 valoarea
//muchiei i , daca muchia i este orientata in graful initial in sensul
//ales si in cost2 valoare muchiei i daca a fost parcursa in sens invers
// valoare nodului este minimul dintre cele 2 costuri
void BFS(int *visited, int **Graph, int s, int N, final *Vals)
{
	Queue *Q = (Queue *)malloc(sizeof(Queue));

	Q->node = s;
	Q->next = NULL;
	Queue *END = Q;

	while (Q) {
		Queue *no = Q;

		Q = Q->next;
		int node = no->node;

		free(no);

		if (visited[node])
			continue;

		visited[node] = 1;
		int cost1 = Vals[node].cost1;
		int cost2 = Vals[node].cost2;
		int parent = Vals[node].parent;
		int nivel = Vals[node].Level;

		for (int i = 1; i <= N; ++i)
			if (i != node && !visited[i] && Graph[node][i] && i != parent) {
				int newcost1 = cost1;
				int newcost2 = cost2;

				if (Graph[node][i] < 0)
					newcost2 += ((-1) * Graph[node][i]);
				else if (Graph[node][i] > 0)
					newcost1 += Graph[node][i];

				Vals[i].cost1 = newcost1;
				Vals[i].cost2 = newcost2;
				Vals[i].Level = nivel + 1;
				Vals[i].parent = node;
				Queue *vertex = (Queue *)malloc(sizeof(Queue));

				vertex->node = i;
				vertex->next = NULL;

				if (Q == NULL) {
					Q = vertex;
					END = Q;
				} else {
					END->next = vertex;
					END = END->next;
				}
			} else if (i != node && visited[i] && Graph[node][i]) {
				//caut parintele comun
				//daca parintele este acelasi cu parintele nodului curent
				//atunci sar un pas pentru ca s-ar creea un infinite loop
				int parinte = LCA(node, i, Vals);

				if (!parinte || parinte == Vals[node].parent)
					continue;

				int newcost1 = cost1;
				int newcost2 = cost2;

				if (Graph[node][i] < 0)
					newcost2 += ((-1) * Graph[node][i]);
				else if (Graph[node][i] > 0)
					newcost1 += Graph[node][i];

				//scad costurile parintelui, deoarece fiecare nod are un cost
				//deja calculat de la parintele din arbore si doresc sa
				//calculez exact costul ciclului si sa aflu valoarea doar cu
				//muchiile din ciclu
				//tin cont ca in nodul i costurile se inverseaza fata de
				//nodul curent, deoarece a fost parcurs invers
				newcost1 -= (Vals[parinte].cost1);
				newcost2 -= (Vals[parinte].cost2);
				newcost1 += (Vals[i].cost2 - Vals[parinte].cost2);
				newcost2 += (Vals[i].cost1 - Vals[parinte].cost1);
				printf("%d %d %d %d %d %d %d %d\n",Graph[node][i], cost1, cost2, newcost1, newcost2, node, i, parinte);
				int minim = fmin(newcost1, newcost2);

				Vals[i].value = fmin(Vals[i].value, minim);
			}
	}
}

int main(void)
{
	FILE *fid = fopen("schimbare.in", "r");
	char string[50];

	//citesc numarul de noduri si muchii
	fgets(string, 50, fid);
	string[strlen(string) - 1] = '\0';
	char *p = strtok(string, " ");
	int N = atoi(p);

	p = strtok(NULL, " ");
	int M = atoi(p);
	int **Graph = (int **) malloc(sizeof(int *) * (N + 1));

	for (int i = 0; i <= N ; ++i)
		Graph[i] = (int *) calloc(N + 1, sizeof(int));

	int **Graph1 = (int **) malloc(sizeof(int *) * (N + 1));

	for (int i = 0; i <= N ; ++i)
		Graph1[i] = (int *) calloc(N + 1, sizeof(int));
	final Vals[N + 1];

	for (int i = 1; i <= N; ++i)
		Vals[i].value = Vals[i].cost1 = Vals[i].cost2 = MAXIM;

	//citesc muchiile
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
		Graph1[from][to] = cost;
		Graph[from][to] = cost;
		Graph[to][from] = -cost;
	}

	fclose(fid);
	int *visited, *FStack, *top;

	visited = (int *) calloc(N + 1, sizeof(int));
	FStack = (int *) calloc(N + 1, sizeof(int));
	top = (int *) calloc(N + 1, sizeof(int));

	int w = 0;
	int number = 1;

	//verific daca nu formeaza deja un ciclu
	for (int i = 1; i <= N && !w; ++i)
		if (!visited[i]) {
			int q = checkForCycle(-1, Graph1, i, visited, FStack,
								N, &number, top);
			if (q == 1)
				w = 1;
		}

	fid = fopen("schimbare.out", "w");

	//daca formeaza ciclu afisez 0
	if (w)
		fprintf(fid, "0\n");
	else {
		free(visited);
		visited = (int *) calloc(N + 1, sizeof(int));

		//formez un arbore partial BFS si caut valoarea minima in fiecare nod
		for (int i = 1; i <= N; ++i)
			if (!visited[top[i]]) {
				Vals[top[i]].cost1 = Vals[top[i]].cost2 = 0;
				Vals[top[i]].parent = 0;
				Vals[top[i]].Level = 0;
				BFS(visited, Graph, top[i], N, Vals);
			}

		int minim = MAXIM;

		for (int i = 1; i <= N; ++i)
			minim = fmin(minim, Vals[i].value);

		//daca nu pot forma un ciclu afisez -1 altfel afisez valoarea minima
		if (minim == MAXIM)
			fprintf(fid, "-1\n");
		else
			fprintf(fid, "%d\n", minim);
	}

	fclose(fid);
	free(visited);
	free(FStack);
	free(top);

	for (int i = 0; i <= N; ++i)
		free(Graph[i]);
	free(Graph);

	for (int i = 0; i <= N; ++i)
		free(Graph1[i]);
	free(Graph1);

	return 0;
}

