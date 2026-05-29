#include <stdio.h>

// Умовний оператор if, якщо вираз в круглих дужках повертає true то виконуєть блок коду описаний далі

int main(void)
{
    int x;
    x = -10;

    if(x < 0) x = -x;  // При -10 число зміниться на позитивне

    if(x < 0)
        printf("x < 0");
    else if(x > 0)
        printf("x > 0");
    else
        printf("x == 0");

    return 0;
}

