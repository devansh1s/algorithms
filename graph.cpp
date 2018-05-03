#include<iostream>
#include<list>
#include<queue>
#include<stack>

using namespace std;

class Graph {
    int v;
    list<int> *adj;
public :
    Graph(int x) {
        v = x;
        adj = new list<int>[v];
    }
    void addEdge(int a,int b) {
        adj[a].push_back(b);
    }
    void bfs(int s) {
        bool *visited = new bool[v];
        for (int i=0;i<v;i++) {
            visited[i] = false;
        }
        queue<int> Q;
        Q.push(s);
        visited[s] = true;
        list<int>::iterator i;
        while (!Q.empty()){
            s = Q.front();
            Q.pop();
            cout<<s<<" ";
            for (i=adj[s].begin();i!=adj[s].end();i++) {
                if (!visited[*i]) {
                    Q.push(*i);
                    visited[*i] = true;
                }
            }
        }
        cout<<endl;
    }
    void dfs(int s) {
        bool *visited = new bool[v];
        for (int i=0;i<v;i++) {
            visited[i] = false;
        }
        stack<int> S;
        S.push(s);
        list<int>::iterator i;
        while(!S.empty()) {
            s = S.top();
            S.pop();
            if (!visited[s]) {
                for(i=adj[s].begin();i!=adj[s].end();i++) {
                    S.push(*i);
                }
                cout<<s<<" ";
                visited[s] = true;
            }
        }
        cout<<endl;
    }
    void print_list() {
        list<int>::iterator j;
        cout<<" Node \t Adjacent Nodes"<<endl;
        for (int i=0;i<v;i++) {
            cout<<"  "<<i<<"   \t ";
            for (j=adj[i].begin();j!=adj[i].end();j++) {
                cout<<*j<<" ";
            }
            cout<<endl;
        }
    }
};
int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    cout<<"list :"<<endl;
    g.print_list();
    cout << "Following is Breadth First Traversal(starting from vertex 2) \n";
    g.bfs(2);
    cout << "Following is Depth First Traversal(starting from vertex 2) \n";
    g.dfs(2);
    return 0;
}
