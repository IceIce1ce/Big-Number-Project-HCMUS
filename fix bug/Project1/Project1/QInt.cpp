#include"QInt.h"
#include <vector>
#include<fstream>
#include<numeric> ///convert vector<string> to string
#pragma warning(disable:4996)

int QInt::numToChar(char c)
{
	if (c == '1' || c == '3' || c == '5' || c == '7' || c == '9') return 1;
	return 0;
}

QInt::QInt(const string &str)
{
	this->Init();
	for (int i = str.length() - 1; i >= 0; i--)
	{
		if (str[i] == '1')
		{
			this->TurnOnBit(str.length() - i - 1);
		}
		else this->TurnOffBit(str.length() - i - 1);
	}
}

__int64* QInt::getData()
{
	return arrayBits;
}

string QInt::divByTwo(string str, bool isZero)
{
	stringstream writer;
	writer << "";
	int addition = 0;
	bool firstString = true; //check if first number of string is zero or not then delete '0'
	for (int i = 0; i < str.length(); i++)
	{
		int digit = (str[i] - '0') / 2 + addition;
		if (digit != 0) firstString = false;
		if (!firstString || isZero) writer << digit;
		addition = QInt::numToChar(str[i]) * 5;
	}
	return writer.str();
}

void QInt::changeBit(int pos)
{
	this->arrayBits[4 - pos / 64 - 1] ^= (1 << (pos % 64));
}

int QInt::getBit(int pos)
{
	/*int arr = this->arrayBits[4 - pos / 64 - 1];
	arr &= (1 << (pos % 64));
	int result = arr >> (pos % 64);
	return abs(result);*/
	return (arrayBits[pos / 64] >> (pos % 64)) & 1;
}

void QInt::addToOne() //cong them 1 chuyen ve dang bu 2
{
	string byte = this->toBinary();
	int excess = 0;
	for (int i = byte.length() - 1; i >= 0; i--)
	{
		if (byte[i] == '0' && excess == 0)
		{
			byte[i] = '1';
			break;
		}
		else if (byte[i] == '0' && excess == 1)
		{
			byte[i] = '1';
			break;
		}
		else if (byte[i] == '1' && excess == 0)
		{
			byte[i] = '0';
			excess = 1;
		}
		//else if (byte[i] == '1' && excess == 1)
		else 
		{
			byte[i] = '0';
		}
	}
	//convert to QInt from binary
	for (int i = 0; i < 4; i++) this->arrayBits[i] = 0;
	for (int i = byte.length() - 1; i >= 0; i--)
	{
		if (byte[i] == '1') changeBit(127 - i);
	}
}

bool QInt::checkZero()
{
	/*string str = this->toBinary();
	for (int i = 0; i < str.length(); i++)
	if (str[i] != '0') return false;
	return true;*/
	for (int i = 0; i < 4; i++)
	{
		if (arrayBits[i] != 0) return false;
	}
	return true;
}

string QInt::toBinary(bool check)
{
	stringstream writer;
	for(int i = 0; i < 128; i++)
	{
		int bit = abs(getBit(i));
		writer << bit;
	}
	string result = writer.str();
	reverse(result.begin(), result.end());
	if(check == 1)
	{
		while(result[0] == '0' && result.length() > 1) result.erase(0, 1);
	}
	return result;
}

void QInt::shiftLeft(string& str, int num)
{
	stringstream writer;
	str.erase(0, num);
	writer << str;
	for (int i = 0; i < num; i++) writer << '0';
	str = writer.str();
}

void QInt::shiftRight(string& str, int num)
{
	stringstream writer;
	str.erase(127 - num, num);
	if (str[0] == '1')
	{
		for (int i = 0; i < num; i++) writer << "1";
	}
	else
	{
		for (int i = 0; i < num; i++) writer << "0";
	}
	writer << str;
	str = writer.str();
}

QInt::QInt()
{
	for (int i = 0; i < 4; i++) this->arrayBits[i] = 0;
}

QInt::~QInt()
{
}

string QInt::addString(string a, string b)
{
	stringstream writer;
	int lenA = a.length(), lenB = b.length(), temp = 0;
	if(lenB > lenA)
	{
		string temp2 = a;
		a = b;
		b = temp2;
		int temp1 = lenA;
		lenA = lenB;
		lenB = temp1;
	}
	for(int i = 0; i < lenA; i++)
	{
		int digitA = a[lenA - i - 1] - 48, digitB = 0;
		if (i < lenB) digitB = b[lenB - i - 1] - 48;
		int sum = digitA + digitB + temp;
		writer << sum % 10;
		temp = sum >= 10 ? 1:0;
	}
	if (temp == 1) writer << 1;
	string result = writer.str();
	reverse(result.begin(), result.end());
	return result;
}

string QInt::sumOf2PowN(int num)
{
	string result = "1";
	if(num == 0) return "1";
	else if(num > 0)
	{
		for(int i = 0; i < num; i++) result = QInt::addString(result, result);
	}
	else
	{
		for(int i = -1; i >= num; i--)
		{
			if (QInt::numToChar(result[result.length() - 1]) == 1) result += "0";
			if((result[0] == '1' || result[0] == '0') && i < -1) result = QInt::divByTwo(result,1);
			else result = QInt::divByTwo(result, 0);
		}
	}
	return result;
}

string QInt::toString()
{
	string bin, result = "0";
	stringstream writer;
	QInt temp = *this;
	if(this->getBit(127) == 1)
	{
		writer << "-";
		for(int i = 0; i < 4; i++) temp.arrayBits[i] = ~temp.arrayBits[i];
		temp.addToOne();
	}
	bin = temp.toBinary();
	for(int i = bin.length() - 1; i >= 0; i--)
	{
		if (bin[i] == '1') 
		{
			string pow = temp.sumOf2PowN(bin.length() - i - 1);
			result = temp.addString(result, pow);
		}
	}
	writer << result;
	result = writer.str();
	return result;
}

ostream& operator << (ostream& os, QInt &q)
{
	os << q.toString();
	return os;
}

istream& operator >> (istream& is, QInt& q)
{
	string temp;
	is >> temp;
	q.decimalToQInt(temp);
	return is;
}

void QInt::decimalToQInt(string str)
{
	bool negative = false;
	// if first character is negative then delete 
	if(str[0] == '-') 
	{
		negative = true;
		str.erase(0, 1);
	}
	//delete list of redundant zero 
	int countZero = 0;
	for(int i = 0; i < str.length(); i++)
	{
		if(str[i] != '0') break;
		countZero++;
	}
	str.erase(0, countZero);
	for(int i = 0; i < 4; i++) this->arrayBits[i] = 0;
	int i = 0;
	//bit calc from right to left
	while(str != "")
	{
		int redundant = (str[str.length() - 1] - 48) % 2;
		if(redundant == 1) changeBit(i);
		str = divByTwo(str);
		i++;
	}
	//if negative, convert addToOne to addToTwo
	if(negative)
	{
		for(int i = 0; i < 4; i++)
		{
			this->arrayBits[i] = ~this->arrayBits[i];
			this->addToOne();
		}
	}
}

