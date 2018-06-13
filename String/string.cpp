#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

class String
{
public:
    String(const char*str = NULL); //普通构造函数
    String(const String &other); //拷贝构造函数
    ~String(void); //析构函数
    String &operator=(const String &other); //赋值函数, 重载=
    //const成员函数，可以访问非const成员变量，但是不能改变非const成员变量的值
    //const成员函数, 可以访问const成员变量, 但是普通成员函数不能访问const成员变量
    String operator+(const String &other) const; //重载+
    String &operator+=(const String &other); //重载+=
    bool operator==(const String &other) const; //重载==
    char & operator[] (int n) const;  //重载[]

    size_t size() const;    //获取长度
    const char * c_str() const; //获取C字符串

    friend istream& operator>>(istream &is, String &str); //输入
    friend ostream& operator<<(ostream &os, String &str); //输出 
private:
    char *m_String; //私有成员
};

//析构函数
String::~String(void)
{
    cout << "Destructing...." << endl;
    if(m_String != NULL) //m_String 不为空，释放空内存
    {
        delete[] m_String;
        m_String = NULL;
    }
}

//构造函数
String::String(const char *str)
{
    cout << "Constructing...." << endl;
    if(str == NULL) //如果str为NULL， 存空字符串
    {
        m_String = new char[1]; //分配一个字节
        *m_String = '\0';       //复制为'\0'
    } else {
        m_String = new char[strlen(str)+1]; //分配内存空间,容纳string内容
        strcpy(m_String, str); //拷贝str到私有成员m_String
    }
}

//拷贝构造函数
String::String(const String &other)
{
    cout << "Constructing Copy....." << endl;
    m_String = new char[strlen(other.m_String)+1];//分配空间容纳str内容
    strcpy(m_String, other.m_String); //拷贝str到私有成员
}

//复制函数，重载=
//this指针指向对象本身，*this 表示对象本身，可以使用 (*this).xxx 来使用对象的成员
String &String::operator=(const String& other)
{
    cout << "Operate = Function......." << endl;
    if(this == &other){ //如果对象与other是同一个对象
        return *this; //直接返回本身
    }
    delete[] m_String; //释放堆内存
    m_String = new  char[strlen(other.m_String)+1];
    strcpy(m_String, other.m_String);
    return *this;
}

//重载+
String String::operator+(const String& other) const
{
    String newString;
    int len = strlen(m_String) + strlen(other.m_String);
    newString.m_String = new char[len+1];
    strcpy(newString.m_String, m_String);
    strcat(newString.m_String, other.m_String);
    return newString;
}

//重载+=
String &String::operator+=(const String& other)
{
    int len = strlen(m_String) + strlen(other.m_String);
    char *newString = new char[len+1];
    strcpy(newString, m_String);
    strcat(newString, other.m_String);
    delete[] m_String;
    m_String = newString;
    return *this;
}

//重载==
bool String::operator==(const String& other) const
{
    if(strlen(m_String) != strlen(other.m_String)) return false;
    return strcmp(m_String, other.m_String)? false : true;
}

//重载[]
char &String::operator[](int n) const
{
    if(strlen(m_String) <= n) 
        return m_String[strlen(m_String)-1]; //错误处理
    else
        return m_String[n];
}

//获取C字符串
const char *String::c_str() const
{
    return m_String;
}

//输入流
istream& operator>>(istream &is, String &str)
{
    char temp[1000]; //简单的申请一块内存
    is >> temp;
    str.m_String = new char[strlen(temp)+1];
    strcpy(str.m_String, temp);
    return is;
}

//输出流
ostream& operator<<(ostream &os, String &str)
{
    os << str.m_String;
    return os;
}

int main()
{
    String a("hello");          //调用普通构造函数
    String b("world");          //调用普通构造函数
    String c(a);                //调用拷贝构造函数
    c = b;                      //调用赋值函数
    String a1 = "1234";
    String a2 = "abcd";
    String a3 = a1 + a2;
    printf("a3 = %s.\n", a3.c_str());

    String a4 = "fdgffds";
    a4 += a1;
    cout << "a4 =  " << a4 << endl; 
    return 0;
}
