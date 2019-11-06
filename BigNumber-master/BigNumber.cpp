// BigNumber.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
//	BigInteger A("622803791148300"), B("88407606117740");
	BigInteger A("222222"), B("4444");
//	BigInteger A("2346748646876"), B("-78946846844");
//	BigInteger A("-3579102"), B("1253");
//	BigInteger A("-134384738800000000000"), B("-45875875875845");
	cout << A / B << endl;
//	calExpressionFile("e:\\BigInteger.txt", "e:\\res.txt");
	

// 3. Yeu cau nang cao 
	/*string loadPath, savePath;
	cout << "Nhap duong dan load file: ";
	cin >> loadPath;
	cout << "Nhap duong dan save file: ";
	cin >> savePath;
	calExpressionFile(loadPath, savePath);*/

// 1 + 2. Yeu cau co ban
	/*BigInteger A[10], S, M, T, Q;
	int n;
	BigInteger::loadFile("e:\BigInteger.txt", A, n);
	S = M = T = Q = A[0];
	for(int i = 1 ; i < n; i++) {
		S = S + A[i];
		M = M - A[i];
		T = T * A[i];
		Q = Q / A[i];
	}

	cout << "S: " << S << endl;
	cout << "M: " << M << endl;
	cout << "T: " << T << endl;
	cout << "Q: " << Q << endl;

	string s = "S: " + S.getStringNumber();
	string m = "M: " + M.getStringNumber();
	string t = "T: " + T.getStringNumber();
	string q = "Q: " + Q.getStringNumber();

	BigInteger::saveFile("e:\\result.txt", A, n);
	BigInteger::appendFile("e:\\result.txt", s);
	BigInteger::appendFile("e:\\result.txt", m);
	BigInteger::appendFile("e:\\result.txt", t);
	BigInteger::appendFile("e:\\result.txt", q);*/


	/*BigInteger A, B, S, M, T, Q;
	cin >> A;
	cin >> B;
	S = A + B;
	M = A - B;
	T = A * B;
	Q = A / B;

	cout << "S: " << S << endl;
	cout << "M: " << M << endl;
	cout << "T: " << T << endl;
	cout << "Q: " << Q << endl;

	if(S > M)
		cout << S << " > " << M << endl;
	else if(S == M)
		cout << S << " = " << M << endl;
	else
		cout << S << " < " << M << endl;

	if(S > T)
		cout << S << " > " << T << endl;
	else if(S == T)
		cout << S << " = " << T << endl;
	else
		cout << S << " < " << T << endl;

	if(S > Q)
		cout << S << " > " << Q << endl;
	else if(S == M)
		cout << S << " = " << Q << endl;
	else
		cout << S << " < " << Q << endl;*/

	return 0;
}