string QInt::sumBinaryString(string a, string b)
{
	/*int excess = 0;
	string result;
	stringstream writer;
	for (int i = 0; i < 128; i++) writer << "0";
	result = writer.str();
	for(int i = 127; i >= 0; i--)
	{
		int digitA = a[i] - 48, digitB = b[i] - 48;
		if(digitA + digitB + excess == 0) continue;
		else if (digitA + digitB + excess == 1) 
		{
			result[i] = '1';
			excess = 0;
		}
		else if (digitA + digitB + excess == 2) excess = 1;
		else if (digitA + digitB + excess == 3)
		{
			result[i] = '1';
			excess = 1;
		}
	}
	return result;*/
	bool Negative = false;
	if (a[0] == '-' && b[0] != '-')
	{
		a.erase(a.begin());
		a = subtractBinaryString(b, a);
	}
	else
	{
		if (b[0] == '-' && a[0] != '-')
		{
			b.erase(b.begin());
			a = subtractBinaryString(a, b);
		}
		else
		{
			int Temp = 0;
			if (a[0] == '-' && b[0] == '-')
			{
				a.erase(a.begin());
				Negative = true;
				b.erase(b.begin());
			}
			if (a.size() > b.size())
			{
				while (a.size() != b.size())
				{
					b.insert(b.begin(),'0');
				}
			}
			else
			{
				while (a.size() != b.size())
				{
					a.insert(a.begin(),'0');
				}
			}
			for (int i = a.size() - 1; i > -1; i--)
			{
				Temp = Temp + a[i] + b[i] - 2 * '0';
				a[i] = (Temp % 10) + '0';
				Temp = Temp / 10;
			}
			if (Temp != 0)
			{
				a.insert(a.begin(), Temp + '0');
				Temp = 0;
			}
		}
	}
	while (a[0] == '0')
	{
		a.erase(a.begin());
	}
	if (Negative == true)
	{
		a.insert(a.begin(), '-');
	}
	return a;
}

string QInt::subtractBinaryString(string a, string b)
{
	/*int excess = 0;
	for (int i = 0; i < 128; i++) 
	{
		if (b[i] == '1') b[i] = '0';
		else b[i] = '1';
	}
	for (int i = b.length() - 1; i >= 0; i--)
	{
		if (b[i] == '0' && excess == 0) 
		{
			b[i] = '1';
			break;
		}
		else if(b[i] == '0' && excess == 1) 
		{
			b[i] = '1';
			break;
		}
		else if (b[i] == '1' && excess == 0) 
		{
			b[i] = '0';
			excess = 1;
		}
		//else if(b[i] == '1' && excess == 1)
		else b[i] = '0';
	}
	return sumBinaryString(a, b);*/
	int Temp = 0;
	bool Negative = false;
	if (a == b) return "0";
	if (a == "0") return '-' + b;
	else if (b == "0") return a;
	if (a[0] == '-')
	{
		a.erase(a.begin());
		if (b[0] == '-')
		{
			b.erase(b.begin());
			if (a.size() == b.size())
			{
				if (strcmp(a.c_str(), b.c_str()) > 0)
				{
					Negative = true;
				}
			}
			else if (strcmp(a.c_str(), b.c_str()) < 0)
			{
				Negative = true;
			}
		}
		else
		{
			Negative = true;
			if (a.size() > b.size())
			{
				while (a.size() != b.size())
				{
					b.insert(b.begin(), '0');
				}
			}
			else
			{
				while (a.size() != b.size())
				{
					a.insert(a.begin(), '0');
				}
			}
			for (int i = a.size() - 1; i > -1; i--)
			{
				Temp = Temp + a[i] + b[i] - 2 * '0';
				a[i] = (Temp % 10) + '0';
				Temp = Temp / 10;
			}
			while (a[0] == '0')
			{
				a.erase(a.begin());
			}
			if (Negative == true)
			{
				a.insert(a.begin(), '-');
			}
			return a;
		}
	}
	else
	{
		if (b[0] == '-')
		{
			b.erase(b.begin());
			if (strcmp(a.c_str(), b.c_str()) < 0)
			{
				if (a.size() > b.size())
				{
					while (a.size() != b.size())
					{
						b.insert(b.begin(), '0');
					}
				}
				else
				{
					while (a.size() != b.size())
					{
						a.insert(a.begin(), '0');
					}
				}
				for (int i = a.size() - 1; i > -1; i--)
				{
					Temp = Temp + a[i] + b[i] - 2 * '0';
					a[i] = (Temp % 10) + '0';
					Temp = Temp / 10;
				}
				while (a[0] == '0')
				{
					a.erase(a.begin());
				}
				if (Negative == true)
				{
					a.insert(a.begin(), '-');
				}
				return a;
			}
			else
			{
				if (a.size() > b.size())
				{
					while (a.size() != b.size())
					{
						b.insert(b.begin(), '0');
					}
				}
				else
				{
					while (a.size() != b.size())
					{
						a.insert(a.begin(), '0');
					}
				}
				for (int i = a.size() - 1; i > -1; i--)
				{
					Temp = Temp + a[i] + b[i] - 2 * '0';
					a[i] = (Temp % 10) + '0';
					Temp = Temp / 10;
				}
				while (a[0] == '0')
				{
					a.erase(a.begin());
				}
				if (Negative == true)
				{
					a.insert(a.begin(), '-');
				}
				return a;
			}
		}
		else
		{
			if (a.size() < b.size())
			{
				while (a.size() != b.size())
				{
					a.insert(a.begin(), '0');
				}
				if (strcmp(a.c_str(), b.c_str()) < 0)
				{
					Negative = true;
				}
			}
			else
			{
				while (a.size() != b.size())
				{
					b.insert(b.begin(), '0');
				}
				if (strcmp(a.c_str(), b.c_str()) < 0)
				{
					Negative = true;
				}
			}
		}
	}
	if (a.size() > b.size())
	{
		while (a.size() != b.size())
		{
			b.insert(b.begin(), '0');
		}
	}
	else
	{
		while (a.size() != b.size())
		{
			a.insert(a.begin(), '0');
		}
	}
	if (strcmp(a.c_str(), b.c_str()) < 0)
	{
		string TempStr = a;
		a = b;
		b = TempStr;
	}
	for (int i = a.size() - 1; i > -1; i--)
	{
		if ((a[i] - Temp) < b[i])
		{
			a[i] = (10 + a[i] - b[i] - Temp) + '0';
			Temp = 1;
		}
		else
		{
			a[i] = a[i] - b[i] - Temp + '0';
			Temp = 0;
		}
	}
	while (a[0] == '0' && a.size() != 1)
	{
		a.erase(a.begin());
	}
	if (Negative == true)
	{
		a.insert(a.begin(), '-');
	}
	return a;
}

string QInt::multiplyBinaryString(string a, string b)
{
	string Result = "0";
	string TempStr;
	int Temp = 0;
	bool Negative = false;
	if (a == "0" || b == "0")
	{
		return "0";
	}
	if (a[0] == '-')
	{
		a.erase(a.begin());
		if (b[0] != '-')
		{
			Negative = true;
		}
		else  b.erase(b.begin());
	}
	else if (b[0] == '-')
	{
		Negative = true;
		b.erase(b.begin());
	}
	for (int i = 0; i < b.size(); i++)
	{
		for (int j = a.size() - 1; j > -1; j--)
		{
			Temp = Temp + (a[j] - '0') * (b[b.size() - i - 1] - '0');
			TempStr.push_back((Temp % 10) + '0');
			Temp = Temp / 10;
		}
		if (Temp != 0) 
		{
			TempStr.push_back(Temp + '0');
			Temp = 0;
		}
		reverse(TempStr.begin(), TempStr.end());
		for (int j = 0; j < i; j++)
		{
			TempStr.push_back('0');
		}
		Result = sumBinaryString(Result, TempStr);
		TempStr.clear(); 
	}
	if (Negative == true)
	{
		Result.insert(Result.begin(), '-');
	}
	return Result;
}

