// 교재에서는 연결리스트로 구현했음. 메인함수랑 Union Find도 깔끔하게햇으니 다시 볼 것 ,,,
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX 100
//#define INF 10000

int parent[MAX];

void set_init(int n) {
   for (int i = 0; i < n; i++) {
      parent[i] = -1;
   }
}

int set_find(int curr) {
   if (parent[curr] == -1)
      return curr;
   while (parent[curr] != -1) curr = parent[curr];
   return curr;
}

void set_union(int a, int b) {
   int root1 = set_find(a);
   int root2 = set_find(b);
   if (root1 != root2) {
      parent[root1] = root2;
   }
}

struct Edge {
   int start, end, weight;
};

typedef struct GraphType {
   int n;
   int nVertex;
   struct Edge edges[200];
}GraphType;

void graph_init(GraphType* g) {
   g->n = g->nVertex= 0;
   for (int i = 0; i < 200; i++) {
      g->edges[i].start = 0;
      g->edges[i].end = 0;
      g->edges[i].weight = 1000;
   }
}

void insert_edge(GraphType* g, int start, int end, int w) {
   g->edges[g->n].start = start;
   g->edges[g->n].end = end;
   g->edges[g->n].weight = w;
   g->n++;
}

int compare(const void* a, const void* b) {
   struct Edge* x = (struct Edge*)a;
   struct Edge* y = (struct Edge*)b;
   return (x->weight - y->weight);
}

void kruskal(GraphType* g) {
   int edge_accepted = 0;
   int uset, vset;
   struct Edge e;

   set_init(g->nVertex);
   qsort(g->edges, g->n, sizeof(struct Edge), compare);

   printf("(edge):weight\n");
   int i = 0;
   while (edge_accepted < (g->nVertex - 1)) {
      e = g->edges[i];
      uset = set_find(e.start);
      vset = set_find(e.end);
      if (uset != vset) {
         printf("(%d, %d): %d\n", e.start, e.end, e.weight);
         edge_accepted++;
         set_union(uset, vset);
      }
      i++;
   }
}

void main() {
   FILE* fp = fopen("in.txt", "r");
   int n, w;
   fscanf(fp, "%d", &n);

   GraphType* g;
   g = (GraphType*)malloc(sizeof(GraphType));
   graph_init(g);
   g->nVertex = n;
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         fscanf(fp, "%d", &w);
         if (w != 0)
            insert_edge(g, i, j, w);
      }
   }

   
   kruskal(g);
   free(g);
   return 0;
}
