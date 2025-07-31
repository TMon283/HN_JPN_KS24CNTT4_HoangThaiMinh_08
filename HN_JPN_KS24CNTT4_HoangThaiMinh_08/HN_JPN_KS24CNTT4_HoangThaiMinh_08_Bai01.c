#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Operation {
    char string[100];
    char timestamp[50];
    struct Operation* next;
} Operation;

typedef struct SinglyNode {
    Operation operation;
    struct SinglyNode* next;
}SinglyNode;

typedef struct Stack {
    Operation* head;
    int top;
    int capacity;
} Stack;

SinglyNode* createSinglyNode(Operation operation) {
    SinglyNode* newNode = (SinglyNode*)malloc(sizeof(SinglyNode));
    newNode->operation = operation;
    newNode->next = NULL;
    return newNode;
}

Stack* createStack(int capacity) {
    Stack* newStack = (Stack*)malloc(sizeof(Stack));
    newStack->top = -1;
    newStack->capacity = capacity;
    return newStack;
}

int isStackEmpty(Stack* stack) {
    if (stack->top == -1) {
        return 1;
    }
    return 0;
}

int isStackFull(Stack* stack) {
    if (stack->top == stack->capacity - 1) {
        return 1;
    }
    return 0;
}

void push(Stack* stack, Operation operation) {
    if (isStackFull(stack)) {
        printf("Stack is full\n");
        return;
    }
    Operation* newOp = (Operation*)malloc(sizeof(Operation));
    strcpy(newOp->string, operation.string);
    newOp->next = stack->head;
    stack->head = newOp;
    stack->top++;
}

Operation pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    Operation* temp = stack->head;
    stack->head = temp->next;
    stack->top--;
    Operation result;
    strcpy(result.string, temp->string);
    free(temp);
    return result;
}

void clear(Stack* stack) {
    while (!isStackEmpty(stack)) {
        pop(stack);
    }
}

void show(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    Operation* current = stack->head;
    while (current->next != NULL) {
        printf("%s\n", current->string);
        current = current->next;
    }
}

int main() {
    int choice;
    Stack* Backward = createStack(100);
    Stack* Forward = createStack(100);
    Stack* History = createStack(100);
    Operation operation;
    do {
        printf("\n------WEB HISTORY------\n");
        printf("1. VISIT url\n");
        printf("2. BACKWARD\n");
        printf("3. FORWARD\n");
        printf("4. CURRENT\n");
        printf("5. HISTORY\n");
        printf("6. CLEAR HISTORY\n");
        printf("7. EXIT\n");
        printf("Enter your choice:");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter url:");
                scanf("%s", operation.string);
                push(Backward, operation);
                push(History, operation);
                clear(Forward);
                break;
            case 2:
                Operation backward = pop(Backward);
                if (strcmp (backward.string, "") != 0) {
                    push(Forward, backward);
                    printf("Backward: %s\n", backward.string);
                } else {
                    printf("Backward is empty\n");
                }
                break;
            case 3:
                Operation forward = pop(Forward);
                if (strcmp (forward.string, "") != 0) {
                    push(Backward, forward);
                    printf("Forward: %s\n", forward.string);
                } else {
                    printf("Forward is empty\n");
                }
                break;
            case 4:
                Operation current = pop(History);
                if (strcmp (current.string, "") != 0) {
                    printf("%s\n", current.string);
                }
                break;
            case 5:
                printf("HISTORY\n");
                show(History);
                break;
            case 6:
                clear(History);
                break;
            case 7:
                printf("Exit...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 7);
    return 0;
}