#include "IO_STREAM.h"
#include "ProcessString.h"
#include "QInt.h"

bool readExponent2(vector<string>& exponent_2, const string& path){
	fstream myFile;
	myFile.open(path, ios::in);
	
	if (myFile){
		string temp;
		while (1){
			getline(myFile, temp);
			if (temp.length() == 0)
				break;
			exponent_2.push_back(temp);
		}
		myFile.close();
		return true;
	}
	return false;
}

bool readTestFile(vector<string>& argcsTest, const string& path){
	fstream myFile;
	myFile.open(path, ios::in);
	if (myFile){
		string temp;
		while (1){
			temp = "";
			getline(myFile, temp);
			if (temp.length() == 0)
				break;
			argcsTest.push_back(temp);
		}
		myFile.close();
		return true;
	}
	return false;
}

bool Process_WriteFileOutput(const vector<string>& argcsTest, const string& path){
	fstream myFile;
	myFile.open(path, ios::out);
	if (myFile){
		int numberTest = argcsTest.size();
		for (int i = 0; i < numberTest; i++){
			string order = argcsTest[i];
			string outPut;
			outPut = Calculate(order);
			myFile << outPut << endl;
		}
		myFile.close();
		return true;
	}
	return false;
}

string Calculate(const string& order){
	string outPut = "";
	unsigned int c_blankspace = countCharacter(order, ' ');
	string param1, param2, param3, param4;
	assignDataToString(order, param1, param2, param3, param4, ' ');
	QInt A;
	if (c_blankspace == 2){
		int num_Param1 = stoi(param1);
		if (checkDecimalNumber(param2)){
			int num_Param2 = stoi(param2);
			if (num_Param2 < 11){
				if (num_Param1 == 2 && num_Param2 == 10){
					A.setBitFromBinaryStr(param3);
					outPut = SimpleDecimalStr(A.toNumberDecimal());
				}
				else if (num_Param1 == 10 && num_Param2 == 2){
					A.setBitFromDecNumberStr(param3);
					outPut = SimpleDecimalStr(A.toNumberBinary());
				}
				else if (num_Param1 == 16 && num_Param2 == 2){
					A.setBitFromHexaStr(param3);
					outPut = SimpleDecimalStr(A.toNumberBinary());
				}
				else if (num_Param1 == 2 && num_Param2 == 16){
					A.setBitFromBinaryStr(param3);
					outPut = SimpleDecimalStr(A.toNumberHexa());
				}
			}
		}
		else if (param2 == "ror"){
			if (num_Param1 == 2){
				A.setBitFromBinaryStr(param3);
				A = A.ror();
				outPut = SimpleDecimalStr(A.toNumberBinary());
			}
			else if (num_Param1 == 10){
				A.setBitFromDecNumberStr(param3);
				A = A.ror();
				outPut = SimpleDecimalStr(A.toNumberDecimal());
			}
			else if (num_Param1 == 16){
				A.setBitFromHexaStr(param3);
				A = A.ror();
				outPut = SimpleDecimalStr(A.toNumberHexa());
			}
		}
		else if (param2 == "rol"){
			if (num_Param1 == 2){
				A.setBitFromBinaryStr(param3);
				A = A.rol();
				outPut = SimpleDecimalStr(A.toNumberBinary());
			}
			else if (num_Param1 == 10){
				A.setBitFromDecNumberStr(param3);
				A = A.rol();
				outPut = SimpleDecimalStr(A.toNumberDecimal());
			}
			else if (num_Param1 == 16){
				A.setBitFromHexaStr(param3);
				A = A.rol();
				outPut = SimpleDecimalStr(A.toNumberHexa());
			}
		}
		else if (param2 == "~"){
			if (num_Param1 == 2){
				A.setBitFromBinaryStr(param3);
				A = ~A;
				outPut = SimpleDecimalStr(A.toNumberBinary());
			}
			else if (num_Param1 == 10){
				A.setBitFromDecNumberStr(param3);
				A = ~A;
				outPut = SimpleDecimalStr(A.toNumberDecimal());
			}
			else if (num_Param1 == 16){
				A.setBitFromHexaStr(param3);
				A = ~A;
				outPut = SimpleDecimalStr(A.toNumberHexa());
			}
		}
	}
	else if (c_blankspace == 3){
		int num_Param1 = stoi(param1);
		QInt B, Result;
		if (num_Param1 == 2){
			A.setBitFromBinaryStr(param2);
			if (param3 == "+" || param3 == "-" || param3 == "*" || param3 == "/" || param3 == "&"
				|| param3 == "|" || param3 == "^"){
				B.setBitFromBinaryStr(param4);
				if (param3 == "+"){
					Result = A + B;
				}
				else if (param3 == "-"){
					Result = A - B;
				}
				else if (param3 == "*"){
					Result = A * B;
				}
				else if (param3 == "/"){
					Result = A / B;
				}
				else if (param3 == "&"){
					Result = A & B;
				}
				else if (param3 == "|"){
					Result = A | B;
				}
				else if (param3 == "^"){
					Result = A ^ B;
				}			
			}
			else if (param3 == ">>" || param3 == "<<"){
				int k = stoi(param4);
				if (param3 == ">>"){
					Result = A >> k;
				}
				else if (param3 == "<<"){
					Result = A << k;
				}
			}
			outPut = SimpleDecimalStr(Result.toNumberBinary());
		}
		else if (num_Param1 == 10){
			A.setBitFromDecNumberStr(param2);
			if (param3 == "+" || param3 == "-" || param3 == "*" || param3 == "/" || param3 == "&"
				|| param3 == "|" || param3 == "^"){
				B.setBitFromDecNumberStr(param4);
				if (param3 == "+"){
					Result = A + B;
				}
				else if (param3 == "-"){
					Result = A - B;
				}
				else if (param3 == "*"){
					Result = A * B;
				}
				else if (param3 == "/"){
					Result = A / B;
				}
				else if (param3 == "&"){
					Result = A & B;
				}
				else if (param3 == "|"){
					Result = A | B;
				}
				else if (param3 == "^"){
					Result = A ^ B;
				}	
			}
			else if (param3 == ">>" || param3 == "<<"){
				int k = stoi(param4);
				if (param3 == ">>"){
					Result = A >> k;
				}
				else if (param3 == "<<"){
					Result = A << k;
				}
			}
			outPut = SimpleDecimalStr(Result.toNumberDecimal());
		}
		else if (num_Param1 == 16){
			A.setBitFromHexaStr(param2);
			if (param3 == "+" || param3 == "-" || param3 == "*" || param3 == "/" || param3 == "&"
				|| param3 == "|" || param3 == "^"){
				B.setBitFromHexaStr(param4);
				if (param3 == "+"){
					Result = A + B;
				}
				else if (param3 == "-"){
					Result = A - B;
				}
				else if (param3 == "*"){
					Result = A * B;
				}
				else if (param3 == "/"){
					Result = A / B;
				}
				else if (param3 == "&"){
					Result = A & B;
				}
				else if (param3 == "|"){
					Result = A | B;
				}
				else if (param3 == "^"){
					Result = A ^ B;
				}	
			}
			else if (param3 == ">>" || param3 == "<<"){
				int k = stoi(param4);
				if (param3 == ">>"){
					Result = A >> k;
				}
				else if (param3 == "<<"){
					Result = A << k;
				}
			}
			outPut = SimpleDecimalStr(Result.toNumberHexa());
		}
	}
	return outPut;
}