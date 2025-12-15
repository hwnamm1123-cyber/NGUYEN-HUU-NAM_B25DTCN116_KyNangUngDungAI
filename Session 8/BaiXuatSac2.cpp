#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 10

typedef struct {
    unsigned int id;
    char name[50];
    unsigned int age;
    float gpa;
} Student;

void displayMenu();
void print_student_list(Student students[], int size);
int input_student_list(Student students[], int max_size, int start_index);
void saveToFile(Student students[], int size, const char* filename);
int readFromFile(Student students[], int max_size, int *size, const char* filename);
Student* searchStudentById(Student students[], int size, unsigned int student_id);
void sortStudentsByGPA(Student students[], int size);
int addStudent(Student students[], int *size, Student new_student, const int max_capacity);
int deleteStudentById(Student students[], int *size, unsigned int student_id);
void clearInputBuffer();

void displayMenu() {
    printf("\n===== Student Manager =====\n");
    printf("1. Nhap sinh vien moi (Toi da %d)\n", MAX_CAPACITY);
    printf("2. In danh sach\n");
    printf("3. Ghi file (students.txt)\n");
    printf("4. Doc file (students.txt)\n");
    printf("5. Tim kiem theo ID\n");
    printf("6. Sap xep theo GPA Giam dan\n");
    printf("7. Them sinh vien moi (ID, Ten, Tuoi, GPA)\n");
    printf("8. Xoa sinh vien theo ID\n");
    printf("0. Thoat\n");
    printf("===========================\n");
    printf("Chon chuc nang: ");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_student_list(Student students[], int size) {
    printf("====================================================\n");
    printf("| %-5s | %-15s | %-5s | %-5s |\n", "ID", "TEN", "TUOI", "GPA");
    printf("====================================================\n");

    for (int i = 0; i < size; i++) {
        printf("| %-5u | %-15s | %-5u | %-5.2f |\n",
               students[i].id, students[i].name, students[i].age, students[i].gpa);
    }

    printf("====================================================\n");
}

int input_student_list(Student students[], int max_size, int start_index) {
    int count = 0;
    char next_input;

    printf("--- BAT DAU NHAP DANH SACH SINH VIEN (Toi da %d) ---\n", max_size);
    printf("Nhap thong tin theo dinh dang: ID TEN TUOI GPA (Nhap ky tu khac Enter de dung nhap)\n");

    for (int i = start_index; i < max_size; i++) {
        printf("Sinh vien %d (ID TEN TUOI GPA): ", i + 1);

        int result = scanf("%u %49s %u %f",
                           &students[i].id,
                           students[i].name,
                           &students[i].age,
                           &students[i].gpa);

        if (result != 4) {
            while ((next_input = getchar()) != '\n' && next_input != EOF);
            printf("Ket thuc nhap lieu hoac dinh dang khong hop le.\n");
            break;
        }

        count++;
    }
    printf("--- KET THUC NHAP, Da nhap %d sinh vien ---\n\n", count);
    return start_index + count;
}

void saveToFile(Student students[], int size, const char* filename) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Loi: Khong the mo file %s de ghi du lieu.\n", filename);
        return;
    }

    fprintf(file, "ID,NAME,AGE,GPA\n");

    for (int i = 0; i < size; i++) {
        fprintf(file, "%u,%s,%u,%.2f\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].gpa);
    }

    fclose(file);
    printf("--- Luu file thanh cong tai: %s (%d sinh vien) ---\n", filename, size);
}

int readFromFile(Student students[], int max_size, int *size, const char* filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Loi: Khong the mo file %s de doc du lieu. Hay dam bao file ton tai.\n", filename);
        *size = 0;
        return 0;
    }

    char header_buffer[100];
    if (fgets(header_buffer, sizeof(header_buffer), file) == NULL) {
        printf("Canh bao: File %s rong hoac khong co header.\n", filename);
    }

    int count = 0;
    while (count < max_size &&
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
    printf("--- Da doc thanh cong %d sinh vien tu %s ---\n", count, filename);
    return 1;
}

Student* searchStudentById(Student students[], int size, unsigned int student_id) {
    for (int i = 0; i < size; i++) {
        if (students[i].id == student_id) {
            return &students[i];
        }
    }
    return NULL;
}