string QInt::divisionBinaryString(string Dividend, string divisor)
{
	if (divisor == "0")
	{
		return "denominator equals to zero";
	}
	else if (Dividend == "0")
	{
		return "0";
	}
	bool Negative = false;
	if (Dividend[0] == '-')
	{
		Dividend.erase(Dividend.begin());
		if (divisor[0] != '-')
		{
			Negative = true;
		}
		else  divisor.erase(divisor.begin());
	}
	else if (divisor[0] == '-')
	{
		Negative = true;
		divisor.erase(divisor.begin());
	}
	string dividend = Dividend;
	int divisorLength = divisor.size();
	int dividendLength = dividend.size();
	std::string tempDividendString = "";
	std::string quotient = "";
	for (int i = dividendLength - 1; i >= 0; i--)
	{
		int digit = Dividend[dividendLength - i - 1] - '0';
		tempDividendString += '0' + digit;
		if (static_cast<int>(tempDividendString.length()) >= divisorLength)
		{
			string tempDividend(tempDividendString);
			string tempDivisor(divisor);
			int newDigit = 0;
			if (tempDividend > divisor )
			{
				newDigit = 1;
				string temp = sumBinaryString(tempDivisor, divisor);
				while (tempDividend  > temp || tempDividend == temp)
				{
					tempDivisor = sumBinaryString(tempDivisor, divisor);
					temp = tempDivisor;
					newDigit++;
				}
				if (newDigit != 1)
				{
					newDigit--;
				}
			}
			tempDivisor = divisor;
			string multiplier(std::to_string(newDigit));
			string temp = multiplyBinaryString(tempDivisor, multiplier);
			tempDividend = subtractBinaryString(tempDividend,temp);
			tempDividendString = tempDividend;
			quotient += '0' + newDigit;
		}
		else
		{
			quotient += '0';
		}
	}
	while (quotient.length() != 0 && quotient[0] == '0')
	{
		quotient.erase(0, 1);
	}
	if (quotient.length() == 0) return "0";
	if (Negative == true)
	{
		quotient.insert(quotient.begin(), '-');
	}
	return quotient;
}

bool operator > (string a, string b)
{
	if (a.size() > b.size())
	{
		return true;
	}
	else if (a.size() < b.size())
	{
		return false;
	}
	else
	{
		int index = a.size() - 1;
		for (int i = index; i >= 0; i--)
		{
			int digit1 = a[a.size() - i-1] -'0';
			int digit2 = b[b.size() - i-1] -'0';
			if (digit1 > digit2) return true;
			else if (digit1 < digit2) return false;
		}
	}
	return false;
}

string QInt::Power(int a, int n)
{
	string Result;
	if (a > -1)
	{
		if (a > 1)
		{
			int Pow = n;
			if (n > (BIT_INT64 / 2 - 1) * 2 / a) 
			{
				Pow = (BIT_INT64 / 2 - 1) * 2 / a;
			}
			Result = to_string((unsigned _int32)pow(a, Pow));
			for (int i = Pow + 1; i <= n; i++)
			{
				Result = multiplyBinaryString(Result, to_string(a));
			}
		}
		else
		{
			Result.push_back(a + '0');
		}
	}
	return Result;
}

void QInt::binaryToQInt(string str)
{
	for (int i = 0; i < 4; i++) this->arrayBits[i] = 0;
	for (int i = str.length() - 1; i >= 0; i--)
	{
		if (str[i] == '1') changeBit(str.length() - i - 1);
	}
}

/*QInt& QInt::operator = (const QInt& q)
{
	for (int i = 0; i < 4; i++) this->arrayBits[i] = q.arrayBits[i];
	return *this;
}*/

void QInt::operator =  (const string &k) 
{ 
	this->Init();
	__int64 temp = 0;
	for (int i = k.length() - 1; i >= 0; i--)
	{
		if (k[i]=='1') this->TurnOnBit(k.length()-1-i); else this->TurnOffBit(k.length()-1-i);
	}
}

void QInt::operator =  (const QInt &k) 
{
	arrayBits[0] = k.arrayBits[0];
	arrayBits[1] = k.arrayBits[1];
	arrayBits[2] = k.arrayBits[2];
	arrayBits[3] = k.arrayBits[3];
}

QInt QInt::QIntToTwosComplement(QInt q)
{
	QInt result = ~q;
	result = result + QInt("1");
	return result;
}

string QInt::QIntToBinaryString(QInt &q)
{
	string temp;
	for (int i = 0; i < 128; i++) temp = to_string(q.getBit(i)) + temp;
	if (temp.find('/', 0) != -1) temp[temp.find('/', 0)] = '1';
	while (temp[0] == '0') temp.erase(0, 1);
	if (temp.length() == 0) temp = "0";
	return temp;
}

string QInt::QIntToDec(QInt& q)
{
	string temp = QIntToBinaryString(q);
	string result = BinToDec(temp);
	return result;
}

string QInt::QIntToHex(QInt& q)
{
	string temp = QIntToBinaryString(q);
	string result = BinToHex(temp);
	return result;
}

QInt QInt::operator + (QInt q)
{
	/*int excess = 0;
	QInt result;
	if (q.checkZero()) return *this;
	for(int i = 0; i < 128; i++)
	{
		int bitA = this->getBit(i);
		int bitB = q.getBit(i);
		if (bitA + bitB + excess == 0) continue;
		else if (bitA + bitB + excess == 1) 
		{
			result.changeBit(i);
			excess = 0;
		}
		else if (bitA + bitB + excess == 2) excess = 1;
		else if (bitA + bitB + excess == 3) 
		{
			result.changeBit(i);
			excess = 1;
		}
	}
	return result;*/
	QInt result = *this;
	QInt temp;
	while (!(q.checkZero()))
	{
		temp = result & q;
		result = result ^ q;
		q = temp << 1;
	}
	return result;
}

QInt QInt::operator - (QInt q)
{
	/*QInt temp = q;
	for (int i = 0; i < 4; i++) 
	{
		temp.arrayBits[i] = ~temp.arrayBits[i];
	}
	temp.addToOne();
	return (*this + temp);*/
	string StrResult;
	string tempStr1, tempStr2;
	tempStr1 = QIntToBinaryString(*this);       
	tempStr1 = BinToDec(tempStr1);		
	tempStr2 = QIntToBinaryString(q);      
	tempStr2 = BinToDec(tempStr2);		
	StrResult = subtractBinaryString(tempStr1, tempStr2);
	StrResult = DecToBin(StrResult);
	QInt Result(StrResult);
	return Result;
}

