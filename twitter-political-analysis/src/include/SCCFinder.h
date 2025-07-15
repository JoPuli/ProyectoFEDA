#ifndef SCCFINDER_H
#define SCCFINDER_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

class SCCFinder {
public:
    // Constructor takes a reference to a user graph (adjacency list)
    SCCFinder(const std::unordered_map<std::string, std::unordered_set<std::string>>& graphF,
              const std::unordered_map<std::string, std::unordered_set<std::string>>& graphR);

    // Returns all strongly connected components as vectors of usernames
    std::vector<std::vector<std::string>> getSCCs();

private:
    const std::unordered_map<std::string, std::unordered_set<std::string>>& adjList;
    const std::unordered_map<std::string, std::unordered_set<std::string>>& reversedAdjList;
    std::unordered_map<std::string, bool> visited;
    std::vector<std::string> order;
    

    void dfs1(const std::string& node);
    void dfs2(const std::string& node, std::vector<std::string>& component);
};

#endif // SCCFINDER_H