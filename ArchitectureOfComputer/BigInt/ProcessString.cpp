#include "IO_STREAM.h"
#include "ProcessString.h"


string initStr(const int& size, const char& c){
	string temp = "";
	for (int i = 0; i < size; i++){
		temp += c;
	}
	return temp;
}


////TEST STRING
int compareDecimalString(const string& s1, const string& s2){
	if (s1[0] == '-' && s2[0] != '-')
		return -1;
	if (s1[0] != '-' && s2[0] == '-')
		return 1;
	unsigned int lengthS1 = s1.length();
	unsigned int lengthS2 = s2.length();
	if (s1[0] == '-'){
		if (lengthS1 > lengthS2)
			return -1;
		else if (lengthS1 < lengthS2)
			return 1;
		else if (lengthS1 == lengthS2){
			for (unsigned int i = 0; i < lengthS1; i++){
				if (s1[i] > s2[i])
					return -1;
				else if (s1[i] < s2[i])
					return 1;
			}
		}
	}
	if (s1[0] != '-'){
		if (lengthS1 > lengthS2)
			return 1;
		else if (lengthS1 < lengthS2)
			return -1;
		else if (lengthS1 == lengthS2){
			for (unsigned int i = 0; i < lengthS1; i++){
				if (s1[i] > s2[i])
					return 1;
				else if (s1[i] < s2[i])
					return -1;
			}
		}
	}
	
	return 0;
}

bool checkDecimalNumber(const string& numDec){
	unsigned int length = numDec.length();
	if ((numDec[0] <'0' || numDec[0] > '9') && numDec[0] != '-')
		return false;
	for (unsigned int i = 1; i<length; i++){
		if (numDec[i] <'0' || numDec[i] > '9')
			return false;
	}
	if (compareDecimalString(numDec, MIN_DECIMAL_QINT) > -1 && compareDecimalString(numDec, MAX_DECIMAL_QINT) < 1)
		return true;
	return false;
}

bool checkBinaryNumber(const string& numBin){
	unsigned int length = numBin.length();
	if (length > 128 || length == 0)
		return false;
	for (unsigned int i = 0; i < length; i++){
		if (numBin[i] != '1' && numBin[i] != '0')
			return false;
	}
	return true;
}

bool checkHexaNumber(const string& numHex){
	unsigned int length = numHex.length();
	if (length > 32 || length == 0)
		return false;
	for (unsigned int i = 0; i < length; i++){
		if ((numHex[i] < 65 || numHex[i] >70) && (numHex[i] < '0' || numHex[i]> '9'))
			return false;
	}
	return true;
}



int checkDicimalStr0(const string& numDec){
	if (numDec[0] == '-' || numDec[0] == '0'){
		int length = numDec.length();
		int i = 1;
		while (i < length){
			if (numDec[i] != '0' && numDec[i] != ' ')
				return i;
			i++;
		}
		if (i == length)
			return length - 1;
	}
	return -1;
}

string SimpleDecimalStr(const string& numDec){
	int pos = checkDicimalStr0(numDec);
	if (pos > 0){
		if (pos == numDec.length()) return "0";
		return numDec[0] == '-' ? '-' + numDec.substr(pos) : numDec.substr(pos);
	}
	return numDec;
}

string BinToDec(const string& numBin, const char& sign){
	vector<string> exponent_2;
	readExponent2(exponent_2, "Exponent_2.txt");
	string numDec = "0";
	int length = numBin.length();
	for (int i = 1; i < length; i++){
		if (numBin[i] == '1')
			numDec = addDecimalStr(numDec, exponent_2[length - i - 1]);
	}
	if (numBin[0] == '1'){
		if (sign == 's')
			numDec = subDecimalStr(numDec, exponent_2[length - 1]);
		else if (sign == 'u')
			numDec = addDecimalStr(numDec, exponent_2[length - 1]);
	}
	return SimpleDecimalStr(numDec);
}


char toCharacterHexaFromNumDec(const string& numDec){
	if (numDec == "0")
		return '0';
	else if (numDec == "1")
		return '1';
	else if (numDec == "2")
		return '2';
	else if (numDec == "3")
		return '3';
	else if (numDec == "4")
		return '4';
	else if (numDec == "5")
		return '5';
	else if (numDec == "6")
		return '6';
	else if (numDec == "7")
		return '7';
	else if (numDec == "8")
		return '8';
	else if (numDec == "9")
		return '9';
	else if (numDec == "10")
		return 'A';
	else if (numDec == "11")
		return 'B';
	else if (numDec == "12")
		return 'C';
	else if (numDec == "13")
		return 'D';
	else if (numDec == "14")
		return 'E';
	else if (numDec == "15")
		return 'F';
}

