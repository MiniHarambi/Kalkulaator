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
#include <gdk/gdk.h>
#include <stdio.h>
#include <stdlib.h>


G_DEFINE_TYPE (KalkulaatorWindow, kalkulaator_window, GTK_TYPE_APPLICATION_WINDOW);


static void kalkulaator_window__nr_clicked(GtkButton *button, gpointer user_data)
{
    KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
    const gchar* text = gtk_button_get_label(button);
    /*
    gint position = gtk_editable_get_position(GTK_EDITABLE(window->display));
    const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strdup_printf("%s%c%s", g_strndup(current_text, position), *text, current_text + position);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);

    gtk_editable_set_position(GTK_EDITABLE(window->display), position + 1);
     */

    const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, text, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);


    /*
    gchar *updated_expression = g_strdup_printf("%s%s", window->expression, text);
    g_free(window->expression);
    window->expression = updated_expression;

    if (window->expression != NULL) {
        gtk_editable_set_text(GTK_EDITABLE(window->display), window->expression);
    }
     */

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

    // Get the current text from the display widget
    const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));

    // Delete the last character from the current text
    size_t len = strlen(current_text);
    if (len > 0) {
        gchar *updated_text = g_strndup(current_text, len - 1);
        // Update the display
        gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
        g_free(updated_text);
    }
}
static void kalkulaator_window__dot_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append a dot to the expression
  gchar *dot = ".";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, dot, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}

static void kalkulaator_window__add_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append a plus sign to the expression
  gchar *add = "+";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, add, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}

static void kalkulaator_window__subtract_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append a minus sign to the expression
  gchar *subtract = "-";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, subtract, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}

static void kalkulaator_window__multiply_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append a multiplication sign to the expression
  gchar *multiply = "*";
  const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, multiply, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}

static void kalkulaator_window__divide_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append a division sign to the expression
  gchar *divide = "/";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, divide, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}

static void kalkulaator_window__sqrt_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append the sqrt function to the expression
  gchar *sqrt = "sqrt(";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, sqrt, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}

static void kalkulaator_window__square_clicked(GtkButton *button,gpointer  user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append the square function to the expression
  gchar *pow = "^";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, pow, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}

static void open_history_file()
{
/*
  const char *filepath = "Desktop/Kalk/Kalkulaator_GTK4/src/History.txt";
  FILE *fHis =fopen(filepath, "r");
  if(fHis == NULL)
    {
      g_print("Error opening file for reading\n");
      return;
    }
 */


  const gchar *command= "xdg-open Desktop/Kalk/Kalkulaator_GTK4/src/History.txt";
  system(command);

}
static void kalkulaator_window__history_clicked(GtkButton *button, gpointer user_data)
{
  // Functionality for the history button
  g_print("History button clicked.\n");

  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
/*
  GtkWidget *popover = gtk_popover_new();
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  GtkWidget *text_view = gtk_text_view_new();
  gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);

  GtkWidget *scrolled_window = gtk_scrolled_window_new();
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), text_view);

  gchar *history_content = NULL;
  GError *error = NULL;
  if (!g_file_get_contents("Desktop/Kalk/Kalkulaator_GTK4/src/History.txt",
                           &history_content, NULL, &error))
    {
        g_print("Error reading history.txt: %s\n", error->message);
        g_error_free(error);
        return;
    }
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
  gtk_text_buffer_set_text(buffer, history_content, -1);
  g_free(history_content);

  gtk_box_append(GTK_BOX(box), scrolled_window);
  gtk_popover_set_child(GTK_POPOVER(popover), box);
  gtk_widget_set_visible(popover, TRUE);

  gtk_popover_popup(GTK_POPOVER(popover));
   */
 open_history_file();
}

static void kalkulaator_window__ans_clicked(GtkButton *button, gpointer user_data)
{
    // Functionality for the ans button
    g_print("Ans button clicked.\n");
    KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

    // Check if there is a previous result and it's a valid number
    if (window->last_result != NULL && g_ascii_isdigit(window->last_result[0]))
    {
        // Get the text from the display widget
        const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));

        // Convert the last result to a numerical value
        double ans = atof(window->last_result);

        // Convert the numerical value back to string
        gchar *ans_string = g_strdup_printf("%g", ans);

        // Concatenate the numerical value to the current text
        gchar *updated_text = g_strconcat(current_text, ans_string, NULL);

        // Update the display with the new expression
        gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);

        // Free the string representation of the numerical value
        g_free(ans_string);
        g_free(updated_text);
    }
}

