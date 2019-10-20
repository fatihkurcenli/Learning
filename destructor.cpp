//Destructor yapilarin ne oldugu ve neden kullanildigi ogrenildi..
//pointer adreslemesinde neden silme islemi uygulanildigi ogrenildi..
#include <iostream>

using namespace std;

class Employee
{
public:
    string *s;
    int *i;
    Employee(string str, int ivalue)
    {
        s = new string;
        i = new int;
        *s = str;
        *i = ivalue;
    }
    void show()
    {
        cout << "String deger : " << *s << endl
             << "Int deger : " << *i << endl;
    }
    ~Employee()
    {
        delete s, i;
        cout << "Desctructor cagrildi" << endl;
    }
};

int main(int argc, char const *argv[])
{
    Employee *emp = new Employee("Fatih kurcenli", 21);
    emp->show();
    delete emp;
    return 0;
}
