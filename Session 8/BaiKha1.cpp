#include <stdio.h>
#include <stdlib.h> 

// (Gi? ð?nh struct Student ð? ðý?c ð?nh ngh?a ? ðây)
typedef struct {
    unsigned int id;    
    char name[50];      
    unsigned int age;   
    float gpa;          
} Student;


/**
 * @brief T?m ki?m sinh viên trong m?ng d?a trên ID.
 * * @param students M?ng ch?a danh sách sinh viên.
 * @param size Kích thý?c hi?n t?i c?a m?ng.
 * @param student_id ID (unsigned int) c?a sinh viên c?n t?m.
 * @return Student* Con tr? t?i sinh viên n?u t?m th?y, ngý?c l?i tr? v? NULL.
 */
Student* searchStudentById(Student students[], int size, unsigned int student_id) {
    // 1. Ki?m tra trý?ng h?p ð?c bi?t: ID = 0 thý?ng không h?p l? ho?c m?ng r?ng
    if (student_id == 0 || students == NULL || size <= 0) {
        return NULL;
    }

    // 2. Th?c hi?n T?m ki?m Tuy?n tính (Linear Search)
    for (int i = 0; i < size; i++) {
        // So sánh ID c?n t?m v?i ID c?a t?ng sinh viên trong m?ng
        if (students[i].id == student_id) {
            // Tr? v? con tr? t?i ph?n t? sinh viên ðý?c t?m th?y
            return &students[i]; 
        }
    }

    // 3. N?u v?ng l?p k?t thúc mà không t?m th?y, tr? v? NULL
    return NULL;
}

// (Gi? ð?nh hàm print_student_list và các hàm khác ð? có)

void print_student_info(Student *s) {
    if (s != NULL) {
        printf("ID: %u, Name: %s, Age: %u, GPA: %.2f\n", s->id, s->name, s->age, s->gpa);
    }
}

// Hàm main ðý?c s?a ð?i ð? bao g?m Test Case
int main() {
    // Khai báo m?ng v?i 3 sinh viên m?u
    Student student_list[3] = {
        {101, "Nguyen Van A", 20, 3.55},
        {102, "Tran Thi Binh", 21, 2.90},
        {103, "Le Hoang Chung", 19, 3.99}
    };
    int size = 3;
    Student *result = NULL;

    printf("--- B?T Ð?U KI?M TRA CH?C NÃNG T?M KI?M ---\n\n");

    // ---------------------------------------------
    // TEST CASE 1: ID T?N T?I (Ví d?: 102)
    // ---------------------------------------------
    unsigned int search_id_1 = 102;
    printf("1. T?m ki?m ID: %u\n", search_id_1);
    result = searchStudentById(student_list, size, search_id_1);
    if (result != NULL) {
        printf("K?t qu? t?m ki?m: T?M TH?Y -> ");
        print_student_info(result);
    } else {
        printf("K?t qu? t?m ki?m: KHÔNG T?M TH?Y.\n");
    }
    printf("\n");

    // ---------------------------------------------
    // TEST CASE 2: ID KHÔNG T?N T?I (Ví d?: 999)
    // ---------------------------------------------
    unsigned int search_id_2 = 999;
    printf("2. T?m ki?m ID: %u\n", search_id_2);
    result = searchStudentById(student_list, size, search_id_2);
    if (result != NULL) {
        printf("K?t qu? t?m ki?m: T?M TH?Y -> ");
        print_student_info(result);
    } else {
        printf("K?t qu? t?m ki?m: KHÔNG T?M TH?Y.\n");
    }
    printf("\n");

    // ---------------------------------------------
    // TEST CASE 3: ID ÂM (Trong unsigned int, giá tr? âm tr? thành giá tr? r?t l?n)
    // Ta s? test v?i ID = 0 (giá tr? không h?p l?)
    // ---------------------------------------------
    unsigned int search_id_3 = 0; 
    printf("3. T?m ki?m ID: %u (ID không h?p l?)\n", search_id_3);
    result = searchStudentById(student_list, size, search_id_3);
    if (result != NULL) {
        printf("K?t qu? t?m ki?m: T?M TH?Y -> ");
        print_student_info(result);
    } else {
        printf("K?t qu? t?m ki?m: KHÔNG T?M TH?Y.\n");
    }
    printf("\n");

    return 0;
}
