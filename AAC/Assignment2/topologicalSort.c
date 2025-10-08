#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 50

typedef struct Node {
    int dest;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

Node* createNode(int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

void topologicalSortUtil(int u, Graph* graph, bool visited[], int result[], int* result_idx) {
    visited[u] = true;

    Node* temp = graph->adjLists[u];
    while (temp != NULL) {
        int v = temp->dest;
        if (!visited[v]) {
            topologicalSortUtil(v, graph, visited, result, result_idx);
        }
        temp = temp->next;
    }

    result[(*result_idx)--] = u;
}

void topologicalSort(Graph* graph) {
    bool visited[MAX_VERTICES] = {false};
    int result[MAX_VERTICES];
    int result_idx = graph->numVertices - 1;

    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, graph, visited, result, &result_idx);
        }
    }

    printf("Topological Sort (assumes the graph is a DAG):\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* current = graph->adjLists[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adjLists);
    free(graph);
}

int main() {
    Graph* g = createGraph(6);
    addEdge(g, 5, 2);
    addEdge(g, 5, 0);
    addEdge(g, 4, 0);
    addEdge(g, 4, 1);
    addEdge(g, 2, 3);
    addEdge(g, 3, 1);

    topologicalSort(g);

    freeGraph(g);

    return 0;
}