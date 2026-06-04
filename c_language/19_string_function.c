#include <stdio.h>
#include <string.h>

/*
Рядкові функції
*/

int main(void){

    char source[100] = "Source string";
    char destination[10];
    
    /*
    Копіюємо рядок за допомогою циклу з source в destination, вкінці додаємо знак закінчення стрічки
    const char *src = source;
    char *dst = destination;

    int max_len_copy = sizeof(destination);
    while(*src != '\0' && max_len_copy-- > 1)
        *dst++ = *src++;
    *dst = '\0';
    */


    // Для копіювання рядків є окремі функції
    // strcpy(destination, source); - Небезпечна функція так як скопіює все у destination незважаючи на розмір масиву
    
    int max_len_copy = sizeof(destination) - 1;
    strncpy(destination, source, max_len_copy);  // Безпечна функція, вказуємо довжину
    destination[max_len_copy] = '\0';
    puts(destination);

    char str[50] = "Hello world";
    // Дізнаємось довжину рядка. Не плутати довжину масиву і стрічки
    
    /*
    За допомогою циклу
    const char *buf = str;
    size_t lenght = 0;

    while(*buf++) // Читаємо і збільшуємо на 1, знак '\0' рахується нулем, коли дойдемо то вийдемо з циклу
        lenght++;

    printf("length = %zu\n", lenght);
    */

    size_t lenght = strlen(str); // Дізнаємось довжину за допомогою функції

    // Обєднання рядків. До рядка який вказаний перший додається другий рядом і повертається адреса першого масиву
    char str_cat[100] = "Hello";
    char str_1[15] = "World";

    strcat(str_cat, str_1);  // Небезпечна так як можемо вийти за межі масиву.
    // strcat(str_cat, "World"); - можемо вказувати рядок другим аргументом
    printf("%s", str_cat);
    
    printf("\n");

    size_t max_add = sizeof(str_1) - strlen(str_1) - 1;  // Максимальна кількість символів скільки можна додати до str_1
    strncat(str_1, str_cat, max_add);  // Третім аргументом вказуємо скільки символів максимально додаємо
    str_1[sizeof(str) - 1] = '\0';  // Останнім додаємо знак закінчення стрічки
    printf("%s", str_1);

    // Функії порівняння рядків. Рядки рівні якщо довжини та літери однакові. "H", "h" - різні символи
    // Рядки рівні навіть якщо масивив в яких вони знаходяться різні по розміру
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
        puts("String lenght are not equal");
    }

    puts("String are equal");
    */

    // Порівняння за допомогою функцій. Якщо функція повертає 0 то рядки рівні, якщо 0 < то перший рядок менший чим другий
    int res = strcmp(s1, s2);
    if(res == 0)
        puts("String are equal");
    else
        puts("String are not equal");


    // Масив указників
    const char *strings[] = {
        "Ship",      // strings[0]
        "Shopping",  // strings[1]
        "Super",     // strings[2]
        "Car"        // strings[3]
    };
    
    // strncmp - дає змогу порівнювати по кількості символів, в нашому випадку порівнюємо перші 2
    for(int i = 0; i < sizeof(strings) / sizeof(*strings); ++i)
        if(strncmp(strings[i], "Sh", 2) == 0){
            puts(strings[i]);
        };
    
    char str_r[] = "Abrakadabra";

    // Пошук символу зліва на право
    char *ptr = strchr(str_r, 'a');
    printf("str_r = %p\nptr = %p\n", str_r, ptr);  // Адерса ptr на 3 зміщена
    if(ptr != NULL)
        printf("*ptr = %c\n", *ptr);
    
    // Пошук символу справа на ліво
    char *ptr_2 = strrchr(str_r, 'g');
    
    // Пошук зліва на право підрядка
    char *ptr_3 = strstr(str_r, "ra");
    printf("str_r = %p\nptr_3 = %p\n", str_r, ptr_3);
    if(ptr_3 != NULL)
        printf("*ptr_3 = %s\n", ptr_3); // rakadabra
    
    // Пошук зліва на право любого символу підрядка find
    char pass[] = "seewggsfg@&9!?";
    char *ptr_4 = strpbrk(pass, "@!#$^&");  // Чи є хоча б один символ в паролі

    
    // sprintf - результат заносить не у вихідний потік а в указаний рядок
    double width = 2.4, heigth = 0.78, depth = 3.14;
    char info[100];
    const char format[] = "(%.2f x %.2f x %.2f)";
    
    sprintf(info, format, width, heigth, depth);  // Уважно! Масив має бути достатного розміру, в на с це масив info
    puts(info);  // (2.40 x 0.78 x 3.14)

    // sprintf - для преобразування чисел в рядки
    int var_i = -123;
    char str_var[10];

    sprintf(str_var, "%d", var_i);
    puts(var_i); // Число у вигляді набору символів

    int a = atoi("123");  // Переводимо стрічку в число int
    long b = atol("3423456354634");  // Переводимо стрічку в число long
    long long c = atoll("43534654353453453");  // Переводимо стрічку в число long long
    double d = atof("3.14");  // Переводимо стрічку в число double


    return 0;

}