static void kalkulaator_window__sulg1_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append an opening parenthesis to the expression
  gchar *parenthesis_open = "(";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, parenthesis_open, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}
static void kalkulaator_window__sulg2_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append an opening parenthesis to the expression
  gchar *parenthesis_close = ")";
  const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, parenthesis_close, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}


static void kalkulaator_window__equal_clicked(GtkButton *button, gpointer user_data)
{
    KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

    // Get the text from the display widget
    const gchar *text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    type__file((gchar*)text);
    type__file((gchar*)" = ");
    // Calculate the result
    gchar *result = CalcMain((char*)text);
    type__file(result);
    type__file((gchar*)"\n");
    gtk_editable_set_text(GTK_EDITABLE(window->display2), text);

   //gtk_print_operation_set_export_filename( )
    // Store the result as the last result
    g_free(window->last_result);
    window->last_result = g_strdup(result);

    // Print the result on the display
    gtk_editable_set_text(GTK_EDITABLE(window->display), result);
    g_free(result);
}



static void kalkulaator_window__log_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  // Append the square function to the expression
  gchar *log = "log(";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, log, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}

void history_delete()
{
  const char *filepath = "Desktop/Kalk/Kalkulaator_GTK4/src/History.txt";
  FILE *fOut = fopen(filepath, "w");
    if (fOut == NULL)
    {
      g_print("Error opening file for writing\n");
      return;
    }


    // Close the file
    fclose(fOut);
}
/*
static void kalkulaator_window__toggle_button_toggled(GtkToggleButton *toggle_button, gpointer user_data)
{
    KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
    gboolean active = gtk_toggle_button_get_active(toggle_button);

    if (active)
    {
        // Show additional buttons
        gtk_widget_set_visible(GTK_WIDGET(window->xtrabutton1), TRUE);
        gtk_widget_set_visible(GTK_WIDGET(window->xtrabutton2), TRUE);
    }
    else
    {
        // Hide additional buttons
        gtk_widget_set_visible(GTK_WIDGET(window->xtrabutton1), FALSE);
        gtk_widget_set_visible(GTK_WIDGET(window->xtrabutton2), FALSE);
    }
}


static void kalkulaator_window_xtrabutton1_clicked(GtkButton *data, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
  g_print("xtrabutton clicked");
}
static void kalkulaator_window_xtrabutton2_clicked(GtkButton *data, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
  g_print("xtrabutton clicked");
}

 */

static void kalkulaator_window_class_init (KalkulaatorWindowClass *klass)
{
 // gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS(klass), "/org/example/App/kalkulaator-window.ui");
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(klass), "/org/github/kalkulaator/kalkulaator-window.ui");


  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS(klass), KalkulaatorWindow, header_bar);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS(klass), KalkulaatorWindow, display);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS(klass), KalkulaatorWindow, display2);
 //gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS(klass), KalkulaatorWindow, togglebutton);
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
 //// gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__toggle_button_toggled);
  //gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window_xtrabutton1_clicked);
  //gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window_xtrabutton2_clicked);

}

static void
kalkulaator_window_init (KalkulaatorWindow *self)
{

  gtk_widget_init_template (GTK_WIDGET (self));

  g_print("initializing display widget: %p\n", (void*) self->display);
  //self->display = g_strdup("");


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
  g_signal_connect(self->buttonlog, "clicked", G_CALLBACK(kalkulaator_window__log_clicked), self);
  //g_signal_connect(self->togglebutton, "toggled", G_CALLBACK(kalkulaator_window__toggle_button_toggled), self);
  //g_signal_connect(self->xtrabutton1, "clicked", G_CALLBACK(kalkulaator_window_xtrabutton1_clicked), self);
  //g_signal_connect(self->xtrabutton2, "clicked", G_CALLBACK(kalkulaator_window_xtrabutton2_clicked), self);
  //gtk_editable_set_position(GTK_EDITABLE(self->display), +0);

   history_delete();
}
