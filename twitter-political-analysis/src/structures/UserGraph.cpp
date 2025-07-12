#include "UserGraph.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

class UserGraph {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>> adjacencyList;
};

UserGraph::UserGraph() {}

void UserGraph::addUser(const std::string& username) {
    adjacencyList[username]; // Create an entry if it doesn't exist
}

void UserGraph::addConnection(const std::string& follower, const std::string& followee) {
    addUser(follower);
    addUser(followee);
    adjacencyList[follower].insert(followee);
}

std::unordered_set<std::string> UserGraph::getFollowers(const std::string& username) const {
    std::unordered_set<std::string> followers;
    for (const auto& pair : adjacencyList) {
        if (pair.second.find(username) != pair.second.end()) {
            followers.insert(pair.first);
        }
    }
    return followers;
}

std::unordered_set<std::string> UserGraph::getFollowing(const std::string& username) const {
    auto it = adjacencyList.find(username);
    if (it != adjacencyList.end()) {
        return it->second;
    }
    return {};
}