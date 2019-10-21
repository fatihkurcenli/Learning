#include <iostream>

using namespace std;

class part
{
private:
    int modelnumber; //model numarasi
    int partnumber;  //parca numarasi
    float cost;      //parcanin maliyeti
public:
    void setpart(int mn, int pn, float c)
    { //veriyi belirle
        modelnumber = mn;
        partnumber = pn;
        cost = c;
    }
    void showpart()//veriyi goster
    {
        cout<<"Model : " << modelnumber<<", part "<<partnumber<<", cousts $"<<cost<<endl;
    }
};

int main(int argc, char const *argv[])
{
    part part1; //part sinifini tanimla     nesneyi tanimla
    part1.setpart(6244,373,215.55F);////üye fonksiyonunu cagir
    part1.showpart(); //üye fonksiyonunu cagir
    return 0;
}
