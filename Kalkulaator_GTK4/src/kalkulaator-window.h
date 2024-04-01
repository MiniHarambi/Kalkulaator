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

G_BEGIN_DECLS

#define KALKULAATOR_TYPE_WINDOW (kalkulaator_window_get_type())

struct _KalkulaatorWindow
{
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  GtkLabel            *label;
  GtkWindow           *gtk_window;
  GtkBox              *main_box;
  GtkEntry            *display;
  GtkEntry            *display2;

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
  GtkButton           *buttonsin;
  GtkButton           *buttoncos;
  GtkButton           *buttontan;
  GtkButton           *buttonarcsin;
  GtkButton           *buttonarccos;
  GtkButton           *buttonarctan;
  GtkButton           *xtrabutton1;
  GtkButton           *xtrabutton2;
  GtkButton           *xtrabutton3;
  GtkButton           *xtrabutton4;
  GtkButton           *buttonfact;
  /*
  GtkToggleButton     *togglebutton;

  GtkButton           *xtrabutton5;
   */
  //
  gchar               *expression;
  gchar               *last_result;
  };

G_DECLARE_FINAL_TYPE (KalkulaatorWindow, kalkulaator_window, KALKULAATOR, WINDOW, GtkApplicationWindow)

G_END_DECLS
