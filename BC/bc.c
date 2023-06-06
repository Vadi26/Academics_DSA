#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

typedef struct Node {
    int digit;
    struct Node* next;
} Node;

Node* createNode(int digit) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->digit = digit;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(Node** head, int digit) {
    Node* newNode = createNode(digit);
    newNode->next = *head;
    *head = newNode;
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d", current->digit);
        current = current->next;
    }
    printf("\n");
}

Node* addNumbers(Node* num1, Node* num2) {
    Node* result = NULL;
    Node* current = NULL;
    int carry = 0;

    while (num1 != NULL || num2 != NULL) {
        int sum = carry;
        if (num1 != NULL) {
            sum += num1->digit;
            num1 = num1->next;
        }
        if (num2 != NULL) {
            sum += num2->digit;
            num2 = num2->next;
        }

        carry = sum / 10;
        int digit = sum % 10;
        Node* newNode = createNode(digit);

        if (result == NULL) {
            result = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    if (carry > 0) {
        Node* newNode = createNode(carry);
        current->next = newNode;
    }

    return result;
}

Node* subtractNumbers(Node* num1, Node* num2) {
    Node* result = NULL;
    Node* current = NULL;
    int borrow = 0;

    while (num1 != NULL || num2 != NULL) {
        int diff = borrow;
        if (num1 != NULL) {
            diff += num1->digit;
            num1 = num1->next;
        }
        if (num2 != NULL) {
            diff -= num2->digit;
            num2 = num2->next;
        }

        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }

        Node* newNode = createNode(diff);

        if (result == NULL) {
            result = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    // Remove leading zeros
    while (result->next != NULL && result->digit == 0) {
        Node* temp = result;
        result = result->next;
        free(temp);
    }

    return result;
}

int main() {
    char num1String[MAX_LENGTH];
    char num2String[MAX_LENGTH];

    printf("Enter the first number: ");
    scanf("%s", num1String);
    printf("Enter the second number: ");
    scanf("%s", num2String);

    int num1Length = strlen(num1String);
    int num2Length = strlen(num2String);

    // Create linked list for num1
    Node* num1 = NULL;
    for (int i = num1Length - 1; i >= 0; i--) {
        int digit = num1String[i] - '0';
        insertAtBeginning(&num1, digit);
    }

    // Create linked list for num2
    Node* num2 = NULL;
    for (int i = num2Length - 1; i >= 0; i--) {
        int digit = num2String[i] - '0';
        insertAtBeginning(&num2, digit);
    }

    // Perform addition
    Node* sum = addNumbers(num1, num2);
    printf("Sum: ");
    printList(sum);

    // Perform subtraction
    Node* difference = subtractNumbers(num1, num2);
    printf("Difference: ");
    printList(difference);

    // Free memory
    freeList(num1);
    freeList(num2);
    freeList(sum);
    freeList(difference);

    return 0;
}
