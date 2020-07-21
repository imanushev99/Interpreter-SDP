#include "AssignmentFunction.h"
#include <iostream>
#include <vector>
using namespace std;

string AssignmentFunction::expressionEval(string expression, vector<Operator*> objects) {
	string error = "NULL";

	for (unsigned i = 0; i < expression.length(); i++) {
		string curr;
		if (expression[i] == ' ')
			i++;

		if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '%') {
			if (expression[i] == '/' && expression[++i] == '0') {
				cerr << "ERROR: CAN'T DIVIDE BY 0!" << endl;
				return error;
			}
			i++;
		}

		if (expression[i] == '(' || expression[i] == ')' || expression[i] == ' ')
			i++;

		if (expression[i] >= '0' && expression[i] <= '9')
			while (expression[i] >= '0' && expression[i] <= '9')
				i++;

		if (expression[i] >= 'a' && expression[i] <= 'z') {
			while (expression[i] >= 'a' && expression[i] <= 'z') {
				curr.push_back(expression[i]);
				i++;
			}
			bool valid_name = false;
			if (this->getRealParam().compare(curr) != 0) { //ако тази променлива не е реалния параметър на функцията, проверяваме във вектора с променливи
				for (unsigned int v = 0; v < objects.size(); v++) {
					if (curr.compare(objects[v]->getName()) == 0)
						valid_name = true;
				}
				if (!valid_name) {
					cerr << "ERROR(func): VAR WITH NAME " << curr << " NOT FOUND!" << endl;
					return error;
				}
			}
		}
		if (expression[i] >= 'A' && expression[i] <= 'Z') {
			while (expression[i] >= 'A' && expression[i] <= 'Z') {
				curr.push_back(expression[i]);
				i++;
			}
			bool valid_name = false;
			for (unsigned int v = 0; v < objects.size(); v++) {
				if (curr.compare(objects[v]->getName()) == 0)
					valid_name = true;
			}
			if (!valid_name) {
				cerr << "ERROR(func): FUNCTION WITH NAME " << curr << " NOT FOUND!" << endl;
				return error;
			}
			i++;

			string fakt_param;
			while (expression[i] != ']') {
				fakt_param.push_back(expression[i]);
				i++;
			}
			//проверка дали и фактическия параметър е валиден, без да го изчиславаме; 
			//изчисляваме го само когато викаме функцията в променлива или print, т.к сега във фактическия параметър може да се съдържа реалния параметър на текущата функция
			string fakt_param_correction = this->expressionEval(fakt_param, objects); 
			if (fakt_param_correction.compare("NULL") == 0) {
				cerr << "ERROR(func): FUNCTION WITH NAME " << curr << " HAS INVALID expressionESSION PARAMETER!" << endl;
				return false;
			}
		}
	}

	return expression;

}

string AssignmentFunction::realToFaktParam(string fakt_param) {
		string return_body = this->getExpression(); // взимаме тялото на функцията, за която този метод е извикан
		for (unsigned int i = 0; i < return_body.length(); i++) {
			string curr;
			if (return_body[i] == ' ' ||
				return_body[i] == '+' || return_body[i] == '-' ||
				return_body[i] == '*' || return_body[i] == '/' || return_body[i] == '%' ||
				return_body[i] == ']' || return_body[i] == '[' || return_body[i] == '(' || return_body[i] == ')' ||
				(return_body[i] >= '0' && return_body[i] <= '9') ||
				(return_body[i] >= 'A' && return_body[i] <= 'Z'))
				i++;
			if (return_body[i] >= 'a' && return_body[i] <= 'z') {
				int i_copy = i;
				while (return_body[i] >= 'a' && return_body[i] <= 'z') {
					curr.push_back(return_body[i]);
					i++;
				}
				if (curr.compare(this->getRealParam()) == 0) {
					return_body.replace(i_copy, this->getRealParam().length(), fakt_param);
				}
			}
		}
		return return_body;
}