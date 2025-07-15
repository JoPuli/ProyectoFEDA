#include "PoliticalAnalyzer.h"

SCCPoliticalProfile::SCCPoliticalProfile(const std::vector<User>& members)
    : members(members) {
    // Initialize topNinfluencers based on members' followers count
    
    // Sort descending by follower count
    std::sort(members.begin(), members.end(),
              [](const auto& a, const auto& b) { return a.followers_count > b.followers_count; });

    std::vector<std::string> result;
    for (size_t i = 0; i < members.size() && i < 10; ++i) {
        result.push_back(members[i].user_name);
    }
    return result;
}

// Assign tendency based on direct newspaper follows
void SCCPoliticalProfile::assignPureOrMixedTendency(
    const std::unordered_map<std::string, std::string>& newspaperTendencies,
    const UserGraph& userGraph,
    const std::unordered_set<std::string>& newspapers)
{
    std::unordered_set<std::string> foundTendencies;
    for (const auto& user : members) {
        const auto& following = userGraph.getFollowing(user);
        for (const auto& newspaper : newspapers) {
            if (following.count(newspaper)) {
                foundTendencies.insert(newspaperTendencies.at(newspaper));
            }
        }
    }
    if (!foundTendencies.empty()) {
        double weight = 1.0 / foundTendencies.size();
        for (const auto& tendency : foundTendencies) {
            tendencyWeights.weights[tendency] = weight;
        }
        tendencyWeights.normalize();
    }
}

// Assign tendency based on top influencers in SCC
void SCCPoliticalProfile::assignByInfluencers(
    const std::unordered_map<std::string, SCCPoliticalProfile*>& userToSCC)
{
    if (topNInfluencers.empty()) return;
    std::unordered_map<std::string, double> sumWeights;
    for (const auto& influencer : topNInfluencers) {
        auto it = userToSCC.find(influencer);
        if (it != userToSCC.end()) {
            const auto& infWeights = it->second->getTendencyWeights().weights;
            for (const auto& pair : infWeights) {
                sumWeights[pair.first] += pair.second;
            }
        }
    }
    // Average the weights
    for (auto& pair : sumWeights) {
        pair.second /= topNInfluencers.size();
    }
    tendencyWeights.weights = sumWeights;
    tendencyWeights.normalize();
}

const TendencyWeights& SCCPoliticalProfile::getTendencyWeights() const {
    return tendencyWeights;
}

