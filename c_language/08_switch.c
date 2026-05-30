#include <stdio.h>

/*
Оператор switch.
Краще виносити в окрему функцію так як може сильно розростатись та переривати роботу за допомогою return
*/


int main(void)
{
    int value = 2;

    switch (value) {  // Ключове слово switch, value може бути тільки цілим числом
    // Порінюємо наше value з значеннями після case, якщо співпадає то виконуємо весь блок кожу нижче
    case 1:
        printf("Case == 1\n");
    case 2:
        printf("Case == 2\n");
    case 3:
        printf("Case == 3\n");
    // При value = 2 відпрацює 2 та 3 кейс. Щоб відпрацював код який описаний у відповідному кейсі використовуємо break, return
    }

    // break - достроково завершає роботу switch і передає управління далі. return - буде повертати значенн якщо реалізувати в окремій функції
    switch (value) {
    case 1:
        printf("Case == 1\n");
        break;
    case 2:
        printf("Case == 2\n");
        break;
    case 3:
        printf("Case == 3\n");
        break;
    default:  // Дана умова буде виконана якщо жодна з умов case не підійде
        printf("Error - value does not match any of the conditions");
    }

    char item = 'a';

    // При item = 'a' відпраює все нижче до break. Якщо ввести символ 'a' або 'А' то вдіпраює один і той самий блок коду
    switch (item) { 
    case 'a':
    case 'A':
        printf("Symbol A\n");
        break;
    case 'b':
    case 'B':
        printf("Symbol B\n");
        break;
    }

    return 0;
}