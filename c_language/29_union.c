#include <stdio.h>

/*
Принцип роботи union та бітових полів у C.

union:
- Тип даних, який визначає декілька полів, але всі вони розташовані в одній області пам'яті.
- Підходить для збереження різних представлень одного і того ж блоку даних.
- Розмір union дорівнює розміру найбільшого члена плюс вирівнювання.
- Запис у один з членів змінює дані для всіх інших членів, бо вони ділять ту саму пам'ять.
- Читання неактивного члена зазвичай призводить до інтерпретації тих самих байтів по-іншому.

Бітові поля:
- Дозволяють визначати поля структури з точним числом бітів.
- Користуються для компактного зберігання даних і доступу до прапорів або кодування.
- Типове застосування: дати, прапорці, пристрійні регістри.
*/

typedef enum {
    union_var_none,
    union_var_ch,
    union_var_i,
    union_var_d
} TYPE_VAR;

union tag_var {
    char var_ch;   // 1 байт
    int var_i;     // зазвичай 4 байти
    double var_d;  // зазвичай 8 байт
};

/*
Функція show_var показує значення union в залежності від типу.
Якщо в union було записано одне поле, але читається інше,
тоді дані інтерпретуються по-іншому.
*/
void show_var(union tag_var v, TYPE_VAR type) {
    switch (type) {
    case union_var_ch:
        printf("var_ch = %c\n", v.var_ch);
        break;
    case union_var_i:
        printf("var_i = %d\n", v.var_i);
        break;
    case union_var_d:
        printf("var_d = %f\n", v.var_d);
        break;
    case union_var_none:
        printf("Undefined type\n");
        break;
    }
}

/*
Структура date_time з бітовими полями.
- day: 5 біт (0..31)
- month: 4 біти (0..15)
- year: 12 біт (0..4095)
*/
struct dite_time {
    unsigned day : 5;   // 0..31
    unsigned month : 4; // 0..15
    unsigned year : 12; // 0..4095
};

void show_date(const struct dite_time *date) {
    printf("date = %u.%u.%u\n", date->day, date->month, date->year);
}

int main(void) {
    union tag_var var;

    /* Запис символу у union */
    var.var_ch = 'c';
    printf("After storing var_ch:\n");
    show_var(var, union_var_ch);
    show_var(var, union_var_i); // ті самі байти інтерпретуються як int

    /* Запис цілого числа у union */
    var.var_i = 42;
    printf("\nAfter storing var_i:\n");
    show_var(var, union_var_i);
    show_var(var, union_var_ch); // цей char може бути «сміттям» після запису int

    /* Запис числа з плаваючою комою у union */
    var.var_d = 3.14159;
    printf("\nAfter storing var_d:\n");
    show_var(var, union_var_d);
    show_var(var, union_var_i); // ці ж байти інтерпретуються як int

    printf("\nSize of union tag_var = %zu bytes\n", sizeof(var));

    /* Приклад роботи бітових полів */
    struct dite_time date = {31, 12, 2025};
    show_date(&date);
    printf("Size of struct dite_time = %zu bytes\n", sizeof(date));

    return 0;
}
