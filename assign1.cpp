#include<iostream>
#include<queue>
#include<list>

using namespace std;
#define INF 0x3f3f3f3f
 
typedef pair<int, int> iPair;
 
// Graph using adjacency list representation
class Graph
{
    int V;    // No. of vertices
 
    list< pair<int, int> > *adj;
 
public:
    Graph(int V);  // Constructor
 
    // function to add an edge to graph
    void addEdge(int u, int v, int w);
 
    void dijkstra(int s);
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair> [V];
}
 
void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}
 
void Graph::dijkstra(int src)
{
	// Creates a Min heap
    // see http://geeksquiz.com/implement-min-heap-using-stl/ for more explanations
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;


	// Initiate start parameters

	// Creates an vector for all distances and fill it with infinite
    vector<int> distances(V, INF);
	// Push startVertex into priority queue and set it's distance to 0
    pq.push(make_pair(0, src));
    distances[src] = 0;

    /* Looping till all vertices was selected */
    while (!pq.empty())
    {
	      int selectedVertex = pq.top().second;
		  pq.pop();

		  list< pair<int, int> >::iterator checkVertex;
		  checkVertex = adj[selectedVertex].begin();

		  for(checkVertex; checkVertex != adj[selectedVertex].end(); ++checkVertex)
		  {
			  int checkVertexWeight = (*checkVertex).second;
			  int checkVertexLabel = (*checkVertex).first;

			if (distances[checkVertexLabel] > distances[selectedVertex] + checkVertexWeight)
            {
                // Updating distance
                distances[checkVertexLabel] = distances[selectedVertex] + checkVertexWeight;
                pq.push(make_pair(distances[checkVertexLabel], checkVertexLabel));
            }

		  }

    }
 
    // Print shortest distances
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, distances[i]);
}
 
int main()
{
    // create graph
    int V = 6;
    Graph g(V);

	//example graph here: https://www.youtube.com/watch?v=S8y-Sk7u1So
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(0, 4, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 3);
    g.addEdge(2, 4, 5);
    g.addEdge(3, 5, 2);
    g.addEdge(4, 5, 1);
    
    g.dijkstra(0);
    
    system("PAUSE");
 
    return 0;
}

