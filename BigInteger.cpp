#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iomanip>
using namespace std;
class BigInterger
{
public:
    static const int BASE=100000000;
    static const int WIDTH=8;
    vector <int> data;
    BigInterger(long long int a=0);
    BigInterger& operator = (const long long int& a);
    BigInterger& operator = (const string &a);
    BigInterger operator + (const BigInterger& b);
    BigInterger operator - (const BigInterger& b);
    bool operator < (const BigInterger& b)const;
    bool operator > (const BigInterger& b)const;
    bool operator <= (const BigInterger& b)const;
    bool operator >= (const BigInterger& b)const;
    bool operator == (const BigInterger& b)const;
};
ostream& operator << (ostream& out,const BigInterger &b);
istream& operator >> (istream& in,BigInterger &b);
int main()
{
    BigInterger a,b;
    cin>>a>>b;
    cout<<a+b;
}
BigInterger::BigInterger(long long int a)
{
    *this=a;
}
BigInterger& BigInterger::operator =(const long long int& a)
{
    data.clear();
    long long int temp=a;
    while(temp)
    {
        data.push_back(temp%BASE);
        temp/=BASE;
    }
    return *this;
}
BigInterger& BigInterger::operator = (const string &a)
{
    data.clear();
    int time=(a.length()-1)/WIDTH+1;
    int temp;
    for(int m=0;m<time;m++)
    {
        int end=a.length()-m*WIDTH;
        int start=max(0,end - WIDTH);
        sscanf(a.substr(start,end - start).c_str(),"%d",&temp);
        data.push_back(temp);
    }
    return *this;
}
ostream& operator << (ostream& out,const BigInterger &b)
{
    //存储时按低位~高位存储，则输出时要由高至低
    out<<b.data[b.data.size()-1];
    for(int m=b.data.size()-2;m>=0;m--)
    {
        char buf[20];
        sprintf(buf,"%08d",b.data[m]);
        for(int n=0;n<strlen(buf);n++)
            out<<buf[n];
    }
    return out;
}
istream& operator >> (istream& in,BigInterger &b)
{
    string temp;
    if(!(in>>temp))
    {
        return in;
    }
    b=temp;
    return in;
}
BigInterger BigInterger:: operator + (const BigInterger& b)
{
    BigInterger sum;
    int temp,n;
    for(temp=0,n=0;;n++)
    {
        if(!temp&&n>=data.size()&&n>=b.data.size())
            break;
        if(n<data.size())
        temp+=data[n];
        if(n<b.data.size())
        temp+=b.data[n];
        sum.data.push_back(temp%BASE);
        temp/=BASE;
    }
    return sum;
}
BigInterger BigInterger:: operator - (const BigInterger& b)
{
    BigInterger sum;
    int sub=0,n=0,flag=0;
    while(1)
    {
        int temp;
        if(!sub&&n>=data.size()&&n>=b.data.size())
        {
            break;
        }
        if(n<data.size())
            sub+=data[n];
        if(n<b.data.size())
        {
            if(data[n]<b.data[n])
            {
                flag=1;
                sub+=BASE;
            }
            sub-=b.data[n];
        }
        sum.data.push_back(sub);
        n++;
        if(flag)
        {
            flag=0;
            sub=-1;
        }
        else
            sub=0;
    }
    return sum;
}
bool BigInterger::operator < (const BigInterger& b) const
{
    if(data.size()>b.data.size())
        return false;
    if(data.size()<b.data.size())
        return true;
    else
    {
        for(int n=data.size();n>=0;n--)
        {
            if(data[n]<b.data[n])
                return true;
            else if(data[n]>b.data[n])
                return false;
        }
        return false;
    }
}
bool BigInterger::operator > (const BigInterger& b) const
{
    return b<(*this);
}
bool BigInterger:: operator == (const BigInterger& b) const
{
    return !(*this<b||*this>b);
}
bool BigInterger:: operator >= (const BigInterger& b) const
{
    if(*this>b||*this==b)
        return true;
    else
        return false;
}
bool BigInterger:: operator <= (const BigInterger& b) const
{
    if(*this<b||*this==b)
        return true;
    else
        return false;
}
