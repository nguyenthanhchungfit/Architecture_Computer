#include <iostream>
#include "ProcessBit.h"



class QInt
{
private:
	int data[4];
public:
	// CONSTRUCTOR, DESTRUCTOR
	QInt();
	QInt(const QInt& src);
	~QInt();


	// GET, SET
	int getDataAt(const int& index) const;
	bool getBitQIntAt(const int& index) const;
	bool* getBitQInt();
	void setData(int dataInput[4]);
	void setBitQIntAt(const bool& bit, const int& index);
	void setBitFromDecNumberStr(const string& numDec);
	void setBitFromBinaryStr(const string& numBin);
	void setBitFromHexaStr(const string& numHex);

	//operator
	QInt operator = (const QInt& src);
	QInt operator + (const QInt& src);
	QInt operator - (const QInt& src);
	QInt operator * (const QInt& src);
	QInt operator / (const QInt& src);
	QInt operator & (const QInt& src);
	QInt operator | (const QInt& src);
	QInt operator ^ (const QInt& src);
	QInt operator ~ () const;
	QInt operator >> (const int& iShift);
	QInt operator << (const int& iShift);

	friend istream& operator >>(istream& inDev, QInt &src);
    friend ostream& operator << (ostream& inDev,const QInt& src);

	// method function
	friend void DevideAndSetBit(QInt& src, const string&str);
	QInt rol();
	QInt ror();
	QInt complement_2() const;
	string toNumberDecimal() const;
	string toNumberHexa() const;
	string toNumberBinary() const;
	void Nhap();
};

