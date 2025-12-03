#define _CRT_SECURE_NO_WARNINGS // 1) 关闭 MSVC 关于“非安全”C 函数的告警，便于使用如 strcpy 等旧接口

#include <iostream>
#include <cstring> // 4) 本文件用到的 cstring 函数: strlen, strcpy, strcmp, strcat
using namespace std;

class String {
private:
    size_t length;
    char* str;

public:
    String();
    String(const char* s); // 2) 与第15行的拷贝构造不同：从 C 字符串构造（入参 const char*）
    String(const String& s); // 2) 拷贝构造：用同类对象构造（入参 const String&）
    ~String();
    size_t getLength() const;
    char operator[](size_t index) const;
    String& operator=(const String& s);
    bool operator==(const String& s) const;
    bool operator!=(const String& s) const;
    String copy() const;
    String operator+(const String& s) const;

    friend ostream& operator<<(ostream& out, const String& s); // 3) 友元：允许此函数访问私有成员（如 s.str）
};



String::String() {
    length = 0;
    str = new char[1];
    str[0] = '\0';
}

String::String(const char* s) {
    length = strlen(s); // 4) cstring: strlen
    str = new char[length + 1];
    strcpy(str, s); // 4) cstring: strcpy
}

String::String(const String& s) {
    length = s.length;
    str = new char[length + 1];
    strcpy(str, s.str); // 4) cstring: strcpy
}

String::~String() {
    delete[] str;
}

size_t String::getLength() const {
    return length;
}

char String::operator[](size_t index) const {
    return str[index];
}

String& String::operator=(const String& s) {
    if (this != &s) { // 5) this 是“当前对象”的指针；&s 是右值对象地址；防止自赋值
        delete[] str;
        length = s.length;
        str = new char[length + 1];
        strcpy(str, s.str);
    }
    return *this; // 6) *this 是“当前对象本身”；返回引用以支持 a=b=c 的链式赋值
}

bool String::operator==(const String& s) const {
    return strcmp(str, s.str) == 0; // 4) cstring: strcmp
}

bool String::operator!=(const String& s) const {
    return strcmp(str, s.str) != 0; // 4) cstring: strcmp
}

String String::copy() const {
    String s = *this;
    return s;
}

String String::operator+(const String& s) const {
    String result;
    result.length = length + s.length;
    result.str = new char[result.length + 1];
    strcpy(result.str, str); // 4) cstring: strcpy
    strcat(result.str, s.str); // 4) cstring: strcat
    return result;
}

ostream& operator<<(ostream& out, const String& s) { // 3) 输出运算符重载：返回 ostream& 以支持链式 <<
    out << s.str; // 3) 直接访问私有成员 str，因第25行声明其为友元
    return out; // 3) 返回输出流自身，允许 cout << a << b 连续输出
}

int main() {
    String s("12345d");
    cout << s << endl;
    cout << s + "445" << endl;
    cout << s[5] << endl;
    cout << (s == "12345d") << endl;
    cout << (s != "12345d") << endl;
    s = s + "asd";
    String a, b, c;
    a = b = c = s;
    cout << s << endl;
    cout << a << b << c << s << endl;
    String x = s.copy();
    cout << x << endl;


    return 0;
}