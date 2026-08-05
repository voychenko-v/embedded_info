#include <iostream>

namespace firsSpase {
// оголошуємо простір імен в якому бодемо обєднувати певну реалізацію
void print_hello()
{
    std::cout << "Hello: firsSpase" << std::endl;
}
}

void print_hello()
{
    std::cout << "Hello: global" << std::endl;
}

namespace firsSpase {
// знову оголошуємо простір імен який оголошували раніше і це буде важатись як один простір імен
struct point {
    int x, y;
};
}

int global_a = 5;

using std::cout;  // після дагого оголешення далі можемо звертатись до cout напряму без std:: Доступно голобально в модулі
// using namespace std;  імпортуємо весь простір імен, погана практика так як багато що реалізовано можуть бути конфлікти імен
using byte_8 = unsigned char;  // аліас, далі можемо оголошувати ансайнед чар як байт_8. Тільки для типів даних
using point2D = firsSpase::point;
typedef unsigned char byte_8_2;  // ще одина варіант оголошення, для програми нічим не відрізняється від юзінг але юзінг має додаткові фічі

int main() {

    using std::endl;  // доступно локально, тільки в даній функції

    int global_a = 10;

    // звернення до локальної змінної та глобільної, :: звернення до глобального простору імен, звернення
    std::cout << global_a << " " << ::global_a << std::endl;
    cout << global_a << " " << ::global_a << std::endl;

    // викликаємо функції з однаковими іменами але різні просторів імен
    ::print_hello();
    firsSpase::print_hello();
    
    return 0;
}



