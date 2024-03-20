#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "kalkulaator-calc.h"
#include "kalkulaator-window.h"

void type__file(const gchar *content)
{
    const char *filepath = "Desktop/Kalk/Kalkulaator_GTK4/src/History.txt";
    FILE *fOut = fopen(filepath, "at+");
    if (fOut == NULL)
    {
      g_print("Error opening file for writing\n");
      return;
    }

    // Write content to the file
    fprintf(fOut, "%s", content);

    // Close the file
    fclose(fOut);

    g_print("Content written to file.\n");
}

// Function implementations
void initialize(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return (s->top == -1);
}

void push(Stack *s, double value) {
    if (s->top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    s->items[++(s->top)] = value;
}

double pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->items[(s->top)--];
}

int precedence(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        case 'l':
        case 's':
            return 4;
        default:
            return 0;
    }
}

double applyOperator(double op1, double op2, char operatorr) {
    switch(operatorr) {
        case '+':
            return op1 + op2;
        case '-':
            return op1 - op2;
        case '*':
            return op1 * op2;
        case '/':
            if (op2 == 0) {
                printf("Division by zero\n");
                exit(EXIT_FAILURE);
            }
            return op1 / op2;
        case '^':
            return pow(op1, op2);
        case 'l':
            return log10(op1);
        case 's':
            return sqrt(op1);
        default:
            printf("Invalid operator\n");
            exit(EXIT_FAILURE);
    }
}

double evaluateExpression(char *expr, int start, int end) {
    Stack operator_stack;
    Stack operand_stack;
    initialize(&operator_stack);
    initialize(&operand_stack);
    for (int i = start; i < end; i++) {
        if (expr[i] == ',') {
            expr[i] = '.';
        }
    }
    int i = start;
    while (i < end) {
        if (expr[i] == ' ') {
            i++;
            continue;
        }
        if (isdigit(expr[i]) || expr[i] == '.') {
            char* endptr;
            double operand = strtod(&expr[i], &endptr); // Convert string to double
            push(&operand_stack, operand);
            i = endptr - expr - 1; // Move i to the end of the parsed number
        }
        else if (expr[i] == '(') {
            int j = i + 1;
            int count = 1; // Parentheses count
            while (count != 0) {
                if (expr[j] == '(') count++;
                else if (expr[j] == ')') count--;
                j++;
            }
            double result = evaluateExpression(expr, i + 1, j - 1);
            push(&operand_stack, result);
            i = j - 1; // Adjust i for next loop increment
        }
        else if (expr[i] == ')' || expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '^') {
            while (!isEmpty(&operator_stack) && precedence(operator_stack.items[operator_stack.top]) >= precedence(expr[i])) {
                double op2 = pop(&operand_stack);
                double op1 = pop(&operand_stack);
                char operator = pop(&operator_stack);
                push(&operand_stack, applyOperator(op1, op2, operator));
            }
            push(&operator_stack, expr[i]);
        }
        else if (expr[i] == 'L') {
            int j = i + 1; // Move past the 'L'
            int base = 0;
            while (isdigit(expr[j])) {
                base = base * 10 + (expr[j] - '0');
                j++;
            }
            if (expr[j] != '(') {
                printf("Invalid expression: unable to find opening parenthesis for logarithm\n");
                exit(EXIT_FAILURE);
            }
            int k = j + 1;
            int count = 1; // Parentheses count
            while (count != 0) {
                if (expr[k] == '(') count++;
                else if (expr[k] == ')') count--;
                k++;
            }
            double operand = evaluateExpression(expr, j + 1, k - 1);

            double result = applyCustomLog(operand, base);
            push(&operand_stack, result);
            i = k; // Move i past the processed logarithm expression
        }
        else if (expr[i] == 'l' || expr[i] == 'r') {
            int j = i + 1;
            while (expr[j] != '(') j++;
            int k = j + 1;
            int count = 1; // Parentheses count
            while (count != 0) {
                if (expr[k] == '(') count++;
                else if (expr[k] == ')') count--;
                k++;
            }
            double arg = evaluateExpression(expr, j + 1, k - 1);
            double result = 0;
            if (expr[i] == 'l') {
                result = log10(arg);
            } else if (expr[i] == 'r') {
                result = sqrt(arg);
            }
            push(&operand_stack, result);
            i = k - 1; // Adjust i for next loop increment
        }

        i++;
    }

    while (!isEmpty(&operator_stack)) {
        char operator = pop(&operator_stack);
        double op2 = pop(&operand_stack);
        double op1 = pop(&operand_stack);
        push(&operand_stack, applyOperator(op1, op2, operator));
    }

    return pop(&operand_stack);
}

double evaluateInfix(char *expr) {
    return evaluateExpression(expr, 0, strlen(expr));
}

double applyCustomLog(double operand, double base) {
    if (operand <= 0 || base <= 0 || base == 1) {
        printf("Invalid arguments for logarithm\n");
        exit(EXIT_FAILURE);
    }
    return log2(operand) / log2(base);
}

gchar *CalcMain(char *expr) {
    double result = evaluateInfix(expr);

    return g_strdup_printf("%g", result);
}

