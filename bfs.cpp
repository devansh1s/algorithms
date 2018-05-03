#include<iostream>
#include <vector>
#include<queue>
 
using namespace std;

class Graph
{
    public:
    int V;  
    vector<int> *adj;
    bool *discovered;   
    Graph(int V);  
    
    void addEdge(int v, int w); 
 
 
    void BFS(int s);  
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new vector<int>[V];
    discovered = new bool[V];
    for(int i = 0; i < V; i++)
        discovered[i] = false;
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); 
}




void Graph::BFS(int s)
{
   
    queue<int> qu;
 

    discovered[s] = true;
    qu.push(s);
 
    vector<int>::iterator i;
 
    while(!qu.empty())
    {
   
        s = qu.front();
        cout << s << " ";
        qu.pop();
 
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!discovered[*i])
            {
                discovered[*i] = true;
                qu.push(*i);
            }
        }
    }
}
 

int main()
{
    
    int size,a,b;
     
    cout<<"Enter the number of nodes in graph: ";
    cin>>size;
    Graph g(size);

    cout<<"\nAdd Edges:: (enter -1 ,-1 to stop ) : ";
   
    cin>>a>>b;
    while(a!=-1 && b!=-1){
     
     g.addEdge(a,b);
     cin>>a>>b;
    
    }
    


    cout<<"All nodes are:: \n";
    for(int i=0;i<g.V;i++){
      if(g.discovered[i]==false)
      g.BFS(i);
    }
 
    return 0;
}
