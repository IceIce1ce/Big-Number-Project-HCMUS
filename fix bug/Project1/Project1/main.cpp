#include"QInt.h"

int main(int argc, const char* argv[])
{
	//char *s1 = _strdup("input.txt");
	//char *s2 = _strdup("output.txt");
	//mainCaculate(s1, s2);
	readFile("input.txt", "output.txt");
	/*if(argc != 3)
	{
		cout << "Need 3 argument";
		return -1;
	}
	readFile(argv[1],argv[2]);*/
	return 0;
}