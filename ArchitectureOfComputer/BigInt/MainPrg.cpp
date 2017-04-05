#include "IO_STREAM.h"
#include "QInt.h"
#include "ProcessString.h"

int main(int argv, char* argc[]){
	if (argv == 3){
		vector<string> argcsTest;
		if (readTestFile(argcsTest, argc[1])){
			Process_WriteFileOutput(argcsTest, argc[2]);
		}
	}
	system("pause");
	return 0;
}