string BinToHex(const string& numBin){
	int lengthBit = numBin.length();
	int lengthHex = 0;
	lengthHex = (lengthBit % 4 == 0) ? lengthBit / 4 : lengthBit / 4 + 1;
	string numHex = initStr(lengthHex, '0');
	string temp;
	string numDec;
	for (int i = lengthHex -1 ; i >= 0; i--){
		numDec = BinToDec(numBin.substr(4 * i, 4),'u');
		numHex[i] = toCharacterHexaFromNumDec(numDec);
	}
	return numHex;
}

string toNumDecFromCharacterHexa(const char& c){
	if (c == '0')
		return "0";
	else if (c == '1')
		return "1";
	else if (c == '2')
		return "2";
	else if (c == '3')
		return "3";
	else if (c == '4')
		return "4";
	else if (c == '5')
		return "5";
	else if (c == '6')
		return "6";
	else if (c == '7')
		return "7";
	else if (c == '8')
		return "8";
	else if (c == '9')
		return "9";
	else if (c == 'A')
		return "10";
	else if (c == 'B')
		return "11";
	else if (c == 'C')
		return "12";
	else if (c == 'D')
		return "13";
	else if (c == 'E')
		return "14";
	else if (c == 'F')
		return "15";
}

string HexToBin(const string& numHex){
	int lengthHex = numHex.length();
	string numBin = "";
	string tempBin = initStr(4, '0');
	string numDec;
	for (int i = 0; i < lengthHex; i++){
		numDec = toNumDecFromCharacterHexa(numHex[i]);
		int j = 0;
		while (j < 4){
			tempBin[4 - j - 1] = (numDec[numDec.length() - 1] - 48) % 2 + 48;
			numDec = strDiv2(numDec);
			j++;
		}
		numBin += tempBin;
	}
	return numBin;
}



//// TINH TOAN

string strDiv2(string x){
	int length = x.length();
	char temp_r;
	int temp_k = 0;
	int i;
	string result = "";
	if (x[0] == '-')
		i = 1;
	else
		i = 0;
	for (i; i < length; i++){
		int k = temp_k * 10 + (x[i] - 48);
		if (k % 2 == 0){
			temp_k = 0;
		}
		else{
			temp_k = 1;
		}
		temp_r = k / 2 + 48;
		result += temp_r;
	}
	int pos = checkDicimalStr0(result);
	if (pos > 0)
		result = result.substr(pos);
	if (x[0] == '-')
		result = '-' + result;
	return SimpleDecimalStr(result);
}

string addDecimalStrPP(const string& numDec1, const string& numDec2){
	string result = "";
	unsigned int lengthNum1 = numDec1.length();
	unsigned int lengthNum2 = numDec2.length();
	if (lengthNum1 < lengthNum2)
		return addDecimalStrPP(numDec2, numDec1);
	unsigned int lengthResult = 0;
	unsigned int distance = 0;
	unsigned int iLoop = 0;
	distance = lengthNum1 - lengthNum2;
	lengthResult = lengthNum1;
	iLoop = lengthNum2;
	result = initStr(lengthResult,' ');
	char temp = 0;
	char res = 0;
	int i;
	for (i = 0; i < iLoop; i++){
		res = numDec1[iLoop - i - 1 + distance] - 48 + numDec2[iLoop - i - 1] - 48 + temp;
		if (res >= 10){
			res -= 10;
			temp = 1;
		}
		else{
			temp = 0;
		}
		result[iLoop - i - 1 + distance] = res + 48;
	}
	for (; i < lengthNum1; i++){
		res = numDec1[lengthNum1 - i - 1] - 48 + temp;
		if (res >= 10){
			res -= 10;
			temp = 1;
		}
		else{
			temp = 0;
		}
		result[lengthNum1 - i - 1] = res +48;
		
	}
	if (temp == 1)
		result = '1' + result;
	return result;
}

string addDecimalStrNN(const string& numDec1, const string& numDec2){
	string temp_numDec1 = numDec1.substr(1);
	string temp_numDec2 = numDec2.substr(1);
	return '-' + addDecimalStrPP(temp_numDec1, temp_numDec2);
}

