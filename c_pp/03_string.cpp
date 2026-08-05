#include <iostream>
#include <string>

using std::cout;
using std::endl;


int main ()
{
    // char msg[] = "Hello world";  - в С стрічки були одномірним масивом типу чар що було не зручно

    std::string msg;  // в с+ string це клас, при діній ініціалізації є пустою стрічкою. Всередені використовує динамічний масив симвалів

    cout << msg.size() << " " << msg.capacity() << endl;  // 0 22 - виведе що стрічка розміром 0 але сам масив займає 22 символи

    msg = "Hello world. Hello world. Hello world";

    cout << msg.size() << " " << msg.capacity() << endl; // 37 47 - динамічний масив збільшився

    // Створюємо вказівник на масив символів
    const char* data = msg.data();
    cout << data << endl;

    for(const char& ch : msg)
        cout << ch << " ";

    // Можемо перебрати використовуючи механізм ітерації
    for(auto i = msg.begin(); i != msg.cend(); ++i)
        cout << *i << " ";

    msg.append(", add new striong");  // додаємо до існуючої стрічки нову

    std::string new_string {"New string"};

    msg = msg + new_string;  // додаємо дві стрічки
    
    return 0;
}