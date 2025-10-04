#include <stdio.h>
#include <stdlib.h>

// Adjacency list node
struct Node {
    int dest;
    struct Node* next;
};

// Graph structure with an array of adjacency lists
struct Graph {
    int V; // Number of vertices
    struct Node** adj; // Adjacency lists
};

// Utility function to create a new adjacency list node
struct Node* createNode(int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Utility function to create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adj = (struct Node**)malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; i++) {
        graph->adj[i] = NULL;
    }
    return graph;
}

// Adds a directed edge from src to dest
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adj[src];
    graph->adj[src] = newNode;
}

/**
 * @brief Recursive helper function for Topological Sort.
 * @param v         The current vertex being visited.
 * @param graph     The graph.
 * @param visited   Array to track the state of each vertex (0: unvisited, 1: visiting, 2: visited).
 * @param stack     Array used as a stack to store the sorted vertices.
 * @param stackIndex Pointer to the current top of the stack.
 * @return int      1 if a cycle is detected, 0 otherwise.
 */
int topologicalSortUtil(int v, struct Graph* graph, int visited[], int* stack, int* stackIndex) {
    // Mark the current node as visiting
    visited[v] = 1;

    // Recur for all adjacent vertices
    struct Node* temp = graph->adj[v];
    while (temp != NULL) {
        int connectedVertex = temp->dest;
        
        // If the adjacent vertex is currently being visited, we have a cycle
        if (visited[connectedVertex] == 1) {
            return 1; // Cycle detected
        }

        // If the adjacent vertex has not been visited, recurse on it
        if (visited[connectedVertex] == 0) {
            if (topologicalSortUtil(connectedVertex, graph, visited, stack, stackIndex)) {
                return 1; // Propagate cycle detection
            }
        }
        temp = temp->next;
    }

    // Mark the current node as fully visited
    visited[v] = 2;
    // Push the current vertex to stack which stores the result
    stack[(*stackIndex)++] = v;

    return 0; // No cycle found in this path
}

// The main function to perform Topological Sort
void topologicalSort(struct Graph* graph) {
    int V = graph->V;
    int* stack = (int*)malloc(V * sizeof(int));
    int stackIndex = 0;

    // `visited` array stores the state of each vertex
    // 0 = unvisited, 1 = visiting (in recursion stack), 2 = visited
    int* visited = (int*)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
    }

    int hasCycle = 0;
    // Call the recursive helper function for all unvisited vertices
    for (int i = 0; i < V; i++) {
        if (visited[i] == 0) {
            if (topologicalSortUtil(i, graph, visited, stack, &stackIndex)) {
                hasCycle = 1;
                break;
            }
        }
    }

    if (hasCycle) {
        printf("Error: The graph contains a cycle. Topological sort is not possible.\n");
    } else {
        printf("Topological Sort of the given graph:\n");
        // Print contents of the stack in reverse order of insertion
        while (stackIndex > 0) {
            printf("%d ", stack[--stackIndex]);
        }
        printf("\n");
    }

    // Free allocated memory
    free(stack);
    free(visited);
}

// Driver program to test above functions
int main() {
    printf("--- Example 1: A Directed Acyclic Graph (DAG) ---\n");
    // Graph from a typical course prerequisite scenario
    int V = 6;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    topologicalSort(graph);
    
    // In a real application, you would free the graph's adjacency lists as well.
    // For this simple example, we'll just free the main structure.
    free(graph->adj);
    free(graph);

    printf("\n--- Example 2: A Graph with a Cycle ---\n");
    V = 4;
    struct Graph* cyclic_graph = createGraph(V);
    addEdge(cyclic_graph, 0, 1);
    addEdge(cyclic_graph, 1, 2);
    addEdge(cyclic_graph, 2, 3);
    addEdge(cyclic_graph, 3, 1); // This edge creates a cycle 1 -> 2 -> 3 -> 1

    topologicalSort(cyclic_graph);

    free(cyclic_graph->adj);
    free(cyclic_graph);

    return 0;
}