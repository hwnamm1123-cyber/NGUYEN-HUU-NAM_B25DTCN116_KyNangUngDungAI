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
 * @brief Tính ði?m GPA trung b?nh c?a danh sách sinh viên.
 * * @param students M?ng ch?a danh sách sinh viên.
 * @param size Kích thý?c hi?n t?i c?a m?ng.
 * @return float Ði?m GPA trung b?nh. Tr? v? 0.0 n?u danh sách r?ng.
 */
float calculateAverageGPA(Student students[], int size) {
    // 1. X? l? trý?ng h?p ð?c bi?t: Danh sách r?ng
    if (size <= 0) {
        printf("C?nh báo: Danh sách sinh viên r?ng, không th? tính GPA trung b?nh.\n");
        return 0.0f;
    }

    float total_gpa = 0.0f;

    // 2. Tính t?ng GPA c?a t?t c? sinh viên
    for (int i = 0; i < size; i++) {
        total_gpa += students[i].gpa;
    }

    // 3. Tính và tr? v? GPA trung b?nh
    return total_gpa / size;
}

// (Gi? ð?nh hàm calculateAverageGPA ð? ðý?c ð?nh ngh?a ? trên)

int main() {
    
    // ===============================================================
    // TEST CASE 1: Danh sách 10 sinh viên gi? l?p
    // ===============================================================
    printf("--- TEST CASE 1: DANH SÁCH 10 SINH VIÊN ---\n");
    
    // T?ng GPA c?a 10 sinh viên này là 82.5
    Student mock_students[10] = {
        {1, "An", 20, 9.0f},
        {2, "Binh", 21, 8.5f},
        {3, "Chung", 19, 7.0f},
        {4, "Dung", 22, 9.5f},
        {5, "Hoa", 20, 7.5f},
        {6, "Kien", 21, 8.0f},
        {7, "Lan", 19, 9.2f},
        {8, "Minh", 22, 7.8f},
        {9, "Ngoc", 20, 9.0f},
        {10, "Phuong", 21, 7.0f}
    };
    int mock_size = 10;
    
    float avg_gpa_1 = calculateAverageGPA(mock_students, mock_size);
    printf("GPA trung b?nh c?a l?p là: %.2f\n", avg_gpa_1);
    
    printf("\n");

    // ===============================================================
    // TEST CASE 2: Danh sách R?NG (size = 0)
    // ===============================================================
    printf("--- TEST CASE 2: DANH SÁCH R?NG ---\n");
    
    Student empty_students[1];
    int empty_size = 0;
    
    float avg_gpa_2 = calculateAverageGPA(empty_students, empty_size);
    printf("GPA trung b?nh c?a l?p r?ng là: %.2f\n", avg_gpa_2);
    
    return 0;
}