QInt QInt::operator * (QInt q)
{
	/*string A = this->toBinary();
	string B = q.toBinary();
	QInt result;
	if (q.checkZero()) return *this;
	bool negativeA = (A[0] == '1');
	bool negativeB = (B[0] == '1');
	if(negativeA)
	{
		for (int i = 0; i < 128; i++) 
		{
			if (A[i] == '1') A[i] = '0';
			else A[i] = 1;
		}
		int excess = 0;
		for (int i = A.length() - 1; i >= 0; i--) 
		{
			if (A[i] == '0' && excess == 0) 
			{
				A[i] = '1';
				break;
			}
			else if (A[i] == '0' && excess == 1) 
			{
				A[i] = '1';
				break;
			}
			else if (A[i] == '1' && excess == 0) 
			{
				A[i] = '0';
				excess = 1;
			}
			//else if (A[i] == '1' && excess == 1) 
			else A[i] = '0';
		}
	}
	if(negativeB)
	{
		for (int i = 0; i < 128; i++) 
		{
			if (B[i] == '0') B[i] = '1';
			else B[i] = '0';
		}
		int excess = 0;
		for(int i = B.length() - 1; i >= 0; i--)
		{
			if (B[i] == '0' && excess == 0) 
			{
				B[i] = '1';
				break;
			}
			else if (B[i] == '0' && excess == 1) 
			{
				B[i] = '1';
				break;
			}
			else if (B[i] == '1' && excess == 0) 
			{
				B[i] = '0';
				excess = 1;
			}
			//else if (B[i] == '1' && excess == 1) 
			else B[i] = '0'; 
		}
	}
	stringstream writer;
	for(int i = 0; i < 128; i++) writer << "0";
	string sum = writer.str();
	for(int i = 0; i < 128; i++) 
	{
		if(B[127 - i] == '1') 
		{
			string temp = A;
			shiftLeft(temp, i);
			sum = sumBinaryString(sum, temp);
		}
	}
	if(negativeA + negativeB == 1)
	{
		for (int i = 0; i < 128; i++)
		if (sum[i] == '0') sum[i] = '1';
		else sum[i] = '0';
		int excess = 0;
		for (int i = sum.length() - 1; i >= 0; i--)
		{
			if (sum[i] == '0' && excess == 0) 
			{
				sum[i] = '1';
				break;
			}
			else if (sum[i] == '0' && excess == 1) 
			{
				sum[i] = '1';
				break;
			}
			else if (sum[i] == '1' && excess == 0) 
			{
				sum[i] = '0';
				excess = 1;
			}
			//else if (sum[i] == '1' && excess == 1) 
			else sum[i] = '0';
		}
	}
	for (int i = sum.length() - 1; i >= 0; i--) 
	{
		if (sum[i] == '1') result.changeBit(127 - i);
	}
	return result;*/
	string StrResult;
	string tempStr1, tempStr2;
	tempStr1 = QIntToBinaryString(*this);       
	tempStr1 = BinToDec(tempStr1);		
	tempStr2 = QIntToBinaryString(q);       
	tempStr2 = BinToDec(tempStr2);		
	StrResult = multiplyBinaryString(tempStr1, tempStr2);  
	StrResult = DecToBin(StrResult);
	QInt Result(StrResult);
	return Result;
}

QInt QInt::operator / (QInt q)
{
	/*string Q = this->toBinary();
	string M = q.toBinary();
	string A, ans;
	int k = 128;
	stringstream writer;
	QInt result;
	if (q.checkZero()) throw "Division by zero !";
	bool negativeQ = (Q[0] == '1');
	bool negativeM = (M[0] == '1');
	if(negativeQ)
	{
		for(int i = 0; i < 128; i++) 
		{
			if (Q[i] == '1') Q[i] = '0';
			else Q[i] = 1;
		}
		int excess = 0;
		for (int i = Q.length() - 1; i >= 0; i--) 
		{
			if (Q[i] == '0' && excess == 0) 
			{
				Q[i] = '1';
				break;
			}
			else if (Q[i] == '0' && excess == 1) 
			{
				Q[i] = '1';
				break;
			}
			else if (Q[i] == '1' && excess == 0) 
			{
				Q[i] = '0';
				excess = 1;
			}
			//else if (Q[i] == '1' && excess == 1) 
			else Q[i] = '0';
		}
	}
	if(negativeM)
	{
		for (int i = 0; i < 128; i++) 
		{
			if (M[i] == '1') M[i] = '0';
			else M[i] = '1';
		}
		int excess = 0;
		for (int i = M.length() - 1; i >= 0; i--)
		{
			if (M[i] == '0' && excess == 0) 
			{
				M[i] = '1';
				break;
			}
			else if (M[i] == '0' && excess == 1) 
			{
				M[i] = '1';
				break;
			}
			else if (M[i] == '1' && excess == 0) 
			{
				M[i] = '0';
				excess = 1;
			}
			//else if (M[i] == '1' && excess == 1) 
			else M[i] = '0';
		}
	}
	if (Q[0] == '1') 
	{
		for (int i = 0; i < 128; i++) writer << "1";
	}
	else
	{
		for (int i = 0; i < 128; i++) writer << "0";
	}
	A = writer.str();
	writer.str("");
	writer << A << Q;
	ans = writer.str();
	while(k > 0)
	{
		shiftLeft(ans, 1);
		for (int i = 0; i < 128; i++) A[i] = ans[i];
		for (int i = 0; i < 128; i++) Q[i] = ans[i + 128];
		A = subtractBinaryString(A, M);
		for (int i = 0; i < 128; i++) ans[i] = A[i];
		if (A[0] == '1') 
		{ 
			Q[127] = '0';
			ans[255] = '0';
			A = sumBinaryString(A, M);
			for (int i = 0; i < 128; i++) ans[i] = A[i];
		}
		else 
		{
			Q[127] = '1';
			ans[255] = '1';
		}
		k--;
	}
	if (negativeM + negativeQ == 1) 
	{ 
		for (int i = 0; i < 128; i++)
		{
			if (Q[i] == '0') Q[i] = '1';
			else Q[i] = '0';
		}
		int excess = 0;
		for (int i = Q.length() - 1; i >= 0; i--) 
		{
			if (Q[i] == '0' && excess == 0) 
			{
				Q[i] = '1';
				break;
			}
			else if (Q[i] == '0' && excess == 1) 
			{
				Q[i] = '1';
				break;
			}
			else if (Q[i] == '1' && excess == 0) 
			{
				Q[i] = '0';
				excess = 1;
			}
			//else if (Q[i] == '1' && excess == 1) 
			else Q[i] = '0';
		}
	}
	for (int i = Q.length() - 1; i >= 0; i--) 
	{
		if (Q[i] == '1') result.changeBit(127 - i);
	}
	return result;*/
	string StrResult;
	string tempStr1, tempStr2;
	tempStr1 = QIntToBinaryString(*this);      
	tempStr1 = BinToDec(tempStr1);		
	tempStr2 = QIntToBinaryString(q);       
	tempStr2 = BinToDec(tempStr2);		
	StrResult = divisionBinaryString(tempStr1, tempStr2);
	StrResult = DecToBin(StrResult);
	QInt Result(StrResult);
	return Result;
}

