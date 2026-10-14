#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  COMMON DEFINITIONS 
#define MAX_STUDENTS 100
#define MAX_TEACHERS 100
#define STUDENT_FILE "students.txt"
#define TEACHER_FILE "teachers.txt"

//  STRUCTURES 
struct Student {
    char id[20];
    char name[50];
    int age;
    char grade[30];
    char major[50];
};

struct Teacher {
    char id[20];
    char name[50];
    int age;
    char subject[50];
};

//GLOBAL VARIABLES 
struct Student students[MAX_STUDENTS];
int studentCount = 0;

struct Teacher teachers[MAX_TEACHERS];
int teacherCount = 0;

//  STUDENT FUNCTION DECLARATIONS 
void studentMenu();
void addStudent();
void displayStudents();
void updateStudent();
void removeStudent();
void searchStudent();
int findStudentIndex(char id[]);
void saveStudentsToFile();
void loadStudentsFromFile();
void runStudentManagement();

//  TEACHER FUNCTION DECLARATIONS 
void teacherMenu();
void addTeacher();
void displayTeachers();
void updateTeacher();
void removeTeacher();
void searchTeacher();
int findTeacherIndex(char id[]);
void saveTeachersToFile();
void loadTeachersFromFile();
void runTeacherManagement();

//  MAIN MENU 
void mainMenu() {
    int choice;
    do {
        printf("\n \033[1;33m===== DPU SCHOOL MANAGEMENT SYSTEM =====\033[0m\n");
        printf("\033[1;36m1. Student Management\033[0m\n");
        printf("\033[1;36m2. Teacher Management\033[0m\n");
        printf("\033[1;36m0. Exit Program\033[0m\n");
        printf("\033[1;33m=====================================\033[0m\n");
        printf("\033[1;35mEnter your choice: \033[0m");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                runStudentManagement();
                break;
            case 2:
                runTeacherManagement();
                break;
            case 0:
                printf("\033[1;34mGoodbye!\n\033[0m");
                break;
            default:
                printf("\033[1;31mInvalid choice! Try again.\033[0m\n");
        }
    } while (choice != 0);
}

//  MAIN FUNCTION 
int main() {
    mainMenu();
    return 0;
}

// STUDENT MANAGEMENT 
void runStudentManagement() {
    int choice;
    loadStudentsFromFile();

    do {
        studentMenu();
        printf("\033[1;35mEnter your choice: \033[0m");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: updateStudent(); break;
            case 4: removeStudent(); break;
            case 5: searchStudent(); break;
            case 0:
                printf("\033[1;32mSaving data and returning to main menu...\n\033[0m");
                saveStudentsToFile();
                break;
            default: printf("\033[1;31mInvalid choice!\033[0m\n");
        }
    } while (choice != 0);
}

void studentMenu() {
    printf("\n\033[1;33m===== Student Management =====\033[0m\n");
    printf("\033[1;36m1. Add Student\033[0m\n");
    printf("\033[1;36m2. Display Students\033[0m\n");
    printf("\033[1;36m3. Update Student\033[0m\n");
    printf("\033[1;36m4. Remove Student\033[0m\n");
    printf("\033[1;36m5. Search Student\033[0m\n");
    printf("\033[1;36m0. Back to Main Menu\033[0m\n");
    printf("\033[1;33m=================================\033[0m\n");
}

int findStudentIndex(char id[]) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, id) == 0) return i;
    }
    return -1;
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("\033[1;31mCannot add more students. Limit reached!\033[0m\n");
        return;
    }

    struct Student s;
    printf("\033[1;35mEnter Student ID: \033[0m");
    fgets(s.id, sizeof(s.id), stdin); s.id[strcspn(s.id, "\n")] = 0;

    printf("\033[1;35mEnter Name: \033[0m");
    fgets(s.name, sizeof(s.name), stdin); s.name[strcspn(s.name, "\n")] = 0;

    printf("\033[1;35mEnter Age: \033[0m");
    scanf("%d", &s.age); getchar();

    printf("\033[1;35mEnter Grade (e.g., First Year, Master, PhD): \033[0m");
    fgets(s.grade, sizeof(s.grade), stdin); s.grade[strcspn(s.grade, "\n")] = 0;

    printf("\033[1;35mEnter Major: \033[0m");
    fgets(s.major, sizeof(s.major), stdin); s.major[strcspn(s.major, "\n")] = 0;

    students[studentCount++] = s;
    saveStudentsToFile();
    printf("\033[1;32mStudent added successfully!\033[0m\n");
}

void displayStudents() {
    if (studentCount == 0) {
        printf("\033[1;31mNo students to display.\033[0m\n");
        return;
    }
    printf("\n\033[1;34m--- Student List ---\033[0m\n");
    for (int i = 0; i < studentCount; i++) {
        printf("[%d] ID: %s | Name: %s | Age: %d | Grade: %s | Major: %s\n",
               i + 1, students[i].id, students[i].name, students[i].age,
               students[i].grade, students[i].major);
    }
}

