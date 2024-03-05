#include "testing-config.h"
#include "testing-window.h"


struct _TestingWindow
{
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  GtkGrid             *main_grid;
  GtkEntry            *input_entry;
  GtkLabel            *label;
  GtkWindow           *window;

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

  gchar               *expression;

};

G_DEFINE_TYPE (TestingWindow, testing_window, GTK_TYPE_APPLICATION_WINDOW)

// Signal handlers
static void on_nrbutton_clicked(GtkButton *button, gpointer user_data)
{
    TestingWindow *window = TESTING_WINDOW(user_data);
    const gchar *text = gtk_button_get_label(button);

    gchar *updated_expression = g_strdup_printf("%s%s", window->expression, text);
    g_free(window->expression);
    window->expression = updated_expression;

    gtk_entry_set_text(GTK_ENTRY(window->input_entry), window->expression);
}

static void on_buttonclear_clicked(gpointer user_data)
{
    TestingWindow *window = TESTING_WINDOW(user_data);

    // Clear the expression
    g_free(window->expression);
    window->expression = g_strdup("");

    // Update the display
    gtk_entry_set_text(GTK_ENTRY(window->input_entry), "");
}

static void on_buttondelete_clicked(gpointer user_data)
{
    TestingWindow *window = TESTING_WINDOW(user_data);

    // Delete the last character from the expression
    size_t len = strlen(window->expression);
    if (len > 0)
    {
        window->expression[len - 1] = '\0';

        // Update the display
        gtk_entry_set_text(GTK_ENTRY(window->input_entry), window->expression);
    }
}

static void on_buttondot_clicked(gpointer user_data)
{
    TestingWindow *window = TESTING_WINDOW(user_data);

    // Append a dot to the expression
    gchar *dot = ".";
    gchar *updated_expression = g_strconcat(window->expression, dot, NULL);
    g_free(window->expression);
    window->expression = updated_expression;

    // Update the display
    gtk_entry_set_text(GTK_ENTRY(window->input_entry), window->expression);
}

static void on_buttonadd_clicked(gpointer user_data)
{
    TestingWindow *window = TESTING_WINDOW(user_data);

    // Append a plus sign to the expression
    gchar *add = "+";
    gchar *updated_expression = g_strconcat(window->expression, add, NULL);
    g_free(window->expression);
    window->expression = updated_expression;

    // Update the display
    gtk_entry_set_text(GTK_ENTRY(window->input_entry), window->expression);
}

static void on_buttonsubtract_clicked(gpointer user_data)
{
    TestingWindow *window = TESTING_WINDOW(user_data);

    // Append a minus sign to the expression
    gchar *subtract = "-";
    gchar *updated_expression = g_strconcat(window->expression, subtract, NULL);
    g_free(window->expression);
    window->expression = updated_expression;

    // Update the display
    gtk_entry_set_text(GTK_ENTRY(window->input_entry), window->expression);
}

static void on_buttonmultiply_clicked(gpointer user_data)
{
    TestingWindow *window = TESTING_WINDOW(user_data);

    // Append a multiplication sign to the expression
    gchar *multiply = "*";
    gchar *updated_expression = g_strconcat(window->expression, multiply, NULL);
    g_free(window->expression);
    window->expression = updated_expression;

    // Update the display
    gtk_entry_set_text(GTK_ENTRY(window->input_entry), window->expression);
}

static void on_buttondivide_clicked(gpointer user_data)
{
    TestingWindow *window = TESTING_WINDOW(user_data);

    // Append a division sign to the expression
    gchar *divide = "/";
    gchar *updated_expression = g_strconcat(window->expression, divide, NULL);
    g_free(window->expression);
    window->expression = updated_expression;

    // Update the display
    gtk_entry_set_text(GTK_ENTRY(window->input_entry), window->expression);
}

static void on_buttonsqrt_clicked(gpointer user_data)
{
    TestingWindow *window = TESTING_WINDOW(user_data);

    // Append the sqrt function to the expression
    gchar *sqrt = "sqrt(";
    gchar *updated_expression = g_strconcat(window->expression, sqrt, NULL);
    g_free(window->expression);
    window->expression = updated_expression;

    // Update the display
    gtk_entry_set_text(GTK_ENTRY(window->input_entry), window->expression);
}

