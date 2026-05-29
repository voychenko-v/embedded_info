#include <stdio.h>
#include <stdbool.h>

/*
Бульові типи. Операції порівняння. Логічні І, АБО, НЕ
true - правда, будь що що не 0
false - брехня, 0

Операції порівняння вираховують і повертають значення true або false 

Приріоритети логічних операцій
АБО(||)  | 1
І(&&)    | 2
НЕ(!)    | 3
*/


int main(void)
{   
    // _Bool на основі типу char
    _Bool fl_viev = 0; // false.
    _Bool fl_viev = 10;  // true. Будь що буде преведено до 1

    // #include <stdbool.h> - після підключення файлу можемо використовувати bool що підмінює _Bool, виглядає більш краще.
    bool fl_false = false;
    bool fl_true = true;

    double x = 7.43;
    int n = 7;

    bool res_1 = x <= 10;  // true, спочатку < потім знак =
    bool res_2 = 5 > 7;  // false
    bool res_3 = x + 2 >= 10; // false
    bool res_4 = n == 8;  // false - тільки з цілими числами так як дійсні числа неточні, можуть виникнути проблеми.
    bool res_5 = n != 8;  // true

    // || - логічна операція АБО. Якщо хоча б одна умова правда поверне true
    double y = 1.34;
    bool is_range_2 = y < -2 || y > 5; // false

    // && - логічна операція І. Якщо всі умови правда то поверне true
    bool is_range = y >= -2 && y <= 5;  // true

    // ! - логічна операція НЕ. Інвертує, було false стане true
    bool is_range_3 = !is_range_2;  // true

    return 0;
}