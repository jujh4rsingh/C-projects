#include <stdio.h>
#include <ctype.h>  // for isdigit() and isalpha()
#include <stdlib.h> // for exit()

#define MAX 100

// Stack structure
struct Stack {
    int top;
    char items[MAX];
};

// Initialize stack
void initStack(struct Stack *s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(struct Stack *s) {
    return s->top == -1;
}

// Push to stack
void push(struct Stack *s, char c) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    s->items[++(s->top)] = c;
}

// Pop from stack
char pop(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return s->items[(s->top)--];
}

// Peek top of stack
char peek(struct Stack *s) {
    if (isEmpty(s))
        return '\0';
    return s->items[s->top];
}

// Check operator precedence
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Check if character is an operator
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Function to convert infix to postfix
void infixToPostfix(char *infix, char *postfix) {
    struct Stack s;
    initStack(&s);
    int i = 0, k = 0;
    char c;

    while (infix[i] != '\0') {
        c = infix[i];

        // If the character is an operand, add it to the output
        if (isalnum(c)) {
            postfix[k++] = c;
        }
        // If the character is '(', push it onto the stack
        else if (c == '(') {
            push(&s, c);
        }
        // If the character is ')', pop from the stack until '(' is found
        else if (c == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[k++] = pop(&s);
            }
            pop(&s);  // Remove '(' from stack
        }
        // If the character is an operator
        else if (isOperator(c)) {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(c)) {
                postfix[k++] = pop(&s);
            }
            push(&s, c);
        }

        i++;
    }

    // Pop all remaining operators from the stack
    while (!isEmpty(&s)) {
        postfix[k++] = pop(&s);
    }

    postfix[k] = '\0';  // Null-terminate the postfix expression
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
