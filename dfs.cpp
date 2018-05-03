#include<bits/stdc++.h>
using namespace std;
 
class Graph
{
    public:
    int V;    
    vector<int> *adj;   
    vector<bool> visited; 
    Graph(int V);  
    void addEdge(int v, int w);
    void DFS(int s);  
   
};
 
Graph::Graph(int v)
{
    V = v;
    for(int i=0;i<V;i++)
     visited.push_back(false);
    adj = new vector<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); 
}
 

void Graph::DFS(int s)
{
    stack<int> stack;
 
   
    stack.push(s);
 
    while (!stack.empty())
    {
        
        s = stack.top();
        stack.pop();
 
      
        if (!visited[s])
        {
            cout << s << " ";
            visited[s] = true;
        }
 
        vector<int> :: iterator i;       

        for ( i = adj[s].begin(); i != adj[s].end(); ++i)
            if (!visited[*i])
                stack.push(*i);
    }
}
 

int main()
{
    int v;
    cout<<"Enter the no. of vertices: ";
    cin>>v;
    Graph g(v);

    int e1,e2;
    cout<<"\nEnter the pair of vertices for each edge in the graph, (-1,-1 to stop): ";
    cin>>e1>>e2;
    while(e1!=-1&&e2!=-1&&e1<v&&e2<v){
	g.addEdge(e1,e2); 	      
        cin>>e1>>e2;
    } 
   
    cout<<"\nDepth First Traversal::\n";
    for(int i=0;i<g.V;i++){
	if(g.visited[i]==false){
           g.DFS(i);
           cout<<"  ";
	} 
    }
    cout<<endl;
    return 0;
}
