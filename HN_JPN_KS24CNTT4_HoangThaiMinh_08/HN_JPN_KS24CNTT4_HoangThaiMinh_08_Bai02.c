#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int id;
    char name[100];
    int age;
} Student;

typedef struct Node {
    Student student;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct TreeNode {
    Node* node;
    struct TreeNode* next;
} TreeNode;

typedef struct {
    TreeNode* front;
    TreeNode* rear;
} Queue;

Node* createNode(Student student) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->student = student;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, Node* node) {
    TreeNode* tnode = (TreeNode*)malloc(sizeof(TreeNode));
    tnode->node = node;
    tnode->next = NULL;
    if (!q->rear) {
        q->front = q->rear = tnode;
    } else {
        q->rear->next = tnode;
        q->rear = tnode;
    }
}

Node* dequeue(Queue* q) {
    if (!q->front) return NULL;
    TreeNode* temp = q->front;
    Node* result = temp->node;
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return result;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

void freeQueue(Queue* q) {
    TreeNode* cur = q->front;
    while (cur) {
        TreeNode* nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    free(q);
}

int exists(Node* root, int id) {
    if (!root) return 0;
    if (root->student.id == id) return 1;
    return exists(root->left, id) || exists(root->right, id);
}

void insertNodeToTree(Node** rootRef, Student student) {
    if (*rootRef == NULL) {
        *rootRef = createNode(student);
        return;
    }
    if (exists(*rootRef, student.id)) {
        printf("Student already exists\n");
        return;
    }
    Queue* q = createQueue();
    enqueue(q, *rootRef);
    while (!isEmpty(q)) {
        Node* cur = dequeue(q);
        if (!cur->left) {
            cur->left = createNode(student);
            break;
        } else {
            enqueue(q, cur->left);
        }
        if (!cur->right) {
            cur->right = createNode(student);
            break;
        } else {
            enqueue(q, cur->right);
        }
    }
    freeQueue(q);
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("ID:%d\n", root->student.id);
    printf("Name:%s\n", root->student.name);
    printf("Age:%d\n\n", root->student.age);
    inorder(root->right);
}

Node* searchStudent(Node* root, int id) {
    if (!root) return NULL;
    if (root->student.id == id) return root;
    Node* leftRes = searchStudent(root->left, id);
    if (leftRes) return leftRes;
    return searchStudent(root->right, id);
}

void deleteDeepestNode(Node* root, Node* delNode) {
    Queue* q = createQueue();
    enqueue(q, root);
    Node* cur = NULL;
    while (!isEmpty(q)) {
        cur = dequeue(q);
        if (cur->left) {
            if (cur->left == delNode) {
                free(cur->left);
                cur->left = NULL;
                break;
            } else {
                enqueue(q, cur->left);
            }
        }
        if (cur->right) {
            if (cur->right == delNode) {
                free(cur->right);
                cur->right = NULL;
                break;
            } else {
                enqueue(q, cur->right);
            }
        }
    }
    freeQueue(q);
}

Node* deleteStudent(Node* root, int id) {
    if (!root) return NULL;
    if (!root->left && !root->right) {
        if (root->student.id == id) {
            free(root);
            return NULL;
        }
        return root;
    }
    Queue* q = createQueue();
    enqueue(q, root);
    Node* keyNode = NULL;
    Node* cur = NULL;
    while (!isEmpty(q)) {
        cur = dequeue(q);
        if (cur->student.id == id) {
            keyNode = cur;
        }
        if (cur->left) enqueue(q, cur->left);
        if (cur->right) enqueue(q, cur->right);
    }
    if (keyNode) {
        keyNode->student = cur->student;
        deleteDeepestNode(root, cur);
    } else {
        printf("Student not found\n");
    }
    freeQueue(q);
    return root;
}

int main() {
    Node* root = NULL;
    int choice;
    Student student;
    int nextId = 1;

    do {
        printf("\n----- STUDENT MANAGER -----\n\n");
        printf("1. Add Student\n");
        printf("2. Show Student List\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                student.id = nextId++;
                printf("Enter Student Name: ");
                scanf("%s", student.name);
                printf("Enter Student Age: ");
                scanf("%d", &student.age);
                insertNodeToTree(&root, student);
                break;
            }
            case 2:
                printf("\n--- STUDENT LIST ---\n\n");
                inorder(root);
                break;
            case 3: {
                int searchId;
                printf("Enter Student ID to search: ");
                scanf("%d", &searchId);
                Node* found = searchStudent(root, searchId);
                if (found) {
                    printf("\nStudent Found:\n");
                    printf("ID:%d\n", found->student.id);
                    printf("Name:%s\n", found->student.name);
                    printf("Age:%d\n", found->student.age);
                } else {
                    printf("Student not found\n");
                }
                break;
            }
            case 4: {
                int deleteId;
                printf("Enter Student ID to delete: ");
                scanf("%d", &deleteId);
                root = deleteStudent(root, deleteId);
                break;
            }
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 5);

    return 0;
}
