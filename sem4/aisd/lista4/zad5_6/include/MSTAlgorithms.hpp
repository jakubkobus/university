#ifndef MST_ALGORITHMS_HPP
#define MST_ALGORITHMS_HPP

#include <vector>
#include <algorithm>

#include "DSU.hpp"

template<typename T>
using Vec2D = std::vector<std::vector<T>>;

struct Edge {
  int u, v;
  double weight;
  bool operator< (const Edge &other) const {
    return weight < other.weight;
  }
};

inline double prim(const int n, const Vec2D<double> &adj) {
  std::vector<double> minWeight(n, 1e9);
  std::vector<bool> inMST(n, false);
  minWeight[0] = 0;
  double totalWeight = 0;

  for(int i = 0; i < n; i++) {
    int u = -1;
    for(int j = 0; j < n; j++)
      if(
        !inMST[j] && (
          u == -1 ||
          minWeight[j] < minWeight[u]
        )
      ) u = j;

    inMST[u] = true;
    totalWeight += minWeight[u];

    for(int v = 0; v < n; v++)
      if(
        u != v &&
        !inMST[v] &&
        adj[u][v] < minWeight[v]
      ) minWeight[v] = adj[u][v];
  }

  return totalWeight;
}

inline Vec2D<int> kruskalMST(const int n, std::vector<Edge> &edges) {
  std::sort(edges.begin(), edges.end());

  DSU dsu(n);
  Vec2D<int> mst(n);
  int edgesUsed = 0;

  for(const auto &edge : edges) {
    if(dsu.find(edge.u) != dsu.find(edge.v)) {
      dsu.unite(edge.u, edge.v);
      mst[edge.u].push_back(edge.v);
      mst[edge.v].push_back(edge.u);
      edgesUsed++;
      if (edgesUsed == n - 1) break;
    }
  }

  return mst;
}

#endif // MST_ALGORITHMS_HPP