QInt QInt::operator << (const int &k)
{
	/*stringstream writer;
	string str = this->toBinary();
	str.erase(0, num);
	writer << str;
	for (int i = 0; i < num; i++) writer << '0';
	str = writer.str();
	for (int i = 0; i < 4; i++) this->arrayBits[i] = 0;
	for (int i = 0; i < 128; i++) 
	{
		if (str[i] == '1') this->changeBit(127 - i);
	}
	return *this;*/
	int temp;			
	for (int i = 127; i >= k; i--)
	{
		temp = this->getBit(i - k);
		if (temp) this->TurnOnBit(i); else this->TurnOffBit(i);
	}
	for (int i = 0; i < k; i++) this->TurnOffBit(i);
	return (*this);
}

QInt QInt::operator >> (const int &k)
{
	/*stringstream writer;
	string str = this->toBinary();
	str.erase(127 - num, num);
	for (int i = 0; i < 4; i++) this->arrayBits[i] = 0;
	if (str[0] == '1') 
	{
		for (int i = 0; i < num; i++) writer << "1";
	}
	else
	{
		for (int i = 0; i < num; i++) writer << "0";
	}
	writer << str;
	str = writer.str();
	for (int i = 0; i < 128; i++) 
	{
		if (str[i] == '1') this->changeBit(127 - i);
	}
	return *this;*/
	int temp;
	int sign = this->getBit(127);
	for (int i = 0; i < 128 - k; i++)
	{
		temp = this->getBit(i + k);
		if (temp) this->TurnOnBit(i); else this->TurnOffBit(i);
	}
	if (sign) for (int i = 127; i > 127 - k; i--) this->TurnOnBit(i);
	else for (int i = 127; i > 127 - k; i--) this->TurnOffBit(i);
	if (sign) this->TurnOnBit(127); else this->TurnOffBit(127);
	return (*this);
}

void QInt::Init() 
{
	arrayBits[0] = 0;
	arrayBits[1] = 0;
	arrayBits[2] = 0;
	arrayBits[3] = 0;
}

QInt QInt::operator & (QInt q)
{
	/*string A = this->toBinary();
	string B = q.toBinary();
	stringstream writer;
	string ans;
	QInt result;
	for(int i = 0; i < 128; i++) writer << '0';
	ans = writer.str();
	for (int i = 0; i < 128; i++) 
	{
		int digitA = A[i] - 48;
		int digitB = B[i] - 48;
		if (digitA + digitB == 2) ans[i] = '1';
		else ans[i] = '0';
	}
	for (int i = 0; i < QInt::num_of_int; i++) this->arrayBits[i] = 0;
	for (int i = ans.length() - 1; i >= 0; i--) 
	{
		if (ans[i] == '1') result.changeBit(127 - i);
	}
	return result;*/
	QInt temp;
	temp.Init();
	for (int i = 0; i < 128; i++)
	{
		if (q.getBit(i) & this->getBit(i)) temp.TurnOnBit(i);
	}
	return temp;
}

QInt QInt::operator | (QInt q)
{
	/*string A = this->toBinary();
	string B = q.toBinary();
	stringstream writer;
	string ans;
	QInt result;
	for(int i = 0; i < 128; i++) writer << " ";
	ans = writer.str();
	for (int i = 0; i < 128; i++) 
	{
		int digitA = A[i] - 48;
		int digitB = B[i] - 48;
		if (digitA + digitB >= 1) ans[i] = '1';
		else ans[i] = '0';
	}
	for(int i = ans.length() - 1; i >= 0; i--) 
	{
		if (ans[i] == '1') result.changeBit(127 - i);
	}
	return result;*/
	QInt temp;
	temp.Init();
	for (int i = 0; i < 128; i++)
	{
		if (q.getBit(i) | this->getBit(i)) temp.TurnOnBit(i);
	}
	return temp;
}

QInt QInt::operator ^ (QInt q)
{
	/*string A = this->toBinary();
	string B = q.toBinary();
	stringstream writer;
	string ans;
	QInt result;
	for(int i = 0; i < 128; i++) writer << '0';
	ans = writer.str();
	for (int i = 0; i < 128; i++) 
	{
		if (A[i] != B[i]) ans[i] = '1';
		else ans[i] = '0';
	}
	for (int i = 0; i < QInt::num_of_int; i++) this->arrayBits[i] = 0;
	for (int i = ans.length() - 1; i >= 0; i--) 
	{
		if (ans[i] == '1') result.changeBit(127 - i);
	}
	return result;*/
	QInt temp;
	temp.Init();
	for (int i = 0; i < 128; i++)
	{
		if (q.getBit(i) ^ this->getBit(i)) temp.TurnOnBit(i);
	}
	return temp;
}

QInt& QInt::operator ~ ()
{
	/*string str = this->toBinary();
	QInt result = *this;
	for (int i = 0; i < 128; i++) result.changeBit(i);
	return result;*/
	arrayBits[0] = ~arrayBits[0];
	arrayBits[1] = ~arrayBits[1];
	arrayBits[2] = ~arrayBits[2];
	arrayBits[3] = ~arrayBits[3];
	return *this;
}

string QInt::toHexa()
{
	string str = this->toBinary();
	return BinToHex(str);
}

