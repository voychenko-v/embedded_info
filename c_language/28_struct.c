#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
  struct - складний тип даних, що групує кілька полів різних типів.

  Синтаксис:
    struct tag_name {
        type1 field1;
        type2 field2;
        ...
    } variable;

  Особливості:
    - struct визначає новий тип, оголошує збірку елементів у єдиному блоці.
    - Розмір структури обчислюється як сума розмірів полів + padding для alignment.
    - Alignment - вирівнювання полів за адресами, кратних їхнім розмірам.
      Це може призвести до того, що sizeof(struct) > суми sizeof усіх полів.
    - Поля структури доступні через оператор крапка (.) або стрілка (->) для вказівників.
    - Структури можуть вкладатися одна в одну.
    - Структури можуть ініціалізуватися: struct tag s = {val1, val2, ...};
    - Структури можуть копіюватися повністю: struct tag s2 = s1;
    - Без явної ініціалізації значення не визначені (або 0 для static/global).

  Приклади:
    struct point { int x, y, z; };
    struct person { char name[50]; int age; };
    struct point_d { double x, y, z; };

  Ініціалізація:
    struct point p1 = {1, 2, 3};
    struct point p2 = {};  // усі поля = 0
    struct person per = {"John", 25};

  Оператори:
    p.x = 10;        // доступ до поля через крапку
    ptr->x = 10;     // доступ через вказівник
    sizeof(struct point); // розмір у байтах
*/
enum { name_length = 50, b_length = 20 };


struct tag_fio {
    char name[name_length];
    char last_name[b_length];
};


struct tag_person{
    struct tag_fio fio;  // Вкладена структура
    char sex;
    unsigned short old;
};

struct tag_point {
    int x;
    int y;
    int z;
};

struct tag_point_d {
    double x, y, z;
};

/*
 Функція яка повертає структуру (копіювання значення).
 Повернення структури означає копіювання всіх даних на стек.
 Локальна змінна p перестає існувати після завершення функції.
 Для малих структур це нормально, для великих може переповнити стек.
*/
struct tag_point create_point(int x, int y, int z)
{
    struct tag_point p = {x, y, z};
    return p;
}

/*
 Функція яка повертає вказівник на структуру (динамічне виділення пам'яті).
 Данні розташовуються на купі (heap), не на стеку.
 Це дозволяє уникнути переповнення стеку для великих структур.
 Важливо: викликуючий код повинен освободити пам'ять через free().
*/
struct tag_point* create_point_m(int x, int y, int z)
{
    struct tag_point* p = malloc(sizeof(struct tag_point));
    if (p == NULL) {
        return NULL;
    }
    p->x = x;
    p->y = y;
    p->z = z;
    return p;
}


/*
 typedef створює зручний псевдонім для складного типу.
 Дозволяє писати VECTOR замість struct tag_vector.
*/
typedef struct tag_vector {
    double x;
    double y;
} VECTOR;

/*
 Функція для додавання двох векторів.
 const параметри означають, що функція не модифікує вхідні дані.
*/
struct tag_vector sum_vector(const struct tag_vector v1, const struct tag_vector v2)
{
    struct tag_vector res = {v1.x + v2.x, v1.y + v2.y};
    return res;
}


