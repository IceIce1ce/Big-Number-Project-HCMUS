#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<math.h>
#include<algorithm>
#include<vector>
#define BIT_INT64 64
using namespace std;

class QInt
{
public:
	static QInt QIntToTwosComplement(QInt); //convert QInt to negative 1 //fixed
	string QIntToBinaryString(QInt&);  //fixed
	string QIntToHex(QInt&);  //fixed
	string QIntToDec(QInt&);  //fixed
	string Power(int a, int n); //fixed  //use for integer number type string
public:
	//const static int num_of_int = 4;
	//int arrayBits[num_of_int];
	__int64 arrayBits[4] = { 0, 0, 0, 0 }; //fixed
	QInt(const string& str); //fixed
	__int64* getData(); //fixed
	int getBit(int pos); //fixed
	void changeBit(int pos);
	void addToOne(); //negative 2
	bool checkZero(); //fixed
	void binaryToQInt(string str);
	void decimalToQInt(string str);
	void hexaToQInt(string str);
	static int numToChar(char c);
	static string divByTwo(string str, bool isZero = 0);
	static void shiftLeft(string& str, int num);
	static void shiftRight(string& str, int num);
	static string sumOf2PowN(int num);
	static string addString(string a, string b);
	static string sumBinaryString(string a, string b);  //fixed
	static string subtractBinaryString(string a, string b);  //fixed
	string multiplyBinaryString(string a, string b);  //fixed
	string divisionBinaryString(string number, string divisor); //fixed
	friend bool operator > (string a, string b); //fixed
	void clear();
	void Init(); //fixed
public:
	QInt();
	~QInt();
	//QInt(string str);
	string toString(); //=toDecimal()
	string toBinary(bool check = 0);
	string toHexa();
	//QInt& operator = (const QInt& q);
	QInt operator + (QInt q); //fixed
	QInt operator - (QInt q); //fixed
	QInt operator * (QInt q); //fixed
	QInt operator / (QInt q);  //fixed
	QInt operator & (QInt q); //fixed
	QInt operator | (QInt q); //fixed
	QInt operator ^ (QInt q); //fixed
	QInt& operator ~ ();  ///fixed
	QInt operator << (const int &k); //move bit to left   //fixed
	QInt operator >> (const int &k); //move bit to right    /fixed
	friend ostream& operator << (ostream& os, QInt& q);
	friend istream& operator >> (istream& is, QInt& q);
	void operator = (const string &k); //fixed
	void operator = (const QInt &k);  //fixed
public:
	string HexToBin(string& str); //fixed
	//string DecToHex(string str);
	//string HexToDec(string str);
	string BinToDec(string& str); //fixed
	string BinToHex(string& str); //fixed
	string DecToBin(string& str); //fixed
	//////process
	void printQInt(int base);
	void ScanQInt(string source, int sourceBase);
	/////handle for ror, rol
	void TurnOnBit(int k); //fixed
	void TurnOffBit(int k); //fixed
	QInt rol(); //fixed
	QInt ror(); //fixed
};
///cut zero for bin
string normalizeString(string str);
///process
void printBin(QInt x);
void printDec(QInt x);
void printHex(QInt x);
void process(vector<string> str_arr);
void mainCaculate(char* file_input, char* file_output);
vector<string> cut_stringInput(string str_input);
QInt CalculateOpe(QInt a, QInt b, string ope);
////handle for ror, rol
int getInfo(string& str); //fixed
void subProcess(string& line);
///cut zero for hex, dec
string cutZero(string str);
string StringDivTwo(string &number); //fixed
void process(string &s); //fixed
void readFile(const string Input,const string Output); //fixed