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
#include "bitmask.h"
#include <gtk/gtk.h>
#include <gdk/gdk.h>

static void setButton__clicked(GtkWidget *widget, gpointer user_data);
static void resetButton__clicked(GtkWidget *widget, gpointer user_data);
static void masking__clicked(GtkButton *data, gpointer user_data);
void on_bits_changed(GtkWidget *widget, gpointer data);

G_DEFINE_TYPE (KalkulaatorWindow, kalkulaator_window, GTK_TYPE_APPLICATION_WINDOW);

int count = 0;
int option = 0;
int bit = 0;

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
    if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
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
    gtk_editable_set_text(GTK_EDITABLE(window->display), "0");
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
    else
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "0");
    }
}
static void kalkulaator_window__dot_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
  if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
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
  if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
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
  if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
  // Append the square function to the expression
  gchar *pow = "^";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, pow, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}

static void show_history_dialog(GtkWidget *parent)
{
    // Create a new dialog window
    GtkWidget *dialog = gtk_dialog_new();

    gtk_window_set_title(GTK_WINDOW(dialog), "History");

    // Create a text view to display the history content
    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);

    // Create a scrolled window to hold the text view
    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), text_view);

    // Read content from file
    FILE *file = fopen("History.txt", "r");
    if (file == NULL)
      {
        g_warning("Failed to open file.");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = g_malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    // Load content into the text view
    GtkTextBuffer *text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(text_buffer, buffer, -1);
    g_free(buffer);

    // Set the size of the scrolled window
    gtk_widget_set_size_request(scrolled_window, 400, 300);

    // Add the scrolled window to the dialog's content area
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_box_append(GTK_BOX(content_area), scrolled_window);

    GtkWidget *label = gtk_label_new("Set history to ... lines:");
    gtk_box_append(GTK_BOX(content_area), label);

    GtkWidget *count_entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(content_area), count_entry);


    GtkButton *setButton = GTK_BUTTON(gtk_button_new_with_label("Set"));
    gtk_box_append(GTK_BOX(content_area), GTK_WIDGET(setButton));
    g_signal_connect(setButton, "clicked", G_CALLBACK(setButton__clicked), count_entry);

    GtkButton *resetButton = GTK_BUTTON(gtk_button_new_with_label("reset history"));
    gtk_box_append(GTK_BOX(content_area), GTK_WIDGET(resetButton));
    g_signal_connect(resetButton, "clicked", G_CALLBACK(resetButton__clicked), 0);

    // Show the dialog
    gtk_widget_show(dialog);
}

static void setButton__clicked(GtkWidget *widget, gpointer user_data)
{
  const gchar *num = gtk_editable_get_text(GTK_EDITABLE(user_data));

  const char *filepath2 = "len.txt";
  FILE *fInLen = fopen(filepath2, "w");
    if (fInLen == NULL)
    {
      g_print("Error opening file for writing\n");
      return;
    }

  fprintf(fInLen, "%s\n", num);
  fclose(fInLen);

}

static void resetButton__clicked(GtkWidget *widget, gpointer user_data)
{
  const char *filepath = "History.txt";
  FILE *fOut = fopen(filepath, "w");
    if (fOut == NULL)
    {
      g_print("Error opening file for writing\n");
      return;
    }


    // Close the file
    fclose(fOut);

}

static void kalkulaator_window__history_clicked(GtkButton *button, gpointer user_data)
{
  // Functionality for the history button
  g_print("History button clicked.\n");

  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
  show_history_dialog(GTK_WIDGET(window));

}

