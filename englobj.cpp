//englobj.cpp
//Ingiliz olcumleri kullanan nesneler

#include <iostream>

using namespace std;

class Distance //Ingiliz Distance(uzaklik) sinifi
{
private:
    int feet;
    float inches;

public:
    void setdist(int ft, float in) //Distance'i argumanlara esitle
    {
        feet = ft;
        inches = in;
    }
    void getdist()
    {
        cout << "\nEnter feet: ";
        cin >> feet;
        cout << "Enter inches: ";
        cin >> inches;
    }
    void showdist() //uzakligi ekranda goster
    {
        cout << feet << "\'- " << inches << '\"';
    }
};

int main(int argc, char const *argv[])
{
    Distance dist1, dist2;    //iki uzaklik tanimla
    dist1.setdist(11, 6.25); //dist1'i ayarla
    dist2.getdist();          //dist2'yi kullanicidan al ve uzakligi ekranda goster
    cout << "\ndist1 = ";
    dist1.showdist();
    cout << "\ndist2 = ";
    dist2.showdist();
    cout << endl;
    return 0;
}