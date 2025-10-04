#include <stdio.h>
#include <limits.h>

#define V 100 // Maximum number of vertices

int minKey(int key[], int mstSet[], int n) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < n; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void printMST(int parent[], int graph[V][V], int n) {
    int totalCost = 0;
    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++) {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
        totalCost += graph[i][parent[i]];
    }
    printf("\nTotal cost: %d\n", totalCost);
}

void displayTreeInTerminal(int parent[], int n) {
    printf("\n--- MST Adjacency List ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", i);
        int firstChild = 1;
        for (int j = 0; j < n; j++) {
            if (parent[j] == i) {
                if (!firstChild) {
                    printf(", ");
                }
                printf("%d", j);
                firstChild = 0;
            }
        }
        printf("\n");
    }
}

void primMST(int graph[V][V], int n, int parent[]) {
    int key[V];    // Key values used to pick minimum weight edge
    int mstSet[V]; // To represent set of vertices included in MST

    for (int i = 0; i < n; i++)
        key[i] = INT_MAX, mstSet[i] = 0;

    key[0] = 0;     // Start from first vertex
    parent[0] = -1; // First node is always root of MST

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = 1;

        for (int v = 0; v < n; v++)
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
}

int main() {
    int n;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    int graph[V][V] = {0};
    printf("Enter adjacency matrix (use 0 for no edge):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    int parent[V];
    primMST(graph, n, parent);
    printMST(parent, graph, n);
    displayTreeInTerminal(parent, n);

    return 0;
}