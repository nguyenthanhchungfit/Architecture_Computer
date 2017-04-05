#include "QInt.h"
#include "ProcessString.h"
#include "IO_STREAM.h"
//
//
QInt::QInt()
{
	data[0] = data[1] = data[2] = data[3] = 0;
}

QInt::QInt(const QInt& src){
	for (int i = 0; i < 4; i++){
		data[i] = src.getDataAt(i);
	}
}

QInt::~QInt()
{
}



// GET, SET
int QInt::getDataAt(const int& index) const{
	if (index <0 || index > 3)
		return 0;
	return data[index];
}

bool QInt::getBitQIntAt(const int& index) const{
	unsigned int i_param = 4 - index / 32 - 1;
	unsigned int i_bitParam = index % 32;
	return getBitAt(data[i_param], i_bitParam);
}

bool* QInt::getBitQInt(){
	bool* param0 = getBit(data[0]);
	bool* param1 = getBit(data[1]);
	bool* param2 = getBit(data[2]);
	bool* param3 = getBit(data[3]);
	

	unsigned int sizeQ = sizeof(QInt)* 8;
	bool* bitQ = new bool[sizeQ];
	unsigned int k = 0;
	unsigned int i_Loop = 0;
	unsigned int size_param = sizeof(data[0]) * 8;
	for (; i_Loop < size_param; i_Loop++){
		bitQ[i_Loop] = param0[i_Loop];
		bitQ[32 + i_Loop] = param1[i_Loop];
		bitQ[32*2 + i_Loop] = param2[i_Loop];
		bitQ[32*3 + i_Loop] = param3[i_Loop];
	}
	delete[] param0;
	delete[] param1;
	delete[] param2;
	delete[] param3;
	return bitQ;
}

void QInt::setData(int dataInput[4]){
	for (int i = 0; i < 4; i++){
		data[i] = dataInput[i];
	}
}

void QInt::setBitQIntAt(const bool& bit, const int& index){
	unsigned int i_param = 4 - index / 32 - 1;
	unsigned int i_bitParam = index % 32;
	setBitAt(data[i_param], bit, i_bitParam);
}

void QInt::setBitFromBinaryStr(const string& numBin){
	if (checkBinaryNumber(numBin)){
		int length = numBin.length();
		for (int i = length - 1; i >= 0; i--){
			this->setBitQIntAt(numBin[i] - 48, length - i - 1);
		}
	}
}

void QInt::setBitFromHexaStr(const string& numHex){
	if (checkHexaNumber(numHex)){
		string numBin = HexToBin(numHex);
		this->setBitFromBinaryStr(numBin);
	}
}

void QInt::setBitFromDecNumberStr(const string& numDec){
	DevideAndSetBit(*this, numDec);
}


// OPERATOR
QInt QInt::operator = (const QInt& src){
	for (int i = 0; i < 4; i++){
		data[i] = src.data[i];
	}
	return *this;
}

QInt QInt::operator + (const QInt& src){
	QInt result;
	int sizeQ = sizeof(QInt)* 8;
	char temp = 0;
	for (unsigned int i = 0; i < sizeQ; i++){
		char a = this->getBitQIntAt(i);
		char b = src.getBitQIntAt(i);
		char bit = a + b + temp;
		if (bit >= 2){
			bit -= 2;
			temp = 1;
		}
		else{
			temp = 0;
		}
		result.setBitQIntAt(bit, i);
	}
	return result;

}

QInt QInt::operator - (const QInt& src){
	QInt result;
	QInt com_2_src = src.complement_2();
	result = com_2_src + *this;
	return result;
}

QInt QInt::operator * (const QInt& src){
	QInt A;
	QInt Q = src; // temp_src = Q; *this = M; //  MxQ
	unsigned int k = 128;
	bool q1 = 0;
	bool qo = 0;
	bool bitAo;
	while (k > 0){
		qo = Q.getBitQIntAt(0);
		if (qo == 1 && q1 == 0)
			A = A - (*this);
		else if (qo == 0 && q1 == 1)
			A = A + (*this);

		// SHIFT RIGHT A Q Q1
		bitAo = A.getBitQIntAt(0);
		q1 = qo;
		Q = Q >> 1;
		Q.setBitQIntAt(bitAo, 127);
		A = A >> 1;
		k--;
	}

	return Q;
}