int main(void)
{
    // Приклад 1: Структура з простими полями
    struct tag_point pt;
    pt.x = 1;
    pt.y = 2;
    pt.z = 3;

    printf("=== struct tag_point ===\n");
    printf("pt: x=%d, y=%d, z=%d\n", pt.x, pt.y, pt.z);
    printf("sizeof(pt) = %zu\n\n", sizeof(pt));

    // Ініціалізація структури під час оголошення
    struct tag_point pt2 = {10, 20, 30};
    struct tag_point pt3 = {}; // усі поля = 0
    printf("pt2: x=%d, y=%d, z=%d\n", pt2.x, pt2.y, pt2.z);
    printf("pt3: x=%d, y=%d, z=%d\n", pt3.x, pt3.y, pt3.z);

    // Розмір структури та alignment
    printf("sizeof(struct tag_point) = %zu\n", sizeof(struct tag_point));
    printf("sizeof(struct tag_fio) = %zu\n", sizeof(struct tag_fio));
    printf("sizeof(struct tag_person) = %zu\n\n", sizeof(struct tag_person));

    // Приклад 2: Вкладена структура
    struct tag_person person = {
        {"John", "Doe"},
        'M',
        44
    };

    printf("=== struct tag_person ===\n");
    printf("person: name='\''%s'\'', last_name='\''%s'\'', sex=%c, age=%u\n",
           person.fio.name, person.fio.last_name, person.sex, person.old);

    // Зміна даних в структурі
    person.old = 17;
    printf("age=%u\n\n", person.old);

    // Копіювання структури
    struct tag_person p;
    p = person; // Дані структури будуть повністю скопійовані
    printf("p (копія person): name='\''%s'\'', age=%u\n\n", p.fio.name, p.old);

    // Приклад 3: Масив структур
    struct tag_point_d figure[3];

    figure[0].x = 3.4;
    figure[0].y = 1.2;
    figure[0].z = 4.5;

    figure[1].x = 3.6;
    figure[1].y = 4.7;
    figure[1].z = 9.1;

    figure[2].x = 1.1;
    figure[2].y = 2.2;
    figure[2].z = 3.3;

    printf("=== struct tag_point_d ===\n");
    for (int i = 0; i < 3; ++i) {
        printf("figure[%d]: x=%.2f, y=%.2f, z=%.2f\n",
               i, figure[i].x, figure[i].y, figure[i].z);
    }

    printf("\nsizeof(struct tag_point_d) = %zu\n", sizeof(struct tag_point_d));
    printf("sizeof(figure) = %zu\n\n", sizeof(figure));

    // Приклад 4: Вказівники на структури
    struct tag_point* ptr_pt = &pt;

    // Доступ до полів через оператор * та дужки (крапка має вищий пріоритет ніж *)
    (*ptr_pt).x = 4; // Перезаписуємо x
    int y_val = (*ptr_pt).y;
    printf("(*ptr_pt): x=%d, y=%d\n", (*ptr_pt).x, y_val);

    // Оператор -> спрощує запис і еквівалентний (*ptr_pt).field
    ptr_pt->x = 7;
    int x_val = ptr_pt->x;
    printf("ptr_pt->: x=%d, y=%d\n\n", ptr_pt->x, ptr_pt->y);

    // Динамічне виділення структури на купі
    struct tag_point* ptr_pt_heap = malloc(sizeof(struct tag_point));
    if (ptr_pt_heap != NULL) {
        ptr_pt_heap->x = 10;
        ptr_pt_heap->y = 20;
        ptr_pt_heap->z = 30;
        printf("ptr_pt_heap: x=%d, y=%d, z=%d\n\n", ptr_pt_heap->x, ptr_pt_heap->y, ptr_pt_heap->z);
        free(ptr_pt_heap);
    }

    // Функції що повертають структури
    struct tag_point points_c = create_point(3, 4, 5);
    printf("create_point(3,4,5): x=%d, y=%d, z=%d\n", points_c.x, points_c.y, points_c.z);

    struct tag_point* points_m = create_point_m(6, 7, 2);
    if (points_m != NULL) {
        printf("create_point_m(6,7,2): x=%d, y=%d, z=%d\n", points_m->x, points_m->y, points_m->z);
        /*
         УВАГА: не можна викликати create_point_m() повторно без free().
         Якщо переприсвоїти вказівник новим даними без free(), попередня
         пам'ять залишиться невідновлена - це МЕМОРІЛІК!
        */
        free(points_m);
    }

    // typedef спрощує запис типу
    printf("\n=== typedef(VECTOR) ===\n");
    VECTOR one = {4.4, 5.2};
    VECTOR two = {3.4, 4.5};
    VECTOR sum_v = sum_vector(one, two);
    printf("one: x=%.2f, y=%.2f\n", one.x, one.y);
    printf("two: x=%.2f, y=%.2f\n", two.x, two.y);
    printf("sum_vector(one, two): x=%.2f, y=%.2f\n", sum_v.x, sum_v.y);

    return 0;
}
