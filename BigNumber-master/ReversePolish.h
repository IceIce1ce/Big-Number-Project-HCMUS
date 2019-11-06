void filterOperand(string str, string operand[]);
queue<string> convertReversePolish(string A);  // input the polynomial string and return to the reverse polish pattern
string calRevString(queue<string> Rev);
void calExpressionFile(string pathLoad, string pathSave);
queue<string> refineElement(queue<string> Rev);     // splitted each element consist of signed
void checkTrueExpr(string str); // check if the expression are all operator and operand,not characters
void loadFileString(string path, string str[], int &n);
void saveFileString(string path, string str[], int n);
