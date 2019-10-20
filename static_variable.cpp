//Static variable bir kez olusturulup
//Kaybolmayan variable'lardir
//Ornek olarak acilan bir fonksiyon ve
//Olusturulan bir programi inceleyelim..

#include <iostream>

using namespace std;

void Test()
{
    static int i = 3;
    i++;
    cout << "Int i degeri : " << i << endl;
}

int main(int argc, char const *argv[])
{
    Test();
    Test();
    Test();
    return 0;
}
