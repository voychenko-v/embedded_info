#include <stdio.h>

/*
Операції над масивами
*/

#define TOTAL_MARKS 10

int main(void)
{

    float func_1[20] = {2.3, 4.2, 5.3, -5.34};
    float func_2[10];

    // Визначаємо розміри масивів
    int size_1 = sizeof(func_1) / sizeof(func_1[0]);
    int size_2 = sizeof(func_2) / sizeof(func_2[0]);
    int size = (size_1 < size_2) ? size_1 : size_2;

    // Скопіюємо значення з першого масиву в другий
    for(int i = 0; i < size; ++i){
        func_2[i] = func_1[i];
    }

    // Вставка нового значення в певний індекс, наприклад 4 хочемо вставити між 2 і 5, 5 та інші значення здвинуться на 1 вправо
    int marks[TOTAL_MARKS] = {3, 2, 5};
    int insert_index = 2;  // Значення яке вставляємо має знаходитиьс в 2 індексі

    for(int i = TOTAL_MARKS-1; i > insert_index; --i ){
        marks[i] = marks[i-1];
    }

    marks[insert_index] = 4;

    // Видаляємо елемент а значення здвигаємо вліво
    int del_index = 1; 

    for(int i = del_index; i < TOTAL_MARKS; ++i ){
        marks[i] = marks[i+1];
    }


    // Coртування вибором. Відсортовуємо елементи від найменшого до найбільшого
    char t[] = {5, 0 -3, 10, 8, 1};
    int size = sizeof(t) / sizeof(t[0]);
    int pos;

    for(int i = 0; i < size-1; ++i){
        pos=i;
        for(int j = i + 1; j < size; ++j){
            if(t[pos] > t[j])
                pos = j;
        }
        // Обмін значеннями
        if(pos != i){
            int r = t[i];
            t[i] = t[pos];
            t[pos] = r; 
        }
    }

    return 0;
}