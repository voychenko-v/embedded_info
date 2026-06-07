#include <stdio.h>

/*
  enum - перелік іменованих цілочисельних констант.

  Синтаксис:
    enum tag { enumerator1, enumerator2, ... } variable;
    enum tag { enumerator1 = value, enumerator2, ... };
    enum { enumerator1, enumerator2 };

  Особливості:
    - Кожен елемент enum має ціле значення.
    - Якщо не вказано явно, перший елемент має значення 0,
      а кожен наступний значення попереднього + 1.
    - Можна задавати свої значення для окремих елементів.
    - Якщо елемент прив'язаний до іншої константи, він отримує її значення.
    - enum за стандартом має сумісний цілочисельний тип, зазвичай int.
    - Іменований enum створює новий тип, анонімний enum лише константи.

  typedef - створює псевдонім для існуючого типу.
    typedef unsigned char BYTE;
    typedef char (*PTR_ARR_2D)[4];

  Призначення typedef:
    - спрощує читання коду,
    - дозволяє створювати зручні назви для складних типів,
    - не додає нового типу на відміну від struct/union/enum.
*/

// Іменований enum з одночасним оголошенням змінної.
enum colors { red, green, blue } rgb_colors; // red=0, green=1, blue=2

// Значення можуть задаватися вручну. Наступні елементи без значення беруть попереднє + 1.
enum keys { enter = 24, spaces, del = 30 }; // spaces = 25

// Анонімний enum: оголошує лише константи, типу не створюється.
enum {
    go = 0x1f00,
    stop = 0x0001,
    forward = go,
    run = 0x0002,
    back = run - 1
};

// typedef створює псевдонім для типу.
typedef unsigned char BYTE;

typedef char (*PTR_ARR_2D)[4]; // вказівник на масив з 4 символів

int main(void)
{
    // enum можна використовувати як тип для змінних.
    enum colors current_color = green;
    enum keys pressed_key = spaces;

    printf("red = %d, green = %d, blue = %d\n", red, green, blue);
    printf("current_color = %d, pressed_key = %d\n", current_color, pressed_key);
    printf("go = 0x%x, stop = 0x%x, forward = 0x%x, run = 0x%x, back = 0x%x\n",
           go, stop, forward, run, back);

    BYTE byte = 0xff; // псевдонім для unsigned char

    char ar_2d[5][4] = {0};
    PTR_ARR_2D ptr_2d = ar_2d; // вказівник на перший рядок масиву

    ptr_2d[1][2] = 'A';
    printf("ar_2d[1][2] = %c\n", ar_2d[1][2]);

    return 0;
}
