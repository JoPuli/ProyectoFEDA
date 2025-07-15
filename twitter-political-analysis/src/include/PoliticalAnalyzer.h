#ifndef SCC_POLITICAL_PROFILE_H
#define SCC_POLITICAL_PROFILE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <numeric>
#include "UserGraph.h"
#include "Ranking.h"
#include "SCCFinder.h"


struct TendencyWeights {
    std::unordered_map<std::string, double> weights; // e.g. {"izquierda": 0.5, "derecha": 0.5}

    void normalize() {
        double sum = 0.0;
        for (const auto& pair : weights) sum += pair.second;
        if (sum > 0.0) {
            for (auto& pair : weights) pair.second /= sum;
        }
    }
};

class SCCPoliticalProfile {
public:
    SCCPoliticalProfile(const std::vector<std::string>& members);

    // Assign tendency based on direct newspaper follows
    void assignPureOrMixedTendency(const std::unordered_map<std::string, std::string>& newspaperTendencies,
                                   const UserGraph& userGraph,
                                   const std::unordered_set<std::string>& newspapers);

    // Assign tendency based on top influencers in SCC
    void assignByInfluencers(const std::unordered_map<std::string, SCCPoliticalProfile*>& userToSCC);

    // Get normalized tendency weights
    const TendencyWeights& getTendencyWeights() const;

    // SCC members
    std::vector<std::string> members;

private:
    TendencyWeights tendencyWeights;
    std::vector<std::string> topNInfluencers;
};

#endif // SCC_POLITICAL_PROFILE_H