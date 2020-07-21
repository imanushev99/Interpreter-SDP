#include <iostream>
#include <string>
#include <vector>
#include "Operator.h"

using namespace std;
#pragma once

class AssignmentVar : public Operator {
private:
	
public:
	AssignmentVar(string n) {
		setName(n);
		setExpression("NULL");
	}
	
	virtual string expressionEval(string expr, vector<Operator*> objects);
};