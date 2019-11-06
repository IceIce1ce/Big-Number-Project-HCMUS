#include "StdAfx.h"
#include "BigInteger.h"

Node* Node::getNode(char n)
{
	Node *N = new Node;
	N->value = n;
	return N;
}

BigInteger::BigInteger(string str)
{
	pHead = NULL;
	pTail = NULL;
	sign = '+';
	digit = 0;
	flag = true;   // will repair for destruction case
	if(str != "") {
		setBigInteger(str);
	}
}

BigInteger::BigInteger(int n)
{
	pHead = NULL;
	pTail = NULL;
	sign = '+';
	digit = 0;
	flag = true;   // will repair for destruction case
	setBigInteger(convertInttoString(n));
}


BigInteger::BigInteger(void)
{
	pHead = NULL;
	pTail = NULL;
	sign = '+';
	digit = 0;
	flag = false;   // default mode it will destroy the memory
}


BigInteger::~BigInteger(void)   
{
	if(flag == false) {
		Node *t = pHead;
		Node *s = pHead;
		while(s != NULL) {
			s = s->getpNext();
			delete t;
			t = s;
		}
	}
}

void BigInteger::addHead(Node *Element)
{
	if(pTail == NULL)
	{
		pHead = Element;
		pTail = Element;
	}
	else {
		pHead->setpPrev(Element);
		Element->setpNext(pHead);
		pHead = Element;
	}
}

void BigInteger::addTail(Node *Element)
{
	if(pHead == NULL)
	{
		pHead = Element;
		pTail = Element;
	}
	else {
		pTail->setpNext(Element);
		Element->setpPrev(pTail);
		pTail = Element;
	}
}

string BigInteger::getInteger()  const    // return the string number with unsigned
{
	string str("");
	Node *t = pHead;
	while(t != NULL) {
		str = str + t->getValue();
		t = t->getpNext();
	}
	return str;
}

string BigInteger::getStringNumber() const    // return the string number with signed
{
	string str("");
	if(sign == '-' && pHead->getValue() != '0')
		str = sign;
	str = str + BigInteger::getInteger();
	return str;
}

void BigInteger::setBigInteger(string str)
{
	int i = 0;
	if(str[0] == '-') {
		sign = '-';
		digit = str.length() - 1;
		i = i + 1;
	}
	else digit = str.length();
	for(i; i < str.length(); i++)
	{
		Node *N = Node::getNode(str[i]);
		addTail(N);
	}
}


int convertCharToInt(char a)
{
	const char *a_char = new char(a);
	return atoi(a_char);
}

char convertIntToChar(int n)
{
	char buffer[5];
	itoa (n, buffer, 10);
	char a = buffer[0];

	return a;
}

BigInteger BigInteger::sumDigit (BigInteger const &A, BigInteger const &B)
{
	int t = 0, sum = 0;
	Node *a;
	Node *b;
	Node *c;
	BigInteger S;
	a = A.pTail;
	b = B.pTail;
	while( a != NULL && b != NULL) 
	{
		sum = t + convertCharToInt(a->getValue()) + convertCharToInt(b->getValue()); // plus two node of A, B
		S.addHead(Node::getNode(convertIntToChar(sum % 10)));    // get the unit number eg 18 -> 8 -> node
		t = sum / 10; // get the left number 18 -> 1;
		a = a->getpPrev();
		b = b->getpPrev();
	}

	if( a == NULL){
		while( b != NULL) {               // scan the redundancy of b
			sum = t + convertCharToInt(b->getValue());
			S.addHead(Node::getNode(convertIntToChar(sum % 10)));
			t = sum/10;
			b = b->getpPrev();
		}
		S.digit = B.digit;
	}
	else if( b == NULL) {
		while( a != NULL) {               // scan the element of redundancy of a
			sum = t + convertCharToInt(a->getValue());
			S.addHead(Node::getNode(convertIntToChar(sum % 10)));
			t = sum/10;
			a = a->getpPrev();
		}
		S.digit = A.digit;
	}

	if( t== 1) {
		S.addHead(Node::getNode(convertIntToChar(t)));
		S.digit++;
	}
	S.setFlag(true);
	return S;
}