static void kalkulaator_window__ans_clicked(GtkButton *button, gpointer user_data)
{
    // Functionality for the ans button
    g_print("Ans button clicked.\n");
    KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
    if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
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
  if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
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
    const gchar *x = gtk_editable_get_text(GTK_EDITABLE(window->display2));
    const gchar *y = gtk_editable_get_text(GTK_EDITABLE(window->display3));
    if ((strlen(text) == 0))
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "0");
    }
    else if((strlen(x) == 0))
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display2), "0");
    }
    else if((strlen(y) == 0))
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display3), "0");
    }
    else
    {
      gchar *xVal = CalcMain((char*)x, (double) 0, (double) 0);
      double valX = atof(xVal);

      gchar *yVal = CalcMain((char*)y, (double) 0, (double) 0);
      double valY = atof(yVal);


      // Calculate the result
      gchar *result = CalcMain((char*)text, valX, valY);
      type__file((gchar*)text, "= ", result);
      //gtk_editable_set_text(GTK_EDITABLE(window->display2), text);

     //gtk_print_operation_set_export_filename( )
      // Store the result as the last result
      g_free(window->last_result);
      window->last_result = g_strdup(result);

      // Print the result on the display
      gtk_editable_set_text(GTK_EDITABLE(window->display), result);
      g_free(result);
    }

}



static void kalkulaator_window__log_clicked(GtkButton *button, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
  if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
  // Append the square function to the expression
  gchar *log = "log(";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, log, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}

void history__delete()
{
  const char *filepath = "History.txt";
  FILE *fOut = fopen(filepath, "w");
    if (fOut == NULL)
    {
      g_print("Error opening file for writing\n");
      return;
    }


    // Close the file
    fclose(fOut);
}



static void kalkulaator_window__toggle_button_toggled(GtkToggleButton *toggle_button,
                                                      gpointer user_data)
{
    KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
    gboolean active = gtk_toggle_button_get_active(toggle_button);

    if (active)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display2), "x = ");
    }

}




static void kalkulaator_window__buttonfact_clicked(GtkButton *data, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);

  gchar *fact = "!";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, fact, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}

static void kalkulaator_window__xtrabutton3_clicked(GtkButton *data, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
  if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
  gchar *pi = "pi";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, pi, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);

}
static void kalkulaator_window__xtrabutton4_clicked(GtkButton *data, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
  if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
  // Append the square function to the expression
  gchar *logx = "log_";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, logx, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}


static void kalkulaator_window__sin_clicked(GtkButton *data, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
  if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
  gchar *sin = "sin(";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, sin, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}
static void kalkulaator_window__arcsin_clicked(GtkButton *data, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
  if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
  gchar *asin = "asin(";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, asin, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);

}
static void kalkulaator_window__cos_clicked(GtkButton *data, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
  if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
  gchar *cos = "cos(";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, cos, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}
static void kalkulaator_window__arccos_clicked(GtkButton *data, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
  if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
  gchar *acos = "acos(";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, acos, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}
static void kalkulaator_window__tan_clicked(GtkButton *data, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
  if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
  gchar *tan = "tan(";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, tan, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}
static void kalkulaator_window__arctan_clicked(GtkButton *data, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
  if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
  gchar *atan = "atan(";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, atan, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}

static void kalkulaator_window__xVal_clicked(GtkButton *data, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
  if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
  gchar *x = "x";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, x, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}
static void kalkulaator_window__yVal_clicked(GtkButton *data, gpointer user_data)
{
  KalkulaatorWindow *window = KALKULAATOR_WINDOW(user_data);
  if(strcmp(gtk_editable_get_text(GTK_EDITABLE(window->display)), "0") == 0)
    {
      gtk_editable_set_text(GTK_EDITABLE(window->display), "");
    }
  gchar *y = "y";
   const gchar *current_text = gtk_editable_get_text(GTK_EDITABLE(window->display));
    gchar *updated_text = g_strconcat(current_text, y, NULL);
    gtk_editable_set_text(GTK_EDITABLE(window->display), updated_text);
    g_free(updated_text);
}


GtkWidget *bit_entry;
GtkWidget *set_mask_entry;
GtkWidget *clear_mask_entry;
GtkWidget *toggle_mask_entry;
GtkWidget *read_mask_entry;

GtkWidget *set_bin_entry;
GtkWidget *clear_bin_entry;
GtkWidget *toggle_bin_entry;
GtkWidget *read_bin_entry;

GtkWidget *set_num_entry;
GtkWidget *clear_num_entry;
GtkWidget *toggle_num_entry;
GtkWidget *read_num_entry;

