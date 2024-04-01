#include "programming-window.h"


struct _ProgrammingWindow
{
  GtkApplicationWindow parent_instance;

  GtkHeaderBar        *header_bar;
  GtkLabel            *label;
  GtkWindow           *gtk_window;
  GtkBox              *main_box;
  GtkEntry            *display;
  GtkEntry            *display2;


};

G_DEFINE_TYPE (ProgrammingWindow, programming_window, GTK_TYPE_APPLICATION_WINDOW)
/*
ProgrammingWindow *
programming_window_new (GtkApplication *app)
{
  return g_object_new (PROGRAMMING_WINDOW_TYPE,
                       "application", app,
                       NULL);
}
 */

static void
programming_window_class_init (ProgrammingWindowClass *klass)
{
  gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(klass), "/org/github/kalkulaator/programming-window.ui");

  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS(klass), ProgrammingWindow, header_bar);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS(klass), ProgrammingWindow, display);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS(klass), ProgrammingWindow, display2);

}

static void
programming_window_init (ProgrammingWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

}

