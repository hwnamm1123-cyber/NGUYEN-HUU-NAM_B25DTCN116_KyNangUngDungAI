#include <stdio.h>
#include <stdlib.h> // C?n thi?t n?u b?n dùng malloc ho?c exit, m?c dù ?ây ch? d?ng cho c?u trúc

// 1. Khai báo c?u trúc d? li?u Student
typedef struct {
    unsigned int id;    // M? s? sinh viên (unsigned int, s? d?ng %u)
    char name[50];      // Tên sinh viên
    unsigned int age;   // Tu?i (unsigned int, s? d?ng %u)
    float gpa;          // Ði?m trung b?nh
} Student;

// Khai báo nguyên m?u hàm (Prototypes)
void print_student_list(Student students[], int size);
int input_student_list(Student students[], int max_size);
void saveToFile(Student students[], int size, const char* filename);

// =======================================================================
// HÀM NH?P DANH SÁCH SINH VIÊN
// =======================================================================
int input_student_list(Student students[], int max_size) {
    int count = 0;
    char next_input;

    printf("--- B?T Ð?U NH?P DANH SÁCH SINH VIÊN (T?i ða %d) ---\n", max_size);
    printf("Nh?p thông tin theo ð?nh d?ng: ID TÊN TU?I GPA (Nh?n k? t? khác Enter ð? d?ng nh?p)\n");

    for (int i = 0; i < max_size; i++) {
        printf("Sinh viên %d (ID TÊN TU?I GPA): ", i + 1);

        // S? d?ng %u cho ID và Tu?i ?? phù h?p v?i ki?u unsigned int
        int result = scanf("%u %49s %u %f",
                           &students[i].id,
                           students[i].name,
                           &students[i].age,
                           &students[i].gpa);

        if (result != 4) {
            // Xóa b? ð?m ð?u vào sau khi nh?p l?i/không ð?c ðý?c
            while ((next_input = getchar()) != '\n' && next_input != EOF);
            printf("K?t thúc nh?p li?u ho?c ð?nh d?ng không h?p l?.\n");
            break;
        }

        count++;
    }

    printf("--- K?T THÚC NH?P, Ð? nh?p %d sinh viên ---\n\n", count);
    return count;
}

// =======================================================================
// HÀM IN DANH SÁCH SINH VIÊN (Dùng %u cho ID và Tu?i)
// =======================================================================
void print_student_list(Student students[], int size) {
    printf("=============================================================\n");
    printf("| %-5s | %-25s | %-5s | %-5s |\n", "ID", "TÊN SINH VIÊN", "TU?I", "GPA");
    printf("=============================================================\n");

    for (int i = 0; i < size; i++) {
        // S? d?ng %u ?? hi?n th? ID và Tu?i không d?u
        printf("| %-5u | %-25s | %-5u | %-5.2f |\n",
               students[i].id,
               students[i].name,
               students[i].age,
               students[i].gpa);
    }

    printf("=============================================================\n");
}

// =======================================================================
// HÀM LÝU D? LI?U VÀO FILE (students.txt)
// =======================================================================
void saveToFile(Student students[], int size, const char* filename) {
    FILE *file = fopen(filename, "w"); // M? file ?? ghi (ghi ðè)

    if (file == NULL) {
        printf("L?i: Không th? m? file %s ?? ghi d? li?u.\n", filename);
        return;
    }

    // Ghi header cho d? li?u file
    fprintf(file, "ID,NAME,AGE,GPA\n");

    // Ghi d? li?u t?ng sinh viên
    for (int i = 0; i < size; i++) {
        fprintf(file, "%u,%s,%u,%.2f\n", 
                students[i].id, 
                students[i].name, 
                students[i].age, 
                students[i].gpa);
    }

    fclose(file);
    printf("--- L?u file thành công t?i: %s (%d sinh viên) ---\n", filename, size);
}

// =======================================================================
// HÀM MAIN
// =======================================================================
int main() {
    // Khai báo m?ng t?i ða 5 sinh viên
    Student student_list[5]; 
    int max_students = 5;

    // Kh?i t?o s?n d? li?u m?u (3 sinh viên)
    student_list[0] = (Student){101, "Nguyen Van A", 20, 3.55};
    student_list[1] = (Student){102, "Tran Thi Binh", 21, 2.90};
    student_list[2] = (Student){103, "Le Hoang Chung", 19, 3.99};
    int num_students_initial = 3;

    printf("--- DANH SÁCH M?U BAN Ð?U ---\n");
    print_student_list(student_list, num_students_initial);

    // BÝ?C 1: NH?P SINH VIÊN M?I
    // T?m th?i ch? nh?p vào 2 v? trí c?n l?i (t? ch? s? 3 ð?n 4)
    Student input_buffer[2];
    int num_input = input_student_list(input_buffer, 2);

    // Tích h?p sinh viên m?i nh?p vào m?ng chính (n?u có)
    for (int i = 0; i < num_input; i++) {
        student_list[num_students_initial + i] = input_buffer[i];
    }
    
    int num_students_total = num_students_initial + num_input;

    // BÝ?C 2: IN DANH SÁCH T?NG H?P
    if (num_students_total > 0) {
        printf("\n--- DANH SÁCH SINH VIÊN T?NG H?P ---\n");
        print_student_list(student_list, num_students_total);

        // BÝ?C 3: LÝU VÀO FILE
        saveToFile(student_list, num_students_total, "students.txt"); 
    } else {
        printf("Không có sinh viên nào trong danh sách.\n");
    }

    return 0;
}
