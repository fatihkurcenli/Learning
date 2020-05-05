
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>

using namespace std;

template <class A>
class matrix //template matrix sinifi olusturuyoruz
{
public:
    matrix();                                        //matrix constructor
    ~matrix();                                       //matrix destructor
    void generateMatrix();                           //matrix olusturma
    matrix(int, int);                                //polymorpihsm uyguluyoruz
    matrix(int, int, int);                           //uc parametrili ise
    matrix(int, int, char);                          //uc parametrili ve char karakter giriliyor ise
    matrix<A> &operator+(const matrix<A> &m);        //toplama overloading
    matrix<A> &operator-(const matrix<A> &m);        //cikarma overloading
    matrix<A> &operator*(const matrix<A> &m);        //carpma overloading
    matrix<A> &operator+(int deger);                 //deger ile toplama
    matrix<A> &operator-(int deger);                 //deger ile cikarma
    matrix<A> &operator*(int deger);                 //deger ile carpma
    matrix<A> &operator/(int deger);                 //deger ile bolme
    matrix<A> &operator%(int deger);                 //deger ile mod alma
    void print();                                    //ekrana cikti verme
    void print(string yazdirma);                     //dosyaya yazdirma fonksiyonu
    void degismis(int alinan_rows, int alinan_cols); //matrix resize
    int pow(int alinan_rows, int alinan_cols);       //bir matrixin ussunu alir
    int trap();                                      //matrixin transpozunu alir
    void det();                                      //matrixin determinantini bulur
    matrix<A> &tersi();                              //matrixin tersini alir
    matrix<A> &emul(const matrix<A> &m);             //eleman düzeyinde carpma islemi
    //encapsulation verileri saklama uyguluyoruz
private:
    int rows;   //sutun
    int cols;   //satir
    int **temp; //data matrix datasini tutuyoruz matrixe temp dedim
};

template <>
matrix<int>::matrix() //constructor
{                     //eger deger verilmezse otamatik icini 10x10 matrix olusturma
                      //constructor
    rows = 10;
    cols = 10;
    generateMatrix(); //matrix olusturuyor bu fonksiyon
    //olusturulan matrix icine 0 yaziyoruz
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            temp[i][j] = 0;
        }
    }
}
template <>
matrix<int>::matrix(int rows, int cols)
{                                  //eger satir ve sutun bilgileri verilirse
    temp = new int *[rows];        //satir kadar alan acip temp degiskeni olusturuyoruz
    for (int i = 0; i < rows; ++i) //satir kadar donuyor
    {
        temp[i] = new int[cols]; //satir kadar sutun ekliyoruz
    }
}

template <class A>
matrix<A>::matrix(int satir, int sutun, int dolduracak_sayi)
{ //3'lü constructor icini doldurmak istenilen sayi eger girilirse
    //kullaniyouruz burda yine ayni islemler uygulaniyor sadece tek fark
    //icini kullanicinin girdigi degeri giriyoruz
    rows = satir;
    cols = sutun;
    temp = new int *[rows];
    for (int i = 0; i < rows; ++i)
    {
        temp[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            temp[i][j] = dolduracak_sayi; //doldurulacak sayiyi matrixe
        }                                 // atiyoruz
    }
}

template <class A>
matrix<A>::~matrix()
{ // actigimiz datayi geri verme islemi ediyoruz
    for (int i = 0; i < this->rows; ++i)
    {
        delete[] this->temp[i];
    } //geri vererek gecici olan nesneyi geri veririz
    delete[] this->temp;
}