void sortStudentsByGPA(Student students[], int size) {
    int i, j, max_idx;
    Student temp;

    for (i = 0; i < size - 1; i++) {
        max_idx = i;

        for (j = i + 1; j < size; j++) {
            if (students[j].gpa > students[max_idx].gpa) {
                max_idx = j;
            }
        }

        if (max_idx != i) {
            temp = students[i];
            students[i] = students[max_idx];
            students[max_idx] = temp;
        }
    }
}

int addStudent(Student students[], int *size, Student new_student, const int max_capacity) {
    if (*size >= max_capacity) {
        printf("Loi: Danh sach da day, khong the them sinh vien moi.\n");
        return 0;
    }

    if (searchStudentById(students, *size, new_student.id) != NULL) {
        printf("Loi: ID %u da ton tai. Khong the them sinh vien.\n", new_student.id);
        return 0;
    }

    students[*size] = new_student;
    (*size)++;
    printf("Thong bao: Da them sinh vien ID %u thanh cong.\n", new_student.id);
    return 1;
}

int deleteStudentById(Student students[], int *size, unsigned int student_id) {
    int i, found_index = -1;

    for (i = 0; i < *size; i++) {
        if (students[i].id == student_id) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        printf("Loi: Khong tim thay sinh vien voi ID %u de xoa.\n", student_id);
        return 0;
    }

    for (i = found_index; i < *size - 1; i++) {
        students[i] = students[i + 1];
    }

    (*size)--;
    printf("Thong bao: Da xoa thanh cong sinh vien ID %u.\n", student_id);
    return 1;
}

int main() {
    Student students[MAX_CAPACITY] = {
        {101, "An", 20, 8.5f}, {102, "Binh", 21, 7.8f}, {103, "Chi", 19, 9.2f},
        {104, "Dung", 22, 6.5f}, {105, "Hoa", 20, 8.0f}, {106, "Kien", 21, 7.5f},
        {107, "Lan", 19, 9.0f}, {108, "Minh", 22, 7.0f}, {109, "Ngoc", 20, 8.8f},
        {110, "Phuong", 21, 6.9f}
    };
    int current_size = 10;
    int choice;

    unsigned int id_to_find, id_to_delete;
    Student *found_student;
    Student new_student_data;

    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            choice = -1;
            clearInputBuffer();
        }

        switch (choice) {
            case 1:
                printf("Chuc nang nay se ghi de du lieu hien co neu ban nhap nhieu hon 10 sinh vien.\n");
                current_size = input_student_list(students, MAX_CAPACITY, 0);
                break;
            case 2:
                printf("\n--- DANH SACH SINH VIEN HIEN TAI ---\n");
                print_student_list(students, current_size);
                break;
            case 3:
                saveToFile(students, current_size, "students.txt");
                break;
            case 4:
                readFromFile(students, MAX_CAPACITY, &current_size, "students.txt");
                break;
            case 5:
                printf("Nhap ID can tim: ");
                if (scanf("%u", &id_to_find) == 1) {
                    found_student = searchStudentById(students, current_size, id_to_find);
                    if (found_student != NULL) {
                        printf("Ket qua tim kiem: TIM THAY -> ID: %u, Ten: %s, GPA: %.2f\n",
                               found_student->id, found_student->name, found_student->gpa);
                    } else {
                        printf("Khong tim thay sinh vien co ID %u.\n", id_to_find);
                    }
                }
                clearInputBuffer();
                break;
            case 6:
                sortStudentsByGPA(students, current_size);
                printf("\n--- DANH SACH DA SAP XEP THEO GPA GIAM DAN ---\n");
                print_student_list(students, current_size);
                break;
            case 7:
                printf("Nhap thong tin sinh vien moi (ID TEN TUOI GPA): ");
                if (scanf("%u %49s %u %f",
                          &new_student_data.id, new_student_data.name,
                          &new_student_data.age, &new_student_data.gpa) == 4) {
                    addStudent(students, &current_size, new_student_data, MAX_CAPACITY);
                } else {
                    printf("Loi dinh dang nhap lieu.\n");
                }
                clearInputBuffer();
                break;
            case 8:
                printf("Nhap ID cua sinh vien can xoa: ");
                if (scanf("%u", &id_to_delete) == 1) {
                    deleteStudentById(students, &current_size, id_to_delete);
                }
                clearInputBuffer();
                break;
            case 0:
                printf("Ket thuc chuong trinh. Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le, vui long chon lai.\n");
        }
    } while (choice != 0);

    return 0;
}