QInt QInt::operator / (const QInt& src){
	// src: M
	QInt Q = *this;
	QInt A;                 //  A n bit 0
	string numDecQ = Q.toNumberDecimal();
	string numDecA = "";
	if (numDecQ < "0"){
		int data1[4] = { -1, -1, -1, -1 };
		A.setData(data1);
	}
	unsigned int k = 128;
	bool bitMSB_Q;
	while (k>0){
		bitMSB_Q = Q.getBitQIntAt(127);
		Q = Q << 1;
		A = A << 1;
		A.setBitQIntAt(bitMSB_Q, 0);
		A = A - src;
		numDecA = A.toNumberDecimal();
		if (numDecA < "0"){
			Q.setBitQIntAt(0, 0);
			A = A + src;
		}
		else
			Q.setBitQIntAt(1, 0);
		k--;
		
	}
	return Q;
}

QInt QInt::operator & (const QInt& src){
	QInt result;
	for (int i = 0; i <	 4; i++){
		result.data[i] = data[i] & src.data[i];
	}
	return result;
}

QInt QInt::operator | (const QInt& src){
	QInt result;
	for (int i = 0; i < 4; i++){
		result.data[i] = data[i] | src.data[i];
	}
	return result;
}

QInt QInt::operator ^ (const QInt& src){
	QInt result;
	for (int i = 0; i < 4; i++){
		result.data[i] = data[i] ^ src.data[i];
	}
	return result;
}

QInt QInt::operator ~ () const{
	QInt result;
	for (int i = 0; i < 4; i++){
		result.data[i] = ~data[i];
	}
	return result;
}

QInt QInt::operator >> (const int& iShift){
	QInt result = *this;
	for (unsigned int i = 0; i < iShift; i++){

		bool bitSign = getBitAt(result.data[0], 31);
		bool bitPre0 = getBitAt(result.data[0], 0);
		bool bitPre1 = getBitAt(result.data[1], 0);
		bool bitPre2 = getBitAt(result.data[2], 0);


		for (unsigned int j = 0; j < 4; j++){
			result.data[j] = result.data[j] >> 1;
		}


		setBitAt(result.data[0], bitSign, 31);
		setBitAt(result.data[1], bitPre0, 31);
		setBitAt(result.data[2], bitPre1, 31);
		setBitAt(result.data[3], bitPre2, 31);
	}
	return result;
}

QInt QInt::operator << (const int& iShift){
	QInt result = *this;
	for (unsigned int i = 0; i < iShift; i++){
		bool bitNext0 = getBitAt(result.data[3], 31);
		bool bitNext1 = getBitAt(result.data[2], 31);
		bool bitNext2 = getBitAt(result.data[1], 31);
		for (unsigned int j = 0; j < 4; j++){
			result.data[j] = result.data[j] << 1;
		}
		setBitAt(result.data[2], bitNext0, 0);
		setBitAt(result.data[1], bitNext1, 0);
		setBitAt(result.data[0], bitNext2, 0);
	}
	return result;
}

istream& operator >>(istream& inDev, QInt &src){
	string temp = "";
	getline(cin, temp);
	DevideAndSetBit(src, temp);
	return inDev;
}

ostream& operator << (ostream& outDev, const QInt& src){
	string q = src.toNumberDecimal();
	outDev << q;
	return outDev;
}

void DevideAndSetBit(QInt& src, const string&str){
	string strDiv = str;
	if (checkDecimalNumber(strDiv)){
		if (strDiv[0] == '-'){
			vector<string> exponent_2;
			readExponent2(exponent_2, "Exponent_2.txt");
			strDiv = addDecimalStr(strDiv, addDecimalStr(exponent_2[127], exponent_2[127]));
		}
		int size = sizeof(QInt)* 8;
		int i = 0;
		while (strDiv != "0"){
			bool bit = (strDiv[strDiv.length() - 1] - 48) % 2;
			src.setBitQIntAt(bit, i);
			strDiv = strDiv2(strDiv);
			i++;
		}
	}
}


// METHOD FUNCTIONS

QInt QInt::complement_2() const{
	QInt result;
	result = ~(*this);
	QInt num1;
	num1.setBitFromDecNumberStr("1");
	result = result + num1;
	return result;
}

QInt QInt::rol(){
	QInt result = *this;
	bool bitMSB = result.getBitQIntAt(127);
	result = result << 1;
	result.setBitQIntAt(bitMSB, 0);
	return result;
}

QInt QInt::ror(){
	QInt result = *this;
	bool bitLSB = result.getBitQIntAt(0);
	result = result >> 1;
	result.setBitQIntAt(bitLSB, 127);
	return result;
}

string QInt::toNumberDecimal() const{
	string result = "";
	string numBin = this->toNumberBinary();
	result = BinToDec(numBin, 's');
	return result;
}



string QInt::toNumberHexa() const{
	string result = "";
	string numBin = this->toNumberBinary();
	result = BinToHex(numBin);
	return result;
}

string QInt::toNumberBinary() const{
	string result = "";
	for (unsigned int i = 0; i < 128; i++){
		result = result + (char)(this->getBitQIntAt(127 - i) +48);
	}
	return result;
}