template <class A>
matrix<A>::matrix(int satir, int sutun, char girdi)
{                           //eger random veya birim matrix istenirse bizden
    rows = sutun;           //sutunu  esitleriz
    cols = satir;           //satiri c
    temp = new int *[rows]; //matrix olusturulur
    for (int i = 0; i < rows; i++)
    {
        temp[i] = new int[cols];
    }                 //
    if (girdi == 'e') //eger girdi e ise birim matrix
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (i == j) //i ve j esit ise 1x1 2x2 gibi
                {
                    temp[i][j] = 1; //1 ediyoruz
                }
                else //degilse diger hepsini 0 yapiyoruz
                {
                    temp[i][j] = 0;
                }
            }
        }
    }
    else if (girdi == 'r') //eger girdi r ise random olusturuyoruz
    {                      //ayni degerler olmamasi icin time fonksiyonunu kullaniyoruz
        srand((unsigned)time(NULL));
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            { //random 0<=sayi<256 arasi sayi üretir
                temp[i][j] = (rand() % 256);
            }
        }
    }
    else
    { //eger ki kullanici yanlis kelime girmisse hata ciktisi verir
        cout << "girdiginiz kelime yanlistir lutfen tekrar deneyiniz.."
             << endl;
        cout << "Sifir matrix otamatik olusturuldu" << endl;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                temp[i][j] = 0; //sifir matrix yapiyoruz
            }
        }
    }
}

template <class A>
void matrix<A>::print()
{ //basit bir cikti ekrana bastirma islemi
    for (int i = 0; i < this->rows; ++i)
    {
        for (int j = 0; j < this->cols; ++j)
        {
            cout << this->temp[i][j] << "\t";
        }
        cout << endl;
    }
}

template <class A>
void matrix<A>::degismis(int alinan_rows, int alinan_cols)
{                    //matrixin degeri ve boyutu kullanicidan degistirme islemi
    char sonuc;      //sonuc degiskenini tutuyoruz
    int matrix_sayi; //icini doldurcagimiz matrix sayisi
    this->rows = alinan_rows;
    this->cols = alinan_cols;
    // alinan rowsu dongümüz icin ne kadar yer accagimizi tutuyoruz
    // eger girilen degerler rows ve cols negatif ise
    if (alinan_rows < 0 || alinan_cols < 0)
    { // bu degerlerin girilemeyecegini bastiriyoruz
        cout << "bu degerler resize edilemez" << endl;
        return; //ve return yapip fonksiyonu sonlandiriyoruz
    }
    //matrix degerini kullanici doldurmak isterse y degilse n basiyor
    while (sonuc != 'y' || sonuc != 'n')
    { //eger kullanici y veya n basmadiysa dongüye sokuyoruz
        cout << "Deger girmek istiyor musunuz y/n" << endl;
        cin >> sonuc;     //degiskeni atiyoruz
        if (sonuc == 'y') //eger y ise degeri girmesi lazim
        {
            for (int i = 0; i < this->rows; i++)
            {
                delete[] temp[i]; //matrixi siliyoruz
            }                     //yeni matrix icin kullanicidan matrix sayisini aliyoruz
            cout << "lutfen matrix icini doldurmak"
                 << "istediginiz degeri giriniz:"
                 << endl;
            cin >> matrix_sayi;           //matrix_sayi degiskenine atiyoruz
            temp = new int *[this->rows]; //yeni matrix olusturuyoruz
            for (int i = 0; i < this->rows; ++i)
            {
                temp[i] = new int[this->cols];
            } //yeni matrix icini olusturdugumuz degeri atyoruz
            for (int i = 0; i < this->rows; i++)
            {
                for (int j = 0; j < this->cols; j++)
                { //matrix sayisini yaziyoruz
                    temp[i][j] = matrix_sayi;
                }
            }
            return;
        }
        else if (sonuc == 'n')
        { //eger kullanici n basmissa 0 matrixi otamatik olusturuyourz
            for (int i = 0; i < this->rows; i++)
            { //ayni islemler var matrix siliyoruz
                delete[] temp[i];
            } //tek fark kullanicidan deger almadan otamatik 0 atiyoruz
            cout << "matrix 0 matrixi olusturuluyor" << endl;
            temp = new int *[this->rows];
            for (int i = 0; i < this->rows; ++i)
            {
                temp[i] = new int[this->cols];
            }
            for (int i = 0; i < this->rows; ++i)
            {
                for (int j = 0; j < this->cols; ++j)
                { //degerleri sifira esitliyoruz
                    temp[i][j] = 0;
                }
            }
            return;
        }
        else
        { //eger kullanici yanlis karakter girdiyse hata ciktisi veriyoruz
            cout << "Hatali rakam girdiniz!!"
                 << " Lutfen y-n tuslarini kullaniniz.." << endl;
            cout << endl;
            cout << "Onceki matrix"
                 << "degerleri ve boyutu degismemistir.." << endl;
        }
    }
}

