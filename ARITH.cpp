#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

#define NOT_EXPECTED 0

void parse(const string& exp, string& num1, string& num2, string& op) {	
	size_t pos = exp.find_first_of("+-*");
	assert(pos != string::npos);	
	num1 = exp.substr(0, pos);
	num2 = exp.substr(pos + 1, string::npos);
	op = string(1,exp[pos]);
}

void addition(const string& num1, const string& num2, string& out) {
	int len1 = num1.size(), len2 = num2.size();
	out.resize(max(len1, len2));
	int i = len1-1, j = len2-1, k = max(len1,len2)-1 , carry=0;
	while (i >= 0 || j >= 0) {
		int sum = carry + (i >= 0 ? num1[i--] - '0' : 0) + (j >= 0 ? num2[j--] - '0' : 0);
		carry = (sum > 9 ? 1 : 0);		
		out[k--] = 48 + sum % 10;
	}
	if (carry) out = "1" + out;
}

void subtraction(const string& num1, const string& num2, string& out) {
	if (num1 == num2) {
		out = "0";		
	}
	else {
		int len1 = num1.size(), len2 = num2.size();
		out.resize(len1,'0');
		int i = len1 - 1, j = len2 - 1, k = len1 - 1, borrow = 0;
		while (i >= 0) {
			int val = num1[i]-'0';
			if (borrow > 0) {
				if (val >= borrow) {
					val -= borrow;
					borrow = 0;
				}
				else {
					val = val + 10 - borrow;
				}
			}
			char ch = val + '0';
			if (j >= 0) {
				if (ch >= num2[j]) {					
					out[k--] = ch - num2[j] + '0';
				}
				else {
					borrow++;
					out[k--] = (char)(10 + ch - num2[j] + '0');
				}
				j--;
			}
			else {
				out[k--] = ch;
			}
			i--;
		}
		out.erase(0,out.find_first_not_of("0"));
	}
}

void multiply(const string& num1,int len, char ch, string& out) {
	if (ch == '0') {
		out = "0";
	}
	else {
		int carry = 0, val = ch - '0';
		out.resize(len);
		for (int i = len - 1, k = i; i >= 0; i--) {
			int prod = (num1[i] - '0')*val + carry;
			carry = prod / 10;
			out[k--] = (prod % 10) + '0';
		}
		if (carry) {
			out = string(1, carry + '0') + out;
		}
	}	
}

inline void printString(int spaces, const string& s) {
	for (int i = 0; i < spaces; ++i) { cout << ' '; }
	cout << s << endl;
}

int main()
{
	int test;
	cin >> test;
	while (test--) {
		string exp, num1, num2, op, result;
		cin >> exp;		

		parse(exp, num1, num2, op);

		if (op == "+" || op == "-") {
			if(op == "+")
				addition(num1, num2, result);
			else
				subtraction(num1, num2, result);
			size_t dashes = max(result.size(), num2.size() + 1);
			int maxLen = max(dashes, num1.size());
			printString(maxLen - num1.size(), num1);			
			printString(maxLen - num2.size() - 1, op + num2);			
			printString(maxLen - dashes,string(dashes,'-'));
			printString(maxLen - result.size(),result);			
		}		
		else if (op == "*") {
			size_t len1 = num1.size(), len2 = num2.size();
			vector<string> vecResult(len2);			
			string suffix = "0";

			//calculating partial multiplication result and storing in a vector of string
			for (int i = len2 - 1; i >= 0; i--) {
				multiply(num1, len1, num2[i], vecResult[i]);
				if (i == len2 - 1) result = vecResult[i];
				else {
					addition(vecResult[i]+suffix, result , result);
					suffix += "0";					
				}
			}

			//printing the multiplication result
			size_t first_dash_len = max(vecResult[len2 - 1].size(), len2 + 1);
			int maxLen = max(result.size(),max(first_dash_len,len1));			
			printString(maxLen - len1, num1);
			printString(maxLen - len2 - 1, "*" + num2);			
			printString(maxLen - first_dash_len, string(first_dash_len, '-'));			
			for (int i = len2 - 1,j=0; i >= 0; i--,j++) {
				printString(maxLen - vecResult[i].size()-j, vecResult[i]);				
			}

			//this means second dash line has to be drawn
			if (len2 > 1) {
				size_t second_dash_len = max(result.size(), vecResult[0].size() + len2 - 1);
				printString(maxLen - second_dash_len, string(second_dash_len,'-'));
				printString(maxLen-result.size(), result);				
			}
		}
		else {
			assert(NOT_EXPECTED);
		}

		cout << endl;
	}
    return 0;
}