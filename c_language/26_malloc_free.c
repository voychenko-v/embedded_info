#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 malloc   - виділяє невідініціалізовану пам'ять на купі.
 calloc   - виділяє пам'ять і заповнює її нулями.
 realloc  - змінює розмір наявного блоку пам'яті.
 free     - звільняє раніше виділену пам'ять.
 memcpy   - копіює блок пам'яті (небезпечно при перетині областей).
 memmove  - копіює блок пам'яті безпечно при перетині областей.
 memcmp   - порівнює два блоки пам'яті.

 Куча (Heap) - область динамічної пам'яті, якою керує програма.
*/

/*
 append: приклад розширення масиву на купі за потреби.
 Використовує ручне копіювання елементів у новий буфер.
*/
short* append(short* data, size_t *length, size_t *capacity, short value)
{
    if (*length >= *capacity) {
        size_t new_capacity = *capacity * 2; // збільшуємо ємність вдвічі
        short *new_data = malloc(sizeof *new_data * new_capacity);
        if (new_data == NULL) {
            return data; // залишаємо старий буфер, якщо виділення не вдалося
        }

        for (size_t i = 0; i < *length; ++i) {
            new_data[i] = data[i];
        }

        free(data); // звільняємо старий буфер
        data = new_data;
        *capacity = new_capacity;
    }

    data[*length] = value; // додаємо новий елемент
    (*length)++;

    return data;
}

/*
 append_1: те ж саме, але копіювання здійснюється через memcpy.
 Це швидше, але вимагає правильного розміру байтів.
*/
short* append_1(short* data, size_t *length, size_t *capacity, short value)
{
    if (*length >= *capacity) {
        size_t new_capacity = *capacity * 2;
        short *new_data = malloc(sizeof *new_data * new_capacity);
        if (new_data == NULL) {
            return data;
        }

        memcpy(new_data, data, *length * sizeof *data);
        free(data);
        data = new_data;
        *capacity = new_capacity;
    }

    data[*length] = value;
    (*length)++;

    return data;
}

/*
 append_2: використовує realloc для зміни розміру існуючого блоку.
 realloc може перемістити блок у нове місце, тому потрібно зберегти повернений вказівник.
*/
short* append_2(short* data, size_t *length, size_t *capacity, short value)
{
    if (*length >= *capacity) {
        size_t new_capacity = *capacity * 2;
        short *new_data = realloc(data, sizeof *new_data * new_capacity);
        if (new_data == NULL) {
            return data; // якщо realloc не вдався, залишаємо стару пам'ять
        }

        data = new_data;
        *capacity = new_capacity;
    }

    data[*length] = value;
    (*length)++;

    return data;
}

int main(void)
{
    // malloc виділяє пам'ять, але не ініціалізує її
    char *ar = malloc(10 * sizeof *ar);
    if (ar == NULL) {
        return EXIT_FAILURE;
    }

    // ще один приклад виділення пам'яті для окремого об'єкта
    int *ptr_int = malloc(sizeof *ptr_int);
    if (ptr_int == NULL) {
        free(ar);
        return EXIT_FAILURE;
    }

    free(ar);      // звільнення пам'яті після використання
    free(ptr_int); // звільнення другого блоку пам'яті

    size_t capacity = 10;
    size_t length = 0;

    short *data = malloc(sizeof *data * capacity);
    if (data == NULL) {
        return EXIT_FAILURE;
    }

    // додаємо елементи у динамічний масив, що може розширюватися
    for (int i = 0; i < 11; ++i) {
        data = append_2(data, &length, &capacity, rand() % 40 - 20);
    }

    // calloc виділяє і нульово ініціалізує пам'ять
    short *zeroed = calloc(capacity, sizeof *zeroed);
    if (zeroed != NULL) {
        free(zeroed);
    }

    // зменшуємо блок до фактичного розміру, якщо потрібно
    data = realloc(data, sizeof *data * length);
    if (data != NULL) {
        free(data);
    }

    return EXIT_SUCCESS;
}
