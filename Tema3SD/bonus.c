#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXIM (1 << 30)

typedef struct Muchie {
	int node, value, numar;
	struct Muchie *next;
} Muchie;

typedef struct nod {
	int value, Level, parent, muchia;
} nod;

typedef struct muc {
	int cost, from, to, number;
} muc;

typedef struct unionByRank {
	int parent, rank;
} unionByRank;

//LCA O(h) unde h este inaltimea arborelui care returneaza
//muchiar cu valoare maxima de pe drumul respectiv
int LCA(nod *Nodes, int node1, int node2, int Muchii[])
{
	if (Nodes[node1].Level < Nodes[node2].Level) {
		int temp = node1;

		node1 = node2;
		node2 = temp;
	}

	int maxim = Muchii[Nodes[node1].muchia];

	while (node1 != 1 && Nodes[node1].Level != Nodes[node2].Level) {
		maxim = fmax(maxim, Muchii[Nodes[node1].muchia]);
		node1 = Nodes[node1].parent;
	}

	while (node1 != 1 && node1 != node2) {
		maxim = fmax(maxim, Muchii[Nodes[node1].muchia]);
		maxim = fmax(maxim, Muchii[Nodes[node2].muchia]);
		node1 = Nodes[node1].parent;
		node2 = Nodes[node2].parent;
	}

	return maxim;
}

//DFS pentru a forma legaturile dintre noduri dupa ce au fost
//selectate muchiile din algoritmul lui Kruskal.
//Astfel aflu ce muchie intra in fiecare nod si care este parintele sau
void DFS(int *visited, int node, int *checkedEdges, int muchia,
		nod Vals[], Muchie * Graph[], int Lvl, int parinte)
{
	visited[node] = 1;
	Vals[node].Level = Lvl;
	Vals[node].parent = parinte;
	Vals[node].muchia = muchia;

	Muchie *copie = Graph[node];

	while (copie) {
		int to = copie->node;
		int nr = copie->numar;

		if (checkedEdges[nr] && !visited[to])
			DFS(visited, to, checkedEdges, nr, Vals, Graph,
				Lvl + 1, node);

		copie = copie->next;
	}
}

//Caut root-ul unui nod din uniune
int rootSearch(unionByRank *componente, int value)
{
	if (componente[value].parent != value)
		return rootSearch(componente, componente[value].parent);
	return value;
}

//functie de comparare pentru qsort
int cmp(const void *a, const void *b)
{
	return ((*(muc *)a).cost - (*(muc *)b).cost);
}

int main(void)
{
	FILE *fid = fopen("bonus.in", "r");
	char string[50];

	fgets(string, 50, fid);
	string[strlen(string) - 1] = '\0';
	char *p = strtok(string, " ");
	int N = atoi(p);

	p = strtok(NULL, " ");
	int M = atoi(p);

	p = strtok(NULL, " ");
	int K = atoi(p);

	Muchie *Graph[N + 1];

	for (int i = 1; i <= N; ++i)
		Graph[i] = NULL;

	muc Muchii[M + 1];
	int savedEdges[M + 1];
	int checkedEdges[M + 1];

	for (int i = 1; i <= M; ++i) {
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
		Muchii[i].cost = cost;
		Muchii[i].number = i;
		Muchii[i].from = from;
		Muchii[i].to = to;
		savedEdges[i] = cost;
		checkedEdges[i] = 0;

		Muchie *nod = (Muchie *) malloc(sizeof(Muchie));

		nod->value = cost;
		nod->node = to;
		nod->numar = i;

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
		nod1->numar = i;

		if (Graph[to] == NULL) {
			Graph[to] = nod1;
			nod1->next = NULL;
		} else {
			nod1->next = Graph[to];
			Graph[to] = nod1;
		}
	}

	FILE *fid2 = fopen("bonus.out", "w");

	nod Noduri[N + 1];

	Muchii[0].cost = 0;

	//sortez muchiile crescator
	qsort(Muchii, M + 1, sizeof(muc), cmp);
	unionByRank componente[N + 1];

	//creez componentele
	for (int i = 1; i <= N; ++i) {
		componente[i].parent = i;
		componente[i].rank = 0;
	}

	//daca capetele urmatoarei muchii nu fac parte din aceeasi componenta
	//unesc componentele cu ajutorul algoritmului UnionByRank
	//de complexitate logaritmica si bifez muchia folosita
	//algoritmul este algoritmul lui Kruskal
	for (int i = 1; i <= M; ++i) {
		int fromRoot = rootSearch(componente, Muchii[i].from);
		int toRoot = rootSearch(componente, Muchii[i].to);

		if (fromRoot != toRoot) {
			if (componente[fromRoot].rank < componente[toRoot].rank)
				componente[fromRoot].parent = toRoot;
			else if (componente[fromRoot].rank > componente[toRoot].rank)
				componente[toRoot].parent = fromRoot;
			else {
				componente[toRoot].parent = fromRoot;
				componente[fromRoot].rank++;
			}
			checkedEdges[Muchii[i].number] = 1;
		}
	}

	int *visited = (int *) calloc(N + 1, sizeof(int));

	//fac legaturile in noul arbore pentru a afla parintii fiecarui nod
	DFS(visited, 1, checkedEdges, 0, Noduri, Graph, 0, 0);

	//pentru fiecare pereche start stop folosesc algoritmul LCA
	// si aflu ce muchie are valoarea maxima pe drumul parcurs de cele
	//2 noduri pana la parintele comun
	for (int i = 0; i < K; ++i) {
		int start, stop;

		fscanf(fid, "%d %d", &start, &stop);

		int maxim = LCA(Noduri, start, stop, savedEdges);

		if (start == stop)
			fprintf(fid2, "0\n");
		else
			fprintf(fid2, "%d\n", maxim);
	}

	fclose(fid2);
	fclose(fid);
	free(visited);
	for (int i = 1 ; i <= N; ++i) {
		while (Graph[i]) {
			Muchie *copy = Graph[i];

			Graph[i] = Graph[i]->next;
			free(copy);
		}
	}

	return 0;
}

