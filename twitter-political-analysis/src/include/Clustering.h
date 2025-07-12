#ifndef CLUSTERING_H
#define CLUSTERING_H

#include <vector>
#include <unordered_map>
#include "UserGraph.h"

class Clustering {
public:
    Clustering(UserGraph& userGraph);
    std::vector<std::vector<int>> findStronglyConnectedComponents();
    std::unordered_map<int, double> calculateInfluenceMetrics();

private:
    UserGraph& userGraph;
    void dfs(int v, std::vector<bool>& visited, std::vector<int>& stack);
    void fillOrder(int v, std::vector<bool>& visited, std::vector<int>& stack);
    void dfsUtil(int v, std::vector<bool>& visited, std::vector<int>& component);
};

#endif // CLUSTERING_H