string addDecimalStrPN(const string& numDec1, const string& numDec2){
	string result = "";
	string temp_numDec2 = numDec2.substr(1);
	unsigned int lengthNum1 = numDec1.length();
	unsigned int lengthNum2 = temp_numDec2.length();
	int ss = compareDecimalString(numDec1, temp_numDec2);
	if (ss  == 0){
		return "0";
	}
	else if (ss == 1){
		unsigned int lengthResult = 0;
		unsigned int distance = 0;
		unsigned int iLoop = 0;
		distance = lengthNum1 - lengthNum2;
		lengthResult = lengthNum1;
		iLoop = lengthNum2;
		result = initStr(lengthResult, ' ');
		char temp = 0;
		char res = 0;
		int i;
		for (i = 0; i < iLoop; i++){
			res = numDec1[iLoop - i - 1 + distance] - 48 - (temp_numDec2[iLoop - i - 1] - 48 + temp);
			if (res < 0){
				res += 10;
				temp = 1;
			}
			else{
				temp = 0;
			}
			result[iLoop - i - 1 + distance] = res + 48;
		}
		for (; i < lengthNum1; i++){
			res = numDec1[lengthNum1 - i - 1] - 48 - temp;
			if (res < 0){
				res += 10;
				temp = 1;
			}
			else{
				temp = 0;
			}
			result[lengthNum1 - i - 1] = res + 48;

		}
	}
	else{
		unsigned int lengthResult = 0;
		unsigned int distance = 0;
		unsigned int iLoop = 0;
		distance =  lengthNum2 - lengthNum1;
		lengthResult = lengthNum2;
		iLoop = lengthNum1;
		result = initStr(lengthResult, ' ');
		char res = 0;
		char sign = 0;
		int i;
		for (i = 0; i < iLoop; i++){
			res = numDec1[iLoop - i - 1] - 48 - (temp_numDec2[iLoop - i - 1 + distance] - 48) + sign;
			if (res > 0){
				res = 10 - res;
				sign = 1;
			}
			else{
				sign = 0;
				res = -res;
			}
			result[iLoop - i - 1 + distance] = res + 48;
		}
		for (; i < lengthNum2; i++){
			res = -(temp_numDec2[lengthNum2 - i - 1] - 48) + sign;
			if (res > 0){
				res = 10 - res;
				sign - 1;
			}
			else{
				sign = 0;
				res = -res;
			}
			result[lengthNum2 - i - 1] = res + 48;
		}
		result = '-' + result;
	}
	return  result;
		
}

string addDecimalStrNP(const string& numDec1, const string& numDec2){
	return addDecimalStrPN(numDec2, numDec1);
}

string addDecimalStr(const string& numDec1, const string& numDec2){
	if (numDec1[0] == '-' && numDec2[0] == '-')
		return SimpleDecimalStr(addDecimalStrNN(numDec1, numDec2));
	else if (numDec1[0] == '-')
		return SimpleDecimalStr(addDecimalStrNP(numDec1, numDec2));
	else if (numDec2[0] == '-')
		return SimpleDecimalStr(addDecimalStrPN(numDec1, numDec2));
	return SimpleDecimalStr(addDecimalStrPP(numDec1, numDec2));
}

string oppositeDecimalStr(const string& numDec){
	return numDec[0] == '-' ? numDec.substr(1) : '-' + numDec;
}

string subDecimalStr(const string& numDec1, const string& numDec2){
	return addDecimalStr(numDec1, oppositeDecimalStr(numDec2));
}


// Xu ly Chuoi File
unsigned int countCharacter(const string&src, const char& c){
	unsigned int count = 0;
	unsigned int length = src.length();
	for (unsigned int i = 0; i < length; i++){
		if (src[i] == c)
			count++;
	}
	return count;
}
void assignDataToString(string order, string& param1, string& param2, string& param3, string& param4, const char&c){
	unsigned int numC = countCharacter(order, c);
	int pos = 0;
	int temp_numC = numC;

	param1 = param2 = param3 = param4 = "";
	while (temp_numC >= 0){
		pos = order.find_first_of(c);
		if (temp_numC == numC)
			param1 = order.substr(0, pos);
		else if (temp_numC == numC - 1){
			param2 = order.substr(0, pos);
		}
		else if (temp_numC == numC - 2){
			param3 = order.substr(0, pos);
		}
		else if (temp_numC == numC - 3){
			param4 = order.substr(0, pos);
		}
		order = order.substr(pos + 1);
		temp_numC--;
	}
}