#ifndef USERGRAPH_H
#define USERGRAPH_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

class UserGraph {
public:
    UserGraph();
    void addUser(const std::string& username);
    void addConnection(const std::string& follower, const std::string& followee);
    std::unordered_set<std::string> getFollowers(const std::string& username) const;
    std::unordered_set<std::string> getFollowing(const std::string& username) const;
    std::unordered_map<std::string, std::unordered_set<std::string>> FollowersList;
    std::unordered_map<std::string, std::unordered_set<std::string>> FollowingList;
private:
    void updateUserStats(const std::string& username);
    size_t n_followers = 0;
    size_t n_following = 0;
};

#endif // USERGRAPH_H