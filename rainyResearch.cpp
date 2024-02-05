//
// Created by iansg on 2/5/2024.
//

#include <set>
#include <climits>
#include <unordered_map>
using namespace std;

class rainy_research {
    unordered_map<double,set<pair<int,int>>> um {};
public:
    rainy_research() = default;
    void record_data(int r, double l, int t) {
        auto it = um[l].lower_bound({t-1,INT_MAX});
        if (it != um[l].end() && it->second >= r) return;
        if (it == um[l].begin()) {
            um[l].emplace(l, r);
            return;
        }
        while (--it != um[l].begin() && it->second <= r) {
            it = um[l].erase(it);
        }
        um[l].emplace(l,r);
    }
    int peak_rainfall(double l, int t) {
        auto it = um[l].lower_bound({t, INT_MAX});
        if (it != um[l].end()) return it->second;
        else return 0;
    }
};