void updateStudent() {
    char id[20];
    printf("\033[1;35mEnter Student ID to update: \033[0m");
    fgets(id, sizeof(id), stdin); id[strcspn(id, "\n")] = 0;

    int index = findStudentIndex(id);
    if (index == -1) {
        printf("\033[1;31mStudent not found!\033[0m\n");
        return;
    }

    struct Student *s = &students[index];
    char buffer[50];

    printf("\033[1;35mEnter new name (leave blank to keep current): \033[0m");
    fgets(buffer, sizeof(buffer), stdin); buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(s->name, buffer);

    printf("\033[1;35mEnter new age (0 to keep current): \033[0m");
    int newAge; scanf("%d", &newAge); getchar();
    if (newAge > 0) s->age = newAge;

    printf("\033[1;35mEnter new grade (leave blank to keep current): \033[0m");
    fgets(buffer, sizeof(buffer), stdin); buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(s->grade, buffer);

    printf("\033[1;35mEnter new major (leave blank to keep current): \033[0m");
    fgets(buffer, sizeof(buffer), stdin); buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(s->major, buffer);

    saveStudentsToFile();
    printf("\033[1;32mStudent updated successfully!\033[0m\n");
}

void removeStudent() {
    char id[20];
    printf("\033[1;35mEnter Student ID to remove: \033[0m");
    fgets(id, sizeof(id), stdin); id[strcspn(id, "\n")] = 0;

    int index = findStudentIndex(id);
    if (index == -1) {
        printf("\033[1;31mStudent not found!\033[0m\n");
        return;
    }

    for (int i = index; i < studentCount - 1; i++)
        students[i] = students[i + 1];
    studentCount--;

    saveStudentsToFile();
    printf("\033[1;32mStudent removed successfully!\033[0m\n");
}

void searchStudent() {
    char query[50];
    printf("\033[1;35mEnter search keyword: \033[0m");
    fgets(query, sizeof(query), stdin); query[strcspn(query, "\n")] = 0;

    printf("\n\033[1;34m--- Search Results ---\033[0m\n");
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strstr(students[i].id, query) || strstr(students[i].name, query) ||
            strstr(students[i].grade, query) || strstr(students[i].major, query)) {
            printf("[%d] ID: %s | Name: %s | Age: %d | Grade: %s | Major: %s\n",
                   i + 1, students[i].id, students[i].name, students[i].age,
                   students[i].grade, students[i].major);
            found = 1;
        }
    }
    if (!found) printf("\033[1;31mNo students found.\033[0m\n");
}

void saveStudentsToFile() {
    FILE *fp = fopen(STUDENT_FILE, "w");
    if (!fp) { printf("\033[1;31mError saving file!\033[0m\n"); return; }
    for (int i = 0; i < studentCount; i++)
        fprintf(fp, "%s,%s,%d,%s,%s\n",
                students[i].id, students[i].name, students[i].age,
                students[i].grade, students[i].major);
    fclose(fp);
}

void loadStudentsFromFile() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) return;
    struct Student s;
    while (fscanf(fp, "%[^,],%[^,],%d,%[^,],%[^\n]\n",
                  s.id, s.name, &s.age, s.grade, s.major) == 5)
        students[studentCount++] = s;
    fclose(fp);
}

// TEACHER MANAGEMENT 
void runTeacherManagement() {
    int choice;
    loadTeachersFromFile();

    do {
        teacherMenu();
        printf("\033[1;35mEnter your choice: \033[0m");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addTeacher(); break;
            case 2: displayTeachers(); break;
            case 3: updateTeacher(); break;
            case 4: removeTeacher(); break;
            case 5: searchTeacher(); break;
            case 0:
                printf("\033[1;32mSaving data and returning to main menu...\033[0m\n");
                saveTeachersToFile();
                break;
            default: printf("\033[1;31mInvalid choice!\033[0m\n");
        }
    } while (choice != 0);
}

void teacherMenu() {
    printf("\n\033[1;33m===== DPU Teacher Management =====\033[0m\n");
    printf("\033[1;36m1. Add Teacher\033[0m\n");
    printf("\033[1;36m2. Display Teachers\033[0m\n");
    printf("\033[1;36m3. Update Teacher\033[0m\n");
    printf("\033[1;36m4. Remove Teacher\033[0m\n");
    printf("\033[1;36m5. Search Teacher\033[0m\n");
    printf("\033[1;36m0. Back to Main Menu\033[0m\n");
    printf("\033[1;33m=================================\033[0m\n");
}

int findTeacherIndex(char id[]) {
    for (int i = 0; i < teacherCount; i++) {
        if (strcmp(teachers[i].id, id) == 0) return i;
    }
    return -1;
}

