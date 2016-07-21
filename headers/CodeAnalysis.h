#pragma once
#include<cstring>
#include"core\StringMatcher.h"
using namespace std;
class Counter {
	int count;
public:
	Counter() {
		count = 0;
	}
	void push() { count++; }
	void pop() { count--; }
	bool empty() { return !count; }
};
bool examine(string &code){//true for good code
	Counter countС����, count������;
	for (int i = 0; i < code.length(); i++) {
		switch (code[i]) {
		case '(':
			countС����.push();
			break;
		case ')':
			countС����.pop();
			break;
		case '{':
			count������.push();
			break;
		case '}':
			count������.pop();
			break;
		}
	}
	if (!count������.empty())return false;
	if (!countС����.empty())return false;
	return true;
}