BigInteger BigInteger::subtractDigit (BigInteger const &A, BigInteger const &B)
{
	int t = 0, sum = 0;
	int x, y;
	Node *a;
	Node *b;
	Node *c;
	BigInteger S;
	a = A.pTail;
	b = B.pTail;
	while( a != NULL && b != NULL) 
	{
		x = convertCharToInt(a->getValue());
		y = convertCharToInt(b->getValue());
		if(t + x - y >= 0) {
			sum = t + x - y ; // subtract two node of A, B
			t = 0;
		}
		else {
			sum = 10 + t + x - y ;
			t = -1;          // borrow the previous unit
		}
		S.addHead(Node::getNode(convertIntToChar(sum)));    // get the unit number eg 18 -> 8 -> node
		S.digit++;
		a = a->getpPrev();
		b = b->getpPrev();
	}

	if( a == NULL){
		while( b != NULL) {               // scan the redundancy of b
			y = convertCharToInt(b->getValue());
			if(t - y >= 0) {
				sum = t - y ; // subtract two node of A, B
				t = 0;
			}
			else {
				sum = 10 + t - y ;
				t = -1;          // borrow the previous unit
			}
			S.addHead(Node::getNode(convertIntToChar(sum)));    // get the unit number eg 18 -> 8 -> node
			S.digit++;
			b = b->getpPrev();
		}
	}
	else if( b == NULL) {
		while( a != NULL) {               // scan the element of redundancy of a
			x = convertCharToInt(a->getValue());
			if(t + x >= 0) {
				sum = t + x ; // subtract two node of A, B
				t = 0;
			}
			else {
				sum = 10 + t + x;
				t = -1;          // borrow the previous unit
			}
			S.addHead(Node::getNode(convertIntToChar(sum)));    // get the unit number eg 18 -> 8 -> node
			S.digit++;
			a = a->getpPrev();
		}
	}
	S.setFlag(true);
	S.removePrefixZero();
	return S; // error automatically destructor and lost all of information
}

int BigInteger::compareNumber(BigInteger const &A, BigInteger const &B)
{
	int A_digit = A.amountDigit();
	int B_digit = B.amountDigit();
	Node *a_Ptr = A.pHead;
	Node *b_Ptr = B.pHead;
	int a, b;
	if(A_digit > B_digit)
		return 1;
	else if (A_digit < B_digit)
		return -1;
	else {
		while( a_Ptr != NULL ) {
			a = convertCharToInt(a_Ptr->getValue());
			b = convertCharToInt(b_Ptr->getValue());
			if( a > b)
				return 1;
			else if( a < b)
				return -1;
			a_Ptr = a_Ptr->getpNext();
			b_Ptr = b_Ptr->getpNext();
		}
	}
	return 0;
}

BigInteger operator+ (BigInteger const &A, BigInteger const &B)
{
	BigInteger S;    // Find the sign of number A + B
	if(A.sign == '+' && B.sign == '+')
		return BigInteger::sumDigit(A, B);
	else if(A.sign == '+' && B.sign == '-')
		return BigInteger::subtractOperator(A, B);
	else if(A.sign == '-' && B.sign == '+')
		return BigInteger::subtractOperator(B, A);
	else {
		S = BigInteger::sumDigit(A, B);
		S.sign = '-';
		S.setFlag(true);
		return S;
	}
}

BigInteger BigInteger::subtractOperator(BigInteger const &A, BigInteger const &B)
{
	BigInteger S;       //Check the case happen to A - B
	int compare =BigInteger::compareNumber(A, B);
	if(compare == 1)
		return BigInteger::subtractDigit(A, B);
	else if(compare == 0) {
		S.setBigInteger("0");
		S.flag = true;
		return S;
	}
	else {
		S = BigInteger::subtractDigit(B, A);
		S.sign = '-';
		return S;
	}
}

BigInteger operator- (BigInteger const &A, BigInteger const &B)
{
	if(A.sign == '+' && B.sign == '+')
	{	
		BigInteger &S = BigInteger::subtractOperator(A, B);
		return S;
	}
	else if(A.sign == '+' && B.sign == '-')
	{
		BigInteger &S = BigInteger::sumDigit(A, B);
		return S;
	}
	else if(A.sign == '-' && B.sign == '-')
	{
		BigInteger &S = BigInteger::subtractOperator(B, A);
		return S;
	}
	else {
		BigInteger &S = BigInteger::sumDigit(A, B);
		S.sign = '-';
		S.setFlag(true);
		return S;
	}
}

