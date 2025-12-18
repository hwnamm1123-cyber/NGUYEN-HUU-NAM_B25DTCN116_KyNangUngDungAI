#include <stdio.h>
#include <string.h>
#include <stdlib.h> // C?n cho exit() ho?c các ch?c nãng khác

// =======================================================================
// 1. C?U TRÚC D? LI?U (STRUCT)
// =======================================================================
typedef struct {
    unsigned int id;    // M? s? sinh viên (unsigned int, s? d?ng %u)
    char name[50];      // Tên sinh viên
    unsigned int age;   // Tu?i (unsigned int, s? d?ng %u)
    float gpa;          // Ði?m trung b?nh
} Student;


// =======================================================================
// 2. HÀM IN DANH SÁCH (PRINT_STUDENT_LIST)
// =======================================================================
void print_student_list(Student students[], int size) {
    printf("=============================================================\n");
    printf("| %-5s | %-25s | %-5s | %-5s |\n", "ID", "TÊN SINH VIÊN", "TU?I", "GPA");
    printf("=============================================================\n");

    for (int i = 0; i < size; i++) {
        // S? d?ng %u ð? hi?n th? ID và Tu?i không d?u
        printf("| %-5u | %-25s | %-5u | %-5.2f |\n",
               students[i].id,
               students[i].name,
               students[i].age,
               students[i].gpa);
    }

    printf("=============================================================\n");
}


// =======================================================================
// 3. HÀM Ð?C D? LI?U T? FILE (READFROMFILE)
// =======================================================================
int readFromFile(Student students[], int max_size, int *size, const char* filename) {
    FILE *file = fopen(filename, "r");
    // COMMENT: M? file v?i tên ðý?c truy?n vào, th?c hi?n bý?c then ch?t trong x? l? ða file.
    if (file == NULL) {
        printf("L?i: Không th? m? file %s ?? ð?c d? li?u. H?y ð?m b?o file t?n t?i.\n", filename);
        *size = 0;
        return 0; // Tr? v? 0 ð? báo l?i
    }

    char header_buffer[100];
    // Ð?c và b? qua d?ng header (ID,NAME,AGE,GPA)
    if (fgets(header_buffer, sizeof(header_buffer), file) == NULL) {
        printf("C?nh báo: File %s r?ng ho?c không có header.\n", filename);
    }
    
    int count = 0;
    while (count < max_size && 
           // Ð?c d? li?u theo ð?nh d?ng CSV: %u,%[^,],%u,%f
           fscanf(file, "%u,%49[^,],%u,%f\n", 
                  &students[count].id, 
                  students[count].name, 
                  &students[count].age, 
                  &students[count].gpa) == 4) 
    {
        count++;
    }

    fclose(file);
    *size = count;
    printf("--- Ð? ð?c thành công %d sinh viên t? %s ---\n", count, filename);
    return 1; // Tr? v? 1 n?u thành công
}


// =======================================================================
// 4. HÀM MAIN: X? L? NH?P TÊN FILE
// =======================================================================
int main() {
    char filename[50];
    Student class_roster[50]; // M?ng l?n ð? ch?a danh sách t? file
    int student_count = 0;
    const int MAX_STUDENTS = 50;
    
    // 1. Yêu c?u ngý?i dùng nh?p tên file
    printf("--- CHÝÕNG TR?NH X? L? NHI?U FILE ---\n");
    printf("Nh?p tên file (ví d?: classA.txt, classB.txt): ");
    
    // Ð?c tên file. S? d?ng %49s ð? tránh tràn b? ð?m
    // COMMENT: Bý?c này cho phép chý?ng tr?nh tr? nên linh ho?t, x? l? file nào tùy ? ngý?i dùng.
    if (scanf("%49s", filename) != 1) {
        printf("L?i: Nh?p tên file không thành công.\n");
        return 1;
    }
    
    printf("\n--- Ðang ð?c d? li?u t? file: %
