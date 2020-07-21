#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include "Operator.h"
#include "AssignmentFunction.h"
#include "AssignmentVar.h"
#include "Print.h"
using namespace std;

bool readRow(string row, vector<Operator*>& objects) {
	//size_t find (const string& str, size_t pos = 0); ����� ������� �� ��������� �� ������� ������� �� str; ��� �� �� ����� ������, ����� string::npos
	if (row.find("=") != string::npos) { 
	//������� � ���� "=" => ��� �������� �� ����������� �� ����
	//���� ������ �� ����� ���� � ����������� �� ������� ��� �� ����������;
	//��� � �� ����������, ����� "=" �� ������ �� ��� '[' ��� ']' �����; ������� ���� ���� �� ��� � ������, ����� �� ���������, �.� � ���� ���� �� ���� ��������� ����� ���� ���������� �������, ���� ���������� ���������;

		
		//----------------------------------------------------- FUNCTION -----------------------------------------------------
		if (row.find('[') != string::npos && row.find('[') < row.find('=')) { //��� �������, �� �� � �����, � �� � ������
			string name;
			string real_param;
			string body;

			for (unsigned int i = 0; i < row.find('['); i++) {
				if (row[i] < 'A' || row[i]>'Z') {
					cerr << "ERROR: FUNCTION NAME MUST CONTAIN ONLY CAPITAL LETTERS!" << endl;
					return false;
				}
				name.push_back(row[i]); //��� �� ���������
			}
			for (unsigned int i = row.find('[') + 1; row[i] >= 'a' && row[i] <= 'z'; i++) {
				if (row[i] < 'a' || row[i]>'z') {
					cerr << "ERROR: FUNCTION REAL PARAMETER MUST CONTAIN ONLY SMALL LETTERS!" << endl;
					return false;
				}
				real_param.push_back(row[i]); //������ ���������
			}

			std::cout << " /// NAME: " << name << endl;

			for (unsigned int i = row.find('=') + 1; i < row.length(); i++)
				body.push_back(row[i]); //���� �� ���������

			for (unsigned int i = 0; i < objects.size(); i++) {
				if (name.compare(objects[i]->getName()) == 0) {
					std::cout << "ERROR: FUNCTION WITH THE SAME NAME ALREADY EXIST!" << endl;
					return false;
				}
			}
			if (body.find(real_param) == string::npos) {
				std::cout << "ERROR: FUNCTION PARAMETER DOESN'T EXIST IN FUNCTION EXPRESSION!" << endl;
				return false;
			}

			//��� ����������� �� �-���, �� ����������� ������, � ���� ����������� ���� ��� � ���� ����������, ����� �� �� ���������� ����� ����;
			Operator* f = new AssignmentFunction(name, real_param); // ������� �� ����� �������, ����� ��� ���� ��� � �������� ���������; ������������ ���� ���������� ������� ����������� ���� ������ � �����, �� �� �� set-��� �� expression � ������; ��� �� � ����� ����� ������ � ������ ������;
			string function_expression = f->expressionEval(body, objects);
			if (function_expression.compare("NULL") == 0) {
				cerr << "ERROR: FUNCTION BODY NOT CORRECT!" << endl;
				delete f;
				return false;
			}
			f->setExpression(function_expression);
			objects.push_back(f);
			return true;
		}
		else {
			//----------------------------------------------------- VAR -----------------------------------------------------
			if ((row.find('[') != string::npos && row.find('[') > row.find('=')) || row.find('[') == string::npos) {
				string name;

				for (unsigned int i = 0; i < row.find('='); i++) {
					if (row[i] < 'a' || row[i] > 'z') {
						cerr << "ERROR: VAR NAME MUST CONTAIN ONLY SMALL LETTERS!" << endl;
						return false;
					}
					name.push_back(row[i]); //��� �� ���������
				}
				if (objects.size() > 0) {
					for (unsigned int i = 0; i < objects.size(); i++) {
						if (name.compare(objects[i]->getName()) == 0) {
							std::cout << "ERROR: VAR WITH THE SAME NAME ALREADY EXIST!" << endl;
							return false;
						}
					}
				}

				std::cout << " /// NAME: " << name << endl;

				//��� ����������� �� ���������� var, ���������� �������� �-��� �� ���� �� �������, ������ �� ������������ � ����������� ��������� ��������
				//���� �-��� �� �� ���� � �����, ������ ��� ��������� �� �-��� � ���������� ���������
				//�.�. ��������� ������ �� ����� �����, ������ �� � int, �� �.� expr � Operator � �� ��� string (�� �� ���� �� �� ��������� � ���� �� ������), ��������� �� ���������� �� ����� �� ����� string, �� ����� � ���� ��, �� �� �������� ���������� �� ������������ int � string
				//�� ��� � ������������ ���������� valid, ����� ��� ��� ��������� ����� �� ����� 0;

				Operator* v = new AssignmentVar(name);

				string temp_expression;
				for (unsigned int i = row.find('=') + 1; i < row.length(); i++)
					temp_expression.push_back(row[i]);

				string evaluation = v->expressionEval(temp_expression, objects);
				std::cout << " /// EVALUATION: " << evaluation << endl;
				if (evaluation.compare("NULL") != 0) {
					v->setExpression(evaluation);
					objects.push_back(v);
					return true;
				}
				else {
					std::cout << "ERROR: PROBLEM WITH EVALUATION OF EXPRESSION!" << endl;
					return false;
				}
			}
		}
		return true;
	}
	else {
		//----------------------------------------------------- READ -----------------------------------------------------
		if (row.find("read") != string::npos) {
			//������� � �������� �� ����
			//�������� ���� ��� ���������� ��� ������ ���
			//��� ���� - ��������� ��� ����� var � ���, ��� ��������; ������� �� ���������� �� ����������� � ���� ���� ������� �� ������ ��� �������;

			string read_var_name;
			for (int i = row.find("read") + 5; i < row.length(); i++) {
				if (row[i] < 'a' || row[i]>'z') {
					cerr << "ERROR(read): VAR MUST CONTAIN ONLY SMALL LETTERS!" << endl;
					return false;
				}
				read_var_name.push_back(row[i]);
			}
			bool valid = true;
			for (int k = 0; k < objects.size(); k++) {
				if (read_var_name.compare(objects[k]->getName()) == 0)
					valid = false;
			}
			if (valid == false) {
				cerr << "ERROR(read): VAR WITH NAME " << read_var_name <<" ALREADY EXIST!" << endl;
				return valid;
			}

			string rv_expression;
			cout << "ENETER AN EXPRESSION FOR " << read_var_name << ": ";
			getline(cin, rv_expression);
			cout << endl;

			Operator* rv = new AssignmentVar(read_var_name);

			string evaluation = rv->expressionEval(rv_expression, objects);
			std::cout << " /// EVALUATION: " << evaluation << endl;
			if (evaluation.compare("NULL") != 0) {
				rv->setExpression(evaluation);
				objects.push_back(rv);
				return true;
			}
			else {
				std::cout << "ERROR(read): PROBLEM WITH EVALUATION OF EXPRESSION!" << endl;
				return false;
			}
		}
		//----------------------------------------------------- PRINT -----------------------------------------------------
		else if (row.find("print") != string::npos) {
			string print_expression;
			for (int i = row.find("print") + 6; i < row.length(); i++) {
				print_expression.push_back(row[i]);
			}
			Operator* pr = new Print();

			string evaluation = pr->expressionEval(print_expression, objects);
			std::cout << " /// EVALUATION: " << evaluation << endl;
			if (evaluation.compare("NULL") != 0) {
				pr->setExpression(evaluation);
				objects.push_back(pr);
				return true;
			}
		
			else {
				cout << "ERROR(print): PROBLEM WITH EVALUATION OF EXPRESSION!" << endl;
				return false;
			}
		}
		cerr << "ERROR(global): INVALID EXPR LINE!" << endl;
		return false; //� ������, �� �� ������ ���� ���� �� �����������
	}
	return true;
}

