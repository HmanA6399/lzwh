#include <bits/stdc++.h>
using namespace std;

class Compressor
{
    const int MAX_CHAR_COUNT = 256;

    unordered_map<string, unsigned int> dict;
    unordered_map<unsigned int, string> dict_inv;
    unsigned int dict_cur_pos = 0, dict_inv_cur_pos = 0;
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

    inline bool read3Bytes(int& n) {
        char bytes[3];
        iFile.read(bytes, 3);

        n = int(
            (unsigned char)bytes[0]<<16 |
            (unsigned char)bytes[1]<<8 |
            (unsigned char)bytes[2]
        );

        return !iFile.eof();
    }

    inline void write3bytes(int n) {
        char bytes[3] = {
            (unsigned char) (n >> 16) & 0xFF,
            (unsigned char) (n >> 8) & 0xFF,
            (unsigned char) (n) & 0xFF
        };

        oFile.write(bytes, 3);
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
        initDict(0);
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
                write3bytes(dict[buf]);
                dict[buf + nextChar] = dict_cur_pos++;
                buf = "";
                buf += nextChar;
            }
        }

        write3bytes(dict[buf]);
    }

    void decode()
    {
        initDict(1);
        int nextCode;
        string buf = "", cur;
        read3Bytes(nextCode);
        cur = dict_inv[nextCode];
        oFile << cur;
        buf = cur;

        while (read3Bytes(nextCode)) {
            cur = dict_inv[nextCode];

            oFile << cur;

            dict_inv[dict_inv_cur_pos++] = buf + cur[0];

            buf = cur;
        }
    }

    void testDict()
    {
        for (auto const &p : dict)
        {
            if (p.second >= MAX_CHAR_COUNT) cout << std::hex << p.first << " => " << std::dec << p.second << '\n';
        }
    }
};