static void kalkulaator_window__bitmask_clicked(GtkButton *data, gpointer user_data)
{
   g_print("clicked\n");
    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Bitmask Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 750, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_close), NULL);

    // Create a grid layout
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_margin_top(grid, 10);
    gtk_widget_set_margin_start(grid, 10);
    gtk_widget_set_margin_end(grid, 10);
    gtk_widget_set_margin_bottom(grid, 10);
    gtk_window_set_child(GTK_WINDOW(window), grid);

    //row 1
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("How many bits:"), 0, 0, 1, 1);
    const char *options[6] = {"", "8", "16", "32", "64", NULL};
    GtkWidget *bits_dropdown = gtk_combo_box_text_new();
    for (int i = 0; options[i] != NULL; i++)
    {
      gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(bits_dropdown), options[i]);
    }
    gtk_widget_set_hexpand(bits_dropdown, TRUE);
    gtk_widget_set_vexpand(bits_dropdown, TRUE);
    gtk_grid_attach(GTK_GRID(grid), bits_dropdown, 1, 0, 1, 1);

    //row 2
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Bit to mask:"), 0, 1, 1, 1);
    bit_entry = gtk_entry_new();
    gtk_widget_set_hexpand(bit_entry, TRUE);
    gtk_widget_set_vexpand(bit_entry, TRUE);
    gtk_grid_attach(GTK_GRID(grid), bit_entry, 1, 1, 1, 1);
    g_signal_connect(bits_dropdown, "changed", G_CALLBACK(on_bits_changed), bit_entry);

    //separators between masks
    GtkWidget *empty_row1 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    //gtk_widget_set_hexpand(empty_row1, TRUE);
    //gtk_widget_set_vexpand(empty_row1, TRUE);
    gtk_grid_attach(GTK_GRID(grid), empty_row1, 0, 2, 5, 1);


    //row 4/1
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Mask to set:"), 0, 3, 1, 1);
    set_mask_entry = gtk_entry_new();
    gtk_widget_set_hexpand(set_mask_entry, TRUE);
    gtk_widget_set_vexpand(set_mask_entry, TRUE);
    gtk_editable_set_editable(GTK_EDITABLE(set_mask_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), set_mask_entry, 1, 3, 1, 1);

    //row 5/1
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Use example:"), 0, 4, 1, 1);
    GtkWidget *set_bin_label = gtk_label_new("                        num | 0b");
    gtk_widget_set_hexpand(set_bin_label, TRUE);
    gtk_widget_set_vexpand(set_bin_label, TRUE);
    set_bin_entry = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(set_bin_entry), FALSE);
    gtk_widget_set_hexpand(set_bin_entry, TRUE);
    gtk_widget_set_vexpand(set_bin_entry, TRUE);
    gtk_grid_attach(GTK_GRID(grid), set_bin_label, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), set_bin_entry, 1, 5, 1, 1);

    //row 6/1
    GtkWidget *set_num_label = gtk_label_new("                        num | 0x");
    gtk_widget_set_hexpand(set_num_label, TRUE);
    gtk_widget_set_vexpand(set_num_label, TRUE);
    set_num_entry = gtk_entry_new();
    gtk_widget_set_hexpand(set_num_entry, TRUE);
    gtk_widget_set_vexpand(set_num_entry, TRUE);
    gtk_editable_set_editable(GTK_EDITABLE(set_num_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), set_num_label, 0, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), set_num_entry, 1, 6, 1, 1);

    //empty row 7
    GtkWidget *empty_row2 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    //gtk_widget_set_hexpand(empty_row2, TRUE);
    //gtk_widget_set_vexpand(empty_row2, TRUE);
    gtk_grid_attach(GTK_GRID(grid), empty_row2, 0, 7, 5, 1);

    //row 8/1
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Mask to clear:"), 0, 8, 1, 1);
    clear_mask_entry = gtk_entry_new();
    gtk_widget_set_hexpand(clear_mask_entry, TRUE);
    gtk_widget_set_vexpand(clear_mask_entry, TRUE);
    gtk_editable_set_editable(GTK_EDITABLE(clear_mask_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), clear_mask_entry, 1, 8, 1, 1);

    //row 9/1
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Use example:"), 0, 10, 1, 1);
    GtkWidget *clear_bin_label = gtk_label_new("                        num &~ 0b");
    gtk_widget_set_hexpand(clear_bin_label, TRUE);
    gtk_widget_set_vexpand(clear_bin_label, TRUE);
    clear_bin_entry = gtk_entry_new();
    gtk_widget_set_hexpand(clear_bin_entry, TRUE);
    gtk_widget_set_vexpand(clear_bin_entry, TRUE);
    gtk_editable_set_editable(GTK_EDITABLE(clear_bin_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), clear_bin_label, 0, 11, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), clear_bin_entry, 1, 11, 1, 1);

    //row 10/1
    GtkWidget *clear_num_label = gtk_label_new("                        num &~ 0x");
    gtk_widget_set_hexpand(clear_num_label, TRUE);
    gtk_widget_set_vexpand(clear_num_label, TRUE);
    clear_num_entry = gtk_entry_new();
    gtk_widget_set_hexpand(clear_num_entry, TRUE);
    gtk_widget_set_vexpand(clear_num_entry, TRUE);
    gtk_editable_set_editable(GTK_EDITABLE(clear_num_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), clear_num_label, 0, 12, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), clear_num_entry, 1, 12, 1, 1);

    //separator row between
    GtkWidget *empty_row3 = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    //gtk_widget_set_hexpand(empty_row3, TRUE);
    //gtk_widget_set_vexpand(empty_row3, TRUE);
    gtk_grid_attach(GTK_GRID(grid), empty_row3, 2, 2, 1, 11);

    //row 2/2
    GtkButton *maskingButton = GTK_BUTTON(gtk_button_new_with_label("mask"));
    gtk_grid_attach(GTK_GRID(grid), maskingButton, 3, 0, 2, 2);
    g_signal_connect(maskingButton, "clicked", G_CALLBACK(masking__clicked), user_data);

    //row 4/2
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Mask to toggle:"), 3, 3, 1, 1);
    toggle_mask_entry = gtk_entry_new();
    gtk_widget_set_hexpand(toggle_mask_entry, TRUE);
    gtk_widget_set_vexpand(toggle_mask_entry, TRUE);
    gtk_editable_set_editable(GTK_EDITABLE(toggle_mask_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), toggle_mask_entry, 4, 3, 1, 1);

    //row 5/2
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Use example:"), 3, 4, 1, 1);
    GtkWidget *toggle_bin_label = gtk_label_new("                        num ^ 0b");
    gtk_widget_set_hexpand(toggle_bin_label, TRUE);
    gtk_widget_set_vexpand(toggle_bin_label, TRUE);
    toggle_bin_entry = gtk_entry_new();
    gtk_widget_set_hexpand(toggle_bin_entry, TRUE);
    gtk_widget_set_vexpand(toggle_bin_entry, TRUE);
    gtk_editable_set_editable(GTK_EDITABLE(toggle_bin_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), toggle_bin_label, 3, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), toggle_bin_entry, 4, 5, 1, 1);

    //row 6/2
    GtkWidget *toggle_num_label = gtk_label_new("                        num ^ 0x");
    gtk_widget_set_hexpand(toggle_num_label, TRUE);
    gtk_widget_set_vexpand(toggle_num_label, TRUE);
    toggle_num_entry = gtk_entry_new();
    gtk_widget_set_hexpand(toggle_num_entry, TRUE);
    gtk_widget_set_vexpand(toggle_num_entry, TRUE);
    gtk_editable_set_editable(GTK_EDITABLE(toggle_num_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), toggle_num_label, 3, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), toggle_num_entry, 4, 6, 1, 1);

    //row 8/2
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Mask to read:"), 3, 8, 1, 1);
    read_mask_entry = gtk_entry_new();
    gtk_widget_set_hexpand(read_mask_entry, TRUE);
    gtk_widget_set_vexpand(read_mask_entry, TRUE);
    gtk_editable_set_editable(GTK_EDITABLE(read_mask_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), read_mask_entry, 4, 8, 1, 1);

    //row 9/2
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Use example:"), 3, 10, 1, 1);
    GtkWidget *read_bin_label = gtk_label_new("                        num & 0b");
    gtk_widget_set_hexpand(read_bin_label, TRUE);
    gtk_widget_set_vexpand(read_bin_label, TRUE);
    read_bin_entry = gtk_entry_new();
    gtk_widget_set_hexpand(read_bin_label, TRUE);
    gtk_widget_set_vexpand(read_bin_label, TRUE);
    gtk_editable_set_editable(GTK_EDITABLE(read_bin_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), read_bin_label, 3, 11, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), read_bin_entry, 4, 11, 1, 1);

    //row 10/2
    GtkWidget *read_num_label = gtk_label_new("                        num & 0x");
    gtk_widget_set_hexpand(read_num_label, TRUE);
    gtk_widget_set_vexpand(read_num_label, TRUE);
    read_num_entry = gtk_entry_new();
    gtk_widget_set_hexpand(read_num_entry, TRUE);
    gtk_widget_set_vexpand(read_num_entry, TRUE);
    gtk_editable_set_editable(GTK_EDITABLE(read_num_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), read_num_label, 3, 12, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), read_num_entry, 4, 12, 1, 1);

    gtk_widget_show(window);
}

