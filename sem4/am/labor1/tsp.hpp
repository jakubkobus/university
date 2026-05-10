#pragma once

#include <fstream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

namespace tsp {
  struct Node {
    int id;
    double x;
    double y;
  };

  typedef std::vector<Node> Route;

  inline Route load(const std::string &filepath) {
    std::vector<Node> nodes;
    std::ifstream file(filepath);
    if (!file.is_open())
      throw std::runtime_error("[ERROR] Can't open file `" + filepath + "'");

    std::string line;
    bool readingNodes = false;
    while (std::getline(file, line)) {
      if (line.empty()) continue;
      if (line.find("NODE_COORD_SECTION") != std::string::npos) {
        readingNodes = true;
        continue;
      }
      if (line.find("EOF") != std::string::npos) break;
      if (readingNodes) {
        std::istringstream iss(line);
        Node node;
        if (iss >> node.id >> node.x >> node.y)
          nodes.push_back(node);
      }
    }
    file.close();
    if (nodes.empty())
      throw std::runtime_error("[ERROR] No nodes loaded from file `" + filepath + "'");
    return nodes;
  }

  inline double calculateDistance(const Node &a, const Node &b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
  }

  inline double calculateRouteLength(const Route &route) {
    if (route.empty()) return 0.0;
    double totalDist = 0;
    for (size_t i = 0; i < route.size() - 1; i++)
      totalDist += calculateDistance(route[i], route[i + 1]);
    totalDist += calculateDistance(route.back(), route.front());
    return totalDist;
  }

  inline void saveRoute(const Route &route, const std::string &filepath) {
    std::ofstream out(filepath);
    if (!out.is_open())
      throw std::runtime_error("[ERROR] Can't open file `" + filepath + "'");
    for (const auto &node : route)
      out << node.x << " " << node.y << "\n";
    if (!route.empty())
      out << route.front().x << " " << route.front().y << "\n";
    out.close();
  }
}
