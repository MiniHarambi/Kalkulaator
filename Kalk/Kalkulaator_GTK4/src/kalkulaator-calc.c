#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "kalkulaator-calc.h"
#include "kalkulaator-window.h"

int error = 0;

static unsigned count = 0;
int len;
history *tehted;



void type__file(const gchar *content, char *text, char *result) 
{
    const char *filepath2 = "len.txt";
    FILE *fInLen = fopen(filepath2, "r");
    if (fInLen == NULL) {
        g_print("Error opening file for reading\n");
        return;
    }
    fscanf(fInLen, "%d", &len);
    fclose(fInLen);

    history *new_tehted = realloc(tehted, (count + 1) * sizeof(history));
    if (new_tehted == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    tehted = new_tehted;

    char values[200];
    sprintf(values, "%s %s %s", content, text, result);
    strcpy(tehted[count].text, values);
    count++;
}

void PrintFile() 
{
    const char *filepath = "History.txt";
    FILE *fOut = fopen(filepath, "w");
    if (fOut == NULL) {
        g_print("Error opening file for writing\n");
        return;
    }
    
    int print_count = (count < len) ? count : len;
    for (int j = print_count - 1; j >= 0; j--) {
        fprintf(fOut, "%s\n", tehted[count - j - 1].text);
    }
    fclose(fOut);
}

void initialize(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return (s->top == -1);
}

void push(Stack *s, double value) {
    if (s->top == MAX_SIZE - 1) {
        error = 14;
    }
    s->items[++(s->top)] = value;
}

double pop(Stack *s) {
    if (isEmpty(s)) {
        error = 13;
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
        if (expr[i] == '.') {
            expr[i] = ',';
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
            double operand = strtod(&expr[i], &endptr);
            push(&operand_stack, operand);
            i = endptr - expr - 1;
        }
        else if (expr[i] == '-') {
          if (i == start || (!isdigit(expr[i - 1]) && expr[i - 1] != 'x' && expr[i - 1] != 'y')) {
              i++;
              char *endptr;
              double operand = -strtod(&expr[i], &endptr);
              push(&operand_stack, operand);
              i = endptr - expr - 1;
          } else {
              while (!isEmpty(&operator_stack) && precedence(operator_stack.items[operator_stack.top]) >= precedence(expr[i])) {
                  double op2 = pop(&operand_stack);
                  double op1 = pop(&operand_stack);
                  char operator = pop(&operator_stack);
                  push(&operand_stack, applyOperator(op1, op2, operator));
            }
            push(&operator_stack, expr[i]);
          }
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
                if (expr[j] == '('){
                  count++;
                }
                else if (expr[j] == ')'){
                  count--;
                }
                else if (j == (end))
                {
                  expr[j] = ')';
                  error = 11;
                  count--;
                }
                j++;
            }
            double result = evaluateExpression(expr, i + 1, j - 1, x, y);
            if (isdigit(expr[i-1]))
            {
              double op = pop(&operand_stack);
              result = result * op;
            }
            else if (isdigit(expr[j]))
            {
              double op = 0;
              while (isdigit(expr[j])) {
                op = op * 10 + (expr[j] - '0');
                j++;
              }
              result = result * op;
            }
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
                if (expr[k] == '('){
                  count++;
                }
                else if (expr[k] == ')')
                {
                  count--;
                }
                else if (k == (end))
                {
                  expr[k] = ')';
                  error = 11;
                  count--;
                }
                k++;
            }
            double operand = evaluateExpression(expr, j + 1, k - 1, x, y);
            double result = applyCustomLog(operand, base);
            if (isdigit(expr[i-1]) || expr[i-1] == '-')
            {
              if(expr[i-1] == '-' && ((i-1) == start))
                {
                  result *= -1;
                }
              else if (isdigit(expr[i-1]))
                {
                  double op = pop(&operand_stack);
                  result = result * op;
                }
            }
            if (isdigit(expr[k]))
            {
              double op = 0;
              while (isdigit(expr[k])) {
                op = op * 10 + (expr[k] - '0');
                k++;
              }
              result = result * op;
            }
            push(&operand_stack, result);
            i = k;
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
            int count = 1;
            while (count != 0) {
                if (expr[k] == '(')
                {
                  count++;
                }
                else if (expr[k] == ')')
                {
                  count--;
                }
                else if (k == (end))
                {
                  expr[k] = ')';
                  error = 11;
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
            if (isdigit(expr[i-1]) || expr[i-1] == '-')
            {
              if(expr[i-1] == '-' && ((i-1) == start))
                {
                  result *= -1;
                }
              else if (isdigit(expr[i-1]))
                {
                  double op = pop(&operand_stack);
                  result = result * op;
                }
            }
            if (isdigit(expr[k]))
            {
              double op = 0;
              while (isdigit(expr[k])) {
                op = op * 10 + (expr[k] - '0');
                k++;
              }
              result = result * op;
            }
            push(&operand_stack, result);
            i = k - 1;
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
                else if (k == (end))
                {
                  expr[k] = ')';
                  error = 11;
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
            if (isdigit(expr[i-1]) || expr[i-1] == '-')
            {
              if(expr[i-1] == '-' && ((i-1) == start))
                {
                  result *= -1;
                }
              else if (isdigit(expr[i-1]))
                {
                  double op = pop(&operand_stack);
                  result = result * op;
                }
            }
            if (isdigit(expr[k]))
            {
              double op = 0;
              while (isdigit(expr[k])) {
                op = op * 10 + (expr[k] - '0');
                k++;
              }
              result = result * op;
            }
            push(&operand_stack, result);
            i = k - 1;

        }
        else if((expr[i] == 'p' && expr[i+1] == 'i') || (expr[i] == 'P' && expr[i+1] == 'I'))
        {
          double result = M_PI;
          if (isdigit(expr[i-1]) || expr[i-1] == '-')
            {
              if(expr[i-1] == '-' && ((i-1) == start))
                {
                  result *= -1;
                }
              else if (isdigit(expr[i-1]))
                {
                  double op = pop(&operand_stack);
                  result = result * op;
                }
            }
          push(&operand_stack, result);
          i++;
        }
        else if(expr[i] == '!')
        {
          double result = 0;
          double op = pop(&operand_stack);

          if (op == 0)error = 12;
          if (op < 0)
          {
             op *= -1;
            result = factorialOfNum((int)op);
            result *= -1;
            }
          else
          {
            result = factorialOfNum((int)op);
          }
          push(&operand_stack, result);
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
    else if (n > 0)
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
  else if (error == 11)
    return g_strdup_printf ("%s", "Invalid expression: unable to find closing paranthesis");
  else if (error == 12)
    return g_strdup_printf ("%s", "Can't take fractions from 0 or negative numbers");
  else if (error == 13)
    return g_strdup_printf ("%s", "Too many operators");
  else if (error == 14)
    return g_strdup_printf ("%s", "Too few operators");
  else
    return g_strdup_printf ("%s", "Unknown error");
}

gchar *CalcMain(char *expr, double x, double y) {
    gchar *result_string;
    error = 0;
    double calculated_result = evaluateInfix(expr, x, y);
    if (error != 0) {
        result_string = ErrorMessage(error);
    } else {
        result_string = g_strdup_printf("%g", calculated_result);
    }
    return result_string;
    g_free(result_string);
}
