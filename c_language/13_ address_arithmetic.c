#include <stdio.h>

/*
Address arithmetic / арифметика адрес - це операції з вказівниками:

p + 1      перейти до наступного елемента такого самого типу
p - 1      перейти до попереднього елемента
p++        збільшити адресу вказівника на один елемент
p--        зменшити адресу вказівника на один елемент
p2 - p1    отримати кількість елементів між двома вказівниками

Важливо:
Якщо p має тип int *, то p + 1 переходить не на 1 байт вперед,
а на sizeof(int) байтів вперед.

Якщо p має тип char *, то p + 1 переходить на sizeof(char) байт,
тобто зазвичай на 1 байт.

Тип вказівника визначає "крок" арифметики адрес.

Арифметика вказівників безпечна в межах одного масиву:
- можна рухатися від першого до останнього елемента;
- можна отримати адресу одразу після останнього елемента;
- але не можна розіменовувати адресу після останнього елемента.
*/

int main(void)
{

    int g = 23;
    int *ptr = &g;

    printf("ptr = %u\n", ptr);  // ptr = 1545598860 приклад
    ptr++; 
    printf("ptr = %u\n", ptr); //  ptr = 1545598864 приклад
    /*
    1545598860 -> 1545598864 бачимо що значення збільшилось на 4, так як збільшення відбулось на 1 блок(4 байти тип int)
    */

    //  Приклади варіантів операцій, тільки цілі числа, додавання та віднімання.
    ptr+=3;   // Збільшити на 3 блоки даних 3*4=12
    ptr-=4;
    --ptr;


    int h = 234123;
    unsigned char *ptr_1 = (unsigned char *)&h;

    /*
    h має тип int і зазвичай займає 4 байти.
    ptr_1 має тип char *, а char займає 1 байт.

    Тому ptr_1 дозволяє подивитися на змінну h не як на одне число int,
    а як на набір окремих байтів у пам'яті.

    ptr_1++ переходить до наступного байта, бо крок char * дорівнює 1 байту.
    */

    for (int i = 0; i < sizeof(int); ++i) {
        printf("byte %d  value = %d\n", i, *ptr_1);
        ptr_1++;
    }


    int numbers[] = {10, 20, 30, 40, 50};
    int *p = numbers; // Те саме, що int *p = &numbers[0];

    printf("Array first element: %d\n", numbers[0]);
    printf("Value through pointer p: %d\n", *p);

    /*
    p вказує на numbers[0].
    p + 1 вказує на numbers[1].
    p + 2 вказує на numbers[2].

    Для int * крок дорівнює sizeof(int), зазвичай 4 байти.
    */

    printf("\nPointer movement with int *:\n");
    printf("p address:     %u, value: %d\n", (void *)p, *p);
    printf("p + 1 address: %u, value: %d\n", (void *)(p + 1), *(p + 1));
    printf("p + 2 address: %u, value: %d\n", (void *)(p + 2), *(p + 2));

    /*
    Записи нижче рівнозначні:

    numbers[2]
    *(numbers + 2)
    *(p + 2)

    Масив у багатьох виразах перетворюється на вказівник
    на свій перший елемент.
    */

    printf("\nArray indexing and pointer arithmetic:\n");
    printf("numbers[2]:      %d\n", numbers[2]);
    printf("*(numbers + 2):  %d\n", *(numbers + 2));
    printf("*(p + 2):        %d\n", *(p + 2));

    /*
    Можна змінювати значення елемента масиву через арифметику вказівників.
    */

    *(p + 3) = 400; // Змінюємо numbers[3]
    printf("\nAfter *(p + 3) = 400:\n");
    printf("numbers[3]: %d\n", numbers[3]);

    /*
    Інкремент вказівника:

    p++ змінює сам вказівник.
    Після p++ він вказує вже на наступний елемент.
    */

    p = numbers;
    printf("\nPointer increment:\n");
    printf("Before p++: %u, value: %d\n", (void *)p, *p);
    p++;
    printf("After p++:  %u, value: %d\n", (void *)p, *p);

    /*
    Різниця між двома вказівниками одного масиву.

    last - first повертає не кількість байтів,
    а кількість елементів між ними.
    */

    int *first = &numbers[0];
    int *last = &numbers[4];

    printf("\nPointer difference:\n");
    printf("last - first: %td elements\n", last - first);

    /*
    Крок залежить від типу вказівника.

    char * рухається по 1 байту.
    int * рухається по sizeof(int) байтів.
    double * рухається по sizeof(double) байтів.
    */

    char letters[] = {'A', 'B', 'C'};
    char *cp = letters;

    double prices[] = {1.5, 2.5, 3.5};
    double *dp = prices;

    printf("\nStep depends on pointer type:\n");
    printf("sizeof(char):   %zu byte\n", sizeof(char));
    printf("sizeof(int):    %zu bytes\n", sizeof(int));
    printf("sizeof(double): %zu bytes\n", sizeof(double));

    printf("char * cp:      %u\n", (void *)cp);
    printf("char * cp + 1:  %u\n", (void *)(cp + 1));

    printf("int * first:    %u\n", (void *)first);
    printf("int * first + 1:%u\n", (void *)(first + 1));

    printf("double * dp:    %u\n", (void *)dp);
    printf("double * dp + 1:%u\n", (void *)(dp + 1));

    /*
    Адреса "одразу після останнього елемента" дозволена для порівняння
    або як межа циклу, але її не можна розіменовувати.
    */

    int *end = numbers + 5; // Адреса після numbers[4]

    printf("\nLoop through array using pointers:\n");
    for (int *current = numbers; current < end; current++)
        printf("%d ", *current);

    printf("\n");

    /*
    НЕ МОЖНА:

    printf("%d\n", *end);

    end вказує за межі масиву. Таку адресу можна мати як межу,
    але читати або змінювати значення за нею не можна.
    */

    return 0;
}
