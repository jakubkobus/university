#ifndef DSU_HPP
#define DSU_HPP

#include <vector>

class DSU {
private:
  std::vector<int> parent;
  std::vector<int> rank;

public:
  DSU(const int n);
  int find(const int i);
  void unite(const int i, const int j);
};


inline DSU::DSU(const int n) {
  parent.resize(n);
  rank.resize(n, 0);
  for(int i = 0; i < n; i++)
    parent[i] = i;
}

inline int DSU::find(const int i) {
  if(parent[i] == i)
    return i;
  return parent[i] = find(parent[i]);
}

inline void DSU::unite(const int i, const int j) {
  int iRoot = find(i);
  int jRoot = find(j);

  if(iRoot != jRoot) {
    if(rank[iRoot] < rank[jRoot]) {
      parent[iRoot] = jRoot;
    } else if(rank[iRoot] > rank[jRoot]) {
      parent[jRoot] = iRoot;
    } else {
      parent[jRoot] = iRoot;
      rank[iRoot]++;
    }
  }
}

#endif // DSU_HPP