ostream& operator<< (ostream &os, BigInteger &A) 
{
	if(A.sign == '-')
		os << '-';
	os << A.getInteger();
	return os;
}

void BigInteger::removeNode(Node *PrevElement, Node *Element, Node *NextElement)
{
	delete Element;
	PrevElement->setpNext(NextElement);
	NextElement->setpPrev(PrevElement);
	
}

void BigInteger::removePrefixZero(void)
{
	this->countDigit();
	while(pHead->getValue() == '0' && digit > 1)
	{
		Node *temp = pHead;
		pHead = pHead->getpNext();
		pHead->setpPrev(NULL);
		delete temp;
		digit--;
	}
}


istream& operator>> (istream &is, BigInteger &A)
{
	string str;
	is >> str;
	A.setBigInteger(str);
	return is;
}

BigInteger& BigInteger::operator-()
{
	sign = '-';
	return *this;
}

int productNodeValue(Node *A, Node *B)
{
	return convertCharToInt(A->getValue()) * convertCharToInt(B->getValue());
}

string convertInttoString(int n)
{
	char buffer[10];
	itoa (n, buffer, 10);
	return (string) buffer;
}

BigInteger BigInteger::productOperator(BigInteger const& A, BigInteger const& B)
{
	BigInteger *List = new BigInteger[B.digit];   // define the list to store the element which has been producted.
	Node *A_Ptr; 
	Node *B_Ptr;
	BigInteger S;
	string str;
	int i = 0, t, P;
	for(B_Ptr = B.pTail; B_Ptr != NULL; B_Ptr = B_Ptr->getpPrev())
	{
		t = 0;
		for(A_Ptr = A.pTail; A_Ptr != NULL; A_Ptr = A_Ptr->getpPrev()) // product each element from B to each element to A
		{
			P = t + productNodeValue(A_Ptr, B_Ptr);
			str = convertInttoString(P);

			if(str.length() > 1)
				t = convertCharToInt(str[0]);    // store the second digit
			else
				t = 0;

			List[i].addHead(Node::getNode(str[str.length()-1]));
		}

		if(t != 0)
			List[i].addHead(Node::getNode(convertIntToChar(t)));

		for(int j = 0; j < i; j++)    // add '0' node to Tail to fill the position of Node
			List[i].addTail(Node::getNode('0'));

		S = S + List[i];
		i++;
	}
	
	delete []List;
	S.setFlag(true);
	return S;
}

BigInteger operator* (BigInteger const &A, BigInteger const &B)
{
	if(B.getInteger() == "0")
	{
		BigInteger S;
		S.addHead(Node::getNode('0'));
		S.digit = 1;
		S.setFlag(true);
		return S;
	}
	else {
		BigInteger &S = BigInteger::productOperator(A, B);
		S.countDigit();
		if((A.sign == '+' && B.sign == '-') || (A.sign == '-' && B.sign == '+')) {
			S.sign = '-';
			return S;
		}
		return S; 
	}	
}

BigInteger BigInteger::divideDigit(BigInteger const &A, BigInteger const &B) // A > B
{
	BigInteger S;
	string strA = A.getInteger();
	string strB = B.getInteger();
	string strC = "";       // appendage
	string strD = "";
	string strI = "";
	int i = 0;
	int k, h;
	long long int a, b;
	//if(B.digit <= 18)  {     // suitable for using long long int data type
	//	a = strA;
	//	b = strB;
	//	S = (int &) strA / (int &) strB;
	//}
	//else {
		k = B.digit;
		BigInteger C;
		BigInteger D;
		BigInteger M;
		strC = strA.substr(0,k);   // copy the number of digit from A to C
		M.setBigInteger(strC);
		
		if(M < B)
		{
			strC = strA.substr(0,k+1);
			C.setBigInteger(strC);
			int loop = A.digit - B.digit;
			while(C > B || loop > 0) {
				i = 0;
				D = BigInteger::productOperator(B, i);
				D.removePrefixZero();
				strD = D.getInteger();    // will be erased
				while(C > D && strD != "0")
				{
					D = BigInteger::productOperator(B, i);
					strD = D.getInteger();    // will be erased
					i = i + 1;
				}
				if(i - 2 < 0)
					i = 0;
				else i = i - 2;
				D = BigInteger::productOperator(B, i);
				strD = D.getInteger();    // will be erased
				D = C - D;
				strD = D.getInteger();    // will be erased
				strI = strI + convertIntToChar(i);
				if(k+1 < strA.length())
				{
					C = D.getInteger() + strA[++k];
					strC = C.getInteger();    // will be erased
				}
				else {
					k = k + 1;
					C = D.getInteger();
					strC = C.getInteger();    // will be erased
					strD = D.getInteger();    // will be erased
				}
				loop = loop - 1;
			}
		}
		else {
			C = M;
			while(C > B || k < strA.length()) {
				i = 0;
				D = BigInteger::productOperator(B, i);
				do {
					D = BigInteger::productOperator(B, i);
					i = i + 1;
				}while( C > D);
				i = i - 2;
				D = BigInteger::productOperator(B, i);
				D = C - D;
				strI = strI + convertIntToChar(i);
				if(k+1 <= strA.length())
				{
					C = D.getInteger() + strA[k++];
				}
				else {
					C = D.getInteger();
				}
			}
		}		
	S.setBigInteger(strI);	
	S.removePrefixZero();	
	S.setFlag(true);
	return S;
}

