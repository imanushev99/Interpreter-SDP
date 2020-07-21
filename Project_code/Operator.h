#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
#pragma once

class Operator {
private:
	string name;
	string expression;
public:
	Operator(string n = "NULL", string expr = "NULL") : name(n), expression(expr) {};
	Operator(string _name) { 
		name.assign(_name);
		expression.assign("NULL");
	}

	string getName() const { return name; }
	int getNameLength() const { return name.length(); }
	void setName(string n) { name.assign(n); }

	string getExpression() const { return expression; }
	bool setExpression(string s) { expression.assign(s); return true; }

	virtual string getRealParam() const;
	virtual string realToFaktParam(string fakt_param);

	virtual string expressionEval(string expr, vector<Operator*> objects); // ако има грешка във функцията, връща "NULL"

	int toInt(string s);
	string toString(int a);

};