#include <bits/stdc++.h>
#include <fstream>
using namespace std;

vector<char> readFileIntoVector(string fileName) {
    vector<char> data;
    ifstream file;
    file.open(fileName, ios::in);
    char reader;
    while (file >> reader) {
        data.push_back(reader);
    }


    // for (auto p : data) {
    //     cout << p << '\n';
    // }
    // cout << data.size() << '\n';
}