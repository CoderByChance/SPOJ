// SPOJ_CMPLS_CompleteTheSequence.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int test;
	cin >> test;
	while (test--) {
		int n, c;
		cin >> n >> c;
		vector<int> inp(n) , result;
		bool isSame = true;
		for (int i = 0; i < n; ++i) {
			cin >> inp[i];
			if (i > 0 && inp[i] != inp[i - 1]) isSame = false;
		}

		if (isSame == true) {
			result.resize(c, inp[0]);
		}
		else {
			vector<vector<int> > diffTab;
			diffTab.push_back(inp);
			isSame = false;
			for (int cnt = 1; cnt <= n - 1 && !isSame; ++cnt) {
				vector<int> diffVec(n-cnt);			
				auto& prevVec = diffTab.back();

				isSame = true;
				int diff;
				for (int i = 0; i < n - cnt; ++i) {					
					diffVec[i] = prevVec[i + 1] - prevVec[i];
					if (i == 0) diff = diffVec[i];
					else if (diff != diffVec[i]) isSame = false;
				}
				diffTab.push_back(diffVec);
			}
			
			for (int i = 0; i < c; ++i) {
				for (int j = diffTab.size() - 2; j >= 0; --j) {
					diffTab[j].push_back(diffTab[j].back() + diffTab[j+1].back());
				}
				result.push_back(diffTab[0].back());
			}
		}

		for_each(result.begin(), result.end(), [](int i) {cout << i << " "; });
		cout << endl;
	}
    return 0;
}

