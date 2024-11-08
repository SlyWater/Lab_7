#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

typedef struct node {
    int n;
    struct node* next;
} node;

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




int main() {
    setlocale(LC_ALL, "Rus");
    int n = 4;
    int* vis = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) vis[i] = 0;
    int** M1 = NULL;
    printf("Введите количество вершин: ");
    srand(time(NULL));

    //scanf("%d", &n);
    printf("\n");

    M1 = createG(n);
    printf("Граф G1\n");
    printG(M1, n);
    check_vis(M1, n, vis);
}