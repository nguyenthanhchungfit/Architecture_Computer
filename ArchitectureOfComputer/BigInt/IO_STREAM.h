#include <string>
#include <vector>
#include <fstream>
using namespace std;


bool readExponent2(vector<string>& exponent_2, const string& path);
bool readTestFile(vector<string>& argcsTest, const string& path);
bool Process_WriteFileOutput(const vector<string>& argcsTest, const string& path);
string Calculate(const string& order);