void on_bits_changed(GtkWidget *widget, gpointer data) {
    GtkComboBox *combo_box = GTK_COMBO_BOX(widget);
    option = gtk_combo_box_get_active(combo_box);
}

static void masking__clicked(GtkButton *data, gpointer user_data)
{
    const gchar *bit_text= g_strdup(gtk_editable_get_text(GTK_EDITABLE(bit_entry)));
    bit = atoi(bit_text);//atoi(bit_text);
    if(option == 1)
    {
      option = 8;
    }
    else if (option == 2)
    {
      option = 16;
    }
    else if(option == 3)
    {
      option = 32;
    }
    else if(option == 4)
    {
      option = 64;
    }

    nums *getMask = malloc(option * sizeof(nums));
    if (getMask == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(EXIT_FAILURE);
    }

    GetMask(option, bit, getMask);
    char *set = malloc(option * 2 + 1);
    char *clear = malloc(option * 2 + 1);
    char *toggle = malloc(option * 2 + 1);
    char *show = malloc(option * 2 + 1);

    if (set == NULL || clear == NULL || toggle == NULL || show == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    set[0] = '\0';
    clear[0] = '\0';
    toggle[0] = '\0';
    show[0] = '\0';

    for (int i = option - 1; i >= 0; i--) {
        strcat(set, getMask[i].set);
        strcat(clear, getMask[i].clear);
        strcat(toggle, getMask[i].toggle);
        strcat(show, getMask[i].show);
    }
    gtk_editable_set_text(GTK_EDITABLE(set_mask_entry), set);
    gtk_editable_set_text(GTK_EDITABLE(clear_mask_entry), clear);
    gtk_editable_set_text(GTK_EDITABLE(toggle_mask_entry), toggle);
    gtk_editable_set_text(GTK_EDITABLE(read_mask_entry), show);

    gtk_editable_set_text(GTK_EDITABLE(set_bin_entry), set);
    gtk_editable_set_text(GTK_EDITABLE(clear_bin_entry), clear);
    gtk_editable_set_text(GTK_EDITABLE(toggle_bin_entry), toggle);
    gtk_editable_set_text(GTK_EDITABLE(read_bin_entry), show);

    uint64_t binSet = strtoull(set, NULL, 2);
    char hexSet[option];
    sprintf(hexSet, "%lX\n", binSet);
    
    uint64_t binClear = strtoull(clear, NULL, 2);
    char hexClear[option];
    sprintf(hexClear, "%lX\n", binClear);
    
    uint64_t binToggle = strtoull(toggle, NULL, 2);
    char hexToggle[option];
    sprintf(hexToggle, "%lX\n", binToggle);

    uint64_t binShow = strtoull(show, NULL, 2);
    char hexShow[option];
    sprintf(hexShow, "%lX\n", binShow);
    
    gtk_editable_set_text(GTK_EDITABLE(set_num_entry), hexSet);
    gtk_editable_set_text(GTK_EDITABLE(clear_num_entry), hexClear);
    gtk_editable_set_text(GTK_EDITABLE(toggle_num_entry), hexToggle);
    gtk_editable_set_text(GTK_EDITABLE(read_num_entry), hexRead);

    free(set);
    free(getMask);
}


static void kalkulaator_window_class_init (KalkulaatorWindowClass *klass)
{
 // gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS(klass), "/org/example/App/kalkulaator-window.ui");
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(klass), "/org/github/kalkulaator/kalkulaator-window.ui");


  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS(klass), KalkulaatorWindow, header_bar);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS(klass), KalkulaatorWindow, display);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS(klass), KalkulaatorWindow, display2);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS(klass), KalkulaatorWindow, display3);
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

  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__sin_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__arcsin_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__cos_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__arccos_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__tan_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__arctan_clicked);

  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__xVal_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__yVal_clicked);

  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__buttonfact_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__xtrabutton3_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__xtrabutton4_clicked);
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__bitmask_clicked);
  //gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window__toggle_button_toggled);
