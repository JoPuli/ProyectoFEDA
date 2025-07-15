#include "Ranking.h"
#include <stdexcept>

Ranking::Ranking(
    const std::unordered_map<std::string, std::unordered_set<std::string>>& graphF,
    const std::unordered_map<std::string, std::unordered_set<std::string>>& graphR)
    : adjList(graphF), reversedAdjList(graphR) {}
    // graphF: adjacency list for followees
    // graphR: adjacency list for followers
Ranking::Ranking(
    const std::unordered_map<std::string, std::unordered_set<std::string>>& graphF,
    const std::string& way)
    : adjList(way == "followees" ? graphF : std::unordered_map<std::string, std::unordered_set<std::string>>{}),
      reversedAdjList(way == "followers" ? graphF : std::unordered_map<std::string, std::unordered_set<std::string>>{})
{
    if (way != "followees" && way != "followers") {
        throw std::invalid_argument("Invalid way specified. Use 'followees' or 'followers'.");
    }
}
std::vector<std::string> Ranking::getTopNInfluencers(size_t N) {
    // Get the top N influencers based on follower count
    // Influencers are determined by the number of followers they have
    // in the reversed adjacency list (reversedAdjList).
    // If N is 0, return an empty vector
    if (N == 0) {
        return {};
    }
    // Ensure N is not larger than the number of users
    if (N > reversedAdjList.size()) {
        N = reversedAdjList.size();
    }
    if (reversedAdjList.empty()) {
        return {};
    }
    // Influencers: users with the most followers (in reversedAdjList)
    std::vector<std::pair<std::string, size_t>> counts;
    for (const auto& pair : reversedAdjList) {
        counts.emplace_back(pair.first, pair.second.size());
    }
    // Sort descending by follower count
    std::sort(counts.begin(), counts.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    std::vector<std::string> result;
    for (size_t i = 0; i < counts.size() && i < N; ++i) {
        result.push_back(counts[i].first);
    }
    return result;
}

std::vector<std::string> Ranking::getTopNFollowers(size_t N) {
    // Get the top N users based on the number of followees
    // Followees are determined by the number of users they follow
    // in the adjacency list (adjList).
    // This is the opposite of influencers, focusing on who follows the most users.
    // If N is 0, return an empty vector
    if (N == 0) {
        return {};
    }
    // Ensure N is not larger than the number of users
    if (N > adjList.size()) {
        N = adjList.size();
    }
    if (adjList.empty()) {
        return {};
    }
    // Followers: users who follow the most others (in adjList)
    std::vector<std::pair<std::string, size_t>> counts;
    for (const auto& pair : adjList) {
        counts.emplace_back(pair.first, pair.second.size());
    }
    // Sort descending by following count
    std::sort(counts.begin(), counts.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    std::vector<std::string> result;
    for (size_t i = 0; i < counts.size() && i < N; ++i) {
        result.push_back(counts[i].first);
    }
    return result;
}