template <class A>
void matrix<A>::generateMatrix()
{                           //matrix olusturmada kullaniyoruz
    temp = new int *[rows]; //satir acip
    for (int i = 0; i < rows; ++i)
    { //satir kadar sutun ekliyoruz
        temp[i] = new int[cols];
    }
}

template <class A>
matrix<A> &matrix<A>::operator+(const matrix<A> &m)
{ //toplama overloading
    int deger;
    //matrix<int> sonuc_matrix(rows, cols, 0);
    //matrix<int> *tutulan_deger=&sonuc_matrix;
    matrix<int> *sonuc_matrix = new matrix<int>(rows, cols, deger);
    for (int i = 0; i < this->rows; ++i)
    {
        for (int j = 0; j < this->cols; ++j)
        { //kendi tutulan matrix ile gelen &m adresli matrix toplama
            sonuc_matrix->temp[i][j] = this->temp[i][j] + m.temp[i][j];
            //cout << sonuc_matrix.temp[i][j] << "\t";
        }
        //cout << endl;
    }
    //return *tutulan_deger;
    return *sonuc_matrix;
}
template <class A>
matrix<A> &matrix<A>::operator-(const matrix<A> &m)
{ //cikaram operator overloading
    int deger;
    //matrix sonuc_matrix(rows, cols, 0);
    //matrix *tutulan_deger=&sonuc_matrix;
    matrix<int> *sonuc_matrix = new matrix<int>(rows, cols, deger);
    for (int i = 0; i < this->rows; ++i)
    {
        for (int j = 0; j < this->cols; ++j)
        { //cikarma operator overloading
            sonuc_matrix->temp[i][j] = this->temp[i][j] - m.temp[i][j];
            //cout << sonuc_matrix.temp[i][j] << "\t";
        }
        //cout << endl;
    }
    //return *tutulan_deger;
    return *sonuc_matrix;
}
template <class A>
matrix<A> &matrix<A>::operator*(const matrix<A> &m)
{
    int deger;
    int toplam_deger = 0; //toplam degiskeni aciyoruz
    //matrix sonuc_matrix(rows, cols, 0);
    //matrix *tutulan_deger=&sonuc_matrix;
    matrix<int> *sonuc_matrix = new matrix<int>(rows, cols, deger);
    for (int i = 0; i < this->rows; ++i)
    {
        for (int j = 0; j < this->cols; ++j)
        {
            for (int k = 0; k < this->rows; k++)
            { //ucuncu for degerleri carpmak ve toplamak icin
                toplam_deger += this->temp[i][k] * m.temp[k][j];
                sonuc_matrix->temp[i][j] = toplam_deger;
                //cout<<sonuc_matrix->temp[i][j]<<endl;
            } //ve toplam degeri matrixe atip sifirliyoruz
            toplam_deger = 0;
        }
    }
    //return *tutulan_deger;
    return *sonuc_matrix;
}

template <class A>
matrix<A> &matrix<A>::operator+(int deger)
{ //belli bir deger ile toplama
    //matrix sonuc_matrix(rows, cols, 0);
    //matrix *tutulan_deger = &sonuc_matrix;
    matrix<int> *sonuc_matrix = new matrix<int>(rows, cols, 0);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            sonuc_matrix->temp[i][j] = temp[i][j] + deger;
            //cout<<sonuc_matrix->temp[i][j]<<"\t";
        }
        //cout<<endl;
    }
    //return *tutulan_deger;
    return *sonuc_matrix;
}

template <class A>
matrix<A> &matrix<A>::operator-(int deger)
{
    //matrix sonuc_matrix(rows, cols, 0);
    //matrix *tutulan_deger = &sonuc_matrix;
    matrix<int> *sonuc_matrix = new matrix<int>(rows, cols, 0);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            sonuc_matrix->temp[i][j] = temp[i][j] - deger;
            //cout<<sonuc_matrix->temp[i][j]<<"\t";
        }
        //cout<<endl;
    }
    //return *tutulan_deger;
    return *sonuc_matrix;
}

