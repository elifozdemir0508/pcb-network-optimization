#include <stdio.h>
#include <string.h>

#define MAX_NODES 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char target[MAX_NAME_LENGTH];
    int weight;
} Neighbor;

typedef struct {
    char name[MAX_NAME_LENGTH];
    Neighbor neighbors[MAX_NODES];
    int neighborCount;
} Node;

typedef struct {
    Node nodes[MAX_NODES];
    int nodeCount;
} Graph;

void initGraph(Graph *graph) {
    graph->nodeCount = 0;
}

int findNodeIndex(Graph *graph, const char *nodeName) {
    for (int i = 0; i < graph->nodeCount; i++) {
        if (strcmp(graph->nodes[i].name, nodeName) == 0) {
            return i;
        }
    }
    return -1;
}

void addNode(Graph *graph, const char *nodeName) {
    if (findNodeIndex(graph, nodeName) != -1) {
        return;
    }

    if (graph->nodeCount >= MAX_NODES) {
        printf("Node limit reached.\n");
        return;
    }

    strcpy(graph->nodes[graph->nodeCount].name, nodeName);
    graph->nodes[graph->nodeCount].neighborCount = 0;
    graph->nodeCount++;
}

void addEdge(Graph *graph, const char *source, const char *target, int weight) {
    addNode(graph, source);
    addNode(graph, target);

    int sourceIndex = findNodeIndex(graph, source);
    int targetIndex = findNodeIndex(graph, target);

    Node *sourceNode = &graph->nodes[sourceIndex];
    Node *targetNode = &graph->nodes[targetIndex];

    strcpy(sourceNode->neighbors[sourceNode->neighborCount].target, target);
    sourceNode->neighbors[sourceNode->neighborCount].weight = weight;
    sourceNode->neighborCount++;

    strcpy(targetNode->neighbors[targetNode->neighborCount].target, source);
    targetNode->neighbors[targetNode->neighborCount].weight = weight;
    targetNode->neighborCount++;
}

void displayGraph(Graph *graph) {
    for (int i = 0; i < graph->nodeCount; i++) {
        printf("%s -> ", graph->nodes[i].name);

        for (int j = 0; j < graph->nodes[i].neighborCount; j++) {
            printf("(%s, %d) ",
                   graph->nodes[i].neighbors[j].target,
                   graph->nodes[i].neighbors[j].weight);
        }

        printf("\n");
    }
}

void printNodes(Graph *graph) {
    printf("Nodes: ");

    for (int i = 0; i < graph->nodeCount; i++) {
        printf("%s ", graph->nodes[i].name);
    }

    printf("\n");
}

void printEdges(Graph *graph) {
    printf("Edges:\n");

    for (int i = 0; i < graph->nodeCount; i++) {
        char *source = graph->nodes[i].name;

        for (int j = 0; j < graph->nodes[i].neighborCount; j++) {
            char *target = graph->nodes[i].neighbors[j].target;
            int weight = graph->nodes[i].neighbors[j].weight;

            /*
              Undirected graph olduğu için aynı edge iki kez yazılmasın diye
              sadece source < target durumunda yazdırıyoruz.
            */
            if (strcmp(source, target) < 0) {
                printf("%s - %s : %d\n", source, target, weight);
            }
        }
    }
}

int main() {
    Graph graph;

    initGraph(&graph);

    addEdge(&graph, "A", "B", 4);
    addEdge(&graph, "A", "C", 2);
    addEdge(&graph, "B", "D", 5);
    addEdge(&graph, "C", "D", 1);

    displayGraph(&graph);

    printNodes(&graph);
    printEdges(&graph);

    return 0;
}
