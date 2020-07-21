#include <iostream>
#include <string>
#include <stack>
#include "Operator.h"

using namespace std;
#pragma once

class Print :public Operator {
private:
public:
	Print() {
		this->setName("Print");
		this->setExpression("NULL");
	}

	virtual string expressionEval(string expr, vector<Operator*> objects);
};