static void on_buttonsquare_clicked(gpointer user_data)
{
    TestingWindow *window = TESTING_WINDOW(user_data);

    // Append the square function to the expression
    gchar *square = "^2";
    gchar *updated_expression = g_strconcat(window->expression, square, NULL);
    g_free(window->expression);
    window->expression = updated_expression;

    // Update the display
    gtk_entry_set_text(GTK_ENTRY(window->input_entry), window->expression);
}

static void on_buttonhistory_clicked(GtkButton *button, gpointer user_data)
{
    // Functionality for the history button
    g_print("History button clicked.\n");
}

static void on_buttonans_clicked(GtkButton *button, gpointer user_data)
{
    // Functionality for the ans button
    g_print("Ans button clicked.\n");
}

static void on_buttonsulg1_clicked(gpointer user_data)
{
    TestingWindow *window = TESTING_WINDOW(user_data);

    // Append an opening parenthesis to the expression
    gchar *parenthesis_open = "(";
    gchar *updated_expression = g_strconcat(window->expression, parenthesis_open, NULL);
    g_free(window->expression);
    window->expression = updated_expression;

    // Update the display
    gtk_entry_set_text(GTK_ENTRY(window->input_entry), window->expression);
}

static void on_buttonsulg2_clicked(gpointer user_data)
{
    TestingWindow *window = TESTING_WINDOW(user_data);

    // Append an opening parenthesis to the expression
    gchar *parenthesis_open = ")";
    gchar *updated_expression = g_strconcat(window->expression, parenthesis_open, NULL);
    g_free(window->expression);
    window->expression = updated_expression;

    // Update the display
    gtk_entry_set_text(GTK_ENTRY(window->input_entry), window->expression);
}

static void on_buttonequal_clicked(gpointer user_data)
{
    TestingWindow *window = TESTING_WINDOW(user_data);

    g_print("Expression: %s\n", window->expression);

    gtk_entry_set_text(GTK_ENTRY(window->input_entry), "");
    g_free(window->expression);
    window->expression = NULL;
}

static void testing_window_class_init(TestingWindowClass *klass)
{
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);

    gtk_widget_class_set_template_from_resource(widget_class, "/org/gnome/testingcalc/testing-window.ui");
    gtk_widget_class_bind_template_child(widget_class, TestingWindow, header_bar);
    gtk_widget_class_bind_template_child(widget_class, TestingWindow, label);
    gtk_widget_class_bind_template_child(widget_class, TestingWindow, window);

    // Signal connections
    gtk_widget_class_bind_template_callback(widget_class, on_nrbutton_clicked);
    gtk_widget_class_bind_template_callback(widget_class, on_buttonequal_clicked);
    gtk_widget_class_bind_template_callback(widget_class, on_buttondot_clicked);
    gtk_widget_class_bind_template_callback(widget_class, on_buttonans_clicked);
    gtk_widget_class_bind_template_callback(widget_class, on_buttonclear_clicked);
    gtk_widget_class_bind_template_callback(widget_class, on_buttondelete_clicked);
    gtk_widget_class_bind_template_callback(widget_class, on_buttonmultiply_clicked);
    gtk_widget_class_bind_template_callback(widget_class, on_buttondivide_clicked);
    gtk_widget_class_bind_template_callback(widget_class, on_buttonadd_clicked);
    gtk_widget_class_bind_template_callback(widget_class, on_buttonsubtract_clicked);
    gtk_widget_class_bind_template_callback(widget_class, on_buttonsqrt_clicked);
    gtk_widget_class_bind_template_callback(widget_class, on_buttonsquare_clicked);
    gtk_widget_class_bind_template_callback(widget_class, on_buttonhistory_clicked);
}

static void testing_window_init(TestingWindow *self)
{
    gtk_widget_init_template(GTK_WIDGET(self));
}
