#include <stdio.h>
#include <stdlib.h>
#include <string.h> // C?n thi?t cho hàm swap n?u dùng cách khác

// (Gi? ð?nh struct Student ð? ðý?c ð?nh ngh?a)
typedef struct {
    unsigned int id;
    char name[50];
    unsigned int age;
    float gpa;
} Student;


/**
 * @brief S?p x?p danh sách sinh viên theo GPA gi?m d?n b?ng Selection Sort.
 * * @param students M?ng ch?a danh sách sinh viên.
 * @param size Kích thý?c hi?n t?i c?a m?ng.
 */
void sortStudentsByGPA(Student students[], int size) {
    int i, j, max_idx;
    Student temp; // Dùng ð? hoán ð?i

    // V?ng l?p ngoài cùng: Duy?t qua t?t c? các ph?n t? (tr? ph?n t? cu?i cùng)
    for (i = 0; i < size - 1; i++) {
        // Gi? s? ph?n t? hi?n t?i là l?n nh?t
        max_idx = i;

        // V?ng l?p bên trong: T?m ph?n t? l?n nh?t trong ph?n c?n l?i c?a m?ng
        for (j = i + 1; j < size; j++) {
            // S?p x?p GI?M D?N, nên ta t?m GPA l?n nh?t
            if (students[j].gpa > students[max_idx].gpa) {
                max_idx = j;
            }
        }

        // Hoán ð?i (Swap): Ðýa ph?n t? l?n nh?t (max_idx) v? v? trí hi?n t?i (i)
        // Lýu ?: C?n hoán ð?i toàn b? struct Student
        if (max_idx != i) {
            temp = students[i];
            students[i] = students[max_idx];
            students[max_idx] = temp;
        }
    }
}

// (Gi? ð?nh hàm print_student_list ð? ðý?c ð?nh ngh?a)
void print_student_list(Student students[], int size); 

int main() {
    // ---------------------------------------------
    // TEST CASE 1: GPA NG?U NHIÊN
    // ---------------------------------------------
    printf("--- TEST CASE 1: GPA NG?U NHIÊN ---\n");
    Student students_random[4] = {
        {101, "An", 20, 8.0f},
        {102, "Binh", 21, 7.5f},
        {103, "Chi", 19, 9.0f},
        {104, "Dung", 22, 6.5f}
    };
    int size_random = 4;
    
    printf("Trý?c s?p x?p:\n");
    print_student_list(students_random, size_random);
    
    sortStudentsByGPA(students_random, size_random);
    
    printf("Sau s?p x?p (Gi?m d?n):\n");
    print_student_list(students_random, size_random);
    /* K?t qu? mong mu?n: Chi (9.0), An (8.0), Binh (7.5), Dung (6.5) */
    printf("\n");

    // ---------------------------------------------
    // TEST CASE 2: GPA TÃNG D?N S?N
    // ---------------------------------------------
    printf("--- TEST CASE 2: GPA TÃNG D?N S?N ---\n");
    Student students_asc[3] = {
        {201, "A", 20, 7.0f},
        {202, "B", 21, 8.0f},
        {203, "C", 22, 9.0f} // Ð? s?p x?p tãng d?n
    };
    int size_asc = 3;
    
    sortStudentsByGPA(students_asc, size_asc);
    
    printf("Sau s?p x?p (Gi?m d?n):\n");
    print_student_list(students_asc, size_asc);
    /* K?t qu? mong mu?n: C (9.0), B (8.0), A (7.0) */
    printf("\n");

    // ---------------------------------------------
    // TEST CASE 3: GPA B?NG NHAU (Ki?m tra tính ?n ð?nh)
    // ---------------------------------------------
    printf("--- TEST CASE 3: GPA B?NG NHAU ---\n");
    Student students_equal[3] = {
        {301, "Quang", 20, 8.5f},
        {302, "Thang", 21, 8.5f},
        {303, "Viet", 22, 8.5f}
    };
    int size_equal = 3;
    
    sortStudentsByGPA(students_equal, size_equal);
    
    printf("Sau s?p x?p (Gi?m d?n - Th? t? gi? nguyên do GPA b?ng nhau):\n");
    print_student_list(students_equal, size_equal);
    /* K?t qu? mong mu?n: V?n gi? nguyên th? t? ban ð?u (Quang, Thang, Viet) */
    
    return 0;
}