void QInt::hexaToQInt(string str)
{
	string hexaBin("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	int hexaPos = 124;
	string hexaDigitInBinary;
	for (int i = str.length() - 1; i > -1; i--)
	{
		switch(str[i])
		{
			case '0': hexaDigitInBinary = "0000"; break;
			case '1': hexaDigitInBinary = "0001"; break;
			case '2': hexaDigitInBinary = "0010"; break;
			case '3': hexaDigitInBinary = "0011"; break;
			case '4': hexaDigitInBinary = "0100"; break;
			case '5': hexaDigitInBinary = "0101"; break;
			case '6': hexaDigitInBinary = "0110"; break;
			case '7': hexaDigitInBinary = "0111"; break;
			case '8': hexaDigitInBinary = "1000"; break;
			case '9': hexaDigitInBinary = "1001"; break;
			case 'A': hexaDigitInBinary = "1010"; break;
			case 'B': hexaDigitInBinary = "1011"; break;
			case 'C': hexaDigitInBinary = "1100"; break;
			case 'D': hexaDigitInBinary = "1101"; break;
			case 'E': hexaDigitInBinary = "1110"; break;
			case 'F': hexaDigitInBinary = "1111"; break;
			default: throw "not a hexadecimal"; break;
		}
		hexaBin.replace(hexaPos, 4, hexaDigitInBinary);
		hexaPos -= 4;
	}
	this->binaryToQInt(hexaBin);
}

/*QInt::QInt(string str)
{
	this->decimalToQInt(str);
}*/

void QInt::clear()
{
	for (int i = 0; i < 4; i++)  this->arrayBits[i] = 0;
}

string normalizeString(string str)
{
	unsigned int i;
	for(i = 0; i < str.length(); i++)
	{
		if (str[i] == '1') break;
	}
	if (i == str.length()) i--;
	str.erase(0, i);
	return str;
}

//////HA convert function
string StringDivTwo(string &number)
{
	string Result;
	int Temp = 0;
	for (int i = 0; i < number.size(); i++)
	{
		Temp = Temp * 10 + (number[i] - '0');
		if (i > 0 || (i == 0 && Temp >= 2))
		{
			Result.push_back((Temp / 2) + '0');
		}
		Temp = Temp % 2;
	}
	return Result;
}

string QInt::DecToBin(string& strDec)
{
	string temp = strDec;
	string result;
	bool negative = false;
	if (strDec[0] == '-')
	{
		strDec.erase(strDec.begin());
		negative = true;
	}
	while (strDec != "")
	{
		result.push_back(((strDec[strDec.size() - 1] - '0') % 2) + '0');
		strDec = divByTwo(strDec);
	}
	reverse(result.begin(), result.end());
	if (negative == true)
	{
		/*for (int i = 0; i < 4; i++)
		{
			this->arrayBits[i] = ~this->arrayBits[i];
			this->addToOne();
		}*/
		QInt q(result); //Đưa vào số kiểu CQInt.
		q = QIntToTwosComplement(q); //Chuyển sang dạng bù 2.
		result = QIntToBinaryString(q); //Đưa lại về nhị phân.
	}
	strDec = temp;
	return result;
}

string QInt::HexToBin(string& str)
{
	string binary;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '0') { binary += "0000"; } 
		else if (str[i] == '1') { binary += "0001"; } 
		else if (str[i] == '2') { binary += "0010"; }
		else if (str[i] == '3') { binary += "0011"; }				 	
		else if (str[i] == '4') { binary += "0100"; }            
		else if (str[i] == '5') { binary += "0101"; }
		else if (str[i] == '6') { binary += "0110"; }
		else if (str[i] == '7') { binary += "0111"; }
		else if (str[i] == '8') { binary += "1000"; }
		else if (str[i] == '9') { binary += "1001"; }
		else if (str[i] == 'A' || str[i] == 'a') { binary += "1010"; }
		else if (str[i] == 'B' || str[i] == 'b') { binary += "1011"; }
		else if (str[i] == 'C' || str[i] == 'c') { binary += "1100"; }
		else if (str[i] == 'D' || str[i] == 'd') { binary += "1101"; }
		else if (str[i] == 'E' || str[i] == 'e') { binary += "1110"; }
		else if (str[i] == 'F' || str[i] == 'f') { binary += "1111"; } 
	}
	return binary;
}

string QInt::BinToHex(string& strHex)
{
	string Temp;
	string Result;
	while (strHex.size() % 4 != 0)
	{
		strHex.insert(strHex.begin(), '0'); 
	}
	for (int i = 0; i < strHex.size(); i++)
	{
		Temp.push_back(strHex[i]);
		if (i % 4 == 3) 
		{
			if (Temp == "0000") { Result.push_back('0'); }
			else if (Temp == "0001") { Result.push_back('1'); }
			else if (Temp == "0010") { Result.push_back('2'); }
			else if (Temp == "0011") { Result.push_back('3'); }
			else if (Temp == "0100") { Result.push_back('4'); }
			else if (Temp == "0101") { Result.push_back('5'); }
			else if (Temp == "0110") { Result.push_back('6'); }
			else if (Temp == "0111") { Result.push_back('7'); }
			else if (Temp == "1000") { Result.push_back('8'); }
			else if (Temp == "1001") { Result.push_back('9'); }
			else if (Temp == "1010") { Result.push_back('A'); }
			else if (Temp == "1011") { Result.push_back('B'); }
			else if (Temp == "1100") { Result.push_back('C'); }
			else if (Temp == "1101") { Result.push_back('D'); }
			else if (Temp == "1110") { Result.push_back('E'); }
			else if (Temp == "1111") { Result.push_back('F'); }
			Temp = ""; 
		}
	}
	return Result;
}

/*string QInt::DecToHex(string str)
{
	string dectobin_result = DecToBin(str);
	string Result = BinToHex(dectobin_result);
	return Result;
}

string QInt::HexToDec(string str)
{
	string hextobin_result = HexToBin(str);
	string Result = BinToDec(hextobin_result);
	return Result;
}*/

string QInt::BinToDec(string& strBin)
{
	/*string result = "0";
	stringstream writer;
	for (int i = binary.length() - 1; i >= 0; i--)
	{
		if (binary[i] == '1')
		{
			string pow = QInt::sumOf2PowN(binary.length() - i - 1);
			result = QInt::addString(result, pow);
		}
	}
	writer << result;
	result = writer.str();
	return result;*/
	string dec;
	bool negative = false;
	string temp = "0";
	string resulttemp;
	if (strBin[0] == '1'&& strBin.length() == 128) 
	{
		negative = true;
		int i = strBin.length() - 1;
		while (i >= 0 && strBin[i] == '0') i = i - 1;
		strBin[i] = '0';
		for (int j = i + 1; j < strBin.length(); j++)strBin[j] = '1';
		for (int i = 0; i < strBin.length(); i++)
			if (strBin[i] == '1') strBin[i] = '0'; else strBin[i] = '1';
	}
	for (int i = strBin.size(); i > 0; i--)
	{
		resulttemp = "0";
		if (strBin[strBin.size() - i] == '1')
		{
			resulttemp =  Power(2, i - 1);
		}
		temp = sumBinaryString(temp, resulttemp);
	}
	dec = temp;
	if (negative) dec = '-' + dec;
	return dec;
}

string QInt::StrIntToTwosComplement(string& strBin)
{
	string Temp = strBin;
	char temp;
	for (int i = 0; i < strBin.size(); i++)
	{	if (Temp[i] == '0')
		{
			Temp[i] = '1';
		}
		else if(Temp[i] == '1')
		{
			Temp[i] ='0';
		}
	}
	for (int i = strBin.size(); i > 0; i--)
	{
		if (Temp[i] == '0')
		{
			Temp[i] = '1';
			return Temp;
		}
		Temp[i] = '0';
	}
	return Temp ;
}

/////process
void printBin(QInt x)
{
	string binString = normalizeString(x.toBinary());
	cout << binString;
}

void printDec(QInt x)
{
	string decString = cutZero(x.toString());
	cout << decString;
}

void printHex(QInt x)
{
	string hexString = cutZero(x.toHexa());
	cout << hexString;
}

void QInt::printQInt(int base)
{
	if (base == 2) printBin(*this); 
	else if (base == 10) printDec(*this); 
	else if (base == 16) printHex(*this);
	cout << endl;
}

void QInt::ScanQInt(string source, int sourceBase)
{
	if(sourceBase == 2) this->binaryToQInt(source);
	else if(sourceBase == 10) this->decimalToQInt(source);
	else if(sourceBase == 16) this->hexaToQInt(source);
}

void process(vector<string> str_arr)
{
	if(str_arr.size() == 4)
	{
		int p = stoi(str_arr[0]);
		QInt s1, s2, s3;
		s1.ScanQInt(str_arr[1], p);
		if (str_arr[2] == "<<") 
		{
			int numShift = stoi(str_arr[3]);
			s3 = s1 << numShift;
		}
		else if (str_arr[2] == ">>") 
		{
			int numShift = stoi(str_arr[3]);
			s3 = s1 >> numShift;
		}
		else 
		{
			s2.ScanQInt(str_arr[3], p);
			s3 = CalculateOpe(s1, s2, str_arr[2]);
		}
		s3.printQInt(p);
	}
	else if(str_arr.size() == 3)
	{
		int p1 = stoi(str_arr[0]);
		QInt s, result;
		s.ScanQInt(str_arr[2], p1);
		if(str_arr[1] == "~")
		{
			result = ~s;
			result.printQInt(p1);
		}
		else if(str_arr[1] == "2" || str_arr[1] == "10" || str_arr[1] == "16")
		{
			int p2 = stoi(str_arr[1]);
			s.printQInt(p2);
		}
	}
}

