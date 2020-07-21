#include "Print.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <stack>
using namespace std;


string Print::expressionEval(string expression, vector<Operator*> objects) {
	stack<int> values;
	stack<char> operations;
	int operand1;
	int operand2;
	string curr;

	string error = "ERROR!";

	for (unsigned i = 0; i < expression.length(); i++) {
		if (expression[i] == ' ')
			i++;

		if (expression[i] >= '0' && expression[i] <= '9') {
			while (expression[i] >= '0' && expression[i] <= '9') {
				curr.push_back(expression[i]);
				i++;
			}
			operand1 = toInt(curr);
			values.push(operand1);
			curr.erase();
		}

		if (expression[i] >= 'a' && expression[i] <= 'z') {
			while (expression[i] >= 'a' && expression[i] <= 'z') {
				curr.push_back(expression[i]);
				i++;
			}
			bool valid = false;
			for (unsigned int v = 0; v < objects.size(); v++) {
				if (curr.compare(objects[v]->getName()) == 0) {
					operand1 = toInt(objects[v]->getExpression());
					values.push(operand1);
					valid = true;
				}
			}
			if (!valid) {
				cerr << "ERROR(expression_evaluation): VAR WITH NAME " << curr << " DOESN'T EXIST!" << endl;
				return error;
			}
			curr.erase();
		}

		if (expression[i] >= 'A' && expression[i] <= 'Z') {
			string func_realparam;
			string func_faktparam;
			while (expression[i] >= 'A' && expression[i] <= 'Z') {
				curr.push_back(expression[i]); //име на функцията
				i++;
			}
			while (expression[++i] != ']') {
				func_faktparam.push_back(expression[i]); //фактическият параметър на функцията, с когото ще заместим реалния параметър;
			}
			bool valid = false;
			for (unsigned int v = 0; v < objects.size(); v++) {
				if (curr.compare(objects[v]->getName()) == 0) {
					valid = true;
					string new_body = objects[v]->realToFaktParam(func_faktparam); //тялото на функцията след заместване с фактическия параметър
					string new_body_value = this->expressionEval(new_body, objects);
					if (new_body_value.compare(error) == 0)
						return error;
					values.push(toInt(new_body_value));
				}

			}
			if (!valid) {

				cerr << "ERROR(expression_evaluation): FUNCTION WITH NAME " << curr << " NOT FOUND!" << endl;
				return error;
			}
			curr.erase();
		}

		if (expression[i] == '(') {
			operations.push('(');
		}

		if (expression[i] == ')') {
			while (operations.top() != '(') {
				char op = operations.top();
				operations.pop();
				if (op != '(') {
					operand1 = values.top();
					values.pop();
					operand2 = values.top();
					values.pop();
					if (op == '+')  values.push(operand1 + operand2);
					else if (op == '-') values.push(operand2 - operand1);
					else if (op == '*') values.push(operand1 * operand2);
					else if (op == '/') values.push(operand2 / operand1);
					else if (op == '%') values.push(operand2 % operand1);
				}

			}
			operations.pop(); //за '('
		}


		if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '%') {
			char thisOp = expression[i];
			if (!operations.empty()) {
				while ((!operations.empty()) &&
					(thisOp == '+' || thisOp == '-') &&
					(operations.top() == '*' || operations.top() == '/' || operations.top() == '%' || operations.top() == '+' || operations.top() == '-')) {

					char op = operations.top();
					operations.pop();
					operand1 = values.top();
					values.pop();
					operand2 = values.top();
					values.pop();
					if (op == '+') values.push(operand1 + operand2);
					else if (op == '-') values.push(operand2 - operand1);
					else if (op == '*') values.push(operand1 * operand2);
					else if (op == '/') values.push(operand2 / operand1);
					else if (op == '%') values.push(operand2 % operand1);
				}
				while ((!operations.empty()) &&
					(thisOp == '*' || thisOp == '/' || thisOp == '%') &&
					(operations.top() == '*' || operations.top() == '/' || operations.top() == '%')) {
					char op = operations.top();
					operations.pop();
					operand1 = values.top();
					values.pop();
					operand2 = values.top();
					values.pop();
					if (op == '*') values.push(operand1 * operand2);
					else if (op == '/') values.push(operand2 / operand1);
					else if (op == '%') values.push(operand2 % operand1);
				}
			}
			operations.push(thisOp);
		}


	}

	while (!operations.empty()) {

		char op = operations.top();
		operations.pop();

		operand1 = values.top();
		values.pop();

		operand2 = values.top();
		values.pop();

		if (op == '+') values.push(operand1 + operand2);
		else if (op == '-') values.push(operand2 - operand1);
		else if (op == '*') values.push(operand1 * operand2);
		else if (op == '/') values.push(operand2 / operand1);
		else if (op == '%') values.push(operand2 % operand1);
	}
	if (operations.empty() && values.size() == 1) {
		string return_value = toString(values.top());
		return return_value;
	}
	else {
		cerr << "ERROR(expression_evaluation): expressionESSION NOT EVALUATED!" << endl;
		return error;
	}
}
