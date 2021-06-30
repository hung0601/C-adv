#include <stdio.h>
#include "weighted_graph.h"
int main()
{
    Graph g = createGraph();
    addVertex(g, 0, "0");
    addVertex(g, 1, "1");
    addVertex(g, 2, "2");
    addVertex(g, 3, "3");
    addVertex(g, 4, "4");
    addVertex(g, 5, "5");

    addEdge(g, 0, 1,1.2);
    addEdge(g, 0, 2,7.5);
    addEdge(g, 1, 2,5.5);
    addEdge(g, 1, 4,0.3);
    addEdge(g, 4,2 ,1);
    addEdge(g, 3, 5,0.2);
    // add the vertices and the edges of the graph here
    
    int s, t, length;
    s=0;
    t=2;
    Dllist ptr, path=new_dllist();
    double weight = shortestPath(g, s, t, path, &length);
    if (weight == INFINITIVE_VALUE)
        printf("No path between % d and % d\n", s, t);
    else
    {
        printf("Path between % d and % d:", s, t);
        dll_traverse(ptr, path)
        {
            printf("%5d", jval_i(ptr->val));
        }

        printf("\nTotal weight: % lf\n", weight);
    }
    dropGraph(g);
    free_dllist(path);
    return 0;
}
