#include <bits/stdc++.h>
using namespace std;

int main() {
    unordered_map<char, int> mp = {{'A', 1}, {'C', 3}, {'q', 20}, {'D', 4}};
    vector<int> vec;

    for (auto it : mp) {
        vec.push_back(it.second);// push_heap(vec.begin(), vec.end());
    }
    
    make_heap(vec.begin(), vec.end());

    while (vec.size()) {
        pop_heap(vec.begin(), vec.end());
        cout << vec.back() << '\n';
        vec.pop_back();
    }
}