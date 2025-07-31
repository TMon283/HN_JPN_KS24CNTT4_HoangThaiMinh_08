#include<stdio.h>
#include<stdlib.h>

typedef struct Student {
    int id;
    char name[100];
    int age;
} Student;

typedef struct Node {
    Student student;
    struct Node* left;
    struct Node* right;
}Node;

typedef struct TreeNode {
    Node* root;
    struct TreeNode* next;
}TreeNode;

typedef struct {
    TreeNode* front;
    TreeNode* rear;
} Queue;

Node* createNode(Student student) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->student = student;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Queue* createQueue() {
    Queue* newQueue = (Queue*)malloc(sizeof(Queue));
    newQueue->front = NULL;
    newQueue->rear = NULL;
    return newQueue;
}

void enqueue(Queue* queue, Node* node) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->root = node;
    newNode->next = NULL;
    if (!queue->rear) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

Node* dequeue(Queue* queue) {
    if (!queue->front) return NULL;
    TreeNode* temp = queue->front;
    Node* node = temp->root;
    queue->front = queue->front->next;
    queue->rear = queue->rear->next;
    free(temp);
    free(node);
    return node;
}

int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

int exists(Node* root, Student student) {
    if (!root) return 0;
    if (root->student.id == student.id) return 1;
    return exists(root->left, student) || exists(root->right, student);
}

void insertNodeToTree(Node** rootRef, Student student) {
    if (*rootRef == NULL) {
        *rootRef = createNode(student);
        return;
    }
    if (exists(*rootRef, student)) {
        printf("Student already exists\n");
        return;
    }
    Queue* queue = createQueue();
    enqueue(queue, *rootRef);
    while (!isEmpty(queue)) {
        Node* current = dequeue(queue);
        if (!current->left) {
            current->left = createNode(student);
            break;
        } else {
            enqueue(queue, current->left);
        }
        if (!current->right) {
            current->right = createNode(student);
            break;
        } else {
            enqueue(queue, current->right);
        }
    }
    free(queue);
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("ID:%d\n", root->student.id);
    printf("Name:%s\n", root->student.name);
    printf("Age:%d\n", root->student.age);
    inorder(root->right);
}

int main() {
    int choice;
    Node* root = NULL;
    Student student;
    int id = 1;
    do {
        printf("\n-----STUDENT MANAGER-----\n");
        printf("1. Add Student\n");
        printf("2. Show Student List\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice:");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                student.id = id++;
                printf("Enter Student Name:");
                scanf("%s", student.name);
                printf("Enter Student Age:");
                scanf("%d", &student.age);
                insertNodeToTree(&root, student);
                break;
            case 2:
                printf("INORDER\n");
                inorder(root);
                break;
            case 3:

                break;
            case 4:
                int deleteId;
                printf("Enter Student ID to delete:");
                scanf("%d", &deleteId);

            case 5:
                printf("Exit...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }while (choice != 5);
    return 0;
}