void addTeacher() {
    if (teacherCount >= MAX_TEACHERS) {
        printf("\033[1;31mCannot add more teachers.\033[0m\n");
        return;
    }

    struct Teacher t;
    printf("\033[1;35mEnter Teacher ID: \033[0m");
    fgets(t.id, sizeof(t.id), stdin); t.id[strcspn(t.id, "\n")] = 0;

    printf("\033[1;35mEnter Name: \033[0m");
    fgets(t.name, sizeof(t.name), stdin); t.name[strcspn(t.name, "\n")] = 0;

    printf("\033[1;35mEnter Age: \033[0m");
    scanf("%d", &t.age); getchar();

    printf("\033[1;35mEnter Subject: \033[0m");
    fgets(t.subject, sizeof(t.subject), stdin); t.subject[strcspn(t.subject, "\n")] = 0;

    teachers[teacherCount++] = t;
    saveTeachersToFile();
    printf("\033[1;32mTeacher added successfully!\033[0m\n");
}

void displayTeachers() {
    if (teacherCount == 0) {
        printf("\033[1;31mNo teachers to display.\033[0m\n");
        return;
    }
    printf("\n\033[1;34m--- Teacher List ---\033[0m\n");
    for (int i = 0; i < teacherCount; i++) {
        printf("[%d] ID: %s | Name: %s | Age: %d | Subject: %s\n",
               i + 1, teachers[i].id, teachers[i].name,
               teachers[i].age, teachers[i].subject);
    }
}

void updateTeacher() {
    char id[20];
    printf("\033[1;35mEnter Teacher ID to update: \033[0m");
    fgets(id, sizeof(id), stdin); id[strcspn(id, "\n")] = 0;

    int index = findTeacherIndex(id);
    if (index == -1) {
        printf("\033[1;31mTeacher not found!\033[0m\n");
        return;
    }

    struct Teacher *t = &teachers[index];
    char buffer[50];

    printf("\033[1;35mEnter new name (leave blank to keep current): \033[0m");
    fgets(buffer, sizeof(buffer), stdin); buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(t->name, buffer);

    printf("\033[1;35mEnter new age (0 to keep current): \033[0m");
    int newAge; scanf("%d", &newAge); getchar();
    if (newAge > 0) t->age = newAge;

    printf("\033[1;35mEnter new subject (leave blank to keep current): \033[0m");
    fgets(buffer, sizeof(buffer), stdin); buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(t->subject, buffer);

    saveTeachersToFile();
    printf("\033[1;32mTeacher updated successfully!\033[0m\n");
}

void removeTeacher() {
    char id[20];
    printf("\033[1;35mEnter Teacher ID to remove: \033[0m");
    fgets(id, sizeof(id), stdin); id[strcspn(id, "\n")] = 0;

    int index = findTeacherIndex(id);
    if (index == -1) {
        printf("\033[1;31mTeacher not found!\033[0m\n");
        return;
    }

    for (int i = index; i < teacherCount - 1; i++)
        teachers[i] = teachers[i + 1];
    teacherCount--;

    saveTeachersToFile();
    printf("\033[1;32mTeacher removed successfully!\033[0m\n");
}

void searchTeacher() {
    char query[50];
    printf("\033[1;35mEnter search keyword: \033[0m");
    fgets(query, sizeof(query), stdin); query[strcspn(query, "\n")] = 0;

    printf("\n\033[1;34m--- Search Results ---\033[0m\n");
    int found = 0;
    for (int i = 0; i < teacherCount; i++) {
        if (strstr(teachers[i].id, query) || strstr(teachers[i].name, query) ||
            strstr(teachers[i].subject, query)) {
            printf("[%d] ID: %s | Name: %s | Age: %d | Subject: %s\n",
                   i + 1, teachers[i].id, teachers[i].name,
                   teachers[i].age, teachers[i].subject);
            found = 1;
        }
    }
    if (!found) printf("\033[1;31mNo teachers found.\033[0m\n");
}

void saveTeachersToFile() {
    FILE *fp = fopen(TEACHER_FILE, "w");
    if (!fp) { printf("\033[1;31mError saving file!\033[0m\n"); return; }
    for (int i = 0; i < teacherCount; i++)
        fprintf(fp, "%s,%s,%d,%s\n",
                teachers[i].id, teachers[i].name, teachers[i].age,
                teachers[i].subject);
    fclose(fp);
}

void loadTeachersFromFile() {
    FILE *fp = fopen(TEACHER_FILE, "r");
    if (!fp) return;
    struct Teacher t;
    while (fscanf(fp, "%[^,],%[^,],%d,%[^\n]\n",
                  t.id, t.name, &t.age, t.subject) == 4)
        teachers[teacherCount++] = t;
    fclose(fp);
}