/*
  gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), kalkulaator_window_xtrabutton5_clicked);
   */

}

static void
kalkulaator_window_init (KalkulaatorWindow *self)
{

  gtk_widget_init_template (GTK_WIDGET (self));

  g_print("initializing display widget: %p\n", (void*) self->display);
  //self->display = g_strdup("");
  gtk_editable_set_text(GTK_EDITABLE(self->display), "0");


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
  g_signal_connect(self->buttonsin, "clicked", G_CALLBACK(kalkulaator_window__sin_clicked), self);
  g_signal_connect(self->buttonarcsin, "clicked", G_CALLBACK(kalkulaator_window__arcsin_clicked), self);
  g_signal_connect(self->buttoncos, "clicked", G_CALLBACK(kalkulaator_window__cos_clicked), self);
  g_signal_connect(self->buttonarccos, "clicked", G_CALLBACK(kalkulaator_window__arccos_clicked), self);
  g_signal_connect(self->buttontan, "clicked", G_CALLBACK(kalkulaator_window__tan_clicked), self);
  g_signal_connect(self->buttonarctan, "clicked", G_CALLBACK(kalkulaator_window__arctan_clicked), self);

  g_signal_connect(self->xVal, "clicked", G_CALLBACK(kalkulaator_window__xVal_clicked), self);
  g_signal_connect(self->yVal, "clicked", G_CALLBACK(kalkulaator_window__yVal_clicked), self);

  g_signal_connect(self->buttonfact, "clicked", G_CALLBACK(kalkulaator_window__buttonfact_clicked), self);
  g_signal_connect(self->xtrabutton3, "clicked", G_CALLBACK(kalkulaator_window__xtrabutton3_clicked), self);
  g_signal_connect(self->xtrabutton4, "clicked", G_CALLBACK(kalkulaator_window__xtrabutton4_clicked), self);
  g_signal_connect(self->bitmask, "clicked", G_CALLBACK(kalkulaator_window__bitmask_clicked), self);

  gtk_editable_set_text (GTK_EDITABLE(self->display2), "0");
  gtk_editable_set_text (GTK_EDITABLE(self->display3), "0");

  //g_signal_connect(self->xVal, "toggled", G_CALLBACK(kalkulaator_window__toggle_button_toggled), self);
  //g_signal_connect(self->yVal, "toggled", G_CALLBACK(kalkulaator_window__toggle_button_toggled), self);
  // g_signal_connect(self->togglebutton, "toggled", G_CALLBACK(kalkulaator_window__toggle_button_toggled), self);
  /*
  g_signal_connect(self->xtrabutton5, "clicked", G_CALLBACK(kalkulaator_window_xtrabutton5_clicked), self);
   */
  //gtk_editable_set_position(GTK_EDITABLE(self->display), +0);
  /*
  gtk_widget_set_visible(GTK_WIDGET(self->xtrabutton1), FALSE);
  gtk_widget_set_visible(GTK_WIDGET(self->xtrabutton2), FALSE);
  gtk_widget_set_visible(GTK_WIDGET(self->xtrabutton3), FALSE);
  gtk_widget_set_visible(GTK_WIDGET(self->xtrabutton4), FALSE);
  gtk_widget_set_visible(GTK_WIDGET(self->xtrabutton5), FALSE);
   */
  // history__delete();
}
