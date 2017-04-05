#include <string>
using namespace std;


bool getBitAt(int x, const char& index);                   // Lấy bit của biến x tại vị trí index
void turnOnBitAt(int&x, const char& index);				   // Bật bit của biến x tại vị trí index
void turnOffBitAt(int&x, const char& index);			   // Tắt bit của biến x tại vị trí index
void setBitAt(int&x, const bool& bit, const char& index);  // Set bit 'bit' của biến x tại vị trí index  
bool* getBit(const int&x);                                // Lấy dãy bit của biến x
string showBitStr(bool *x);

