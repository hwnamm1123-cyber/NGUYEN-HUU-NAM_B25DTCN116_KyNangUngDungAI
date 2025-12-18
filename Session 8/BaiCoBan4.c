
#include <stdio.h>
#include <string.h>

// Dinh nghia struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

// Ham nhap du lieu sinh vien tu ban phim
void inputStudents(struct Student students[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin sinh vien thu %d ---\n", i + 1);

        printf("Nhap ID: ");
        scanf("%d", &students[i].id);

        // Xoa bo dem sau scanf
        while (getchar() != '\n');

        printf("Nhap ho va ten: ");
        fgets(students[i].name, 50, stdin);
        // Xoa ky tu xuong dong o cuoi chuoi
        students[i].name[strcspn(students[i].name, "\n")] = '\0';

        printf("Nhap tuoi: ");
        scanf("%d", &students[i].age);

        printf("Nhap GPA: ");
        scanf("%f", &students[i].gpa);
    }
}

// Ham luu du lieu sinh vien vao file
void saveToFile(struct Student students[], int n) {
    FILE *file = fopen("students.txt", "w");

    if (file == NULL) {
        printf("Loi: Khong the mo file de ghi!\n");
        return;
    }

    // Ghi dong tieu de
    fprintf(file, "ID\tName\tAge\tGPA\n");

    // Ghi tung sinh vien vao file, moi sinh vien 1 dong
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\t%s\t%d\t%.2f\n", 
                students[i].id, 
                students[i].name, 
                students[i].age, 
                students[i].gpa);
    }

    // Dong file de dam bao du lieu duoc luu
    fclose(file);
    printf("Da luu thanh cong %d sinh vien vao file students.txt\n", n);
}

// Ham doc du lieu sinh vien tu file
int readFromFile(struct Student arr[], const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Loi: Khong the mo file %s de doc!\n", filename);
        return 0;
    }

    char buffer[200];

    // Bo qua dong tieu de dau tien
    fgets(buffer, sizeof(buffer), file);

    int count = 0;

    // Doc tung sinh vien tu file
    // Su dung %[^\t] de doc chuoi co khoang trang cho den khi gap tab
    while (fscanf(file, "%d\t%[^\t]\t%d\t%f\n", 
                  &arr[count].id, 
                  arr[count].name, 
                  &arr[count].age, 
                  &arr[count].gpa) == 4) {
        count++;
    }

    // Dong file
    fclose(file);
    printf("Da doc thanh cong %d sinh vien tu file %s\n", count, filename);

    return count;
}

// Ham in bang danh sach sinh vien
void printStudentTable(struct Student students[], int size) {
    printf("\n");
    printf("=================================================================================\n");
    printf("%-10s %-30s %-10s %-10s\n", "ID", "Ho va Ten", "Tuoi", "GPA");
    printf("=================================================================================\n");

    for (int i = 0; i < size; i++) {
        printf("%-10d %-30s %-10d %-10.2f\n", 
               students[i].id, 
               students[i].name, 
               students[i].age, 
               students[i].gpa);
    }

    printf("=================================================================================\n");
    printf("\n");
}

int main() {
    // Khai bao mang 2 sinh vien
    struct Student students[2];
    int n = 2;

    printf("=== CHUONG TRINH QUAN LY SINH VIEN ===\n");
    printf("Nhap thong tin cho %d sinh vien:\n", n);

    // Nhap du lieu cho 2 sinh vien
    inputStudents(students, n);

    // Luu du lieu vao file
    printf("\n");
    saveToFile(students, n);

    // In bang danh sach sinh vien vua nhap
    printf("\n=== DANH SACH SINH VIEN VUA NHAP ===");
    printStudentTable(students, n);

    // Doc lai du lieu tu file va hien thi
    printf("\n=== DOC DU LIEU TU FILE ===\n");
    struct Student studentsFromFile[100];  // Mang de luu du lieu doc tu file
    int count = readFromFile(studentsFromFile, "students.txt");

    if (count > 0) {
        printf("\n=== DANH SACH SINH VIEN TU FILE ===");
        printStudentTable(studentsFromFile, count);
    } else {
        printf("Khong co du lieu de hien thi.\n");
    }

    return 0;
}
