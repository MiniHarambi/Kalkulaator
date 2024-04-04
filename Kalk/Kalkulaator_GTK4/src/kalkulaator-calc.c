#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "kalkulaator-calc.h"
#include "kalkulaator-window.h"

int error = 0;

void type__file(const gchar *content)
{
    const char *filepath = "History.txt";
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
    }
    s->items[++(s->top)] = value;
}

double pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
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
                error = 4;
            }
            return op1 / op2;
        case '^':
            return pow(op1, op2);
        case 'l':
            return log10(op1);
        case 's':
            return sqrt(op1);
        default:
            error = 1;
            return 0;
    }
}

double evaluateExpression(char *expr, int start, int end, double x, double y) {
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
        else if (expr[i] == 'x')
        {
          double operand = x;
          push(&operand_stack, operand);
        }
        else if (expr[i] == 'y')
        {
          double operand = y;
          push(&operand_stack, operand);
        }
        else if (expr[i] == '(') {
            int j = i + 1;
            int count = 1; // Parentheses count
            while (count != 0) {
                if (expr[j] == '(') count++;
                else if (expr[j] == ')') count--;
                j++;
            }
            double result = evaluateExpression(expr, i + 1, j - 1, x, y);
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
        else if (expr[i] == 'l' && expr[i+1] == 'o' && expr[i+2] == 'g' && expr[i+3] == '_' && isdigit(expr[i+4])) {
            int j = i + 4; // Move past the 'L'
            int base = 0;
            while (isdigit(expr[j])) {
                base = base * 10 + (expr[j] - '0');
                j++;
            }
            int k = j + 1;
          printf("%d", k);
            int count = 1; // Parentheses count
            while (count != 0) {
                if (expr[k] == '(')
                count++;
                else if (expr[k] == ')')
                {
                   count--;
                }
                k++;
            }
            double operand = evaluateExpression(expr, j + 1, k - 1, x, y);
            double result = applyCustomLog(operand, base);
            push(&operand_stack, result);
            i = k; // Move i past the processed logarithm expression
        }
        else if ((expr[i] == 'l' && expr[i+1] == 'o' && expr[i+2] == 'g') ||
                 (expr[i] == 's' && expr[i+1] == 'q' && expr[i+2] == 'r' && expr[i+3] == 't')) {
            int j = i;
            if (expr[i] == 'l' && expr[i+1] == 'o' && expr[i+2] == 'g')
            {
                j = i + 3;
                if (expr[i+3] != '(')
                  error = 2;
            }
            else if (expr[i] == 's' && expr[i+1] == 'q' && expr[i+2] == 'r' && expr[i+3] == 't')
            {
                j = i + 4;
                if (expr[i+4] != '(')
                  error = 5;
            }
            int k = j + 1;
            int count = 1; // Parentheses count
            while (count != 0) {
                if (expr[k] == '(')
                {
                  count++;
                }
                else if (expr[k] == ')')
                {
                  count--;
                }
                k++;
            }
            double arg = evaluateExpression(expr, j + 1, k - 1, x, y);
            double result = 0;
            if (arg < 0)
            {
              error = 10;
            }
            if (expr[i] == 'l' && expr[i+1] == 'o' && expr[i+2] == 'g') {
                result = log10(arg);
            } else if (expr[i] == 's' && expr[i+1] == 'q' && expr[i+2] == 'r' && expr[i+3] == 't') {
                result = sqrt(arg);
            }
            push(&operand_stack, result);
            i = k - 1; // Adjust i for next loop increment
        }

        else if ((expr[i] == 's' && expr[i+1] == 'i' && expr[i+2] == 'n') ||
                 (expr[i] == 'c' && expr[i+1] == 'o' && expr[i+2] == 's') ||
                 (expr[i] == 't' && expr[i+1] == 'a' && expr[i+2] == 'n') ||
                 (expr[i] == 'a' && expr[i+1] == 't' && expr[i+2] == 'a' && expr[i+3] == 'n') ||
                 (expr[i] == 'a' && expr[i+1] == 's' && expr[i+2] == 'i' && expr[i+3] == 'n') ||
                 (expr[i] == 'a' && expr[i+1] == 'c' && expr[i+2] == 'o' && expr[i+3] == 's'))
        {
            int j = i;
          if ((expr[i] == 's' && expr[i+1] == 'i' && expr[i+2] == 'n') ||
                 (expr[i] == 'c' && expr[i+1] == 'o' && expr[i+2] == 's') ||
                 (expr[i] == 't' && expr[i+1] == 'a' && expr[i+2] == 'n'))
            {
              j = i+3;
              if (expr[j] != '(')
                error = 8;
            }
          else if ((expr[i] == 'a' && expr[i+1] == 't' && expr[i+2] == 'a' && expr[i+3] == 'n') ||
                 (expr[i] == 'a' && expr[i+1] == 's' && expr[i+2] == 'i' && expr[i+3] == 'n') ||
                 (expr[i] == 'a' && expr[i+1] == 'c' && expr[i+2] == 'o' && expr[i+3] == 's'))
            {
              j = i + 4;
              if (expr[j] != '(')
                error = 9;
            }
            int k = j + 1;
            int count = 1; // Parentheses count
            while (count != 0) {
                if (expr[k] == '(')
                {
                  count++;
                }
                else if (expr[k] == ')')
                {
                  count--;
                }
                k++;
            }
            double arg = evaluateExpression(expr, j + 1, k - 1, x, y);
            double result = 0;

            if (expr[i] == 'a' && expr[i+1] == 's' && expr[i+2] == 'i' && expr[i+3] == 'n')
            {
              if ((arg > 1)||(arg < -1))
                error = 6;
              result = asin(arg);
              result = (result*180)/M_PI;
            }
            else if (expr[i] == 'a' && expr[i+1] == 'c' && expr[i+2] == 'o' && expr[i+3] == 's')
            {
              if ((arg > 1)||(arg < -1))
                error = 7;
              result = acos(arg);
              result = (result*180)/M_PI;
            }
            else if (expr[i] == 'a' && expr[i+1] == 't' && expr[i+2] == 'a' && expr[i+3] == 'n')
            {
              result = atan(arg);
              result = (result*180)/M_PI;
            }
            else if (expr[i] == 'c' && expr[i+1] == 'o' && expr[i+2] == 's')
            {
              result = cos((arg*M_PI)/180);
            }
            else if (expr[i] == 't' && expr[i+1] == 'a' && expr[i+2] == 'n')
            {
              result = tan((arg*M_PI)/180);
            }
            else if(expr[i] == 's' && expr[i+1] == 'i' && expr[i+2] == 'n')
            {
              result = sin((arg*M_PI)/180);
            }
            push(&operand_stack, result);
            i = k - 1;

        }
        else if((expr[i] == 'p' && expr[i+1] == 'i') || (expr[i] == 'P' && expr[i+1] == 'I'))
        {
          double operand = M_PI;
          push(&operand_stack, operand);
          i++;
        }
        else if(expr[i] == '!')
        {
          if(expr[i-1] == ')')
          {
              int j = i;
              int k = j - 1;
              while (expr[j] != '(') j--;
              double op = evaluateExpression(expr, j, k - 1, x, y);
              push(&operand_stack, factorialOfNum((int)op));
          }
          else
          {
             double op = pop(&operand_stack);
             push(&operand_stack, factorialOfNum((int)op));
          }
        }
        else if((expr[i] != 'l' && expr[i+1] != 'o' && expr[i+2] != 'g') ||
                (expr[i] != 's' && expr[i+1] != 'q' && expr[i+2] != 'r' && expr[i+3] != 't') ||
                expr[i] != '+' ||
                expr[i] != '-' ||
                expr[i] != '*' ||
                expr[i] != '/' ||
                expr[i] != '^' ||
                (expr[i] != 's' && expr[i+1] != 'i' && expr[i+2] != 'n') ||
                (expr[i] != 'c' && expr[i+1] != 'o' && expr[i+2] != 's') ||
                (expr[i] != 't' && expr[i+1] != 'a' && expr[i+2] != 'n') ||
                (expr[i] != 'a' && expr[i+1] != 't' && expr[i+2] != 'a' && expr[i+3] != 'n') ||
                (expr[i] != 'a' && expr[i+1] != 's' && expr[i+2] != 'i' && expr[i+3] != 'n') ||
                (expr[i] != 'a' && expr[i+1] != 'c' && expr[i+2] != 'o' && expr[i+3] != 's'))
        {
          error = 1;
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

double evaluateInfix(char *expr, double x, double y) {
    return evaluateExpression(expr, 0, strlen(expr), x, y);
}

double applyCustomLog(double operand, double base) {
    if (operand <= 0 || base <= 0 || base == 1) {
        error = 3;
    }
    return log(operand) / log(base);
}

double factorialOfNum(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return n * factorialOfNum(n-1);
    }
}

gchar *ErrorMessage(int error)
{
  if (error == 1)
    return g_strdup_printf("%s", "Invalid expression: invalid operator");
  else if (error == 2)
    return g_strdup_printf ("%s", "Invalid expression: unable to find opening parenthesis for logarithm!");
  else if (error == 3)
    return g_strdup_printf ("%s", "Invalid expression: invalid arguments for logarithm");
  else if (error == 4)
    return g_strdup_printf ("%s", "Division with 0");
  else if (error == 5)
    return g_strdup_printf ("%s", "Invalid expression: unable to find opening parenthesis for square root!");
  else if (error == 6)
    return g_strdup_printf ("%s", "Arcsin parameters must be between -1 and 1");
  else if (error == 7)
    return g_strdup_printf ("%s", "Arccos parameters must be between -1 and 1");
  else if (error == 8)
    return g_strdup_printf ("%s", "Invalid expression: unable to find opening parenthesis for sin, cos or tan!");
  else if (error == 9)
    return g_strdup_printf ("%s", "Invalid expression: unable to find opening parenthesis for arcsin, arccos or arctan!");
  else if (error == 10)
    return g_strdup_printf ("%s", "Can't take logarithm or square root from a number smaller than 0");
  else
    return g_strdup_printf ("%s", "Unknown error");
}

gchar *CalcMain(char *expr, double x, double y) {
    gchar *result_string;
    double calculated_result = evaluateInfix(expr, x, y);
    if (error != 0) {
        result_string = ErrorMessage(error);
    } else {
        result_string = g_strdup_printf("%g", calculated_result);
    }
    return result_string;
}


