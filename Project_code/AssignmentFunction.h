#include <iostream>
#include <string>
#include <vector>
#include "Operator.h"

using namespace std;
#pragma once

class AssignmentFunction :public Operator {
private:
	string real_param;
public:
	AssignmentFunction(string n, string rp) {
		setRealParam(rp);
		setName(n);
		setExpression("NULL");
	};
	virtual string getRealParam() const { return real_param; }
	void setRealParam(string rp) { real_param.assign(rp); }

	virtual string realToFaktParam(string fakt_param);
	virtual string expressionEval(string expr, vector<Operator*> objects);

};