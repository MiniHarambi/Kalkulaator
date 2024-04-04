/* kalkulaator-application.c
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

#include <gtk/gtk.h>

#include "kalkulaator-application.h"
#include "kalkulaator-window.h"


struct _KalkulaatorApplication
{
  GtkApplication parent_instance;
};

G_DEFINE_TYPE (KalkulaatorApplication, kalkulaator_application, GTK_TYPE_APPLICATION)

KalkulaatorApplication *
kalkulaator_application_new (gchar *application_id,
                             GApplicationFlags  flags)
{
  return g_object_new (KALKULAATOR_TYPE_APPLICATION,
                       "application-id", application_id,
                       "flags", flags,
                       NULL);
}

static void
kalkulaator_application_finalize (GObject *object)
{
  KalkulaatorApplication *self = (KalkulaatorApplication *)object;

  G_OBJECT_CLASS (kalkulaator_application_parent_class)->finalize (object);
}

static void
kalkulaator_application_activate (GApplication *app)
{
  GtkWindow *window;

  /* It's good practice to check your parameters at the beginning of the
   * function. It helps catch errors early and in development instead of
   * by your users.
   */
  g_assert (GTK_IS_APPLICATION (app));

  /* Get the current window or create one if necessary. */
  window = gtk_application_get_active_window (GTK_APPLICATION (app));
  if (window == NULL)
    window = g_object_new (KALKULAATOR_TYPE_WINDOW,
                           "application", app,
                           NULL);

  /* Ask the window manager/compositor to present the window. */
  gtk_window_present (window);
}


static void
kalkulaator_application_class_init (KalkulaatorApplicationClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

  object_class->finalize = kalkulaator_application_finalize;

  /*
   * We connect to the activate callback to create a window when the application
   * has been launched. Additionally, this callback notifies us when the user
   * tries to launch a "second instance" of the application. When they try
   * to do that, we'll just present any existing window.
   */
  app_class->activate = kalkulaator_application_activate;
}

static void
kalkulaator_application_show_about (GSimpleAction *action,
                                    GVariant      *parameter,
                                    gpointer       user_data)
{
  KalkulaatorApplication *self = KALKULAATOR_APPLICATION (user_data);
  GtkWindow *window = NULL;
  const gchar *authors[] = {"Markus Parm and Tristan Tsopp", NULL};

  g_return_if_fail (KALKULAATOR_IS_APPLICATION (self));

  window = gtk_application_get_active_window (GTK_APPLICATION (self));

  gtk_show_about_dialog (window,
                         "program-name", "kalkulaator",
                         "authors", authors,
                         "version", "0.1.0",
                         NULL);
}

static void
kalkulaator_application_programming (GSimpleAction *action,
                                     GVariant      *parameter,
                                     gpointer       user_data)
{

  KalkulaatorApplication *self = KALKULAATOR_APPLICATION(user_data);
  GtkBuilder *builder;
  GtkWidget *window;
   char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return;
    }
  g_return_if_fail (KALKULAATOR_IS_APPLICATION (self));

  // Load the new XML file
  builder = gtk_builder_new_from_resource("/org/github/kalkulaator/programming-window.ui");
  // Get the main window from the XML file
  window = GTK_WIDGET(gtk_builder_get_object (builder, "main_window"));

  // Set the application reference
  g_object_set_data_full(G_OBJECT(window), "application", g_object_ref(self), g_object_unref);

  // Present the window
  gtk_window_present (GTK_WINDOW(window));

  // Free the builder, the window is now responsible for its widgets
  g_object_unref (builder);


}

static void
kalkulaator_application_scientific (GSimpleAction *action,
                                    GVariant      *parameter,
                                    gpointer       user_data)
{
  KalkulaatorApplication *self = KALKULAATOR_APPLICATION(user_data);
  GtkWindow *window = NULL;

  g_return_if_fail (KALKULAATOR_IS_APPLICATION (self));

  window = g_object_new (KALKULAATOR_TYPE_WINDOW,
                         "application", self,
                         "title", "Scientific Window",
                         "default-width", 610,
                         "default-height", 460,
                         NULL);

  gtk_window_present (window);
}


static void
kalkulaator_application_converter (GSimpleAction *action,
                                   GVariant      *parameter,
                                   gpointer       user_data)
{
  KalkulaatorApplication *self = KALKULAATOR_APPLICATION(user_data);
  GtkWindow *window = NULL;

  g_return_if_fail (KALKULAATOR_IS_APPLICATION (self));

  window = gtk_application_get_active_window (GTK_APPLICATION(self));

  gtk_window_set_title(window, "Converter Window");
  gtk_window_set_default_size(window, 610, 460);
}



static void
kalkulaator_application_init (KalkulaatorApplication *self)
{
  g_autoptr (GSimpleAction) quit_action = g_simple_action_new ("quit", NULL);
  g_signal_connect_swapped (quit_action, "activate", G_CALLBACK (g_application_quit), self);
  g_action_map_add_action (G_ACTION_MAP (self), G_ACTION (quit_action));

  g_autoptr (GSimpleAction) about_action = g_simple_action_new ("about", NULL);
  g_signal_connect (about_action, "activate", G_CALLBACK (kalkulaator_application_show_about), self);
  g_action_map_add_action (G_ACTION_MAP (self), G_ACTION (about_action));


  g_autoptr (GSimpleAction) programming_action = g_simple_action_new ("programming", NULL);
  g_signal_connect (programming_action, "activate", G_CALLBACK (kalkulaator_application_programming), self);
  g_action_map_add_action (G_ACTION_MAP (self), G_ACTION (programming_action));

  g_autoptr (GSimpleAction) scientific_action = g_simple_action_new ("scientific", NULL);
  g_signal_connect (scientific_action, "activate", G_CALLBACK (kalkulaator_application_scientific), self);
  g_action_map_add_action (G_ACTION_MAP (self), G_ACTION (scientific_action));

  g_autoptr (GSimpleAction) converter_action = g_simple_action_new ("converter", NULL);
  g_signal_connect (converter_action, "activate", G_CALLBACK (kalkulaator_application_converter), self);
  g_action_map_add_action (G_ACTION_MAP (self), G_ACTION (converter_action));



  gtk_application_set_accels_for_action (GTK_APPLICATION (self),
                                         "app.quit",
                                         (const char *[]) {
                                           "<primary>q",
                                           NULL,
                                         });

}
