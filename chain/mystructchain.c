#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义学生信息的链表结点类型
typedef struct Student {
    int id;
    char name[50];
    char className[50];
    char major[50];
    float scores[3];
    struct Student* next;
} Student;

// 创建一个新的学生结点
Student* CreateNode(int id, char* name, char* className, char* major, float scores[3]) {
    Student* newNode = (Student*)malloc(sizeof(Student));
    newNode->id = id;
    strcpy(newNode->name, name);
    strcpy(newNode->className, className);
    strcpy(newNode->major, major);
    for (int i = 0; i < 3; i++) {
        newNode->scores[i] = scores[i];
    }
    newNode->next = NULL;
    return newNode;
}

// 按学号由小到大建立有序链表
void CreateList(Student** head, int n) {
    for (int i = 0; i < n; i++) {
        int id;
        char name[50], className[50], major[50];
        float scores[3];
        printf("输入第%d个学生的信息（学号 姓名 班级 专业 成绩1 成绩2 成绩3）：\n", i + 1);
        scanf("%d %s %s %s %f %f %f", &id, name, className, major, &scores[0], &scores[1], &scores[2]);
        Student* newNode = CreateNode(id, name, className, major, scores);
        if (*head == NULL || (*head)->id > id) {
            newNode->next = *head;
            *head = newNode;
        } else {
            Student* current = *head;
            while (current->next != NULL && current->next->id < id) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }
}

// 格式化输出学生信息
void Output(Student* student) {
    if (student) {
        printf("学号: %d, 姓名: %s, 班级: %s, 专业: %s, 成绩: %.2f, %.2f, %.2f\n",
               student->id, student->name, student->className, student->major,
               student->scores[0], student->scores[1], student->scores[2]);
    }
}

// 将学生信息存入文件
void Save(Student* student) {
    FILE* file = fopen("student_info.txt", "a");
    if (file) {
        fprintf(file, "%d %s %s %s %.2f %.2f %.2f\n", student->id, student->name, student->className,
                student->major, student->scores[0], student->scores[1], student->scores[2]);
        fclose(file);
    } else {
        printf("文件打开失败！\n");
    }
}

// 从文件中随机读取某个学生的信息
void Fetch() {
    FILE* file = fopen("student_info.txt", "r");
    if (file) {
        int id;
        char name[50], className[50], major[50];
        float scores[3];
        while (fscanf(file, "%d %s %s %s %f %f %f", &id, name, className, major, &scores[0], &scores[1], &scores[2]) != EOF) {
            printf("学号: %d, 姓名: %s, 班级: %s, 专业: %s, 成绩: %.2f, %.2f, %.2f\n",
                   id, name, className, major, scores[0], scores[1], scores[2]);
        }
        fclose(file);
    } else {
        printf("文件打开失败！\n");
    }
}

// 查找指定学号的学生
Student* Search_num(Student* head, int id) {
    Student* current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// 插入学生信息
void InsertList(Student** head, int id, char* name, char* className, char* major, float scores[3]) {
    Student* newNode = CreateNode(id, name, className, major, scores);
    if (*head == NULL || (*head)->id > id) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Student* current = *head;
        while (current->next != NULL && current->next->id < id) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// 删除指定学号的学生
void Delete_num(Student** head, int id) {
    Student* current = *head;
    Student* previous = NULL;
    while (current != NULL && current->id != id) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("没有找到学号为 %d 的学生。\n", id);
        return;
    }
    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }
    free(current);
    printf("已删除学号为 %d 的学生。\n", id);
}

// 查找某个专业某门课程成绩小于某个分数的学生
void Search_major_subject_score(Student* head, char* major, int subjectIndex, float score) {
    Student* current = head;
    while (current != NULL) {
        if (strcmp(current->major, major) == 0 && current->scores[subjectIndex] < score) {
            Output(current);
        }
        current = current->next;
    }
}

// 删除某个专业某门课程成绩小于某个分数的学生
void Delete_major_subject(Student** head, char* major, int subjectIndex, float score) {
    Student* current = *head;
    Student* previous = NULL;
    while (current != NULL) {
        if (strcmp(current->major, major) == 0 && current->scores[subjectIndex] < score) {
            if (previous == NULL) {
                *head = current->next;
                free(current);
                current = *head;
            } else {
                previous->next = current->next;
                free(current);
                current = previous->next;
            }
        } else {
            previous = current;
            current = current->next;
        }
    }
}

void menu() {
    printf("请选择操作：\n");
    printf("1. 创建学生链表\n");
    printf("2. 输出学生信息\n");
    printf("3. 保存学生信息到文件\n");
    printf("4. 从文件中读取学生信息\n");
    printf("5. 查找指定学号的学生\n");
    printf("6. 插入学生信息\n");
    printf("7. 删除指定学号的学生\n");
    printf("8. 查找某专业某门课程成绩小于某分数的学生\n");
    printf("9. 删除某专业某门课程成绩小于某分数的学生\n");
    printf("0. 退出\n");
}

int main() {
    Student* head = NULL;
    int choice;
    while (1) {
        menu();
        scanf("%d", &choice);
        if (choice == 0) break;
        switch (choice) {
            case 1: {
                int n;
                printf("输入学生数量：\n");
                scanf("%d", &n);
                CreateList(&head, n);
                break;
            }
            case 2: {
                Student* current = head;
                while (current != NULL) {
                    Output(current);
                    current = current->next;
                }
                break;
            }
            case 3: {
                Student* current = head;
                while (current != NULL) {
                    Save(current);
                    current = current->next;
                }
                break;
            }
            case 4: {
                Fetch();
                break;
            }
            case 5: {
                int id;
                printf("输入要查找的学生学号：\n");
                scanf("%d", &id);
                Student* student = Search_num(head, id);
                if (student) {
                    Output(student);
                } else {
                    printf("未找到学号为 %d 的学生。\n", id);
                }
                break;
            }
            case 6: {
                int id;
                char name[50], className[50], major[50];
                float scores[3];
                printf("输入学生信息（学号 姓名 班级 专业 成绩1 成绩2 成绩3）：\n");
                scanf("%d %s %s %s %f %f %f", &id, name, className, major, &scores[0], &scores[1], &scores[2]);
                InsertList(&head, id, name, className, major, scores);
                break;
            }
            case 7: {
                int id;
                printf("输入要删除的学生学号：\n");
                scanf("%d", &id);
                Delete_num(&head, id);
                break;
            }
            case 8: {
                char major[50];
                int subjectIndex;
                float score;
                printf("输入专业、课程索引（0, 1, 2）和分数：\n");
                scanf("%s %d %f", major, &subjectIndex, &score);
                Search_major_subject_score(head, major, subjectIndex, score);
                break;
            }
            case 9: {
                char major[50];
                int subjectIndex;
                float score;
                printf("输入专业、课程索引（0, 1, 2）和分数：\n");
                scanf("%s %d %f", major, &subjectIndex, &score);
                Delete_major_subject(&head, major, subjectIndex, score);
                break;
            }
            default:
                printf("无效的选择。\n");
        }
    }
    return 0;
}
