#include <stdio.h>

// 1. Khai báo c?u trúc d? li?u Student
typedef struct {
    int id;           // M? s? sinh viên (int)
    char name[50];    // Tên sinh viên (chu?i k? t?, t?i ða 50)
    int age;          // Tu?i (int)
    float gpa;        // Ði?m trung b?nh (float)
} Student;

// Hàm in danh sách sinh viên ra màn h?nh dý?i d?ng b?ng
void print_student_list(Student students[], int size) {
    // In tiêu ð? b?ng v?i cãn ch?nh c? ð?nh
    printf("=============================================================\n");
    printf("| %-5s | %-25s | %-5s | %-5s |\n", "ID", "TÊN SINH VIÊN", "TU?I", "GPA");
    printf("=============================================================\n");

    // L?p qua m?ng và in thông tin t?ng sinh viên
    for (int i = 0; i < size; i++) {
        printf("| %-5d | %-25s | %-5d | %-5.2f |\n", 
               students[i].id, 
               students[i].name, 
               students[i].age, 
               students[i].gpa); // Cãn ch?nh GPA l?y 2 s? th?p phân
    }
    
    printf("=============================================================\n");
}

int main() {
    // 2. Kh?i t?o s?n m?t m?ng g?m 3 sinh viên m?u
    Student student_list[3] = {
        {101, "Nguyen Van A", 20, 3.55},
        {102, "Tran Thi Binh", 21, 2.90},
        {103, "Le Hoang Chung", 19, 3.99}
    };

    int num_students = sizeof(student_list) / sizeof(student_list[0]);

    // 3. In danh sách ra màn h?nh dý?i d?ng b?ng
    print_student_list(student_list, num_students);
    
    return 0;
}
