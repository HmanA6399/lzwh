#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
	unordered_map<char, unsigned int> freq;
	unsigned long charCount = 0;
	float entropy = 0;

	ifstream iFile;

	iFile.open(argv[1], ios::binary);

	char now;


	while (iFile.get(now)) {
		charCount++;
		if (!freq.count(now))
			freq.insert({now, 0});
		freq[now]++;
	}

	cout << "Total no of characters : " << charCount << '\n';
	for (auto p : freq) {
		entropy += ((p.second+0.0f)/charCount) * log2((charCount+0.0f)/p.second);
	}

	cout << "Entropy : " << entropy << '\n';
}
