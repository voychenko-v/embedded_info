#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::endl;

/*
ifstream - для читання даниз з файлу
ofstream - для запису даних
fstream -  для читання та запису 

Режими доступу до файлів
ios::in - для читання, тільки обєкти класів ifstream, fstream
ios::out - для запису, попередні дані видаляються, тільки обєкти класів ifstream, fstream
ios::app - для дозапису, попередні дані залишаються
ios::ate - при відкриті вказівник в файлі зміщається вкінець
ios::binary - бінарний режим доступу
*/

int main()
{   
    using std::ios;
    std::ofstream ofs;
    std::ifstream ifs;

    ofs.open("path_to_file.dat");  // параметром вказуємо шлях до файлу. Дана реалізація означає що файл створиться(якщо немає) в поточній деректорії
    if(ofs.is_open())
    {
        ofs << 10 << " " << 5.3 << " " << -44 << endl;
    }
    ofs.close();

    int data_i1{}, data_i2{};
    double data_d{};


    ifs.open("path_to_file.dat");  // за допомогою вертикальної полоски обєднуємо модифікатори ios::app | ios::binary
    cout << (ifs.is_open() ? "File is open" : "Error") << endl;
    ifs >> data_i1 >> data_d >> data_i2;
    ifs.close();

    cout << data_i1 << data_d << data_i2 << endl;
    
    return 0;
}