int main()
{
	cout << "Enter A Valid Name Of A Text File Containing EXPR Code: ";
	string file_name;
	getline(cin, file_name);
	cout << "Entered File Name: " << file_name << endl;
	file_name.append(".txt");

	ifstream file;
	file.open(file_name, ios::in);
	if (!file.is_open()) {
		cerr << "Problem With Loading File With Name " << file_name << ", Please Try Again!" << endl << "---------------------------------------------------------------" << endl;
		return 0;
	}
	cout << "File " << file_name << " Opened Successfully" << endl << "---------------------------------------------------------------" << endl;

	vector<Operator*> objects;
	unsigned row_index = 0;
	string row;

	while (!file.eof()) {
		getline(file, row);
		row_index++;
		cout << "#ROW: " << row_index << endl;

		if (readRow(row, objects) == false) {
			cerr << "--> ERROR AT LINE #" << row_index << ": \"" << row << "\" ! PLEASE, CHECK FOR CORRECT SYNTAX AND TRY AGAIN." << endl << "---------------------------------------------------------------" << endl;
			return 0;}
		else
			cout << "WORKS!" << endl << "----------------" << endl;
		for (int i = 0; i < objects.size(); i++) {
			cout << objects[i]->getName() << "=" << objects[i]->getExpression() << endl;
		}
		cout << endl;
	}
	cout << "---Print---" << endl;
	for (unsigned i = 0; i < objects.size(); i++) {
		if (objects[i]->getName().compare("Print") == 0) {
			cout << "Print: " << objects[i]->getExpression() << endl;
		}
	}

}
