#include <stdio.h>

/*
Багатомірні масиви
*/

int main(void)
{
    char game_pole[3][3] = {1, 2, 3, 4};  // Масив 3*3=9. Значення вставляться підряд 
    /*
    1 2 3 
    4 0 0 
    0 0 0
    */

    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j)
            printf("%d ", game_pole[i][j]);
        printf("\n");
    }

    char game_pole_2[3][3] = {{1, 2}, {3, 4}};  // Значення розподіляються по строкам
    /*
    1 2 0 
    3 4 0 
    0 0 0
    */
    
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j)
            printf("%d ", game_pole_2[i][j]);
        printf("\n");
    }

    // Отримуємо значення з масиву по індексам
    short value_arr = game_pole_2[1][1]; // 4

    int arr[5][3];
    size_t bytes = sizeof(arr);  // 60 байт - елемент(4 байти) * кількість(5*3)
    size_t row_bytes = sizeof(arr[0]);  // 12 - кількість байт які займає стрічка
    size_t cols = sizeof(arr[0]) / sizeof(arr[0][0]);  // 3 - кількість елементів в стрічці 


    return 0;
}