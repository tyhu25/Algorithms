#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class UnionFind;
ostream& operator<<(ostream& out, UnionFind &uf);

class UnionFind {
    friend ostream& operator<<(ostream& out, UnionFind &uf);
public:
    UnionFind(int n) {
        ids = vector<int>(n, 0);
        for(int i=0; i<n; i++) {
            ids[i] = i;
        }
        sizes = vector<int>(n, 1);
    }
    
    bool find(int p, int q) {
        return root(p)==root(q);
    }
    
    void unite(int p, int q) {
        int pRoot = root(p);
        int qRoot = root(q);
        //Weighted union
        if(sizes[pRoot]<sizes[qRoot]) {
            sizes[qRoot] += sizes[pRoot];
            ids[pRoot] = qRoot;
        } else {
            sizes[pRoot] += sizes[qRoot];
            ids[qRoot] = pRoot;
        }
    }
    
private:
    int root(int p) {
        while(p!=ids[p]) {
            //path compression
            ids[p] = ids[ids[p]];
            p = ids[p];
        }
        return p;
    }
    vector<int> ids;
    vector<int> sizes;
};

ostream& operator<<(ostream& out, UnionFind &uf) {
    unordered_map<int, vector<int>> m;
    for(int i=0; i<uf.ids.size(); i++) {
        int r = uf.root(i);
        m[r].push_back(i);
    }
    out<<"UnionFind Set:\n";
    for(auto it : m) {
        for(int i=0; i<it.second.size(); i++) {
            out<<it.second[i]<<" ";
        }
        out<<"\n";
    }
    return out;
}

int main() {
    UnionFind uf(10);
    uf.unite(3, 4);
    uf.unite(4, 9);
    uf.unite(8, 0);
    uf.unite(2, 3);
    uf.unite(5, 6);
    uf.unite(7, 8);
    uf.unite(1, 2);
    uf.unite(6, 7);
    cout<<uf;
    
    return 0;
}