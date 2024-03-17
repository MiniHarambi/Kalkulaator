/* kalkulaator-window.c
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

#include "kalkulaator-config.h"
#include "kalkulaator-window.h"
#include "kalkulaator-calc.h"
#include <gtk/gtk.h>
#include <stdio.h>

struct _KalkulaatorWindow
{
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  GtkLabel            *label;
  GtkWindow           *gtk_window;
  GtkBox              *main_box;
  GtkEntry            *display;

  GtkButton           *button0;
  GtkButton           *button1;
  GtkButton           *button2;
  GtkButton           *button3;
  GtkButton           *button4;
  GtkButton           *button5;
  GtkButton           *button6;
  GtkButton           *button7;
  GtkButton           *button8;
  GtkButton           *button9;

  GtkButton           *buttonclear;
  GtkButton           *buttondelete;
  GtkButton           *buttondot;
  GtkButton           *buttonadd;
  GtkButton           *buttonsubtract;
  GtkButton           *buttonmultiply;
  GtkButton           *buttondivide;
  GtkButton           *buttonsqrt;
  GtkButton           *buttonsquare;
  GtkButton           *buttonhistory;
  GtkButton           *buttonans;
  GtkButton           *buttonsulg1;
  GtkButton           *buttonsulg2;
  GtkButton           *buttonequal;
  GtkButton           *buttonlog;

  gchar               *expression;
  gchar               *last_result;
  };

G_DEFINE_TYPE (KalkulaatorWindow, kalkulaator_window, GTK_TYPE_APPLICATION_WINDOW)

static void kalkulaator_window__nr_clicked(GtkButton *button, gpointer user_data)
{
    KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
    const gchar* text = gtk_button_get_label(button);

    gchar *updated_expression = g_strdup_printf("%s%s", window->expression, text);
    g_free(window->expression);
    window->expression = updated_expression;

    if (window->expression != NULL) {
        gtk_editable_set_text(GTK_EDITABLE(window->display), window->expression);
    }
}


static void kalkulaator_window__clear_clicked(GtkButton *button, gpointer user_data)
{
    KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

    // Clear the expression
    g_free(window->expression);
    window->expression = g_strdup("");
g_print("clear button");
    // Update the display
    gtk_editable_set_text(GTK_EDITABLE(window->display), "");
}


static void kalkulaator_window__delete_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Delete the last character from the expression
  size_t len = strlen(window->expression);
  if (len > 0) {
    window->expression[len - 1] = '\0';
g_print("delete button");
    // Update the display
    gtk_editable_set_text(GTK_EDITABLE(window->display), window->expression);
  }
}

static void kalkulaator_window__dot_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append a dot to the expression
  gchar *dot = ".";
  gchar *updated_expression = g_strconcat(window->expression, dot, NULL);
  g_free(window->expression);
  window->expression = updated_expression;
g_print(". button");
  // Update the display
  gtk_editable_set_text(GTK_EDITABLE(window->display), window->expression);
}

static void kalkulaator_window__add_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append a plus sign to the expression
  gchar *add = "+";
  gchar *updated_expression = g_strconcat(window->expression, add, NULL);
  g_free(window->expression);
  window->expression = updated_expression;
g_print("+ button");
  // Update the display
  gtk_editable_set_text(GTK_EDITABLE(window->display), window->expression);
}

static void kalkulaator_window__subtract_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append a minus sign to the expression
  gchar *subtract = "-";
  gchar *updated_expression = g_strconcat(window->expression, subtract, NULL);
  g_free(window->expression);
  window->expression = updated_expression;
g_print("- button");
  // Update the display
  gtk_editable_set_text(GTK_EDITABLE(window->display), window->expression);
}

static void kalkulaator_window__multiply_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append a multiplication sign to the expression
  gchar *multiply = "*";
  gchar *updated_expression = g_strconcat(window->expression, multiply, NULL);
  g_free(window->expression);
  window->expression = updated_expression;
g_print("* button");
  // Update the display
  gtk_editable_set_text(GTK_EDITABLE(window->display), window->expression);
}

static void kalkulaator_window__divide_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append a division sign to the expression
  gchar *divide = "/";
  gchar *updated_expression = g_strconcat(window->expression, divide, NULL);
  g_free(window->expression);
  window->expression = updated_expression;
g_print("/ button");
  // Update the display
  gtk_editable_set_text(GTK_EDITABLE(window->display), window->expression);
}

static void kalkulaator_window__sqrt_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append the sqrt function to the expression
  gchar *sqrt = "sqrt(";
  gchar *updated_expression = g_strconcat(window->expression, sqrt, NULL);
  g_free(window->expression);
  window->expression = updated_expression;
g_print("sqrt button");
  // Update the display
  gtk_editable_set_text(GTK_EDITABLE(window->display), window->expression);
}

static void kalkulaator_window__square_clicked(GtkButton *button,gpointer  user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append the square function to the expression
  gchar *pow = "^";
  gchar *updated_expression = g_strconcat(window->expression, pow, NULL);
  g_free(window->expression);
  window->expression = updated_expression;
g_print("square button");
  // Update the display
  gtk_editable_set_text(GTK_EDITABLE(window->display), window->expression);
}

static void kalkulaator_window__history_clicked(GtkButton *button, gpointer user_data)
{
  // Functionality for the history button
  g_print("History button clicked.\n");
}

static void kalkulaator_window__ans_clicked(GtkButton *button, gpointer user_data)
{
    // Functionality for the ans button
    g_print("Ans button clicked.\n");
    KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

    // Check if there is a previous result and it's a valid number
    if (window->last_result != NULL && g_ascii_isdigit(window->last_result[0]))
    {
        // Convert the last result to a numerical value
        double ans = atof(window->last_result);

        // Convert the numerical value back to string
        gchar *ans_string = g_strdup_printf("%g", ans);

        // Append the numerical value to the expression
        gchar *updated_expression = g_strconcat(window->expression, ans_string, NULL);

        // Free the previous expression
        g_free(window->expression);

        // Update the expression with the new one
        window->expression = updated_expression;

        // Update the display with the new expression
        gtk_editable_set_text(GTK_EDITABLE(window->display), window->expression);

        // Free the string representation of the numerical value
        g_free(ans_string);
    }
}




static void kalkulaator_window__sulg1_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append an opening parenthesis to the expression
  gchar *parenthesis_open = "(";
  gchar *updated_expression = g_strconcat(window->expression, parenthesis_open, NULL);
  g_free(window->expression);
  window->expression = updated_expression;
g_print("( button");
  // Update the display
  gtk_editable_set_text(GTK_EDITABLE(window->display), window->expression);
}
static void kalkulaator_window__sulg2_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append an opening parenthesis to the expression
  gchar *parenthesis_open = ")";
  gchar *updated_expression = g_strconcat(window->expression, parenthesis_open, NULL);
  g_free(window->expression);
  window->expression = updated_expression;
  g_print(") button");
  // Update the display
  gtk_editable_set_text(GTK_EDITABLE(window->display), window->expression);
}


static void kalkulaator_window__equal_clicked(GtkButton *button, gpointer user_data)
{
    KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

    // Get the text from the entry widget
    const gchar *text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *result = CalcMain((char*)text);

    // Store the result as the last result
    g_free(window->last_result);
    window->last_result = g_strdup(result);

    // Print the result on the display
    gtk_editable_set_text(GTK_EDITABLE(window->display), result);
    g_free(result);

    // Clear the expression if it's not already empty
    if (strlen(window->expression) > 0) {
        g_free(window->expression);
        window->expression = g_strdup("");
    }
}


static void kalkulaator_window__log_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append the square function to the expression
  gchar *log = "log(";
  gchar *updated_expression = g_strconcat(window->expression, log, NULL);
  g_free(window->expression);
  window->expression = updated_expression;
g_print("log button");
  // Update the display
  gtk_editable_set_text(GTK_EDITABLE(window->display), window->expression);
}

static void kalkulaator_window_class_init (KalkulaatorWindowClass *klass)
{
 // gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS(klass), "/org/example/App/kalkulaator-window.ui");
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(klass), "/org/github/kalkulaator/kalkulaator-window.ui");


  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS(klass), KalkulaatorWindow, header_bar);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS(klass), KalkulaatorWindow, display);
  // Bind other template children as needed

  // Bind signal handlers
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__nr_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__clear_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__delete_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__dot_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__add_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__subtract_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__multiply_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__divide_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__sqrt_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__square_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__history_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__ans_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__sulg1_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__sulg2_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__equal_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__log_clicked);

}

static void
kalkulaator_window_init (KalkulaatorWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  g_print("initializing display widget: %p\n", (void*) self->display);

  self->expression = g_strdup("");

  g_signal_connect(self->button0, "clicked", G_CALLBACK(kalkulaator_window__nr_clicked), self);
  g_signal_connect(self->button1, "clicked", G_CALLBACK(kalkulaator_window__nr_clicked), self);
  g_signal_connect(self->button2, "clicked", G_CALLBACK(kalkulaator_window__nr_clicked), self);
  g_signal_connect(self->button3, "clicked", G_CALLBACK(kalkulaator_window__nr_clicked), self);
  g_signal_connect(self->button4, "clicked", G_CALLBACK(kalkulaator_window__nr_clicked), self);
  g_signal_connect(self->button5, "clicked", G_CALLBACK(kalkulaator_window__nr_clicked), self);
  g_signal_connect(self->button6, "clicked", G_CALLBACK(kalkulaator_window__nr_clicked), self);
  g_signal_connect(self->button7, "clicked", G_CALLBACK(kalkulaator_window__nr_clicked), self);
  g_signal_connect(self->button8, "clicked", G_CALLBACK(kalkulaator_window__nr_clicked), self);
  g_signal_connect(self->button9, "clicked", G_CALLBACK(kalkulaator_window__nr_clicked), self);


  g_signal_connect(self->buttonclear, "clicked", G_CALLBACK(kalkulaator_window__clear_clicked), self);
  g_signal_connect(self->buttondelete, "clicked", G_CALLBACK(kalkulaator_window__delete_clicked), self);
  g_signal_connect(self->buttondot, "clicked", G_CALLBACK(kalkulaator_window__dot_clicked), self);
  g_signal_connect(self->buttonadd, "clicked", G_CALLBACK(kalkulaator_window__add_clicked), self);
  g_signal_connect(self->buttonsubtract, "clicked", G_CALLBACK(kalkulaator_window__subtract_clicked), self);
  g_signal_connect(self->buttonmultiply, "clicked", G_CALLBACK(kalkulaator_window__multiply_clicked), self);
  g_signal_connect(self->buttondivide, "clicked", G_CALLBACK(kalkulaator_window__divide_clicked), self);
  g_signal_connect(self->buttonsqrt, "clicked", G_CALLBACK(kalkulaator_window__sqrt_clicked), self);
  g_signal_connect(self->buttonsquare, "clicked", G_CALLBACK(kalkulaator_window__square_clicked), self);
  g_signal_connect(self->buttonhistory, "clicked", G_CALLBACK(kalkulaator_window__history_clicked), self);
  g_signal_connect(self->buttonans, "clicked", G_CALLBACK(kalkulaator_window__ans_clicked), self);
  g_signal_connect(self->buttonsulg1, "clicked", G_CALLBACK(kalkulaator_window__sulg1_clicked), self);
  g_signal_connect(self->buttonsulg2, "clicked", G_CALLBACK(kalkulaator_window__sulg2_clicked), self);
  g_signal_connect(self->buttonequal, "clicked", G_CALLBACK(kalkulaator_window__equal_clicked), self);
  g_signal_connect(self->buttonlog, "clicked", G_CALLBACK(kalkulaator_window__equal_clicked), self);
}


