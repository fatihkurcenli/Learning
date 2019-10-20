//Friend kavrami nedir ne icin kullanilir
//Friend ile fonksiyonlarin classlardaki ozel iceriklere ulasmayi ogrendik
//Friend ile class ile class icindeki private ozelliklere erismeyi ogrendik

#include <iostream>

using namespace std;

class Employee //employee diye bir class olusturalim
{
private: // ozel icerikler olusturalim
    string name;
    int age;
    int salary;

public:                                        //Bir constructor olusturalim
    Employee(string name, int age, int salary) //Constructor ad,yas,maas alsin
    {
        this->name = name; //this pointer ile bunlari ozel verilerin iclerine aktaralim
        this->age = age;
        this->salary = salary;
    }
    //friend void showInfo(Employee employee);// boyle bir fonksiyonum vardir ve
    //class yapisindaki verileri kullanabileyim izni verilir
    friend class Test; //class yapisini test classinin verilerimize erismesine izin verelim
};

class Test
{
public:
    static void showInfos(Employee employee) // ekrana basan bir statik fonksiyon olusturalim
    {                                        //ve degerleri ekrana bastiralim
        cout << employee.name << endl
             << employee.age << endl
             << employee.salary << endl;
    }
};

/*
void showInfo(Employee employee) // fonksiyon yazilir ve icine class yapisi atilir
{
    cout << employee.name << endl
         << employee.age << endl
         << employee.salary << endl;
}*/

int main(int argc, char const *argv[])
{
    // Employee employee("Fatih",21,123232);
    // showInfo(employee);
    Employee employee("Fatih", 21, 5000);
    Test::showInfos(employee);

    return 0;
}
