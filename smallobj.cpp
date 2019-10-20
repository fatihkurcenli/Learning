//smallobj.cpp
//kucuk ve basit bir nesne ornegi
#include <iostream>

using namespace std;

class smallobj //bir sinif tanimlama
{
private:
    int somedata; //sinif verisi
public:
    void setdata(int d) //veriyi atanyan fonksiyon
    {
        somedata = d;
    }
    void showdata() //veriyi gosteren fonksiyon
    {
        cout << "Data is " << somedata << endl;
    }
};

int main(int argc, char const *argv[])
{
    smallobj s1, s2; //smallobj sinifindan iki nesne tanimla
    s1.setdata(1066);
    s2.setdata(1776);
    s1.showdata(); //veriyi gostermek icin uye fonksiyonu cagir
    s2.showdata();
    return 0;
}