vector<string> cut_stringInput(string str_input) 
{
	vector<string> str_arr;
	int i = 0;
	while (i < str_input.length()) 
	{
		int j = i;
		while (j < str_input.length() && str_input[j] != ' ') j++;
		string s = str_input.substr(i, j - i);
		str_arr.push_back(s);
		i = j + 1;
	}
	return str_arr;
}

void mainCaculate(char* file_input, char* file_output)
{
	FILE* fin = freopen(file_input, "r", stdin); 
	FILE* fout = freopen(file_output, "w", stdout);
	string string_input; 
	vector<string> string_arr;
	while(getline(cin, string_input)) 
	{
		string_arr = cut_stringInput(string_input);
		process(string_arr);  ///handle for operator and convert
		subProcess(string_input); ////handle for ror, rol
	}
	fclose(fin);
	fclose(fout);
}

QInt CalculateOpe(QInt a, QInt b, string ope)
{
	switch (ope[0])
	{
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': return a / b;
		case '&': return a & b;
		case '|': return a | b;
		case '^': return a ^ b;
	}
}

/////handle for ror, rol
void QInt::TurnOffBit(int k)
{
	__int64 temp = 1;
	this->arrayBits[k / 64] = this->arrayBits[k / 64] & (~(temp << (k % 64)));
}

void QInt::TurnOnBit(int k)
{
	__int64 temp = 1;
	this->arrayBits[k / 64] = this->arrayBits[k / 64] | (temp << (k % 64));
}

QInt QInt::rol()
{
	int Bit_127 = (*this).getBit(127);
	*this = *this << 1;
	if(Bit_127) (*this).TurnOnBit(0); else (*this).TurnOffBit(0);
	return (*this);
}

QInt QInt::ror()
{
	int Bit_0 = (*this).getBit(0);
	*this = *this >> 1;
	if (Bit_0) (*this).TurnOnBit(127); else (*this).TurnOffBit(127);
	return (*this);
}

int getInfo(string &str)
{
	int temp = 0;
	if (str[0] == '2' && str[1] == ' ')
	{
		temp = 2;
		str.erase(0, 2);
	}
	else if (str[0] == '1')
	{
		if (str[1] == '0' && str[2] == ' ')
		{
			temp = 10;
			str.erase(0, 3);
		}
		else if (str[1] == '6' && str[2] == ' ')
		{
			temp = 16;
			str.erase(0, 3);
		}
	}
	return temp;
}

void subProcess(string& line)
{
	QInt q;
	int str1, str2;
	str1 = getInfo(line);
	str2 = getInfo(line);
	if (str2 == 0)
	{
		if (line[0] == 'r')
		{
			if (line[2] == 'r')
			{
				line.erase(0, 4);
				if (str1 == 10)
				{
					line = q.DecToBin(line);
				}
				if (str1 == 16)
				{
					line = q.HexToBin(line);
				}
				/*QInt temp_qint, result_qint;
				temp_qint.binaryToQInt(line);
				result_qint = temp_qint.ror();
				result_qint.printQInt(str1);*/
				QInt temp(line);
				temp.ror();
				line = q.QIntToBinaryString(temp);
				if (str1 == 10)
				{
					line = q.BinToDec(line);
				}
				if (str1 == 16)
				{
					line = q.BinToHex(line);
				}
			}
			else if (line[2] == 'l')
			{
				line.erase(0, 4);
				if (str1 == 10)
				{
					line = q.DecToBin(line);
				}
				if (str1 == 16)
				{
					line = q.HexToBin(line);
				}
				/*QInt temp_qint, result_qint;
				temp_qint.binaryToQInt(line);
				result_qint = temp_qint.rol();
				result_qint.printQInt(str1);*/
				QInt temp(line);
				temp = temp.rol();
				line = q.QIntToBinaryString(temp);
				if (str1 == 10)
				{
					line = q.BinToDec(line);
				}
				if (str1 == 16)
				{
					line = q.BinToHex(line);
				}
			}
		}
	}
}

///cut zero for hex, dec
string cutZero(string str)
{
	int count = 0;
	for(unsigned i = 0; i < str.length(); i++)
	{
		if (str[i] != '0') break;
		count++;
	}
	str.erase(0, count);
	return str;
}