template <class A>
matrix<A> &matrix<A>::operator*(int deger)
{
    //matrix sonuc_matrix(rows, cols, 0);
    //matrix *tutulan_deger = &sonuc_matrix;
    matrix<int> *sonuc_matrix = new matrix<int>(rows, cols, 0);
    for (int i = 0; i < this->rows; ++i)
    {
        for (int j = 0; j < this->cols; ++j)
        {
            for (int k = 0; k < rows; k++)
            {
                sonuc_matrix->temp[i][j] = this->temp[i][k] * deger;
            }
            //cout << sonuc_matrix->temp[i][j] << "\t";
        }
        //cout << endl;
    }
    //return *tutulan_deger;
    return *sonuc_matrix;
}

template <class A>
matrix<A> &matrix<A>::operator/(int deger)
{
    //matrix sonuc_matrix(rows, cols, 0);
    //matrix *tutulan_deger = &sonuc_matrix;
    matrix<int> *sonuc_matrix = new matrix<int>(rows, cols, 0);
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            for (int k = 0; k < rows; k++)
            { //ucucu for islemleri yapmak icin
                sonuc_matrix->temp[i][j] = this->temp[i][k] / deger;
            }
            //cout << sonuc_matrix->temp[i][j] << "\t";
        }
        //cout << endl;
    }
    //return *tutulan_deger;
    return *sonuc_matrix;
}

template <class A>
matrix<A> &matrix<A>::operator%(int deger)
{
    //matrix sonuc_matrix(rows, cols, 0);
    //matrix *tutulan_deger = &sonuc_matrix;
    matrix<int> *sonuc_matrix = new matrix<int>(rows, cols, 0);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            sonuc_matrix->temp[i][j] = temp[i][j] % deger;
            //cout << sonuc_matrix->temp[i][j] << "\t";
        }
        //cout << endl;
    }
    //return *tutulan_deger;
    return *sonuc_matrix;
}

template <class A>
int matrix<A>::pow(int alinan_rows, int alinan_cols)
{ // alinan rowsu dongümüz icin ne kadar yer accagimizi tutuyoruz
    this->rows = alinan_rows;
    int toplam_deger = 0; //carpma islemi icin
    int matrix_sayi;      //matrix ici doldurulacak sayi
    int us;               //kac kez us alincagi
    cout << "Matrix ici doldurulacak sayiyi giriniz..:" << endl;
    cin >> matrix_sayi;
    //matrix sonuc_matrix(rows, cols, 0);
    //matrix *tutulan_deger = &sonuc_matrix;
    for (int i = 0; i < alinan_rows; ++i)
    {
        temp[i] = new int[alinan_cols];
    }
    for (int i = 0; i < alinan_rows; ++i)
    {
        for (int j = 0; j < alinan_cols; ++j)
        {
            temp[i][j] = matrix_sayi;
        }
    } //matri olusturulup degerler atandi
    cout << "matrix olusturuluyor.. Lutfen bekleyiniz.." << endl;
    for (int i = 0; i < alinan_rows; ++i)
    { //matrix degerlerini ekrana basma
        for (int j = 0; j < alinan_cols; ++j)
        {
            cout << temp[i][j] << "\t";
        }
        cout << endl;
    } //kacinci ussu alincak bilgisini alma
    cout << "alinacak ussu giriniz 2,3,4" << endl;
    cin >> us;
    cout << "Us alma islemi gerceklesiyor..lutfen bekleyiniz..."
         << endl;
    cout << endl;
    matrix<int> *sonuc_matrix = new matrix<int>(rows, cols, 0);
    matrix<int> *ikinci_toplam_matrix = new matrix<int>(rows, cols, 0);
    matrix<int> *ucuncu_toplam_matrix = new matrix<int>(rows, cols, 0);
    if (us == 2)
    { //eger us 2 ise 2 matrix carpimi gibidir
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                for (int k = 0; k < this->rows; k++)
                {
                    toplam_deger += temp[i][k] * temp[k][j];
                    sonuc_matrix->temp[i][j] = toplam_deger;
                }
                toplam_deger = 0;
                cout << sonuc_matrix->temp[i][j] << "\t";
            }
            cout << endl;
        }
        //return *sonuc_matrix;
    }
    if (us == 3)
    { //ucte ise yine carpma fakat bu sefer
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                for (int k = 0; k < this->rows; k++)
                {
                    toplam_deger += temp[i][k] * temp[k][j];
                    sonuc_matrix->temp[i][j] = toplam_deger;
                }
                toplam_deger = 0;
            }
        }
        //ikinci toplama ihtiyacimiz var ayni matrixi ile carp
        int ikinci_toplam = 0;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                for (int k = 0; k < this->rows; k++)
                {

                    ikinci_toplam += sonuc_matrix->temp[i][k] * temp[k][j];
                    ikinci_toplam_matrix->temp[i][j] = ikinci_toplam;
                }
                ikinci_toplam = 0;
                cout << ikinci_toplam_matrix->temp[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
    if (us == 4)
    { //4 te ise yine ayni islemler bu seferde 3 toplam degiskeni lazim
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                for (int k = 0; k < this->rows; k++)
                {
                    toplam_deger += temp[i][k] * temp[k][j];
                    sonuc_matrix->temp[i][j] = toplam_deger;
                }
                toplam_deger = 0;
            }
        }
        // boylelikle kac us gerekiyorsa 1 dusugu degiskenle
        int ikinci_toplam = 0;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                for (int k = 0; k < this->rows; k++)
                {

                    ikinci_toplam += sonuc_matrix->temp[i][k] * temp[k][j];
                    ikinci_toplam_matrix->temp[i][j] = ikinci_toplam;
                }
                ikinci_toplam = 0;
            };
        }
        cout << endl;
        int ucuncu_toplam = 0;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                for (int k = 0; k < this->rows; k++)
                {

                    ucuncu_toplam += ikinci_toplam_matrix->temp[i][k] * temp[k][j];
                    ucuncu_toplam_matrix->temp[i][j] = ucuncu_toplam;
                }
                ucuncu_toplam = 0;
                cout << ucuncu_toplam_matrix->temp[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
}

