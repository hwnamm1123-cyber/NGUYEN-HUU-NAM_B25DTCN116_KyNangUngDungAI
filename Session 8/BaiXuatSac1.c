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

void print_student_list(Student students[], int size);
Student* searchStudentById(Student students[], int size, unsigned int student_id);
int addStudent(Student students[], int *size, Student new_student, const int max_capacity);
int deleteStudentById(Student students[], int *size, unsigned int student_id);

Student* searchStudentById(Student students[], int size, unsigned int student_id) {
    for (int i = 0; i < size; i++) {
        if (students[i].id == student_id) {
            return &students[i];
        }
    }
    return NULL;
}

int addStudent(Student students[], int *size, Student new_student, const int max_capacity) {
    if (*size >= max_capacity) {
        printf("L?i: Danh sách ð? ð?y, không th? thêm sinh viên m?i.\n");
        return 0;
    }
    if (searchStudentById(students, *size, new_student.id) != NULL) {
        printf("L?i: ID %u ð? t?n t?i. Không th? thêm sinh viên.\n", new_student.id);
        return 0;
    }
    students[*size] = new_student;
    (*size)++;
    printf("Thông báo: Ð? thêm sinh viên ID %u thành công.\n", new_student.id);
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
        printf("L?i: Không t?m th?y sinh viên v?i ID %u ð? xóa.\n", student_id);
        return 0;
    }

    for (i = found_index; i < *size - 1; i++) {
        students[i] = students[i + 1];
    }
    (*size)--;
    printf("Thông báo: Ð? xóa thành công sinh viên ID %u.\n", student_id);
    return 1;
}

void print_student_list(Student students[], int size) {
    printf("====================================================\n");
    printf("| %-5s | %-15s | %-5s | %-5s |\n", "ID", "TÊN", "TU?I", "GPA");
    printf("====================================================\n");
    for (int i = 0; i < size; i++) {
        printf("| %-5u | %-15s | %-5u | %-5.2f |\n",
               students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
    printf("====================================================\n");
}

int main() {
    Student student_roster[MAX_CAPACITY] = {
        {1, "An", 20, 8.0f},
        {2, "Binh", 21, 7.5f},
        {3, "Chi", 19, 9.0f}
    };
    int current_size = 3;

    printf("--- DANH SÁCH BAN Ð?U (%d sinh viên) ---\n", current_size);
    print_student_list(student_roster, current_size);

    printf("\n--- TEST: THÊM THÀNH CÔNG ---\n");
    Student new_student_1 = {4, "Dung", 22, 6.5f};
    addStudent(student_roster, &current_size, new_student_1, MAX_CAPACITY);
    
    printf("\nDanh sách sau khi thêm (D?ng):\n");
    print_student_list(student_roster, current_size);

    printf("\n--- TEST: THÊM TRÙNG ID ---\n");
    Student new_student_2 = {4, "Trung", 25, 5.0f};
    addStudent(student_roster, &current_size, new_student_2, MAX_CAPACITY); 
    
    printf("\n--- TEST: XÓA KHÔNG T?N T?I ---\n");
    deleteStudentById(student_roster, &current_size, 99); 

    printf("\n--- TEST: XÓA THÀNH CÔNG ---\n");
    deleteStudentById(student_roster, &current_size, 2);
    
    printf("\n--- DANH SÁCH CU?I CÙNG ---\n");
    printf("Danh sách sau khi ch?nh s?a:\n");
    print_student_list(student_roster, current_size);

    return 0;
}
