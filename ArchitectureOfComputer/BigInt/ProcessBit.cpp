#include "ProcessBit.h"

bool getBitAt(int x, const char& index){
	return ((x >> index) & 1);
}

void turnOnBitAt(int&x, const char& index){
	x = (x | (1 << index));
}

void turnOffBitAt(int&x, const char& index){
	x = (~(1 << index)) &x;
}

void setBitAt(int&x, const bool& bit, const char& index){
	if (bit == 1){
		turnOnBitAt(x, index);
	}
	else if (bit == 0){
		turnOffBitAt(x, index);
	}
}

bool* getBit(const int&x){
	int temp_x = x;
	int iLoop = sizeof(x)* 8;
	bool* res = new bool[iLoop];

	for (int i = 0; i < iLoop; i++){
		res[iLoop - i - 1] = getBitAt(x, i);
	}
	return res;
}

string showBitStr(bool* bit){
	string temp = "";
	int size = _msize(bit) / sizeof(bool);
	for (int i = 0; i < size; i++){
		temp += bit[i] + 48;
	}
	return temp;
}