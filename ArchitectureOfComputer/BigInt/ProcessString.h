#include <string>
using namespace std;


const string MAX_DECIMAL_QINT =  "170141183460469231731687303715884105727";
const string MIN_DECIMAL_QINT = "-170141183460469231731687303715884105728";


string initStr(const int& size, const char& c);                // Khởi tạo chuỗi string có char kí tự c
int compareDecimalString(const string& s1, const string& s2);  // So sánh hai chuỗi số nguyên hệ thập phân
bool checkDecimalNumber(const string& numDec);                 // Kiểm tra xem chuối số nguyên nhập vào có thỏa bài toán không
bool checkBinaryNumber(const string& numBin);                  // Kiểm tra chuỗi nhị phân nhập vào có thỏa bài toán không
bool checkHexaNumber(const string& numHex);                    // Kiểm tra chuỗi hexa nhập vào có thỏa bài toán không

//----------------------------------------------------------------------------------------------------------------------------

int checkDicimalStr0(const string& numDec);                    // Trả vị trí giản lược chuỗi thừa số 0, -
string SimpleDecimalStr(const string& numDec);                 // Trả về chuỗi đơn giản

//----------------------------------------------------------------------------------------------------------------------------

string BinToDec(const string& numBin, const char& sign = 's'); // Trả về chuỗi thập phân được chuyển từ chuỗi nhị phân, với sign là kiểu dấu nào (s: có dấu, u:không dấu).
char toCharacterHexaFromNumDec(const string& numDec);          // Trả về ký tự của số HEXA từ số nguyên hệ thâp phân tương ứng
string BinToHex(const string& numBin);                         // Trả về chuỗi số HEXA từ chuỗi số BINARY
string toNumDecFromCharacterHexa(const char& c);               // Trả về chuỗi số DECIMAL từ ký tự số HEXA tương ứng
string HexToBin(const string& numHex);                         // Trả về chuỗi số BINARY từ chuỗi số HEXA tương ứng

//----------------------------------------------------------------------------------------------------------------------------

string strDiv2(string x);									   // Trả về kết quả của chuỗi số DECIMAL 'x' / 2
string addDecimalStrPP(const string& numDec1, const string& numDec2);  // Phụ trợ addDecimalStr
string addDecimalStrNN(const string& numDec1, const string& numDec2);  // Phụ trợ addDecimalStr
string addDecimalStrPN(const string& numDec1, const string& numDec2);  // Phụ trợ addDecimalStr
string addDecimalStrNP(const string& numDec1, const string& numDec2);  // Phụ trợ addDecimalStr

string addDecimalStr(const string& numDec1, const string& numDec2);    // Trả về chuỗi số tổng của 2 chuỗi số numDec1 và numDec2
string oppositeDecimalStr(const string& numDec);                       // Trả về chuỗi số đối của chuỗi số DECIMAL
string subDecimalStr(const string& numDec1, const string& numDec2);    // Trả về chuỗi số là hiệu của 2 chuỗi số numDec1 và numDec2


// Xu ly Chuoi File
unsigned int countCharacter(const string&src, const char& c);
void assignDataToString(string order, string& param1, string& param2, string& param3, string& param4, const char&c);