#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Node {
  Node(int v) : val(v) {};
  int val;
  vector<Node*> neighbors;
};

struct Graph{
  Graph(int s) : size(s) {
    for(int i=1; i<=size; i++) {
      nodes.push_back(new Node(i));
    }
  };
  void addEdge(int n, int m) {
    nodes[n-1]->neighbors.push_back(nodes[m-1]);
  };
  vector<Node*> nodes;
  int size;
};

void dfs(Node *node, vector<int>& visited, stack<int>& s){
  if(visited[node->val]) return;
  for(auto n:node->neighbors) {
    dfs(n, visited, s);
  }
  visited[node->val] = 1;
  s.push(node->val);
}

vector<int> topoSort(Graph& g) {
  int size = g.nodes.size();
  vector<int> visited(size, 0);
  stack<int> s;

  for(int i=0; i<size; i++) {
    dfs(g.nodes[i], visited, s);
  }
  vector<int> res;
  while(!s.empty()) {
    int n = s.top(); s.pop();
    res.push_back(n);    
  }

  return res;
}

int main() {
  Graph g(7);

  g.addEdge(1,3);
  g.addEdge(2,3);
  g.addEdge(2,5);
  g.addEdge(3,4);
  g.addEdge(4,6);
  g.addEdge(5,6);
  g.addEdge(6,7);

  vector<int> res = topoSort(g);
  for(auto n:res) {
    cout<<n<<" ";
  }

  return 0;
}
