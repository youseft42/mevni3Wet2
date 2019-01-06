#ifndef MEVNI3WET2_UNION_FIND_H
#define MEVNI3WET2_UNION_FIND_H

class UnionFind{
    int* parent;
    int counter;
    int* size;
public:
    UnionFind(int N){
        counter = N;
        parent = new int[N];
        size = new int[N];
        for (int i = 0; i<N; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }
    ~UnionFind() {
        delete[] parent;
        delete[] size;
    }
    int find(int p) {
        int root = p;
        while (root != parent[root]) root = parent[root];
        while (p != root) {
            int newp = parent[p];
            parent[p] = root;
            p = newp;
        }
        return root;
    }
    void merge(int x, int y){
        int i = find(x);
        int j = find(y);
        if (i == j) return;
        if (size[i] < size[j]){
            parent[i] = j;
            size[j] += size[i];
        }
        else {
            parent[j] = i;
            size[i] += size[j];
        }
        counter--;
    }
    bool connected(int x, int y){
        return find(x) == find(y);
    }
    int count(){
        return counter;
    }
};
#endif //MEVNI3WET2_UNION_FIND_H
