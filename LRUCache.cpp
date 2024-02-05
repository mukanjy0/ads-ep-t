//
// Created by iansg on 2/5/2024.
//

#include<queue>
#include<memory.h>
using namespace std;

class LRUCache {
    int sz{}, capacity {};
    static const int N = 1e4;
    int val[N+1];
    int cnt[N+1];
    queue<int> q {};
public:
    LRUCache(int capacity) : capacity(capacity) {
        memset(val,-1,sizeof(val));
        memset(cnt,0,sizeof(cnt));
    }

    int get(int key) {
        if (val[key] >= 0) {
            q.push(key);
            ++cnt[key];
        }
        return val[key];
    }

    void put(int key, int value) {
        q.push(key);
        ++cnt[key];
        if (val[key] >= 0) {
            val[key]=value;
            return;
        }
        ++sz;
        val[key]=value;
        if (sz <= capacity) return;
        --sz;
        int k = q.front();
        while (--cnt[k]) {
            q.pop();
            k = q.front();
        }
        val[k]=-1;
        q.pop();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
