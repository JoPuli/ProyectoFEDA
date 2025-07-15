#ifndef RANKING_H
#define RANKING_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

class Ranking {
public:
    // Constructor takes a reference to a user graph (adjacency list)
    Ranking(const std::unordered_map<std::string, std::unordered_set<std::string>>& graphF,
            const std::unordered_map<std::string, std::unordered_set<std::string>>& graphR);
    // graphF: adjacency list for followees
    // graphR: adjacency list for followers
    Ranking(const std::unordered_map<std::string, std::unordered_set<std::string>>& graphF,
            const std::string& way);
    // way: "followees" or "followers" to specify which graph to use
    // Returns a ranked list of users based on their number of followers and followees
    std::vector<std::string> getTopNFollowers(size_t N = 10); // Uses the followees list
    std::vector<std::string> getTopNInfluencers(size_t N = 10); // Uses the followers list
private:
    const std::unordered_map<std::string, std::unordered_set<std::string>>& adjList;
    const std::unordered_map<std::string, std::unordered_set<std::string>>& reversedAdjList;
};
#endif // RANKING_H