#include "Stdafx.h"
#include "ReversePolish.h"



map<char, int> initPriorOperator() {
	map<char, int> priorOpertor;
	int max = 10;  // numbers have no priority

	priorOpertor['+'] = 1;
	priorOpertor['-'] = 1;
	priorOpertor['*'] = 2;
	priorOpertor['/'] = 2;
	priorOpertor['('] = 3;
	priorOpertor[')'] = 3;
	priorOpertor['0'] = max;
	priorOpertor['1'] = max;
	priorOpertor['2'] = max;
	priorOpertor['3'] = max;
	priorOpertor['4'] = max;
	priorOpertor['5'] = max;
	priorOpertor['6'] = max;
	priorOpertor['7'] = max;
	priorOpertor['8'] = max;
	priorOpertor['9'] = max;
	return priorOpertor;
}

map<char, int> priorOperator = initPriorOperator();

void filterOperand(string str, string operand[], int &m)    // split each operand and operator into string.
{
	int j, index = 0;
	int n = str.length();
	for(int i = 0; i < n; i++) {
		j = i;
		while(j < n && 48 <= (int) str[j] && (int) str[j] <= 57) {
			operand[index] += str[j];
			j++;
		}
		if(i != j)   // get the filter operand
		{
			index++;
			//	n = str.length();
		}
		if(j < n && priorOperator[str[j]]) {
			operand[index] = str[j];
			index++;
		}
		i = j;
	}
	m = index;
}

queue<string> convertReversePolish(string str)   // input the polynomial string and return to the reverse polish pattern
{
	string exp[100];
	int n;
	bool flag;
	filterOperand(str, exp, n);  // return the expression with array of string, each element is the operand or operator 
	queue<string> operand;   
	stack<string> oprtor;   // store the operator
	for(int i = 0; i < n; i++) 
	{
		flag = true;
		if(!oprtor.empty()) {
			if(priorOperator[oprtor.top()[0]] >= priorOperator[exp[i][0]] && oprtor.top()[0] != '(')
			{
				operand.push(oprtor.top());
				oprtor.pop();
			}
			if(exp[i][0] == ')')
			{
				while(oprtor.top()[0] != '(') {
					operand.push(oprtor.top());
					oprtor.pop();
				}
				oprtor.pop();
			}
		}
		if(priorOperator[exp[i][0]] == 10) {   // push operand to stack
			if(i - 1 >=0 && exp[i-1][0] == '-' && (i-2 < 0 || exp[i-2][0] == '('))
			{
				operand.push('-' + exp[i]);
				oprtor.pop();
			}
			else operand.push(exp[i]);
		}
		else	{ 
			if(exp[i][0] != ')')
				oprtor.push(exp[i]);
		}	
	}
	while(!oprtor.empty()) {
		operand.push(oprtor.top());
		oprtor.pop();
	}
	return operand;
}

bool isOperand(string A) {
	if(48 <= (int) A[0] && (int) A[0] <= 57 || (A.length() > 1 && A[0] == '-' && 48 <= (int) A[1] && (int) A[1] <= 57))
		return true;
	else
		return false;
}

string calRevString(queue<string> Rev) 
{
	BigInteger A, B;
	BigInteger S;
	stack<BigInteger> STACK_OPERAND;
//	Rev = refineElement(Rev);


	while(!Rev.empty()) {
		if(isOperand(Rev.front())) {
			STACK_OPERAND.push(Rev.front());
			Rev.pop();
		}
		else {          // else is the operator
			A = STACK_OPERAND.top();	      
			STACK_OPERAND.pop();
			B = STACK_OPERAND.top();	
			STACK_OPERAND.pop();
			switch(Rev.front()[0]) {
			case '+':
				STACK_OPERAND.push(A + B);
				break;
			case '-':
				STACK_OPERAND.push(B - A);    // B is the operand before A
				break;
			case '*':
				STACK_OPERAND.push(A * B);
				break;
			case '/':
				STACK_OPERAND.push(B / A);    // B is the operand before A
				break;
			}
			Rev.pop();
		}
	}
	S = STACK_OPERAND.top();
	S.removePrefixZero();
	return S.getStringNumber();
}


void loadFileString(string path, string str[], int &n)
{
	ifstream f(path);
	n = 0;
	if(f.is_open()) {
		while (!f.eof()) {
			getline(f, str[n]);
			n++;
		}
		f.close();
	}
	else cout << "Can not open the file !";
}

void saveFileString(string path, string str[], int n)
{
	ofstream f(path);
	if(f.is_open())  {
		for(int i = 0; i < n; i++)
			f << str[i] << "\n";	
		cout << "Save Done" << endl;
	}
	else cout << "Can not save the file" << endl;
	f.close();
}

void checkTrueExpr(string str)   // check if the expression are all operator and operand not character
{
	char temp;
	for(int i = 0; i < str.length(); i++) {
		temp = (int) str[i];
		if(temp == ' ')   // it doesn't relate to the expression
			continue;
		if(priorOperator.find(temp) == priorOperator.end())
			throw ("Expression is illegal.");
	}
}

void calExpressionFile(string pathLoad, string pathSave)
{
	string str[100];
	string result[100];
	string temp;
	int n = 0;
	loadFileString(pathLoad, str, n);
	for(int i = 0; i < n; i++) {
		try {
			checkTrueExpr(str[i]);
			temp = calRevString(convertReversePolish(str[i]));
		} catch(const char *msg) {
			result[i] = msg;
			continue;
		}
		result[i] = temp;
	}
	saveFileString(pathSave, result, n);
}