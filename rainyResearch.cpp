//
// Created by iansg on 2/5/2024.
//

#include <set>
#include <climits>
#include <unordered_map>
#include <random>
#include <cassert>
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

void test() {
    random_device rd;
    mt19937 rng(rd());
    uniform_real_distribution distLat(-180., 180.);
    uniform_int_distribution distTime(1, 1000);
    uniform_int_distribution distR(1, 100000);

    rainy_research res;
    unordered_map<double,set<pair<int,int>>> um;
    for (int i = 0; i < 1000; ++i) {
        double lat = distLat(rng);
        int t = distTime(rng), r = distR(rng);
        res.record_data(r, lat, t);
        um[lat].emplace(t, r);
    }
    for (int i = 0; i < 1000; ++i) {
        double lat = distLat(rng);
        int t = distTime(rng);
        auto ans = res.peak_rainfall(lat, t);
        int correct_ans = 0;
        for (auto it = um[lat].lower_bound({t, INT_MIN}); it != um[lat].end(); ++it)
            correct_ans = max(correct_ans, it->second);
        assert(ans == correct_ans);
    }
}

int main() {
    test();
    return 0;
}