template <class A>
int matrix<A>::trap()
{ //tutulan degisken diye yeni bir matrix aciyoruz
    matrix<int> *tutulan_degisken = new matrix<int>(cols, rows);

    for (int i = 0; i < this->rows; i++)
    { //matrixi bastiriyoruz
        for (int j = 0; j < this->cols; j++)
        {
            cout << temp[i][j] << "\t";
        }
        cout << endl;
    }
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        { //matrixin ixj iken jxi yapiyoruz tutulan degisken sayesinde
            tutulan_degisken->temp[j][i] = this->temp[i][j];
        }
    }
    cout << endl;
    for (int i = 0; i < this->cols; i++)
    {
        for (int j = 0; j < this->rows; j++)
        { //ve tutulan degiskeni bastiriyoruz
            cout << tutulan_degisken->temp[i][j] << "\t";
        }
        cout << endl;
    }
}

template <class A>
void matrix<A>::det()
{

    matrix<int> *determinant = new matrix<int>(rows, cols);
    matrix<int> *sub_determinant = new matrix<int>(rows, cols);
    //matrix boyutlarina gore determinat degismekte
    if (this->rows == 1)
    {
        float det = 0;
        cout << "matrix degerlerini giriniz lutfen" << endl;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                cout << "Matrixin"
                     << "[" << i + 1 << "]"
                                        "["
                     << j + 1 << "] elemanini giriniz:";
                cin >> determinant->temp[i][j];
            }
        }
        cout << "matrixiniz olusturuluyor lutfen bekleyiniz.. "
             << endl;
        cout << endl;
        cout << "matrix degerleriniz bastiriliyor" << endl;
        cout << endl;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                cout << determinant->temp[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
        cout << "Matrix determinanti hesaplaniyor lutfen bekleyiniz..."
             << endl;
        cout << endl;
        det = determinant->temp[0][0]; //determinant kendisidir
        cout << "matrix determinanti = " << det << endl;
    }
    if (this->rows == 2)
    {
        float det = 0;
        cout << "matrix degerlerini giriniz lutfen" << endl;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                cout << "Matrixin"
                     << "[" << i + 1 << "]"
                                        "["
                     << j + 1 << "] elemanini giriniz:";
                cin >> determinant->temp[i][j];
            }
        }
        cout << "matrixiniz olusturuluyor lutfen bekleyiniz.. " << endl;
        cout << endl;
        cout << "matrix degerleriniz bastiriliyor" << endl;
        cout << endl;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                cout << determinant->temp[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
        cout << "Matrix determinanti hesaplaniyor lutfen bekleyiniz..." << endl;
        cout << endl;
        cout << "matrix determinanti = ";
        cout << ((determinant->temp[0][0] * determinant->temp[1][1]) -
                 (determinant->temp[1][0] * determinant->temp[0][1]));
        //klasik ikili determinant hesaplama
    }
    if (this->rows == 3)
    { //uclu determinant degerleri girerek olusturma
        float det = 0;
        cout << "matrix degerlerini giriniz lutfen" << endl;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                cout << "Matrixin"
                     << "[" << i + 1 << "]"
                                        "["
                     << j + 1 << "] elemanini giriniz:";
                cin >> determinant->temp[i][j];
            }
        }
        cout << endl;
        cout << endl;
        cout << "Matrixiniz olusturuldu : " << endl;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                cout << determinant->temp[i][j] << "\t";
            }
            cout << endl;
        }
        for (int i = 0; i < this->rows; i++)
        { //determinant hesaplama
            det = det + (determinant->temp[0][i] *
                         (determinant->temp[1][(i + 1) % 3] *
                              determinant->temp[2][(i + 2) % 3] -
                          determinant->temp[1][(i + 2) % 3] *
                              determinant->temp[2][(i + 1) % 3]));
        }
        cout << "Determinant hesaplaniyor lutfen bekleyiniz.." << endl;
        cout << endl;
        cout << "Matrix determinant = " << det;
    }
}
template <class A>
void matrix<A>::print(string yazdirma) // dosyaya yazdirma islemi
{                                      //eger dosya adi dogru girilmis mi kontrol ediliyor
    if (yazdirma == "file.txt")
    { //dogru ise dosya aciyor yok ise
        ofstream dosya_islemi("file.txt");
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            { //ve matrixi dosyayi bastiriyor
                dosya_islemi << this->temp[i][j] << "\t";
            }
            dosya_islemi << endl;
        }
        cout << "Dosyaniz basariyla olusturulmustur.." << endl;
        dosya_islemi.close(); //dosya islemi bittiginden kapatiyoruz
    }
    else
    { //eger yanlis girilmisse hata ciktisi bastiriyoruz
        cout << endl
             << endl;
        cout << "Hatali dosya adi girdiniz."
             << " Lutfen dosya adini file.txt olarak guncelleyiniz !" << endl;
        cout << endl
             << endl;
    }
}
template <class A>
matrix<A> &matrix<A>::tersi()
{ //tersi icin determinanta ihtiyacımız var
    matrix<int> *determinant = new matrix<int>(rows, cols);
    matrix<int> *tersi = new matrix<int>(rows, cols);
    if (this->rows == 1)
    { //eger satir sayisi 1 ise kendisinin determinanta bölümüdür
        float det = 0;
        cout << "matrix degerlerini giriniz lutfen" << endl;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                cin >> determinant->temp[i][j];
            }
        }
        cout << "matrixiniz olusturuluyor lutfen bekleyiniz.. " << endl;
        cout << endl;
        cout << "matrix degerleriniz bastiriliyor" << endl;
        cout << endl;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                cout << determinant->temp[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
        cout << "Matrix determinanti hesaplaniyor lutfen bekleyiniz..." << endl;
        cout << endl;
        det = determinant->temp[0][0];
        cout << "matrix determinanti = " << det << endl;
        cout << "Matrix tersi hesaplaniyor lutfen bekleyiniz.. " << endl;
        cout << "Matrix tersi :" << endl;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            { //matrix ile (1/det) ile carpıyoruz
                cout << determinant->temp[i][j] * (1 / det);
            }
        }
    }

    if (this->rows == 2)
    { //eger 2 ise 1x1 ile 4x4 degistiriyor 2x2 ve 3x3 negatif alip
        //(1/det) ile carpiyoruz
        float det;
        matrix<int> *sonuc_matrix = new matrix<int>(rows, cols);
        cout << "matrix degerlerini giriniz lutfen" << endl;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                cout << "Matrixin"
                     << "[" << i + 1 << "]"
                                        "["
                     << j + 1 << "] elemanini giriniz:";
                cin >> determinant->temp[i][j];
            }
        }
        cout << "matrixiniz olusturuluyor lutfen bekleyiniz.. " << endl;
        cout << endl;
        cout << "matrix degerleriniz bastiriliyor" << endl;
        cout << endl;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                cout << determinant->temp[i][j] << "\t";
            }
            cout << endl;
        }
        //yer degistirme islemi uyguluyoruz
        tersi->temp[0][0] = determinant->temp[1][1];
        tersi->temp[1][1] = determinant->temp[0][0];
        tersi->temp[0][1] = determinant->temp[0][1] * (-1);
        tersi->temp[1][0] = determinant->temp[1][0] * (-1);
        det = (determinant->temp[0][0] * determinant->temp[1][1]) -
              (determinant->temp[1][0] * determinant->temp[0][1]);
        //determinant hesapladik
        cout << endl;
        cout << "Matrixin tersi olusturuluyor lutfen bekleyiniz.."
             << endl;
        cout << "Matrixin tersi :" << endl;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            { //carpma islemi uyguluyoruz determinant ile
                tersi->temp[i][j] = tersi->temp[i][j] * (1 / det);
            }
        }
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            { //carpma islemi uyguluyoruz determinant ile
                sonuc_matrix->temp[i][j] = tersi->temp[i][j];
            }
        }
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            { //cıktıyı veriyoruz
                cout << tersi->temp[i][j] << "\t";
            }
            cout << endl;
        }
        return *sonuc_matrix;
    }
    if (this->rows == 3)
    {
        float det = 0;
        cout << "matrix degerlerini giriniz lutfen" << endl;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                cout << "Matrixin"
                     << "[" << i + 1 << "]"
                                        "["
                     << j + 1 << "] elemanini giriniz:";
                cin >> determinant->temp[i][j];
            }
        }
        cout << endl;
        cout << endl;
        cout << "Matrixiniz olusturuldu : " << endl;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                cout << determinant->temp[i][j] << "\t";
            }
            cout << endl;
        }
        for (int i = 0; i < this->rows; i++)
        { //determinant hesaplama
            det = det + (determinant->temp[0][i] *
                         (determinant->temp[1][(i + 1) % 3] *
                              determinant->temp[2][(i + 2) % 3] -
                          determinant->temp[1][(i + 2) % 3] *
                              determinant->temp[2][(i + 1) % 3]));
        }
        cout << "Determinant hesaplaniyor lutfen bekleyiniz.." << endl;
        cout << endl;
        cout << "Matrix determinant = " << det << endl;

        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            { //kofaktör hesabı ile tersini bulma
                cout << ((determinant->temp[(j + 1) % 3][(i + 1) % 3] *
                          determinant->temp[(j + 2) % 3][(i + 2) % 3]) -
                         (determinant->temp[(j + 1) % 3][(i + 2) % 3] *
                          determinant->temp[(j + 2) % 3][(i + 1) % 3])) /
                            (det)
                     << "\t";
            }
            cout << "\n";
        }
    }
}
template <class A>
matrix<A> &matrix<A>::emul(const matrix<A> &m)
{ //eleman düzeyinde caprma
    int deger;
    //matrix<int> sonuc(rows,cols,deger); 
    //matrix<int> *tutulan_deger=&sonuc; 
    matrix<int> *sonuc_matrix = new matrix<int>(rows, cols, deger);
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < m.cols; j++)
        {
            for (int k = 0; k < this->rows; k++)
            {
                sonuc_matrix->temp[i][j] =
                    ((this->temp[i][k]) * (m.temp[k][j]));
                //sonuc.temp[i][j] = ((this->temp[i][k]) * (m.temp[k][j]));
            }
            cout << sonuc_matrix->temp[i][j] << "\t";
            //cout << sonuc.temp[i][j] << "\t";
        }
        cout << endl;
    }
    //return *tutulan_deger;
    return *sonuc_matrix;
}