void BigInteger::countDigit ()
{
	string str = getInteger();
	digit = str.length();
};

int BigInteger::amountDigit() const
{
	string str = getInteger();
	return str.length();
}

BigInteger BigInteger::divideOperator(BigInteger const &A, BigInteger const &B)
{
	if(B == BigInteger("0")) {
		throw ("Division By Zero Condition");
	}
	if(A > B) {
		BigInteger &S = BigInteger::divideDigit(A, B);
		return S;
	}
	else if(A == B)
	{
		BigInteger S;
		S.addHead(Node::getNode('1'));
		S.digit = 1;
		S.setFlag(true);
		return S;
	}
	else {
		BigInteger S;
		S.addHead(Node::getNode('0'));
		S.digit = 1;
		S.setFlag(true);
		return S;
	}	
}

BigInteger operator/ (BigInteger const &A, BigInteger const &B)
{
	BigInteger &S = BigInteger::divideOperator(A, B);
	if((A.sign == '+' && B.sign == '-') || (A.sign == '-' && B.sign == '+')) {
		S.sign = '-';
		return S;
	}
	S.removePrefixZero();
	return S; 
}

bool operator> (BigInteger const &A, BigInteger const &B)
{
	if(BigInteger::compareNumber(A, B) == 1)
		return true;
	else return false;
}

bool operator>= (BigInteger const &A, BigInteger const &B)
{
	int check = BigInteger::compareNumber(A, B);
	if(check == 1 || check == 0)
		return true;
	else return false;
}

bool operator< (BigInteger const &A, BigInteger const &B)
{
	int check = BigInteger::compareNumber(A, B);
	if(check == -1)
		return true;
	else return false;
}

bool operator<= (BigInteger const &A, BigInteger const &B)
{
	int check = BigInteger::compareNumber(A, B);
	if(check == -1 || check == 0)
		return true;
	else return false;
}

bool operator== (BigInteger const &A, BigInteger const &B)
{
	int check = BigInteger::compareNumber(A, B);
	if(check == 0)
		return true;
	else return false;
}

bool operator!= (BigInteger const &A, BigInteger const &B)
{
	int check = BigInteger::compareNumber(A, B);
	if(check != 0)
		return true;
	else return false;
}


void BigInteger::loadFile(string path, BigInteger A[], int &n)
{
	fstream f(path);
	string str;
	n = 0;
	if(f.is_open()) {
		while (!f.eof()) {
			f >> str;
			A[n].setBigInteger(str);
			n++;
		}
	}
	else cout << "Can not open the file !";
}

void BigInteger::saveFile(string path, BigInteger A[], int n)
{
	ofstream f(path);
	if(f.is_open())  {
		for(int i = 0; i < n; i++)
			f << A[i].getStringNumber() << "\n";	
		cout << "Save Done" << endl;
	}
	else cout << "Can not save the file" << endl;
	f.close();
}

void BigInteger::appendFile(string path, string str)
{
	fstream f(path, ios::app | ios::in | ios::out);
	if( !f ) {
		cout << "Can not append file !" << endl;
	} else {
		f << str << "\n";
		f.close();
		cout << "Append Succeeded" << endl;
	}

}

