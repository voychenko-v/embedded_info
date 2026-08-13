#include <iostream>

/*
При розміщені нового обєкта в памяті, компілятор автоматично робить виклик спеціального методу "Конcтруктора"
В конструкторі йде початкова ініціалізація.
- імя конструктора завжди співпадає з імят типу даних в нашому випадку Point2D
- конструктор ніколи нічого не повертає
- має довільне число параметрів
- завжди викликається при створенні нового обєкту
- ініціалізуються значення з конструктора навіть якщо аргументи в класі проініціалізовані

При виводі значень Point2D (дивитись в main) поведінка неочікувана так як явно невказано значення. Потрібно описати конструктор
Вивід:
2 106119264
0 0

Додамо конструктор в Point2DConstructor, 


Деструктор.
- викликається перед знищенням обєкта
- імя співпадає з імям класу, але попереду "~"
- нічого не повертає
- не має параметрів
*/


// Клас без конструктора
class Point2D {
private:
    int x, y;  // Доступ до приватних елементів можна отримувати тільки в середині класу
public:
    void set_cords(int a, int b)
        {x = a; y = b;}  // Без проблем звертаємось до приватних елементів, взаємодіємо тільки через публічні ментоди.
    void get_cords(int &a, int &b)
        {a = x; b = y;}
    bool set_cords_range(int a, int b, int min_cord = 0, int max_cord = 10)
    {
        if(a < min_cord || a > max_cord || b < min_cord || b > max_cord )
            return false;
        set_cords(a, b);
        return true;
    }
};


// Клас з конструктруктором
class Point2DConstructor {
private:
    const unsigned max_coord;  // Тільки ініціалізація для const. Можемо const unsigned max_coord {100}; Але проініціалізуємо в конструкторі.
    int x{0}, y{0};  // Значення проініціалізує конструктор(приріоритет) які вказані в ньому, дані значення не будуть враховані.
public:
    /*
    Конструктор. Ініціалізуємо аргументи нулями а тіло буде пустим. Обовязково зберігати порядок ініціалізації змінних х->y
    */
    Point2DConstructor() : max_coord(100), x(10), y(10)  // Відбувається ініціалізація а не присвоювання. const ініціалізуються саме тут а не в тілі де присвоювання.
        { std::cout << "Конструктор без аргументів" << std::endl; }

    // Перегрузка конструктора, даний конструктор очікує 2 аргументи
    Point2DConstructor(int a, int b) : max_coord(200), x(a), y(b)
        { std::cout << "Конструктор очікує 2 аргументи" << std::endl; }

    void set_cords(int a, int b)
        {x = a; y = b;}
    void get_cords(int &a, int &b)
        {a = x; b = y;}
};

// Реалізуємо конструктор з одним параметром(конструктор преобразовання)
class Complex {
    double re;
    double im;

public:
    Complex() : re(0.0), im(0.0)
        {}
    Complex(double real) : re(real), im(0.0)
        {}
    Complex(double real, double imag) : re(real), im(imag)
        {}
    void get_data(double& re, double& im)
    {
        re = this->re;
        im = this->im;
    }

    // Метод додавання двох дійсних чисел обєкту комплекс
    const Complex& add(const Complex& other)
    {
        this->re += other.re;
        this->im += other.im;
        return *this;
    }
};

// Реалізуємо деструктор
class PointND{
    unsigned total {0};
    int *coords {nullptr};
public:
    PointND () : total(0), coords(nullptr)
        { }
    PointND (unsigned sz) : total(sz)
        {
            coords = new int[total] {0};
        }
    PointND (int *cr, unsigned sz) : total(sz)
        {
            coords = new int[total] {0};
            set_coords(cr, sz);
        }
    PointND (const PointND& other) : total(other.total)  // Конструктор копіювання
        {
            coords = new int[total];
            set_coords(other.coords, total);
        }
    /*
    Деструктор. Реалізували видалення зарезервованої памяті конструктором.
    =====
    PointND pt(5);
    PointND pt2 {pt}; - коли створюється обєкт на основі іншого того ж класу ти викликається спец конструктор копіювання, 
    який всі дані копіює в інший обєкт. Потрібно реалізувати логіку копіювання(реалізовано вище). 
    Якщо не реалізувати логіку копіювання, можуть бути проблеми так як память при виклику деструктора буде намагатись видаляться в одному місці 2 рази
    =====
    */
    ~PointND ()  
    { 
        delete[] coords; 
    }

    void set_coords(int *cr, unsigned len)
    {
        for(unsigned i=0; i<= total; ++i)
            coords[i] = (i < len) ? cr[i] : 0;
    }
};

int main()
{   
    Point2D pt; // Зберігається в стекові, приклад нижче зберігає в кучі.
    Point2D* ptr_pt = new Point2D;  // В класичному С++ частіше використовують даний спосіб так як часто створюється багато обєктів
    
    int x, y;
    // 1. =================
    pt.get_cords(x, y);
    std::cout << x << " " << y << std::endl;

    ptr_pt->get_cords(x, y);
    std::cout << x << " " << y << std::endl;

    delete ptr_pt;
    // =================
    Point2DConstructor ptc;
    Point2DConstructor ptc2(10, 20);  // Передали 2 аргументи викликався перегружений конструктор
    // =================
    Complex c1;  // Complex c1 {};
    Complex c2(10.0); // Complex c2 {10.0};  Complex c2 = 10.0; на основі одного значення формує обєкт
    Complex c3(-4.2, 5.3); // Complex c3 {-4.2, 5.3};  Complex c3 = {-4.2, 5.3}

    c2.add(c3);

    double re, im;
    c2.get_data(re, im);

    std::cout << "Complex: " << re << " " << im << std::endl;

    // можна передавати і просто числа, компілятор створить тимчасовий обєкт класу комплекс і вирахується значення
    // explicit - при додавання даного спец слова перед конструктором заборонить неявне перетворення типів і додавання просто чисел буде заборонено
    c2.add(1.1);


    return 0;
}