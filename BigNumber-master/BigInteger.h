#pragma once


class Node {
	char value;
	Node *pNext;
	Node *pPrev;
public:
	Node(void) : pNext(NULL), pPrev(NULL) {}
	~Node(void) { }
	static Node *getNode(char n);    // return the node with the input 'n' character
	char getValue() { return value; }
	Node *getpNext() { return pNext; }
	Node *getpPrev() { return pPrev; }
	void setpNext(Node *Next) { pNext = Next; }
	void setpPrev(Node *Prev) { pPrev = Prev; }
//	Node* operator= (Node *Element);
};

int convertCharToInt(char a);
char convertIntToChar(int n);
string convertInttoString(int n);


class BigInteger
{
	Node *pHead;
	Node *pTail;
	char sign;
	int digit;
	bool flag;  // avoid the undesired destructor case. If true it will not delete object
public:
	BigInteger(void);  // initialize the class
	~BigInteger(void); // Destroy the memory of each element node.
	BigInteger(string str);  // initialize the class
	BigInteger(int);
	void setFlag(bool _f) { flag = _f; }
	void setBigInteger(string str);

	void addHead(Node *Element);
	void addTail(Node *Element);  // push Node into the list
	void removeNode(Node *PrevElement, Node *Element, Node *NextElement);
	void removePrefixZero(void);


	string getInteger() const;   // return the value with string type
	string getStringNumber() const;  // return the string number 
	void countDigit ();
	int amountDigit() const;
	static BigInteger sumDigit (BigInteger const &A, BigInteger const &B);
	static BigInteger subtractDigit (BigInteger const &A, BigInteger const &B); // default mode: A - B with A > B
	static BigInteger subtractOperator(BigInteger const &A, BigInteger const &B);
	static BigInteger productOperator(BigInteger const& A, BigInteger const& B);
	static BigInteger divideDigit(BigInteger const &A, BigInteger const &B);
	static BigInteger divideOperator(BigInteger const &A, BigInteger const &B);
	static int compareNumber(BigInteger const &A, BigInteger const &B); // return 1; greate, 0:equal, -1: lesser

	BigInteger& operator-();
	friend BigInteger operator+ (BigInteger const &A, BigInteger const &B);
	friend BigInteger operator- (BigInteger const &A, BigInteger const &B);
	friend BigInteger operator* (BigInteger const &A, BigInteger const &B);
	friend BigInteger operator/ (BigInteger const &A, BigInteger const &B);
	
	friend bool operator> (BigInteger const &A, BigInteger const &B);
	friend bool operator>= (BigInteger const &A, BigInteger const &B);
	friend bool operator< (BigInteger const &A, BigInteger const &B);
	friend bool operator<= (BigInteger const &A, BigInteger const &B);
	friend bool operator== (BigInteger const &A, BigInteger const &B);
	friend bool operator!= (BigInteger const &A, BigInteger const &B);

	friend istream& operator>> (istream &is, BigInteger &A);  // get the string from cin and call addTail to convert
	friend ostream& operator<< (ostream &os, BigInteger &A); // convert BigInteger to string type and output string	
	
	static void loadFile(string path, BigInteger A[], int &n);  // load each line from the file and save it to array
	static void saveFile(string path, BigInteger A[], int n);
	static void appendFile(string path, string str);

};

