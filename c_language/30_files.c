#include <stdio.h>
#include <string.h>
#include <errno.h>

/*
Робота з файлами в C.

1. Відкриваємо файловий потік.
   fopen повертає вказівник на FILE або NULL, якщо операція не вдалась.
   Файл відкривається з буферизацією, тобто дані спочатку накопичуються у пам'яті,
   а потім записуються у файл пакетами.

   Режими fopen:
   "r"  - відкривати на читання; файл має існувати.
   "w"  - відкривати на запис; файл створюється, якщо не існує; якщо існує, його вміст видаляється.
   "a"  - відкривати на дозапис; дані додаються до кінця файлу.
   "r+" - читання та запис у існуючий файл.
   "w+" - читання та запис; файл створюється або очищується.
   "a+" - читання та дозапис; файл створюється, якщо не існує.

   Додатково можна додавати символ "b":
   "rb", "wb", "ab", "r+b", "w+b", "a+b" - ті ж режими, але у бінарному режимі.
   У бінарному режимі дані читаються і записуються як сирі байти,
   без перетворення символів нового рядка та без спеціального оброблення EOF.
   Це важливо для збереження структур, чисел, зображень, аудіо та інших даних.

2. Основні функції для роботи з файлами:
   fopen(filename, mode) - відкрити файл.
   fclose(fp)            - закрити файл, очистити буфер і звільнити ресурс.
   fflush(fp)            - примусово скинути буфер у файл без закриття.
   fgetc(fp)             - прочитати один символ.
   fputc(ch, fp)         - записати один символ.
   fgets(buf, n, fp)     - прочитати рядок або до n-1 символів.
   fputs(str, fp)        - записати рядок без форматування.
   fprintf(fp, fmt, ...) - форматований запис у файл.
   fscanf(fp, fmt, ...)  - форматоване читання з файлу.
   fread(ptr, size, nmemb, fp)  - читати nmemb елементів розміру size.
   fwrite(ptr, size, nmemb, fp) - записувати nmemb елементів розміру size.
   fseek(fp, offset, whence)    - встановити позицію у файлі.
   ftell(fp)                    - отримати поточну позицію у файлі.
   rewind(fp)                   - перемістити позицію на початок файлу.
   feof(fp)                     - перевірити, чи досягнуто кінця файлу.
   ferror(fp)                   - перевірити, чи сталася помилка у потоці.
   clearerr(fp)                 - скинути стан помилки та EOF.
   setvbuf(fp, buf, mode, size) - налаштувати буферизацію потоку.

3. Бінарний режим:
   У бінарному режимі файли читаються і записуються без інтерпретації
   символів нового рядка та без перетворення кінця файлу. Це дозволяє
   безпечно зберігати ічитувати дані у вигляді структур, чисел або масивів байтів.
   Для бінарних файлів найчастіше використовують fread / fwrite.

4. Додаткові утиліти:
   remove("file.txt") - видалити файл.
   rename("old.txt", "new.txt") - перейменувати файл.
   tmpfile() - створити тимчасовий файл, який видаляється після закриття.

5. Після завершення роботи потік закривається fclose.
   fclose зливає буфер у файл. Якщо не викликати fclose, буфер може не записатися повністю.
   Також можна викликати fflush для примусової очистки буфера без закриття.
*/

enum {buffer_size=512, data_size=10};

int main(void) {
    char str[] = "Function";
    char buffer_v[buffer_size];

    FILE *fp = fopen("func.txt", "w");
    if (fp == NULL) {
        return 1;
    }

    // Налаштовуємо буфер
    if(setvbuf(fp, buffer_v, _IOFBF, buffer_size) != 0) {  // Якщо повернувся не 0 то виникли помилки
        perror("Incorrect type");
        return 2;
    }

    // Записуємо рядок у файл
    fprintf(fp, "%s\n", str);         // форматований запис
    fputs("Another line\n", fp);     // запис рядка
    fflush(fp);                        // скинути буфер у файл без закриття
    fclose(fp);

    // Тепер відкриваємо файл для читання
    char buffer[100];
    fp = fopen("func.txt", "r");  // Якщо змінюєш вже оголошену змінну — присвоєння, тому без FILE
    if (fp == NULL) {
        printf("Error opening file for reading\n");
        return 1;
    }

    // Читаємо рядок з файлу
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("Read from file: %s\n", buffer);
    }

    fclose(fp);

    FILE *fp_none = fopen("funcc.txt", "r");
    if (fp_none == NULL) {
        printf("errno: %d\n", errno);
        perror("funcc.txt");
    } else {
        fclose(fp_none);
    }

    fp = fopen("func.txt", "r");
    if (fp == NULL) {
        printf("Error opening file for reading\n");
        return 1;
    }

    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("Read from file again: %s", buffer);
    }

    fseek(fp, 0, SEEK_END);  // позиція в кінець файлу
    long length = ftell(fp);
    if (length == -1L) {
        perror("ftell");
        fclose(fp);
        return 1;
    }

    // Читаємо файл задом наперед
    for (long i = 1; i <= length; ++i) {
        fseek(fp, -i, SEEK_END);
        putchar(fgetc(fp));
    }
    putchar('\n');

    fclose(fp);

    double pi = 3.14159265;
    // Відкриваємо бінарний файл для запису
    fp = fopen("func.bin", "wb");
    if (fp == NULL) {
        perror("func.bin");
        return 1;
    }

    fwrite(&pi, sizeof(pi), 1, fp);
    fclose(fp);

    // Читаємо з бінарного файлу
    fp = fopen("func.bin", "rb");
    if (fp == NULL) {
        perror("func.bin");
        return 1;
    }

    double pi_read = 0.0;
    if (fread(&pi_read, sizeof(pi_read), 1, fp) == 1) {
        printf("Read binary pi: %.8f\n", pi_read);
    }
    fclose(fp);

    return 0;
}
