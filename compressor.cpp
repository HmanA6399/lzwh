#include <bits/stdc++.h>
#include "Node.cpp"
using namespace std;

class Compressor
{
    const int MAX_CHAR_COUNT = 256;

    unordered_map<unsigned int, unsigned int> freq;
    unordered_map<string, unsigned int> dict;
    unordered_map<unsigned int, string> dict_inv;
    unsigned int dict_cur_pos = 0, dict_inv_cur_pos = 0;
    vector<Node> huffmanDict;
    ifstream iFile;
    ofstream oFile;

    void initDict(bool isInv)
    {
        string cur = "";
 
        if (isInv)
            dict_inv_cur_pos = 0;
        else
            dict_cur_pos = 0;
 
        for (int i = 0; i < MAX_CHAR_COUNT; ++i)
        {
            cur += (char)dict_cur_pos;

            if (isInv)
                dict_inv[dict_inv_cur_pos++] = (char)i;
            else
                dict[cur] = dict_cur_pos++;

            cur = "";
        }
    }

    void constructHuffmanDict() {
        for (auto it : freq) {
            Node tmp(it.first, it.second);
            huffmanDict.push_back(tmp);
        }

        while (huffmanDict.size() > 1) {
            pop_heap(huffmanDict.begin(), huffmanDict.end());
            Node n1 = huffmanDict.back(); huffmanDict.pop_back();
 
            pop_heap(huffmanDict.begin(), huffmanDict.end());
            Node n2 = huffmanDict.back(); huffmanDict.pop_back();

            Node n3 = n1 + n2;
            n3.r = &n1; n3.l = &n2;

            huffmanDict.push_back(n3); push_heap(huffmanDict.begin(), huffmanDict.end());
        }
    }

    void generateCodes(Node* cur, int code) {
        if (cur == nullptr)
            return;
        if (cur && cur->entity != 0) {
            cout << cur->entity << " " << code << '\n';
            oFile << cur->entity << code;
            return;
        }
        generateCodes(cur->l, code<<1);
        generateCodes(cur->r, code<<1 + 1);
    }

    void addFreq(int e)
    {
        if (!freq.count(e)) {
            freq.insert({e, 0});
        } else 
        freq[e]++;
    }

public:
    Compressor(string ifi, string ofi)
    {
        iFile.open(ifi, ios::binary);
        oFile.open(ofi, ios::binary | ios::out | ios::trunc);
    }

    ~Compressor() {
        iFile.close();
        oFile.close();
    }

    void encode()
    {
        dict.clear();
        initDict(0);
        stringstream intermediate;
        char nextChar;
        string buf = "";

        while (iFile.get(nextChar))
        {
            if (dict.find(buf + nextChar) != dict.end())
            {
                buf += nextChar;
            }
            else
            {
                intermediate << dict[buf] << " ";
                addFreq(dict[buf]);
                dict[buf + nextChar] = dict_cur_pos++;
                buf = "";
                buf += nextChar;
            }
        }

        intermediate << dict[buf] << " ";

        constructHuffmanDict();
        generateCodes(&(huffmanDict[0]), 0);
    }

    void decode()
    {
        dict_inv.clear();
        initDict(1);

        stringstream intermediate;
        
        unsigned int nextCode;
        string buf = "", cur;
        iFile >> nextCode;
        cur = dict_inv[nextCode];
        oFile << cur;
        buf = cur;

        while (iFile >> nextCode) {
            cur = dict_inv[nextCode];

            oFile << cur;

            dict_inv[dict_inv_cur_pos++] = buf + cur[0];

            buf = cur;
        }
        iFile.close();
        oFile.close();
    }

    void testDict()
    {
        for (auto const &p : dict)
        {
            if (p.second >= MAX_CHAR_COUNT) cout << std::hex << p.first << " => " << std::dec << p.second << '\n';
        }
    }
};
