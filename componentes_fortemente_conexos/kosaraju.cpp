/*
	Implementação do algoritmo de Kosaraju
	Detecta componentes fortemente conectadas
*/

#include <iostream>
#include <stack>
#include <list>

using namespace std;

class Graph {
private:
    int numVertices;
    list<int> *adjacencyList;
    
    // Função auxiliar para realizar a Busca em Profundidade e preencher a pilha
    void fillOrder(int v, bool visited[], stack<int>& stack) {
        visited[v] = true;
        
        // Percorre os vizinhos do vértice atual
        for (int neighbor : adjacencyList[v]) {
            if (!visited[neighbor])
                fillOrder(neighbor, visited, stack);
        }
        stack.push(v);
    }
    
    // Função auxiliar para a Busca em Profundidade
    void DFS(int v, bool visited[]) {
        visited[v] = true;
        cout << v << " ";
        
        // Percorre os vizinhos do vértice atual
        for (int neighbor : adjacencyList[v]) {
            if (!visited[neighbor])
                DFS(neighbor, visited);
        }
    }

public:
     // Construtor
    Graph(int numVertices) {
        this->numVertices = numVertices;
        adjacencyList = new std::list<int>[numVertices];
    }
    
    // Método para adicionar uma aresta ao grafo
    void addEdge(int i, int j) {
        adjacencyList[i].push_back(j);
    }
    
    // Método para obter o grafo transposto
    Graph getTranspose() {
        Graph transposedGraph(numVertices);
        
         // Percorre o grafo original e popula as listas de adjacência do grafo transposto
        for (int v = 0; v < numVertices; ++v) {
            for (int neighbor : adjacencyList[v]) {
                transposedGraph.adjacencyList[neighbor].push_back(v);
            }
        }

        return transposedGraph;
    }
    
    // Método para imprimir componentes fortemente conectados
    void printStronglyConnectedComponents() {
        stack<int> stack;
        bool *visited = new bool[numVertices];
        
        // Inicializa o array de visitados
        for (int i = 0; i < numVertices; ++i)
            visited[i] = false;
            
        // Preenche a pilha usando Busca em Profundidade
        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i])
                fillOrder(i, visited, stack);
        }
        
        // Obtém o grafo transposto
        Graph transposedGraph = getTranspose();
        
        // Reseta o array de visitados
        for (int i = 0; i < numVertices; ++i)
            visited[i] = false;
            
        // Processa os vértices na ordem da pilha
        while (!stack.empty()) {
            int v = stack.top();
            stack.pop();
            
            // Imprime componente fortemente conectado
            if (!visited[v]) {
                transposedGraph.DFS(v, visited);
                cout << "\n";
            }
        }
    }
};

int main() {
    // Cria um grafo com 5 vértices
    Graph g(5);
    
    // Adiciona arestas ao grafo
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 0);
    g.addEdge(3, 4);
    
    // Imprime componentes fortemente conectados
    g.printStronglyConnectedComponents();

    return 0;
}
