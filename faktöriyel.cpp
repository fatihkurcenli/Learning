#include <iostream>
#include <cstring>
#include <string>
using namespace std;

struct de
{
    string name;
    string surname;
    int age;
    float note;
};


int main()
{
    struct de classroom;
    classroom.name="Fatih";
    classroom.surname="kurcenli";
    classroom.age="21";
    classroom.note="100";
    cout<<sınıf.ad<<endl;

    return 0;
}










/*
int topla(int sayi1,int sayi2)
{
    return sayi1+sayi2;
}

int main(){
    char karakter[]="Welcome the hell ktü";
    int say_moruq=strlen(karakter);
    cout<<say_moruq<<endl;
    cout<<topla(2,3)<<endl;
    return 0;
}

int main()
{
    int fac;
    int i,sonuc=1;
    cout<<"Faktörü alincak sayiyi giriniz:"<<endl;
    cin>>fac;
    for(i=1;i<=fac;i++){
        sonuc=sonuc * i;
        cout<<sonuc<<endl;
    }
    //cout<<sonuc<<endl;
    return 0;
}
*/
