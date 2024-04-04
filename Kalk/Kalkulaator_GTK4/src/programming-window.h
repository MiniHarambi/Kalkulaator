#pragma once

#include "kalkulaator-config.h"
#include <gtk/gtk.h>
#include <gdk/gdk.h>

G_BEGIN_DECLS

#define PROGRAMMING_WINDOW_TYPE (kalkulaator_window_get_type())

G_DECLARE_FINAL_TYPE (ProgrammingWindow, programming_window, PROGRAMMING, WINDOW, GtkApplicationWindow)

ProgrammingWindow *programming_window_new (GtkApplication *app);

G_END_DECLS /* PROGRAMMING_WINDOW_H */

