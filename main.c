#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

typedef struct node {
    int n;
    struct node* next;
} node;

node** createAdj(int** G, int n) {
    node** A = (node**)malloc(n * sizeof(node*));
    for (int i = 0; i < n; ++i) {
        A[i] = NULL;
        node* tail = NULL;
        for (int j = 0; j < n; ++j) {
            if (G[i][j] == 1) {
                node* newNode = (node*)malloc(sizeof(node));
                newNode->n = j;
                newNode->next = NULL;
                if (tail == NULL) {
                    A[i] = newNode;
                }
                else {
                    tail->next = newNode;
                }
                tail = newNode;
            }
        }
    }
    return A;
}

void printAdj(node** A, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d: ", i);
        node* current = A[i];
        while (current != NULL) {
            printf("%d ", current->n);
            current = current->next;
        }
        printf("\n");
    }
    printf("\n");
}


int** createG(int n) {
    int** G = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        G[i] = (int*)malloc(n * sizeof(int));
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            G[i][j] = rand() % 2;
            G[j][i] = (i == j) ? 0 : G[i][j];
        }
    }
    return G;
}

void printG(int** G, int n) {
    printf("  ");
    for (int i = 0; i < n; ++i) printf("%d ", i);
    printf("\n");
    for (int i = 0; i < n; ++i) {
        printf("%d ", i);
        for (int j = 0; j < n; ++j) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void DFS(int** G, int n, int* vis, int s) {
    vis[s] = 1;
    printf("%d ", s);
    for (int i = 0; i < n; ++i) {
        if (G[s][i] == 1 && vis[i] == 0) {
            DFS(G, n, vis, i);
        }
    }
}
void check_vis(int** G, int n, int* vis) {
    for (int i = 0; i < n; ++i) {
        if (vis[i]==0) {
            DFS(G, n, vis, i);
            printf("\n");
        }
    }
}

void DFSA(node** A, int* vis, int s) {
    vis[s] = 1;
    printf("%d ", s);
    node* current = A[s];
    while (current != NULL) {
        if (vis[current->n] == 0) {
            DFSA(A, vis, current->n);
        }
        current = current->next;
    }
}

void check_visA(node** A, int n, int* vis) {
    for (int i = 0; i < n; ++i) {
        if (vis[i] == 0) {
            DFSA(A, vis, i);
            printf("\n");
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    int n = 4;

    int* vis = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) vis[i] = 0;
    printf("Введите количество вершин: ");
    //scanf("%d", &n);
    printf("\n");

    int** M1 = createG(n);
    printf("Граф G1\n");
    printG(M1, n);
    check_vis(M1, n, vis);
    printf("\n");

    node** A1 = createAdj(M1, n);
    printf("Список смежности графа G1\n");
    printAdj(A1, n);
    for (int i = 0; i < n; ++i) vis[i] = 0;
    check_visA(A1, n, vis);

    free(M1);
    free(A1);
    free(vis);
}