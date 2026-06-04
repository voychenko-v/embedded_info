#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Рядкові функції

Основні функції з <string.h>:
strlen(s)              - повертає довжину рядка без символу '\0'.
strcpy(dst, src)       - копіює рядок src у dst. Небезпечна, якщо dst замалий.
strncpy(dst, src, n)   - копіює не більше n символів. Може не додати '\0', якщо src довший або рівний n.
strcat(dst, src)       - додає src у кінець dst. Небезпечна, якщо в dst мало місця.
strncat(dst, src, n)   - додає не більше n символів і завершує рядок символом '\0'.
strcmp(s1, s2)         - порівнює рядки лексикографічно.
strncmp(s1, s2, n)     - порівнює не більше n перших символів.
strchr(s, ch)          - шукає перше входження символу ch зліва направо.
strrchr(s, ch)         - шукає останнє входження символу ch.
strstr(s, sub)         - шукає перше входження підрядка sub.
strpbrk(s, chars)      - шукає перший символ із набору chars.

Корисні функції з інших заголовків:
sprintf(buf, fmt, ...) - записує відформатований текст у рядок. Потрібен <stdio.h>.
snprintf(buf, n, fmt, ...) - як sprintf, але з обмеженням розміру буфера. Безпечніший варіант.
atoi(s), atol(s), atoll(s), atof(s) - перетворюють рядок у число. Потрібен <stdlib.h>.
*/

int main(void){

    char source[100] = "Source string";
    char destination[10];
    
    /*
    Копіюємо рядок за допомогою циклу з source в destination,
    в кінці додаємо знак закінчення рядка.

    const char *src = source;
    char *dst = destination;

    int max_len_copy = sizeof(destination);
    while(*src != '\0' && max_len_copy-- > 1)
        *dst++ = *src++;
    *dst = '\0';
    */


    // Для копіювання рядків є окремі функції
    // strcpy(destination, source); - небезпечна функція, бо скопіює все у destination, не зважаючи на розмір масиву.
    
    int max_len_copy = sizeof(destination) - 1;
    strncpy(destination, source, max_len_copy);  // Копіюємо не більше max_len_copy символів.
    destination[max_len_copy] = '\0';            // Гарантуємо коректне завершення рядка.
    puts(destination);

    char str[50] = "Hello world";
    // Дізнаємось довжину рядка. Не плутати довжину масиву і рядка.
    
    /*
    За допомогою циклу
    const char *buf = str;
    size_t length = 0;

    while(*buf++) // Читаємо і збільшуємо на 1. Коли дійдемо до '\0', вийдемо з циклу.
        length++;

    printf("length = %zu\n", length);
    */

    size_t length = strlen(str); // Дізнаємось довжину за допомогою функції.
    printf("length = %zu\n", length);

    // Об'єднання рядків. До першого рядка додається другий і повертається адреса першого масиву.
    char str_cat[100] = "Hello";
    char str_1[15] = "World";

    strcat(str_cat, str_1);  // Небезпечна, бо можемо вийти за межі масиву.
    // strcat(str_cat, "World"); - можемо вказувати рядок другим аргументом
    printf("%s\n", str_cat);
    
    size_t max_add = sizeof(str_1) - strlen(str_1) - 1;  // Максимальна кількість символів, яку можна додати до str_1.
    strncat(str_1, str_cat, max_add);  // Третім аргументом вказуємо, скільки символів максимально додаємо.
    printf("%s\n", str_1);

    // Функції порівняння рядків. Рядки рівні, якщо довжини та символи однакові. "H" і "h" - різні символи.
    // Рядки можуть бути рівними, навіть якщо масиви, в яких вони знаходяться, різні за розміром.
    char s1[12] = "Hello";
    char s2[10] = "Hello";

    /* Порівняння за допомогою циклу
    const char *str1 = s1;
    const char *str2 = s2;

    int i = 0;
    for(; str1[i] != '\0' && str2[i] != '\0'; ++i)
        if(str1[i] != str2[i]){
            puts("Strings are not equal!");
            return 0;
        }
    
    if(str1[i] != str2[i]){
        puts("String lengths are not equal");
    }

    puts("Strings are equal");
    */

    /*
    Порівняння за допомогою функцій:
    strcmp повертає 0, якщо рядки рівні;
    значення < 0, якщо перший рядок лексикографічно менший за другий;
    значення > 0, якщо перший рядок лексикографічно більший за другий.
    */
    int res = strcmp(s1, s2);
    if(res == 0)
        puts("Strings are equal");
    else
        puts("Strings are not equal");


    // Масив указників
    const char *strings[] = {
        "Ship",      // strings[0]
        "Shopping",  // strings[1]
        "Super",     // strings[2]
        "Car"        // strings[3]
    };
    
    // strncmp - дає змогу порівнювати по кількості символів, в нашому випадку порівнюємо перші 2
    for(size_t i = 0; i < sizeof(strings) / sizeof(*strings); ++i)
        if(strncmp(strings[i], "Sh", 2) == 0){
            puts(strings[i]);
        }
    
    char str_r[] = "Abrakadabra";

    // Пошук символу зліва направо
    char *ptr = strchr(str_r, 'a');
    printf("str_r = %p\nptr = %p\n", (void *)str_r, (void *)ptr);  // Адреса ptr зміщена на 3 символи.
    if(ptr != NULL)
        printf("*ptr = %c\n", *ptr);
    
    // Пошук символу справа наліво
    char *ptr_2 = strrchr(str_r, 'a');
    if(ptr_2 != NULL)
        printf("*ptr_2 = %c\n", *ptr_2);
    
    // Пошук підрядка зліва направо
    char *ptr_3 = strstr(str_r, "ra");
    printf("str_r = %p\nptr_3 = %p\n", (void *)str_r, (void *)ptr_3);
    if(ptr_3 != NULL)
        printf("*ptr_3 = %s\n", ptr_3); // rakadabra
    
    // Пошук зліва направо будь-якого символу з набору find
    char pass[] = "seewggsfg@&9!?";
    char *ptr_4 = strpbrk(pass, "@!#$^&");  // Чи є хоча б один символ в паролі
    if(ptr_4 != NULL)
        printf("special character = %c\n", *ptr_4);

    
    // sprintf - результат заносить не у вихідний потік, а в указаний рядок.
    double width = 2.4, height = 0.78, depth = 3.14;
    char info[100];
    const char format[] = "(%.2f x %.2f x %.2f)";
    
    sprintf(info, format, width, height, depth);  // Уважно! Масив має бути достатнього розміру, у нас це масив info.
    puts(info);  // (2.40 x 0.78 x 3.14)

    // snprintf - безпечніший варіант, бо вказуємо розмір буфера.
    snprintf(info, sizeof(info), "depth = %.2f", depth);
    puts(info);

    // sprintf - для перетворення чисел у рядки.
    int var_i = -123;
    char str_var[10];

    sprintf(str_var, "%d", var_i);
    puts(str_var); // Число у вигляді набору символів.

    int a = atoi("123");  // Перетворюємо рядок у число int.
    long b = atol("1234567890");  // Перетворюємо рядок у число long.
    long long c = atoll("43534654353453453");  // Перетворюємо рядок у число long long.
    double d = atof("3.14");  // Перетворюємо рядок у число double.

    printf("a = %d\nb = %ld\nc = %lld\nd = %.2f\n", a, b, c, d);


    return 0;

}
