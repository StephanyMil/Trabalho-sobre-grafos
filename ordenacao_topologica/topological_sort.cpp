#include <iostream>
#include <vector>
using namespace std;
 
// Estrutura de dados para armazenar uma aresta do gráfico


struct Edge {
    int src, dest;
};
 


class Graph
{
public:
    vector<vector<int>> adjList;
 
    vector<int> indegree;
 
    Graph(vector<Edge> const &edges, int n)
    {
        adjList.resize(n);
 
        vector<int> temp(n, 0);
        indegree = temp;
 
        for (auto &edge: edges)
        {
            adjList[edge.src].push_back(edge.dest);
 
            indegree[edge.dest]++;
        }
    }
};
 
vector<int> doTopologicalSort(Graph const &graph)
{
    vector<int> graphResult;
 
    int n = graph.adjList.size();
 
    vector<int> indegree = graph.indegree;
 
    vector<int> without_edge;
    for (int i = 0; i < n; i++)
    {
        if (!indegree[i]) {
            without_edge.push_back(i);
        }
    }
 
    while (!without_edge.empty())
    {
        int n = without_edge.back();
        without_edge.pop_back();
 
        graphResult.push_back(n);
 
        for (int m: graph.adjList[n])
        {
            indegree[m] -= 1;
 
            if (!indegree[m]) {
                without_edge.push_back(m);
            }
        }
    }
 
    for (int i = 0; i < n; i++)
    {
        if (indegree[i]) {
            return {};
        }
    }
 
    return graphResult;
}
 
int main()
{
    // vector de arestas do gráfico conforme o diagrama acima
    vector<Edge> edges =
    {
        { 0, 6 }, { 1, 2 }, { 1, 4 }, { 1, 6 }, { 3, 0 }, { 3, 4 },
        { 5, 1 }, { 7, 0 }, { 7, 1 }
    };
 
    // número total de nós no gráfico (rotulado de 0 a 7)
    int n = 8;
 
    // constrói um gráfico a partir das arestas fornecidas
    Graph graph(edges, n);
 
    // Realiza ordenação topológica
    vector<int> L = doTopologicalSort(graph);
 
    // imprime a ordem topológica
    if (L.size()) {
        for (int i: L) {
            cout << i << " ";
        }
    } else {
        cout << "Graph has at least one cycle. Topological sorting is not possible";
    }
 
    return 0;
}