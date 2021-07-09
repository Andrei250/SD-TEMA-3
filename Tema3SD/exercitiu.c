#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 128

//problema a fost realizata cu liste. daca exista coliziuni atunci
//urmatorul element se pune la finalul listei pozitie respective.
typedef struct node {
    char *value;
    struct node *next;
} node;

typedef struct hash {
    node *head, *queue;
} hash_table_t;

int hashFunction(char *value) {
    int sum = 0;

    for (int i = 0; i < strlen(value); ++i)
        sum = (sum + value[i]) % N;

    return sum;
}

int exists(hash_table_t *ht, char *value) {
    int position = hashFunction(value);
    node *nod = ht[position].head;

    while (nod) {
        if (strcmp(nod->value, value) == 0)
            return 1;
        nod = nod->next;
    }

    return 0;
}

void insert(hash_table_t *ht, char *value) {
    if (exists(ht, value))
        return;

    int position = hashFunction(value);
    node *nod = (node*) malloc(sizeof(node));
    nod->next = NULL;
    nod->value = strdup(value);

    if (ht[position].head == NULL) {
        ht[position].head = nod;
        ht[position].queue = nod;
        return;
    }

    ht[position].queue->next = nod;
    ht[position].queue = nod;
}

void delete(hash_table_t *ht, char *val) {
    int position = hashFunction(val);
    node *nod = ht[position].head;

    if (nod == NULL)
        return;

    if (nod && strcmp(val, nod->value) == 0) {
        ht[position].head = ht[position].head->next;
        free(nod);
        return;
    }

    while (nod->next) {
        if (nod->next->next == NULL && strcmp(nod->next->value, val) == 0) {
            node *copy = nod->next;
            nod->next = nod->next->next;
            ht[position].queue = nod;
            free(copy);
        } else if (strcmp(nod->next->value, val) == 0) {
            node *copy = nod->next;
            nod->next = nod->next->next;
            free(copy);
        }
        nod = nod->next;
    }
}

void printrHash(hash_table_t *ht) {
    for (int i = 0; i < N; ++i) {
        node *copy = ht[i].head;
        printf("%d.", i);

        while (copy) {
            printf("%s ", copy->value);
            copy= copy->next;
        }

        printf("\n");
    }
}

int main() {
    
    hash_table_t ht[N];

    for (int i = 0; i < N; ++i)
        ht[i].head = NULL;

    printf("pentru a adauga un sir in hash apasati 1 urmat de sir, pentru a sterge apasati 2 apoi sirul,\
            pentru a verifica un sir apasati 3 apoi sirul, pentru a printa hasul, apasati 4, pentru a iesi orice altceva\n");

    char string[250];

    while (fgets(string, 250, stdin)) {

        if (string[0] == '\n')
            break;
        string[strlen(string) - 1] = '\0';

        char *p = strtok(string, " ");
        int number = atoi(p);

        if (number == 1) {
            p = strtok(NULL, " ");
            insert(ht, p);
        } else if (number == 2) {
            p = strtok(NULL, " ");
            delete(ht, p);
        } else if (number == 3) {
            p = strtok(NULL, " ");
            int w = exists(ht, p);
            if (w == 1)
                printf("da\n");
            else
                printf("Nu\n");
        } else if (number == 4) {
            printrHash(ht);
        } else {
            break;
        }

    }

}