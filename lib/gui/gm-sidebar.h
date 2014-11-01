/*
 * Copyright (c) 2014 Intel Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Author:
 *      Ikey Doherty <michael.i.doherty@intel.com>
 */

#ifndef __GTK_SIDEBAR_H__
#define __GTK_SIDEBAR_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GTK_TYPE_SIDEBAR                 (gtk_sidebar_get_type ())
#define GTK_SIDEBAR(obj)                 (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SIDEBAR, GtkSidebar))
#define GTK_IS_SIDEBAR(obj)              (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SIDEBAR))
#define GTK_SIDEBAR_CLASS(klass)         (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SIDEBAR, GtkSidebarClass))
#define GTK_IS_SIDEBAR_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SIDEBAR))
#define GTK_SIDEBAR_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SIDEBAR, GtkSidebarClass))

typedef struct _GtkSidebar        GtkSidebar;
typedef struct _GtkSidebarPrivate GtkSidebarPrivate;
typedef struct _GtkSidebarClass   GtkSidebarClass;

struct _GtkSidebar
{
  GtkBin parent;
};

struct _GtkSidebarClass
{
  GtkBinClass parent_class;

  /* Padding for future expansion */
  void (*_gtk_reserved1) (void);
  void (*_gtk_reserved2) (void);
  void (*_gtk_reserved3) (void);
  void (*_gtk_reserved4) (void);
};

GType       gtk_sidebar_get_type  (void) G_GNUC_CONST;
GtkWidget * gtk_sidebar_new       (void);
void        gtk_sidebar_set_stack (GtkSidebar *sidebar,
                                   GtkStack   *stack);
GtkStack *  gtk_sidebar_get_stack (GtkSidebar *sidebar);

G_END_DECLS

#endif /* __GTK_SIDEBAR_H__ */
