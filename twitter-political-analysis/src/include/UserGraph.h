#ifndef USERGRAPH_H
#define USERGRAPH_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class UserGraph {
public:
    UserGraph();
    void addUser(const std::string& username);
    void addConnection(const std::string& follower, const std::string& followee);
    std::vector<std::string> getFollowers(const std::string& username) const;
    std::vector<std::string> getFollowing(const std::string& username) const;

private:
    std::unordered_map<std::string, std::unordered_set<std::string>> adjacencyList;
};

#endif // USERGRAPH_H