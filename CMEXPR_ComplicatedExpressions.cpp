// ComplexExpression.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

const unsigned int SUB = 1;
const unsigned int ADD = 2;
const unsigned int MUL = 4;
const unsigned int DIV = 8;

int len;

bool
needBracket(const string& inp, int s, int e, int op) {
	if (inp[s] != '(' || inp[e] != ')') return true;

	if (s - 1 >= 0) {
		switch (inp[s - 1]) {
		case '/': return (op>0);

		case '*':
		case '-':
			if (op&ADD || op&SUB)
				return true;
			break;
		}
	}

	if (e + 1 < len) {
		switch (inp[e + 1]) {
		case '/':
		case '*':
			if (op&ADD || op&SUB)
				return true;
			break;
		}
	}

	return false;
}
inline
char getValue(const string& str, int ind) {
	if (ind < 0) return -1;
	return str[ind];
}
int main()
{
	int test;
	cin >> test;
	while (test--) {
		string inp;
		cin >> inp;
		len = inp.length();
		stack<int> st;
		unordered_map<int, int> removeInd;
		for (int i = 0; i < len; ++i) {
			if (inp[i] == ')') {
				unsigned int op = 0;
				while (getValue(inp, st.top()) != '(') {
					switch (getValue(inp, st.top())) {
					case '/':if ((op&DIV) == 0) op |= DIV; break;
					case '*':if ((op&MUL) == 0) op |= MUL; break;
					case '+':if ((op&ADD) == 0) op |= ADD; break;
					case '-':if ((op&SUB) == 0) op |= SUB; break;
					}
					st.pop();
				}

				int b = st.top() - 1, e = i + 1;
				while (b >= 0 && e < len) {
					if (inp[b--] == '(' && inp[e++] == ')') {
						removeInd[st.top()] = removeInd[i] = 1;
						st.pop(); i++;
					}
					else break;
				}

				if (!needBracket(inp, st.top(), i, op)) {
					removeInd[st.top()] = 1;
					removeInd[i] = 1;
				}
				st.pop();
				//dummy to replace right side of expression(that was enclosed within braces)
				//consider : a*(b+c) => after evaluating for (b+c) push -1 to stack[a * -1]
				st.push(-1);
			}
			else
				st.push(i);
		}

		string out;
		for (int i = 0; i < len; ++i) {
			if (!removeInd[i])
				out.push_back(inp[i]);
		}
		cout << out << endl;
	}
	return 0;
}

