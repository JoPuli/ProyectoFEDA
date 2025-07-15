#include "SCCFinder.h"

SCCFinder::SCCFinder(const std::unordered_map<std::string, std::unordered_set<std::string>>& graphF,
                     const std::unordered_map<std::string, std::unordered_set<std::string>>& graphR)
    : adjList(graphF), reversedAdjList(graphR) {}

void SCCFinder::dfs1(const std::string& node) {
    visited[node] = true;
    auto it = adjList.find(node);
    if (it != adjList.end()) {
        for (const auto& neighbor : it->second) {
            if (!visited[neighbor]) {
                dfs1(neighbor);
            }
        }
    }
    order.push_back(node);
}

void SCCFinder::dfs2(const std::string& node, std::vector<std::string>& component) {
    visited[node] = true;
    component.push_back(node);
    auto it = reversedAdjList.find(node);
    if (it != reversedAdjList.end()) {
        for (const auto& neighbor : it->second) {
            if (!visited[neighbor]) {
                dfs2(neighbor, component);
            }
        }
    }
}

std::vector<std::vector<std::string>> SCCFinder::getSCCs() {
    visited.clear();
    order.clear();

    // 1st pass: order vertices by finish time
    for (const auto& pair : adjList) {
        if (!visited[pair.first]) {
            dfs1(pair.first);
        }
    }

    // 2nd pass: find SCCs in reversed graph
    std::vector<std::vector<std::string>> sccs;
    visited.clear();
    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        if (!visited[*it]) {
            std::vector<std::string> component;
            dfs2(*it, component);
            sccs.push_back(component);
        }
    }
    return sccs;
}