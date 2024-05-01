/* kalkulaator-window.h
 *
 * Copyright 2024 Markus Parm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <gtk/gtk.h>
#include "kalkulaator-window.h"

G_BEGIN_DECLS

#define KALKULAATOR_TYPE_CALC

 #define MAX_SIZE 1000
 #define M_PI 3.14159265358979323846
// Stack structure
typedef struct {
    int top;
    double items[MAX_SIZE];
    char errorMessage[MAX_SIZE];
} Stack;

typedef struct {
    char text[200];
} history;

// Function prototypes
void initialize(Stack *s);
int isEmpty(Stack *s);
void push(Stack *s, double value);
double pop(Stack *s);
int precedence(char op);
double applyOperator(double op1, double op2, char operatorr);
double evaluateExpression(char *expr, int start, int end, double x, double y);
double evaluateInfix(char *expr, double x, double y);
gchar *CalcMain(char *expr, double x, double y);
void type__file(const gchar *content, char *text, char *result);
double applyCustomLog(double operand, double base);
double factorialOfNum(int n);
gchar *ErrorMessage(int error);
G_END_DECLS
