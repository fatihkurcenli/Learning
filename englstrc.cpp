// englstrc.cpp
//Ingiliz olculerini kullanarak yapilar
#include <iostream>

using namespace std;

struct Distance //ingiliz olculeri cinsinden uzaklik
{
    int feet;
    float inches;
};

int main(int argc, char const *argv[])
{
    Distance d1, d3;          //iki uzunlugu tanimla
    Distance d2 = {11, 6.25}; //bir uzunlugu tanimla ve degerini ata
    cout << "\nEnter feet:";
    cin >> d1.feet;
    cout << "\nEnter inches:";
    cin >> d1.inches;
    d3.inches = d1.inches + d2.inches; //d3'u elde etmek icin d1 ve d2 uzunluklarini topla
    d3.feet = 0;                       //muhtemel bir elde degeri icin
    if (d3.inches >= 12.0)
    {                      //toplam 12'yi gecerse
        d3.inches -= 12.0; //inches'i 12.0 azalt
        d3.feet++;         //ve feet'i 1 artir
    }
    d3.feet += d1.feet + d2.feet; //feetleri topla
                                  //tum uzunluklari ekranda goster
    cout << d1.feet << "\'-" << d1.inches << "\" +";
    cout << d2.feet << "\'-" << d2.inches << "\" =";
    cout << d3.feet << "\'-" << d3.inches << "\"\n";
    return 0;
}