/////////////////read file
void process(string &s)
{
	QInt q;
	string c;
	int p1, p2;
	cout << s << endl;
	p1 = getInfo(s);
	p2 = getInfo(s);
	if (p2 != 0) 
	{
		if (p1 == 2)
		{
			if (p2 == 10)
			{
				s = q.BinToDec(s);
			}
			if (p2 == 16)
			{
				s = q.BinToHex(s);
			}
		}
		if (p1 == 10)
		{
			if (p2 == 2)
			{
				s = q.DecToBin(s);
			}
			if (p2 == 16)
			{
				s = q.DecToBin(s);
				s = q.BinToHex(s);
			}
		}
		if (p1 == 16)
		{
			if (p2 == 2)
			{
				s = q.HexToBin(s);
			}
			if (p2 == 10)
			{
				s = q.HexToBin(s);
				s = q.BinToDec(s);
			}
		}
	}
	else
	{
		if (s[0] == 'r')
		{
			if (s[2] == 'r')
			{
				s.erase(0, 4);
				if (p1 == 10)
				{
					s = q.DecToBin(s);
				}
				if (p1 == 16)
				{
					s = q.HexToBin(s);
				}
				QInt temp(s);
				temp.ror();
				s = q.QIntToBinaryString(temp);
				if (p1 == 10)
				{
					s = q.BinToDec(s);
				}
				if (p1 == 16)
				{
					s = q.BinToHex(s);
				}
			}
			else if (s[2] == 'l')
			{
				s.erase(0, 4);
				if (p1 == 10)
				{
					s = q.DecToBin(s);
				}
				if (p1 == 16)
				{
					s = q.HexToBin(s);
				}
				QInt temp(s);
				temp = temp.rol();
				s = q.QIntToBinaryString(temp);
				if (p1 == 10)
				{
					s = q.BinToDec(s);
				}
				if (p1 == 16)
				{
					s = q.BinToHex(s);
				}
			}
		}
		else if (s[0] == '~')
		{
			s.erase(0, 2);
			if (p1 == 10)
			{
				s = q.DecToBin(s);
			}
			if (p1 == 16)
			{
				s = q.HexToBin(s);
			}
			QInt temp(s);
			temp = ~temp;
			s = q.QIntToBinaryString(temp);
			if (p1 == 10)
			{
				s = q.BinToDec(s);
			}
			if (p1 == 16)
			{
				s = q.BinToHex(s);
			}
		}
		else if (s.find("<<", 0) != -1)
		{
			int vt = s.find("<<", 0);
			string s1, s2;
			s1 = s.substr(0, vt - 1);       
			s2 = s.substr(vt + 3, s.length());
			int ints2 = stoi(s2);   
			if (p1 == 10)
			{
				s1 = q.DecToBin(s1);
			}
			if (p1 == 16)
			{
				s1 = q.HexToBin(s1);
			}
			QInt temp(s1);
			temp = temp << ints2;
			s = q.QIntToBinaryString(temp);
			if (p1 == 10)
			{
				s = q.BinToDec(s);
			}
			if (p1 == 16)
			{
				s = q.BinToHex(s);
			}
		}
		else if (s.find(">>", 0) != -1)
		{
			int vt = s.find(">>", 0);
			string s1, s2;
			s1 = s.substr(0, vt - 1);
			s2 = s.substr(vt + 3, s.length());
			int ints2 = stoi(s2);   
			if (p1 == 10)
			{
				s1 = q.DecToBin(s1);
			}
			if (p1 == 16)
			{
				s1 = q.HexToBin(s1);
			}
			QInt temp(s1);
			temp = temp >> ints2;
			s = q.QIntToBinaryString(temp);
			if (p1 == 10)
			{
				s = q.BinToDec(s);
			}
			if (p1 == 16)
			{
				s = q.BinToHex(s);
			}
		}
		else if (s.find("+", 0) != -1)
		{
			int vt = s.find("+", 0);
			string s1, s2;
			s1 = s.substr(0, vt - 1);
			s2 = s.substr(vt + 2, s.length());
			if (p1 == 10)
			{
				s1 = q.DecToBin(s1);
				s2 = q.DecToBin(s2);
			}
			if (p1 == 16)
			{
				s1 = q.HexToBin(s1);
				s2 = q.HexToBin(s2);
			}
			QInt temp1(s1), temp2(s2);
			QInt KQ;
			KQ = temp1 + temp2;
			s = q.QIntToBinaryString(KQ);
			if (p1 == 10)
			{
				s = q.BinToDec(s);
			}
			if (p1 == 16)
			{
				s = q.BinToHex(s);
			}
		}
		else if (s.find("- ", 1) != -1)      
		{
			int vt = s.find("- ", 1);
			string s1, s2;
			s1 = s.substr(0, vt - 1);
			s2 = s.substr(vt + 2, s.length());
			if (p1 == 10)
			{
				s1 = q.DecToBin(s1);
				s2 = q.DecToBin(s2);
			}
			if (p1 == 16)
			{
				s1 = q.HexToBin(s1);
				s2 = q.HexToBin(s2);
			}
			QInt temp1(s1), temp2(s2);
			QInt KQ;
			KQ = temp1 - temp2;
			s = q.QIntToBinaryString(KQ);
			if (p1 == 10)
			{
				s = q.BinToDec(s);
			}
			if (p1 == 16)
			{
				s = q.BinToHex(s);
			}
		}          
		else if (s.find("*", 0) != -1)
		{
			int vt = s.find("*", 0);
			string s1, s2;
			s1 = s.substr(0, vt - 1);
			s2 = s.substr(vt + 2, s.length());
			if (p1 == 10)
			{
				s1 = q.DecToBin(s1);
				s2 = q.DecToBin(s2);
			}
			if (p1 == 16)
			{
				s1 = q.HexToBin(s1);
				s2 = q.HexToBin(s2);
			}
			QInt temp1(s1), temp2(s2);
			QInt KQ;
			KQ = temp1 * temp2;
			s = q.QIntToBinaryString(KQ);
			if (p1 == 10)
			{
				s = q.BinToDec(s);
			}
			if (p1 == 16)
			{
				s = q.BinToHex(s);
			}
		}
		else if (s.find("/", 0) != -1)
		{
			int vt = s.find("/", 0);
			string s1, s2;
			s1 = s.substr(0, vt - 1);
			s2 = s.substr(vt + 2, s.length());
			if (p1 == 10)
			{
				s1 = q.DecToBin(s1);
				s2 = q.DecToBin(s2);
			}
			if (p1 == 16)
			{
				s1 = q.HexToBin(s1);
				s2 = q.HexToBin(s2);
			}
			QInt temp1(s1), temp2(s2);
			QInt KQ;
			KQ = temp1 / temp2;
			s = q.QIntToBinaryString(KQ);
			if (p1 == 10)
			{
				s = q.BinToDec(s);
			}
			if (p1 == 16)
			{
				s = q.BinToHex(s);
			}
		}
		else if (s.find("&", 0) != -1)       
		{
			int vt = s.find("&", 0);
			string s1, s2;
			s1 = s.substr(0, vt - 1);
			s2 = s.substr(vt + 2, s.length());
			if (p1 == 10)
			{
				s1 = q.DecToBin(s1);          
				s2 = q.DecToBin(s2);
			}
			if (p1 == 16)
			{
				s1 = q.HexToBin(s1);
				s2 = q.HexToBin(s2);
			}
			QInt temp1(s1),temp2(s2);
			QInt temp;
			temp = temp1 & temp2;
			s = q.QIntToBinaryString(temp);
			if (p1 == 10)
			{
				cout << s << endl;
				s = q.BinToDec(s);
			}
			if (p1 == 16)
			{
				s = q.BinToHex(s);
			}
		}
		else if (s.find("|", 0) != -1)
		{
			int vt = s.find("|", 0);
			string s1, s2;
			s1 = s.substr(0, vt - 1);
			s2 = s.substr(vt + 2, s.length());
			if (p1 == 10)
			{
				s1 = q.DecToBin(s1);
				s2 = q.DecToBin(s2);
			}
			if (p1 == 16)
			{
				s1 = q.HexToBin(s1);
				s2 = q.HexToBin(s2);
			}
			QInt temp1(s1), temp2(s2);
			QInt temp;
			temp = temp1 | temp2;
			s = q.QIntToBinaryString(temp);
			if (p1 == 10)
			{
				s = q.BinToDec(s);        
			}
			if (p1 == 16)
			{
				s = q.BinToHex(s);
			}
		}
		else if (s.find("^", 0) != -1)
		{
			int vt = s.find("^", 0);
			string s1, s2;
			s1 = s.substr(0, vt - 1);
			s2 = s.substr(vt + 2, s.length());
			if (p1 == 10)
			{
				s1 = q.DecToBin(s1);
				s2 = q.DecToBin(s2);
			}
			if (p1 == 16)
			{
				s1 = q.HexToBin(s1);
				s2 = q.HexToBin(s2);
			}
			QInt temp1(s1), temp2(s2);
			QInt temp;
			temp = temp1 ^ temp2;
			s = q.QIntToBinaryString(temp);
			if (p1 == 10)
			{
				s = q.BinToDec(s);
			}
			if (p1 == 16)
			{
				s = q.BinToHex(s);
			}
		}
	}
}

void readFile(const string Input, const string Output)
{
	ifstream fin;
	ofstream fout;
	fin.open(Input);
	fout.open(Output);
	if(!fin.is_open())
	{
		cerr << "File not found";
		exit(0);
	}
	while (!fin.eof())
	{
		string s = "";
		getline(fin, s);
		process(s);
		while (s[0] == '0')
		{
			s.erase(s.begin(), s.begin() + 1);
		}
		if (s == "") s = "0";
		cout << s << endl;
		fout << s << endl;
	}
	fin.close();
	fout.close();
}