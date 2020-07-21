#include "Operator.h"
#include <iostream>
#include <vector>
using namespace std;


string Operator::getRealParam() const {
	return "NULL";
}
string Operator::realToFaktParam(string fakt_param) {
	return "NULL";
}

string Operator::expressionEval(string expr, vector<Operator*> objects) {
	return "NULL";
}

int Operator::toInt(string s) {
	stringstream geek(s);

	int x = 0;
	geek >> x;

	return x;
}
string Operator::toString(int a) {
	stringstream ss;
	ss << a;
	return ss.str();
}