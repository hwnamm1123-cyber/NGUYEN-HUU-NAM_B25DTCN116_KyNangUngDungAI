#include <stdio.h>

// 1. Khai báo c?u trúc d? li?u Student
typedef struct {
    int id;           // M? s? sinh viên (int)
    char name[50];    // Tên sinh viên (chu?i k? t?, t?i ða 50)
    int age;          // Tu?i (int)
    float gpa;        // Ði?m trung b?nh (float)
} Student;

// Hàm b? sung: Nh?p danh sách sinh viên
int input_student_list(Student students[], int max_size) {
    int count = 0;
    char next_input;

    printf("--- B?T Ð?U NH?P DANH SÁCH SINH VIÊN (T?i ða %d) ---\n", max_size);
    printf("Nh?p thông tin theo ð?nh d?ng: ID TÊN TU?I GPA (Nh?n k? t? khác 'Enter' ð? d?ng nh?p)\n");

    for (int i = 0; i < max_size; i++) {
        printf("Sinh viên %d (ID TÊN TU?I GPA): ", i + 1);

        int result = scanf("%d %49s %d %f",
                           &students[i].id,
                           students[i].name,
                           &students[i].age,
                           &students[i].gpa);

        if (result != 4) {
            // Xóa b? ð?m ð?u vào
            while ((next_input = getchar()) != '\n' && next_input != EOF);
            printf("K?t thúc nh?p li?u ho?c ð?nh d?ng không h?p l?.\n");
            break;
        }

        count++;
    }

    printf("--- K?T THÚC NH?P, Ð? nh?p %d sinh viên ---\n\n", count);
    return count;
}

// Hàm in danh sách sinh viên ra màn h?nh dý?i d?ng b?ng
void print_student_list(Student students[], int size) {
    printf("=============================================================\n");
    printf("| %-5s | %-25s | %-5s | %-5s |\n", "ID", "TÊN SINH VIÊN", "TU?I", "GPA");
    printf("=============================================================\n");

    for (int i = 0; i < size; i++) {
        printf("| %-5d | %-25s | %-5d | %-5.2f |\n",
               students[i].id,
               students[i].name,
               students[i].age,
               students[i].gpa);
    }

    printf("=============================================================\n");
}

int main() {
    // Khai báo m?ng l?n nh?t (5 sinh viên) và dùng d? kh?i t?o d? li?u m?u.
    Student student_list[5] = {
        {101, "Nguyen Van A", 20, 3.55},
        {102, "Tran Thi Binh", 21, 2.90},
        {103, "Le Hoang Chung", 19, 3.99}
    };
    
    // D? li?u m?u (3 sinh viên)
    int num_students_sample = 3;

    printf("--- DANH SÁCH M?U BAN Ð?U ---\n");
    print_student_list(student_list, num_students_sample);

    // Kích thý?c t?i ða cho phép nh?p
    int max_students_input = 5;

    // S?a l?i: Ch? khai báo num_students m?t l?n
    // L?n 1: S? l?ng sinh viên ðý?c nh?p vào
    int num_students_input = input_student_list(student_list, max_students_input); 
    
    // Ki?m tra n?u có sinh viên ðý?c nh?p (s? l?ng > 0)
    if (num_students_input > 0) {
        printf("\n--- DANH SÁCH SINH VIÊN Ð? NH?P VÀO M?NG ---\n");
        // In danh sách các sinh viên m?i nh?p.
        print_student_list(student_list, num_students_input);
    } else {
        printf("Không có sinh viên nào ðý?c nh?p.\n");
    }

    return 0;
}