int main()
{
    //otamatik doldurma pointer ile 10lik matrix
    //matrix<int> *m1 = new matrix<int>();
    //otamatik doldurma constructor ile 10x10'lik matrix olusturur nesne ile
    //matrix<int> m1;
    //m1.print();
    //matrix<int> *m2 = new matrix<int>(3, 2, 1);
    //matrix<int> m2();
    //m2->print(); //matrix bastirilir
    //matrix<int> *m3 = new matrix<int>(3, 3, 30);
    //matrix<int> *m4 = new matrix<int>(3, 3, 5);
    //matrix<int> *m5 = new matrix<int>(3, 3, 0);
    //matrix<int> *sonuc = new matrix<int>(3, 3, 0);
    //matrix<int> m2(3, 3, 5);
    //matrix<int> m3(3, 3, 5);
    //matrix<int> m5(3, 3, 0);
    //(*m5) = (*m3) * (*m4);
    //m5 = m2 * m3;
    //m5->print();
    //(*m3) = (*m3) % 10;
    //m2 = m2 + 12;
    //m2.print();
    //m3->print();
    //m5=m3+m2;
    //birim matrix ve random matrix atiyor
    //matrix<int> *m6 = new matrix<int>(4, 4, 'k');
    //m6->print();
    //matrix<int> *m7 = new matrix<int>(3,3,23);//matrix degistirmek
    //m7->degismis(3, 3);//matrix degistirme fonksiyonu
    //m7->print();//matrix fonksiyonunu bastirmas
    //matrix<int> *m2 = new matrix<int>(3, 3, 2);
    //m2->pow(3, 3);
    //matrix<int> *m3 = new matrix<int>(3, 2, 1);
    //m3->trap();
    //matrix<int> *m3 = new matrix<int>(3, 3, 0);
    //m3->det(); //matrix determinant  ve tersi icin ise yariyor
    //m3->tersi(); //matrix tersini aliyor 2x2 ve 3x3 alabiliyor
    //matrix<int> *m3 = new matrix<int>(3,3,5);//dosya islemi
    //m3->print("file.txt"); //dosya islemi gerceklestiriyor
    //matrix<int> m2(3, 3, 5); //nesne ile emul fonksiyonu kullanimi
    //matrix<int> m3(3, 3, 3); //nesne ile emul fonksiyonu kullanimi
    //matrix<int> *m2=new matrix<int>(3,3,5);//pointer emul fonksiyonu
    //matrix<int> *m3 =new matrix<int>(3,3,3);//pointer emul fonksiyonu
    //m3.emul(m2); //nesne icin
    //m3->emul(*m2); //pointer icin
    int sec = 1;
     switch (sec)
    { 
    case 1:
        matrix<int> m1(2, 3, 1);
        m1.print();
        //matrix<int> *m2= new matrix<int>(2,3,1);
        //m2->print();
        matrix<int> m2(2, 3, 9);
        m2.print();
        m1 = m2 + m1 * 1;
        m1.print("file.txt"); // icinde 10 olan matris olmali
        break;
        /*
    case 2:
        matrix<int> m3(4, 4, 'e');
        matrix<int> m4(5, 5, 'r'); // (5,5) boyutu dene
        //matrix<int> *m5=new matrix<int>(4,4,'e');
        //m5->print();
        m3.print();
        cout<<endl;
        m4.print();
        cout<<endl;
        m3 = m3 * m4;
        m3.print();
        break;
        */
        /*
    case 3:
        matrix<int> m3(5, 4, 1);
        m3.print();
        // 
        //m3.degismis(2,6);
        m3.degismis(10, 6);
        //m3.degismis(10, 3);
        m3.print();
        break;*/
        /* case 4:
        // lineer matris olustur
        //matrix<int> m4(2,2,'L');
        //matrix<int> m5 = m4 * m4.inv();
        //m5.print(); 
        matrix<int> m6(3, 3, 'e');
        m6.det(); // sonuc 0 olmalÄ±
        break;*/
        /*
    case 5:
        //matrix<int> m7(2,2,1);
        matrix<int> *m7 = new matrix<int>(2, 2, 1);
        m7->tersi();
        //m7.print();
        break;*/
    /*case 6:
        matrix<int> *m2 = new matrix<int>(3, 3, 5); 
        matrix<int> *m3 = new matrix<int>(3, 3, 3); 
        //m3.emul(m2); 
        m3->emul(*m2); 
        break;*/
    } 
    return 0;
}
