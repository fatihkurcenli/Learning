//englcon.cpp
//kurucu fonksiyon ornegi,uye fonksiyon kullanarak nesneleri toplar
#include <iostream>

using namespace std;

class Distance //ingiliz uzunkluk olcüsü sinifi
{
private: //veriler
    int feet;
    float inches;

public:
    Distance() : feet(0), inches(0.0) //kurucu fonksiyon argumani yok
    {
    }
    Distance(int ft, float in) : feet(ft), inches(in) //kurucu fonksiyon iki argumani var
    {
    }
    void getdist() //uzunluklari kullanicidan al
    {
        cout << "\nEnter feet:";
        cin >> feet;
        cout << "\nEnter inches";
        cin >> inches;
    }
    void showdist() //uzunluklari ekranda goster
    {
        cout << feet << "\'-" << inches << '\"';
    }
    void add_dist(Distance, Distance); //deklarasyon
};
void Distance::add_dist(Distance d2, Distance d3) //d2 ve d3 uzunluklarini toplar
{
    inches = d2.inches + d3.inches; //inches'i topla
    feet = 0;                       //(muhtemel elde icin)
    if (inches >= 12.0)             //eger total 12.0'yi gecerse,
    {
        inches -= 12.0; //inches'i 12.0 azalt
        feet++;         //feet'i 1 arttir
    }
    feet += d2.feet + d3.feet; //feet'i topla
}
int main(int argc, char const *argv[])
{
    Distance dist1, dist3;    //iki uzaklik tanimla
    Distance dist2(11, 6.25); //dist2 tanimla ve ilk degerini ver

    dist1.getdist();              //kullanicidan dist1 uzakligini al
    dist3.add_dist(dist1, dist2); //dist3 = dist1 + dist2
    cout << "\ndist1 = ";
    dist1.showdist();
    cout << "\ndist2 = ";
    dist2.showdist();
    cout << "\ndist3 = ";
    dist3.showdist();
    cout << endl;

    return 0;
}
