#include <stdio.h>

/*
const - кваліфікатор типу, який забороняє змінювати об'єкт через це ім'я або
через цей вказівник. Тобто значення можна читати, але записувати в нього
заборонено.

const int value = 10;   - константна змінна, value змінити не можна
const short *ptr;       - вказівник на константні дані
short *const ptr;       - константний вказівник на змінні дані
const short *const ptr; - константний вказівник на константні дані

Важливо:
const short *ptr означає, що через ptr не можна змінювати дані, але сам ptr
можна перенаправити на іншу адресу.

short *const ptr означає, що ptr завжди зберігає одну й ту саму адресу, але
значення за цією адресою можна змінювати.
*/

int main(void)
{
    const short value = 25;
    // value = 30; - помилка, бо value оголошено як const

    short ar[] = {3, 4, 1, 5};
    short other_ar[] = {7, 8, 9, 10};

    const short *ptr_ar;

    ptr_ar = ar;  // можна присвоїти адресу масиву
    // ptr_ar[0] = 10; - помилка, через ptr_ar не можна змінювати значення

    ptr_ar = other_ar; // можна перенаправити вказівник на інший масив

    ar[0] = 10; // сам масив ar не є const, тому його можна змінювати напряму

    short *const const_ptr = ar;

    const_ptr[1] = 20; // можна змінити значення, бо дані не const
    // const_ptr = other_ar; - помилка, бо сам вказівник const_ptr є const

    const short *const const_ptr_to_const = ar;

    // const_ptr_to_const[2] = 30; - помилка, дані доступні тільки для читання
    // const_ptr_to_const = other_ar; - помилка, сам вказівник теж не можна змінити

    printf("value = %d\n", value);
    printf("ar[0] = %d, ar[1] = %d\n", ar[0], ar[1]);
    printf("ptr_ar[0] = %d\n", ptr_ar[0]);
    printf("const_ptr_to_const[2] = %d\n", const_ptr_to_const[2]);

    return 0;
}
